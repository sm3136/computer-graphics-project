#include <shapes/Shape.hpp>

/**
 * @brief The following variable is used in order
 * to generate an octahedron. (The prefab shape of
 * the sphere)
 * 
 */
float helper_octo_sphere[][3] = {
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
 * @brief Given the pointer to the shape buffer, this method will append all of the 
 * needed data to generate the shape that we plan to use. It will also return the 
 * number of vertices that have been added.
 * 
 * @param buffer_pointer aka the shapeBuffer
 * @param subdivisions the number of subdivisions that we want on our sphere.
 * @return int the number of vertices that have been added.
 */
int Sphere::getShapeData(GLfloat *buffer_pointer, int subdivisions)
{
    float NUM_VERTEX = 24 * pow(4, subdivisions);
    GLfloat *vertices = (GLfloat *)calloc(NUM_VERTEX * FLOATS_PER_VERTEX, sizeof(GLfloat));

    // Loads the octahedron
    for (int i = 0; i < 3 * 4 * 2; i++)
    {
        int offset_modified = i * FLOATS_PER_VERTEX;

        vertices[offset_modified]     = (helper_octo_sphere[i][0] * 0.5);
        vertices[offset_modified + 1] = (helper_octo_sphere[i][1] * 0.5);
        vertices[offset_modified + 2] = (helper_octo_sphere[i][2] * 0.5);
        vertices[offset_modified + 3] = 0;
        vertices[offset_modified + 4] = 0;
        vertices[offset_modified + 5 ] = 0;
    }

    // Subdivides the shape the given number of times.
    int numTriangles = 8;
    for (int sub = 1; sub < subdivisions; sub++)
    {
        Shape::subdivide_all(vertices, numTriangles);
        numTriangles *= 4;
    }

    // Inflates all of the vertices to be 0.5 radius from the center. (Making a unit sphere)
    for (int i = 0; i < NUM_VERTEX; i++)
    {
        int offset = i * FLOATS_PER_VERTEX;

        float magnitude = sqrtf(pow(vertices[offset], 2) + pow(vertices[offset + 1], 2) + pow(vertices[offset + 2], 2)) * 4;
        vertices[offset] /= magnitude;
        vertices[offset + 1] /= magnitude;
        vertices[offset + 2] /= magnitude;
    }
    
    memcpy(buffer_pointer, vertices, NUM_VERTEX * FLOATS_PER_VERTEX * sizeof(GLfloat));
    free(vertices);

    return NUM_VERTEX;
}