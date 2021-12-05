#ifndef FILE_H
#define FILE_H

// * Includes for the cpp file * //
#include <iostream>
using namespace std;

/**
 * Gets the shader code from a file, then
 * returns a pointer to the shader code.
 * 
 * @author - Dr. Girard (Pulled from classwork)
 * 
 * @param filename - the string containing the file name
 * and where to find it.
 */
char* readShaderCode(const char* filename);

#endif