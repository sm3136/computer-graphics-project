#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/glut.h>

/**
 * Checks for shader compilation errors
 * 
 * @author - Dr. Girard or the Video Guy
 * @ref - Pulled from in class examples
 * 
 * @param shader the id associated with that shader
 * that we want to check for errors in.
 */
void checkForShaderError(GLuint shader);

/**
 * Checks to find errors from the GPU program
 * that runs our shaders.
 * 
 * @author - Dr. Girard or the Video Guy
 * @ref - Pulled from in class examples
 * 
 * @param programID the id associated with the shader
 * program that we want to find errors in. 
 */
void checkForProgramError(GLuint programID);

#endif