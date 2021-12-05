#include <shapes/Shape.hpp>

void write_buffer(GLfloat **buffer, Vector3 *vec)
{
    GLfloat *buff = *buffer;

    buff[0] = vec->X;
    buff[1] = vec->Y;
    buff[2] = vec->Z;
    buff[3] = 0;
    buff[4] = 0;
    buff[5] = 0;

    *buffer += 6;
}

/**
 * @brief Adds the cylinder data to the buffer.
 * 
 * @param buffer_pointer The start pointer for Cylinder data
 * @param faces The number of subdivisions for the cylinder
 * @return int the number of vertices in the cylinder
 */
int Cylinder::getShapeData(GLfloat *buffer_pointer, int faces)
{
    Vector3 *origin = new Vector3(0, 0, 0);

    Vector3 *origin_mod = new Vector3(0, 0.5, 0);
    Vector3 *origin_mod_alt = new Vector3(0, -0.5, 0);

    Vector3 *last_pos = new Vector3(0.5, 0.5, 0);
    Vector3 *last_pos_alt = new Vector3(*last_pos * *new Vector3(1, -1, 1));

    Vector3 *new_pos;
    Vector3 *new_pos_alt;

    for (int i = 0; i < faces; i++)
    {
        // Generate the new position
        float fractional = (i + 1.0) / faces;
        float angle_rads = fractional * 3.1415926 * 2;
        new_pos = new Vector3(cos(angle_rads) * 0.5, 0.5, sin(angle_rads) * 0.5);

        // Generates the first endcap of the cylinder.
        write_buffer(&buffer_pointer, origin_mod);
        write_buffer(&buffer_pointer, new_pos);
        write_buffer(&buffer_pointer, last_pos);

        // Generates the second endcap of the cylinder
        new_pos_alt = new Vector3(*new_pos * *new Vector3(1, -1, 1));

        write_buffer(&buffer_pointer, last_pos_alt);
        write_buffer(&buffer_pointer, new_pos_alt);
        write_buffer(&buffer_pointer, origin_mod_alt);

        // Generates the faces connecting them
        write_buffer(&buffer_pointer, last_pos);
        write_buffer(&buffer_pointer, new_pos_alt);
        write_buffer(&buffer_pointer, last_pos_alt);

        // Generates the faces connecting them
        write_buffer(&buffer_pointer, last_pos);
        write_buffer(&buffer_pointer, new_pos);
        write_buffer(&buffer_pointer, new_pos_alt);

        last_pos = new_pos;
        last_pos_alt = new_pos_alt;
    }
    return (faces * 3 * 2) * 2;
}
