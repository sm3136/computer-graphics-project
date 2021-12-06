#ifndef CONFIG
#define CONFIG

#include <math.h>

// * Editable Constants * //
#define SPHERE_SUBDIVISIONS 4
#define CYLINDER_FACES 40

// * Set-In-Stone Constants * //

// Helpful for calculations
#define FLOATS_PER_VERTEX 6
#define VERTEX_PER_TRI 3
#define VERTEX_PER_SQUARE 6

// Constants

const int VERTEX_PER_CUBE = VERTEX_PER_SQUARE * 6;
const int VERTEX_PER_OCTAHEDRON = VERTEX_PER_TRI * 8;
const int VERTEX_PER_SPHERE = VERTEX_PER_OCTAHEDRON * pow(4, SPHERE_SUBDIVISIONS);
const int VERTEX_PER_CYLINDER = (VERTEX_PER_TRI * CYLINDER_FACES * 2) + (VERTEX_PER_SQUARE * CYLINDER_FACES);

const int NUM_VERTICIES = VERTEX_PER_CUBE + VERTEX_PER_OCTAHEDRON + VERTEX_PER_SPHERE + VERTEX_PER_CYLINDER;
const int NUM_FLOATS = NUM_VERTICIES * FLOATS_PER_VERTEX;

#endif