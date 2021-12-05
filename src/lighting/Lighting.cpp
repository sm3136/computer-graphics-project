#include <lighting/Lighting.hpp>

// * START OF Lighting SECTION! * //

/**
 * @brief Returns the color in a GLfloat pointer.
 *
 * @return GLfloat* The data for the color.
 */
GLfloat *Lighting::getColor()
{
    GLfloat *return_color = (GLfloat *)calloc(3, sizeof(GLfloat));
    return_color[0] = this->color->X * this->intensity;
    return_color[1] = this->color->Y * this->intensity;
    return_color[2] = this->color->Z * this->intensity;
    return return_color;
}

/**
 * @brief Gets the color as a human readable Vector3.
 *
 * @return Vector3* The color vector that was being use in the object. To change the values of the
 * color you must use setColor(). Editing this variable alone will not alter the color.
 */
Vector3 *Lighting::getColorVector()
{
    return new Vector3(*this->color * 255);
}

/**
 * @brief Sets the color of the lighting object.
 *
 * @param new_color the color which we want to set
 * the light to.
 */
void Lighting::setColor(Vector3 *new_color)
{
    this->color = new Vector3(*new_color / 255.0);
}

float Lighting::getIntensity()
{
    return this->intensity;
}

void Lighting::setIntensity(float intensity)
{
    this->intensity = intensity;
}

// * START OF Directional Lighting SECTION! * //

/**
 * @brief Gets the direction unit vector as an array of floats.
 *
 * @return GLfloat* An array containing the direction in a GLfloat form.
 */
GLfloat *DirectionalLighting::getDirection()
{
    GLfloat *return_dir = (GLfloat *)calloc(3, sizeof(GLfloat));
    Vector3 unit_direction = this->direction->Unit();

    return_dir[0] = unit_direction.X;
    return_dir[1] = unit_direction.Y;
    return_dir[2] = unit_direction.Z;

    return return_dir;
}

// Get Direction Vector
Vector3 *DirectionalLighting::getDirectionVector()
{
    return new Vector3(*this->direction);
}

// Set Direction
void DirectionalLighting::setDirection(Vector3 *direction)
{
    this->direction = new Vector3(*direction);
}

// * START OF Positional Lighting SECTION! * //

/**
 * @brief Returns the position in a GLfloat pointer.
 *
 * @return GLfloat* The data for the position.
 */
GLfloat *PositionalLight::getPosition()
{
    GLfloat *return_pos = (GLfloat *)calloc(3, sizeof(GLfloat));
    return_pos[0] = this->position->X;
    return_pos[1] = this->position->Y;
    return_pos[2] = this->position->Z;
    return return_pos;
}

/**
 * @brief Gets the position as a human readable Vector3.
 *
 * @return Vector3* The position vector that was being use in the object. To change the values of the
 * position you must use setPosition(). Editing this variable alone will not alter the position.
 */
Vector3 *PositionalLight::getPositionVector()
{
    return new Vector3(*this->position);
}

/**
 * @brief Sets the position of the lighting object.
 *
 * @param new_position the position which we want to set
 * the light to.
 */
void PositionalLight::setPosition(Vector3 *new_position)
{
    this->position = new Vector3(*new_position);
}

// * START OF AmbientLighting SECTION! * //

// Initializes the instance as a nullptr.
AmbientLight *AmbientLight::instance = nullptr;

/**
 * @brief Gets the instance of the ambient light.
 *
 * @return AmbientLight* The ambient light object.
 */
AmbientLight *AmbientLight::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new AmbientLight();
    }

    return instance;
}

// * START OF WorldLight SECTION! * //

WorldLight *WorldLight::instance = nullptr;

/**
 * @brief Gets the instance of the world light
 *
 * @return WorldLight* The world light instance.
 */
WorldLight *WorldLight::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new WorldLight();
    }

    return instance;
}