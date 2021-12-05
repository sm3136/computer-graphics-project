#ifndef SHAPE_GENERATOR_HPP
#define SHAPE_GENERATOR_HPP

#include <iostream>
#include <string>
#include <list>
#include <iterator>

#include <GL/glew.h> // Core OpenGL
#include <GL/glut.h> // Display Window

#include <common/config.hpp>
#include <common/shader.hpp>
#include <common/file.hpp>

#include <shapes/Shape.hpp>

// Used for determining relative offset in a buffer.
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class ShapeGenerator
{
private:
    static ShapeGenerator *instance;
    ShapeGenerator();

    std::list<Shape *> shapes;

    GLuint buffer;
    GLuint vPosition = 0;
    GLuint vColor = 1;
    GLuint vNormal = 2;

    GLfloat *shapeBuffer;

    // Sets up the opengl instance around the shape generator
    void initialize();

public:
    // Stores the id of the program
    int programID;

    static ShapeGenerator *GetInstance();

    void display();
    void addShapeToDisplay(Shape *shape_ptr);

    void computeNormals(int numVerts);
};

#endif