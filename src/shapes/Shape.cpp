#include <shapes/Shape.hpp>

#include <shapes/ShapeGenerator.hpp>

int Shape::programID = 0;

/**
 * Every shape initializes the same, just hold different positions.
 */
Shape::Shape()
{
    ShapeGenerator *jenny = ShapeGenerator::GetInstance();

    // Gets the programID
    this->programID = jenny->programID;

    this->scale = new Matrix(Matrix::identity());
    this->position = new Matrix(Matrix::identity());
    this->orientation = new Matrix(Matrix::identity());

    // Defaults the part to be white
    this->color = new Vector3(1, 1, 1);

    jenny->addShapeToDisplay(this);
}

/**
 * Gets the scale of the current shape in vector form
 */
Vector3 *Shape::getScale()
{
    return new Vector3(*this->scale[0][0], *this->scale[1][1], *this->scale[2][2]);
}
/**
 * Gets the position of the current shape in vector form
 */
Vector3 *Shape::getPosition()
{
    return new Vector3(*this->position[0][3], *this->position[1][3], *this->position[2][3]);
}
/**
 * Gets the orientation of the current shape in vector form
 */
Matrix *Shape::getOrientation()
{
    return this->orientation;
}
/**
 * Sets the scale of the object. This is in vector form, but converted to a matrix in the backend
 */
void Shape::setScale(Vector3 *scale)
{
    this->updated = true;
    this->scale = new Matrix(Matrix::scale(scale->X, scale->Y, scale->Z));
}
/**
 * Sets the position of the shape. All positions are just transfomations from the origin of the world.
 */
void Shape::setPosition(Vector3 *position)
{
    this->updated = true;
    this->position = new Matrix(Matrix::transform(position->X, position->Y, position->Z));
}
/**
 * Sets the orientation matrix of the shape.
 */
void Shape::setOrientation(const Matrix &orientation)
{
    this->updated = true;
    this->orientation = new Matrix(orientation);
}

void Shape::setColor(Vector3 *color)
{
    this->updated = true;
    this->color = new Vector3(color->X / 255, color->Y / 255, color->Z / 255);
}

/**
 * Draws the shape dependent on the information that you give it
 */
void Shape::DrawShape(GLfloat *buffer)
{
    if (!this->visible)
    {
        return;
    }

    // Translation
    Matrix perspectiveMatrix = Matrix::perspective(75, 0.1f, 20.0f);

    Matrix scale_orient = (*this->orientation * *this->scale);
    Matrix transMatrix = *new Matrix(*this->position * scale_orient);
    
    GLint projMatLoc = glGetUniformLocation(this->programID, "projectionMatrix");
    GLint transMatrixLoc = glGetUniformLocation(this->programID, "modelTransMatrix");

    glUniformMatrix4fv(projMatLoc, 1, GL_TRUE, perspectiveMatrix.getMatrix());
    glUniformMatrix4fv(transMatrixLoc, 1, GL_TRUE, transMatrix.getMatrix());
    
    // Color Information
    GLfloat color[3] = { this->color->X, this->color->Y, this->color->Z };

    GLfloat *ambient = AmbientLight::GetInstance()->getColor();

    GLfloat *world_color = WorldLight::GetInstance()->getColor();
    GLfloat *world_direction = WorldLight::GetInstance()->getDirection();

    // Gets the data for non-world lights
    LightController *light_controller = LightController::GetInstance();

    GLfloat *light_colors = light_controller->getLightColors();
    GLfloat *light_positions = light_controller->getLightPositions();
    GLfloat *light_directions = light_controller->getLightDirections();

    // Just default camera position
    GLfloat cameraPosition[3] = { 0, 0, 0 };

    // Handles moving color values into the shader
    GLint object_color = glGetUniformLocation(this->programID, "vColor");
    GLint ambient_color = glGetUniformLocation(this->programID, "ambient");

    GLint world_light_color = glGetUniformLocation(this->programID, "worldLightColor");
    GLint world_light_direction = glGetUniformLocation(this->programID, "worldLightDirection");
    
    GLint point_light_count = glGetUniformLocation(this->programID, "pointLightCount");
    GLint spot_light_count = glGetUniformLocation(this->programID, "spotLightCount");

    GLint light_color = glGetUniformLocation(this->programID, "lightColors");
    GLint light_location = glGetUniformLocation(this->programID, "lightPositions");
    GLint light_direction = glGetUniformLocation(this->programID, "coneDirections");

    GLint camera_location = glGetUniformLocation(this->programID, "viewPos");

    glUniform3fv(object_color, 1, color);
    glUniform3fv(ambient_color, 1, ambient);

    glUniform3fv(world_light_color, 1, world_color);
    glUniform3fv(world_light_direction, 1, world_direction);

    glUniform1f(point_light_count, light_controller->getPointLightCount());
    glUniform1f(spot_light_count, light_controller->getSpotLightCount());

    glUniform3fv(light_color, light_controller->getLightCount(), light_colors);
    glUniform3fv(light_location, light_controller->getLightCount(), light_positions);
    glUniform3fv(light_direction, light_controller->getSpotLightCount(), light_directions);

    glUniform3fv(camera_location, 1, cameraPosition);

    // Draw Shape with this. (Flushing occurs after all shapes have been drawn)
    glDrawArrays(GL_TRIANGLES, this->shape_start, this->shape_size);

    // Clear up the pointers
    delete ambient;

    delete world_color;
    delete world_direction;

    delete light_colors; 
    delete light_positions;
    delete light_directions;

    this->updated = false;
}

