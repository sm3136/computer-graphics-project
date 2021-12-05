#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <cstring>
#include <math.h>

#include <common/config.hpp>

#include <classes/Matrix.hpp>
#include <classes/Vector.hpp>

#include <lighting/Lighting.hpp>
#include <lighting/LightController.hpp>

class Shape
{
protected:
    Matrix *scale;
    Matrix *position;
    Matrix *orientation;
    Vector3 *color;

    int shape_start = 0;
    int shape_size = 0;

    // The id of the program.
    static int programID;

    // ! Deprecated! No longer used
    int updated = true;

public:
    int visible = true;

    Shape();

    Vector3 *getScale();
    Vector3 *getPosition();
    Matrix *getOrientation();

    void setScale(Vector3 *scale);
    void setColor(Vector3 *color);
    void setPosition(Vector3 *position);
    void setOrientation(const Matrix &orientation);

    static GLfloat *subdivide(GLfloat *ptr);
    static void subdivide_all(GLfloat *old_verts, int numTriangles);

    void DrawShape(GLfloat *buffer);
};

/**
 * Creates a cube object in the workspace.
 */
class Cube : public Shape
{
public:
    // Initializes the shape start and size here.
    Cube() : Shape()
    {
        this->shape_start = 0;
        this->shape_size = VERTEX_PER_CUBE;
    }

    static int getShapeData(GLfloat *buffer_pointer);
};

/**
 * Creates a Octahedron object in the workspace.
 */
class Octahedron : public Shape
{
public:
    // Initializes the shape start and size here.
    Octahedron() : Shape()
    {
        this->shape_start = VERTEX_PER_CUBE;
        this->shape_size = VERTEX_PER_OCTAHEDRON;
    }
    static int getShapeData(GLfloat *buffer_pointer);
};

/**
 * Creates a Sphere object in the workspace.
 */
class Sphere : public Shape
{
public:
    // Initializes the shape start and size here.
    Sphere() : Shape()
    {
        this->shape_start = VERTEX_PER_CUBE + VERTEX_PER_OCTAHEDRON;
        this->shape_size = VERTEX_PER_SPHERE;
    }
    static int getShapeData(GLfloat *buffer_pointer, int subdivisions);
};

/**
 * Creates a Cylinder object in the workspace.
 */
class Cylinder : public Shape
{
public:
    // Initializes the shape start and size here.
    Cylinder() : Shape()
    {
        this->shape_start = VERTEX_PER_CUBE + VERTEX_PER_OCTAHEDRON + VERTEX_PER_SPHERE;
        this->shape_size = VERTEX_PER_CYLINDER;
    }
    static int getShapeData(GLfloat *buffer_pointer, int subdivisions);
};

#endif