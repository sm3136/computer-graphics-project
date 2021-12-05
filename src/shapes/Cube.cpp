#include <shapes/Shape.hpp>

/**
 * @brief Used in creating the cube object.
 * This will hold all of the imprtant vertices and points.
 * 
 */
float helper[][3] = {
    // Front Face
    {1, -1, 0},// Bottom Right
    {0, -1, 0},// Bottom Left
    {0, 0, 0}, // Top Left
    {0, 0, 0}, // Top Left
    {1, 0, 0}, // Top Right
    {1, -1, 0},// Bottom Right

    // Back Face
    {0, 0, 1}, // Top Left
    {0, -1, 1},// Bottom Left
    {1, -1, 1},// Bottom Right
    {1, -1, 1},// Bottom Right
    {1, 0, 1}, // Top Right
    {0, 0, 1}, // Top Left

    // Left Face.
    {0, 0, 0}, // Top Left
    {0, -1, 0},// Bottom Left
    {0, -1, 1},// Bottom Right
    {0, -1, 1},// Bottom Right
    {0, 0, 1}, // Top Right
    {0, 0, 0}, // Top Left

    // Right Face
    {1, -1, 1},// Bottom Right
    {1, -1, 0},// Bottom Left
    {1, 0, 0}, // Top Left
    {1, 0, 0}, // Top Left
    {1, 0, 1}, // Top Right
    {1, -1, 1},// Bottom Right 

    // Top Face
    {0, 0, 0}, // Top Left
    {0, 0, 1}, // Bottom Left
    {1, 0, 1}, // Bottom Right
    {1, 0, 1}, // Bottom Right
    {1, 0, 0}, // Top Right
    {0, 0, 0}, // Top Left

    // Bottom Face
    {1, -1, 1}, // Bottom Right
    {0, -1, 1}, // Bottom Left
    {0, -1, 0}, // Top Left
    {0, -1, 0}, // Top Left
    {1, -1, 0}, // Top Right
    {1, -1, 1}, // Bottom Right
};

/**
 * @brief Gets the shape data for the cube.
 * 
 * @param buffer_pointer The pointer in the shapeBuffer to the start
 * of the cube data generation.
 * @return int the number of vertices added to the shape buffer.
 */
int Cube::getShapeData(GLfloat *buffer_pointer)
{
    for (int i = 0; i < 6 * 6; i++)
    {
        int offset_modified = i * FLOATS_PER_VERTEX;

        buffer_pointer[offset_modified]     = (helper[i][0] * 0.5) - 0.25;
        buffer_pointer[offset_modified + 1] = (helper[i][1] * 0.5) + 0.25;
        buffer_pointer[offset_modified + 2] = (helper[i][2] * 0.5) + 0.25;
        buffer_pointer[offset_modified + 3] = 0;
        buffer_pointer[offset_modified + 4] = 0;
        buffer_pointer[offset_modified + 5 ] = 0;
    }

    return 36;
}