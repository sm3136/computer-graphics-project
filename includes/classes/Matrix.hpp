#ifndef MATRIX_H
#define MATRIX_H

#include <GL/glew.h>
#include <GL/glut.h>

class Matrix
{
    private: 
        float data[4][4];
    public:
        Matrix();
        Matrix(const Matrix &one_to_copy);

        Matrix operator *(Matrix &obj);
        float *operator [](int i);

        void print();

        static Matrix perspective(float fov, float near, float far);
        static Matrix identity();
        GLfloat *getMatrix();

        // Rotation Matrix's
        static Matrix rotationXY(float r);
        static Matrix rotationXZ(float r);
        static Matrix rotationYZ(float r);

        // Transformation Matrix
        static Matrix transform(float x, float y, float z);

        // Scale Matrix
        static Matrix scale(float x, float y, float z);
};

#endif