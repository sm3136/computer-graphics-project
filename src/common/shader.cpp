#include <iostream>

#include <common/shader.hpp>

using namespace std;

/**
 * Checks for shader compilation errors
 * 
 * @author - Dr. Girard or the Video Guy
 * @ref - Pulled from in class examples
 * 
 * @param shader the id associated with that shader
 * that we want to check for errors in.
 */
void checkForShaderError(GLuint shader)
{
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE)
    {
        cout << compileStatus << endl;
        GLint maxLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        cout << maxLength << endl;
        GLchar* errorLog = new GLchar[maxLength];
        GLsizei bufferSize;
        glGetShaderInfoLog(shader, maxLength, &bufferSize, errorLog);
        cout << errorLog << endl;
        delete [] errorLog;
    }
}

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
void checkForProgramError(GLuint programID)
{
    GLint linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE)
    {
        GLint maxLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar* errorLog = new GLchar[maxLength];
        GLsizei bufferSize;
        glGetProgramInfoLog(programID, maxLength, &bufferSize, errorLog);
        cout << errorLog << endl;
        delete [] errorLog;
    }
}