#include <iostream>
#include <math.h>

#include <classes/Matrix.hpp>

const float PI = 3.1415;

Matrix::Matrix() 
{
    for (int x = 0; x < 4; x++) 
    {
        for (int y = 0; y < 4; y++)
        {
            data[x][y] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &one_to_copy)
{
    for (int x = 0; x < 4; ++x)
    {
        for (int y = 0; y < 4; ++y)
        {
            data[x][y] = one_to_copy.data[x][y];
        }
    }
}

Matrix Matrix::operator *(Matrix &object)
{
    Matrix tmp;

    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += this->data[i][k] * object[k][j];
            }
        }
    }

    return tmp;
}

float* Matrix::operator [](int i)
{
    return data[i];
}

void Matrix::print()
{
    for (int x = 0; x < 4; x++) 
    {
        for (int y = 0; y < 4; y++)
        {
            std::cout << data[x][y] << " ";
        }
        std::cout << "\n";
    }
}

Matrix Matrix::identity()
{
    Matrix ret;

    for (int i = 0; i < 4; i++)
    {
        ret[i][i] = 1;
    }

    return ret;
}

Matrix Matrix::perspective(float fov, float near_plane, float far_plane)
{
    Matrix M;
    float tan_half_angle = tan(fov * PI / 360);

    M[0][0] = 1 / tan_half_angle;
    M[1][1] = 1 / tan_half_angle;
    M[2][2] = (far_plane + near_plane) / (far_plane - near_plane);
    M[2][3] = -(2 * far_plane * near_plane) / (far_plane - near_plane);
    M[3][2] = 1.0;
    
    return M;
}

GLfloat *Matrix::getMatrix()
{
    return data[0];
}

// Rotation Matrix's
Matrix Matrix::rotationXY(float r) 
{
    Matrix ret;
    ret = ret.identity();

    ret[0][0] = cos(r * PI / 180.0f);
    ret[0][1] = -sin(r * PI / 180.0f);
    ret[1][0] = sin(r * PI / 180.f);
    ret[1][1] = cos(r * PI / 180.0f);

    return ret;
}

Matrix Matrix::rotationXZ(float r) 
{
    Matrix ret;
    ret = ret.identity();

    ret[0][0] = cos(r * PI / 180.0f);
    ret[0][2] = sin(r * PI / 180.0f);
    ret[2][0] = -sin(r * PI / 180.0f);
    ret[2][2] = cos(r * PI / 180.0f);

    return ret;
}

Matrix Matrix::rotationYZ(float r) 
{
    Matrix ret;
    ret = ret.identity();

    ret[1][1] = cos(r * PI / 180.0f);
    ret[1][2] = -sin(r * PI / 180.0f);
    ret[2][1] = sin(r * PI / 180.f);
    ret[2][2] = cos(r * PI / 180.0f);

    return ret;
}

// Transformation Matrix
Matrix Matrix::transform(float x, float y, float z) 
{
    Matrix ret;
    ret = ret.identity();

    ret[0][3] = x;
    ret[1][3] = y;
    ret[2][3] = z;

    return ret;
}

Matrix Matrix::scale(float x, float y, float z) 
{
    Matrix ret;
    ret = ret.identity();

    ret[0][0] = x;
    ret[1][1] = y;
    ret[2][2] = z;

    return ret;
}