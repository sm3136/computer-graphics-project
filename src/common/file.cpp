// * Includes * //
#include <common/file.hpp>

// * Methods * //

/**
 * Gets the shader code from a file, then
 * returns a pointer to the shader code.
 * 
 * @author - Dr. Girard (Pulled from classwork)
 * 
 * @param filename - the string containing the file name
 * and where to find it.
 */
char *readShaderCode(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        cout <<  "File failed to load..." << filename;
        exit(1);
    }
    fseek(fp, 0L, SEEK_END);
    int res = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *data = (char *)calloc(res + 1, sizeof(char));
    size_t _ = fread(data, sizeof(char), res, fp);
    fclose(fp);

    return data;
}