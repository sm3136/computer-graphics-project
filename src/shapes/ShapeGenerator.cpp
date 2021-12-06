#include <shapes/ShapeGenerator.hpp>

// Used in the singleton pattern
ShapeGenerator *ShapeGenerator::instance = nullptr;

/**
 * @brief Gets the instance of the shape generator.
 * I used the singleton pattern because it appeared to simplify
 * a bunch of the code execution.
 * 
 * @return ShapeGenerator* 
 */
ShapeGenerator *ShapeGenerator::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new ShapeGenerator();
    }
    return instance;
}

/**
 * @brief Construct a new Shape Generator:: Shape Generator object
 * 
 */
ShapeGenerator::ShapeGenerator()
{
    this->initialize();
}

/**
 * @brief Initializes the shape generator.
 * Creates all of the shapes and loads every one of them into the shapeBuffer
 * which is then shared with the gpu.
 * 
 */
void ShapeGenerator::initialize()
{
    std::cout << glGetString(GL_VERSION) << std::endl;

    this->shapeBuffer = (GLfloat *)calloc(NUM_FLOATS, sizeof(GLfloat));

    int offset = Cube::getShapeData(this->shapeBuffer);
    offset += Octahedron::getShapeData(this->shapeBuffer + offset * FLOATS_PER_VERTEX);
    offset += Sphere::getShapeData(this->shapeBuffer + offset * FLOATS_PER_VERTEX, SPHERE_SUBDIVISIONS); 
    offset += Cylinder::getShapeData(this->shapeBuffer + offset * FLOATS_PER_VERTEX, CYLINDER_FACES);

    this->computeNormals(offset);

    glGenBuffers(1, &this->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NUM_FLOATS, this->shapeBuffer, GL_STATIC_DRAW);

    // Gets the position pointer and how to move.
    glVertexAttribPointer(this->vPosition, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(this->vPosition);

    // Get the color pointer and how to move.
    // glVertexAttribPointer(this->vColor, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
    // glEnableVertexAttribArray(this->vColor);

    // Get the normal pointer and how to move.
    glVertexAttribPointer(this->vNormal, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
    glEnableVertexAttribArray(this->vNormal);

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER); // VSO
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER); // FSO
    const char *adapter[1];
    adapter[0] = readShaderCode("../shaders/vertex_shader.glsl");
    glShaderSource(vertexShaderID, 1, adapter, 0);

    adapter[0] = readShaderCode("../shaders/frag_shader.glsl");
    glShaderSource(fragShaderID, 1, adapter, 0);

    glCompileShader(vertexShaderID);
    checkForShaderError(vertexShaderID);
    glCompileShader(fragShaderID);
    checkForShaderError(fragShaderID);

    this->programID = glCreateProgram();
    glAttachShader(this->programID, vertexShaderID);
    glAttachShader(this->programID, fragShaderID);
    glLinkProgram(this->programID);
    checkForProgramError(this->programID);

    glUseProgram(this->programID);
}

/**
 * @brief When called, it will look at all of the objects that are in the list
 * of things to be displayed. Then it will clear the old picture, and draw each shape.
 * After it finishes drawing each shape it flushes it out to memory.
 * 
 */
void ShapeGenerator::display()
{
    // Clears off the current window that is generated
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (Shape *shape : this->shapes)
    {
        shape->DrawShape(this->shapeBuffer);
    }

    glFlush();
}

/**
 * @brief Simply adds a shape to the shapes table. This allows the shape to be
 * drawn and kept in memory.
 * 
 * @param shape_ptr 
 */
void ShapeGenerator::addShapeToDisplay(Shape *shape_ptr)
{
    this->shapes.push_back(shape_ptr);
}

/**
 * @brief Computes all of the normals.
 * 
 * @param numVerts The number of vertices that are inside of the shape buffer.
 */
void ShapeGenerator::computeNormals(int numVerts)
{
    for (int i = 0; i < numVerts; i += 3)
    {
        int off = i * FLOATS_PER_VERTEX;
        Vector3 normal = (new Vector3(this->shapeBuffer[off], this->shapeBuffer[off + 1], this->shapeBuffer[off + 2]))->Normal(
            *new Vector3(this->shapeBuffer[off + FLOATS_PER_VERTEX], this->shapeBuffer[off + FLOATS_PER_VERTEX + 1], this->shapeBuffer[off + FLOATS_PER_VERTEX + 2]),
            *new Vector3(this->shapeBuffer[off + FLOATS_PER_VERTEX * 2], this->shapeBuffer[off + FLOATS_PER_VERTEX * 2 + 1], this->shapeBuffer[off + FLOATS_PER_VERTEX * 2 + 2])
        );

        for (int k = 0; k < 3; ++k)
        {
            this->shapeBuffer[i * FLOATS_PER_VERTEX + k * FLOATS_PER_VERTEX + 3] = normal.X;
            this->shapeBuffer[i * FLOATS_PER_VERTEX + k * FLOATS_PER_VERTEX + 4] = normal.Y;
            this->shapeBuffer[i * FLOATS_PER_VERTEX + k * FLOATS_PER_VERTEX + 5] = normal.Z;
        }
    }
}
