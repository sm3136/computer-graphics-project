#ifndef BASEPART_HPP
#define BASEPART_HPP

#include <iostream>
#include <cstring>
#include <math.h>

#include <common/config.hpp>

#include <classes/Matrix.hpp>
#include <classes/Vector.hpp>

#include <lighting/Lighting.hpp>
#include <lighting/LightController.hpp>

class BasePart
{
protected:
    // The id of the program.
    static int programID;

    // ! Deprecated! No longer used
    int updated = true;
    
    Matrix *scale;
    Matrix *position;
    Matrix *orientation;
    Vector3 *color;

    int shape_start = 0;
    int shape_size = 0;

    Matrix &getScaleMatrix();
    Matrix &getPositionOrientation();
public:
    int visible = true;
    BasePart *parent = nullptr;

    BasePart();

    Vector3 *getScale();
    Vector3 *getPosition();
    Matrix *getOrientation();

    Matrix *getModelMatrix();

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
class Cube : public BasePart
{
public:
    // Initializes the BasePart start and size here.
    Cube() : BasePart()
    {
        this->shape_start = 0;
        this->shape_size = VERTEX_PER_CUBE;
    }

    /**
     * @brief Get the BasePart Data object
     *
     * @param buffer_pointer the buffer pointer which we should store
     * the BasePart data in.
     * @param subdivisions the number of subdivisions.
     * @return int the number of faces used.
     */
    static int getShapeData(GLfloat *buffer_pointer);
};

/**
 * Creates a Octahedron object in the workspace.
 */
class Octahedron : public BasePart
{
public:
    // Initializes the BasePart start and size here.
    Octahedron() : BasePart()
    {
        this->shape_start = VERTEX_PER_CUBE;
        this->shape_size = VERTEX_PER_OCTAHEDRON;
    }

    /**
     * @brief Get the BasePart Data object
     *
     * @param buffer_pointer the buffer pointer which we should store
     * the BasePart data in.
     * @param subdivisions the number of subdivisions.
     * @return int the number of faces used.
     */
    static int getShapeData(GLfloat *buffer_pointer);
};

/**
 * Creates a Sphere object in the workspace.
 */
class Sphere : public BasePart
{
public:
    // Initializes the BasePart start and size here.
    Sphere() : BasePart()
    {
        this->shape_start = VERTEX_PER_CUBE + VERTEX_PER_OCTAHEDRON;
        this->shape_size = VERTEX_PER_SPHERE;
    }

    /**
     * @brief Get the BasePart Data object
     *
     * @param buffer_pointer the buffer pointer which we should store
     * the BasePart data in.
     * @param subdivisions the number of subdivisions.
     * @return int the number of faces used.
     */
    static int getShapeData(GLfloat *buffer_pointer, int subdivisions);
};

/**
 * Creates a Cylinder object in the workspace.
 */
class Cylinder : public BasePart
{
public:
    // Initializes the BasePart start and size here.
    Cylinder() : BasePart()
    {
        this->shape_start = VERTEX_PER_CUBE + VERTEX_PER_OCTAHEDRON + VERTEX_PER_SPHERE;
        this->shape_size = VERTEX_PER_CYLINDER;
    }

    /**
     * @brief Get the BasePart Data object
     *
     * @param buffer_pointer the buffer pointer which we should store
     * the BasePart data in.
     * @param subdivisions the number of subdivisions.
     * @return int the number of faces used.
     */
    static int getShapeData(GLfloat *buffer_pointer, int subdivisions);
};

#endif