/**
 * @brief Takes a single triangle and turns it into 4 different triangles.
 * 
 * @param ptr a pointer to the start of the first vertex in the triangle
 * @return GLfloat* a pointer to the 4 new triangles that have been made.
 */
GLfloat *Shape::subdivide(GLfloat *ptr)
{
    Vector3 *A = new Vector3(ptr[0], ptr[1], ptr[2]);
    Vector3 *B = new Vector3(ptr[1 * FLOATS_PER_VERTEX], ptr[1 * FLOATS_PER_VERTEX + 1], ptr[1 * FLOATS_PER_VERTEX + 2]);
    Vector3 *C = new Vector3(ptr[2 * FLOATS_PER_VERTEX], ptr[2 * FLOATS_PER_VERTEX + 1], ptr[2 * FLOATS_PER_VERTEX + 2]);

    Vector3 *AB = new Vector3((*A + *B) / 2.0);
    Vector3 *BC = new Vector3((*B + *C) / 2.0);
    Vector3 *CA = new Vector3((*C + *A) / 2.0);

    GLfloat *result = (GLfloat *)calloc(12 * FLOATS_PER_VERTEX, sizeof(GLfloat));
    Vector3 *order[12] = { A, AB, CA, AB, B, BC, CA, BC, C, BC, CA, AB };
    for (int i = 0; i < 12; i++)
    {
        int offset = i * FLOATS_PER_VERTEX;
        result[offset] = order[i]->X;
        result[offset + 1] = order[i]->Y;
        result[offset + 2] = order[i]->Z;
        result[offset + 3] = 0;
        result[offset + 4] = 0;
        result[offset + 5] = 0;
    }

    delete A;
    delete B;
    delete C;

    delete AB;
    delete BC;
    delete CA;

    return result;
}

/**
 * ? Warning the old verts table will be modified.
 * @brief Takes a list of triangles and subdivides all of them.
 * 
 * @param old_verts a pointer to a table containing the list of vertices that 
 * you want to subdivide
 * @param numTriangles the number of triangles that will be subdivided.
 */
void Shape::subdivide_all(GLfloat *old_verts, int numTriangles)
{
    GLfloat temp[numTriangles * 3 * FLOATS_PER_VERTEX];
    memcpy(temp, old_verts, sizeof(temp));

    for (int triangle = 0; triangle < numTriangles; triangle++)
    {
        GLfloat *subdivided = Shape::subdivide(temp + triangle * 3 * FLOATS_PER_VERTEX);
        memcpy(old_verts + triangle * 4 * 3 * FLOATS_PER_VERTEX, subdivided, 12 * FLOATS_PER_VERTEX * sizeof(GLfloat));
        delete subdivided;
    }
}