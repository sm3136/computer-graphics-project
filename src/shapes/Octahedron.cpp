#include <shapes/Shape.hpp>

float helper_octo[][3] = {
    // Top Front Face
    { -1, 0, -1 }, // Bottom Left
    { 0, 1, 0 }, // Top Center
    { 1, 0, -1 }, // Bottom Right

    // Top Back Face
    { 1, 0, 1 }, // Bottom Right
    { 0, 1, 0 }, // Top Center
    { -1, 0, 1 }, // Bottom Left

    // Top Left Face
    { -1, 0, 1 }, // Bottom Left
    { 0, 1, 0 }, // Top Center
    { -1, 0, -1 }, // Bottom Right

    // Top Right Face
    { 1, 0, -1 }, // Bottom Left
    { 0, 1, 0 }, // Top Center
    { 1, 0, 1 }, // Bottom Right

    // Bottom Front Face
    { 1, 0, -1 }, // Bottom Right
    { 0, -1, 0 }, // Top Center
    { -1, 0, -1 }, // Bottom Left

    // Bottom Back Face
    { -1, 0, 1 }, // Bottom Left
    { 0, -1, 0 }, // Top Center
    { 1, 0, 1 }, // Bottom Right

    // Bottom Left Face
    { -1, 0, -1 }, // Bottom Right
    { 0, -1, 0 }, // Top Center
    { -1, 0, 1 }, // Bottom Left

    // Bottom Right Face
    { 1, 0, 1 }, // Bottom Right
    { 0, -1, 0 }, // Top Center
    { 1, 0, -1 }, // Bottom Left
};

/**
 * @brief Gets all of the data for an octahedron.
 * 
 * @param buffer_pointer the pointer to where the octahedron should
 * start being written.
 * @return int the number of vertices added to the shapeBuffer.
 */
int Octahedron::getShapeData(GLfloat *buffer_pointer)
{
    for (int i = 0; i < 3 * 4 * 2; i++)
    {
        int offset_modified = i * FLOATS_PER_VERTEX;

        buffer_pointer[offset_modified]     = (helper_octo[i][0] * 0.5);
        buffer_pointer[offset_modified + 1] = (helper_octo[i][1] * 0.5);
        buffer_pointer[offset_modified + 2] = (helper_octo[i][2] * 0.5);
        buffer_pointer[offset_modified + 3] = 0;
        buffer_pointer[offset_modified + 4] = 0;
        buffer_pointer[offset_modified + 5 ] = 0;
    }

    return 3 * 4 * 2;
}