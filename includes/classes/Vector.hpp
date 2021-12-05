#ifndef VECTOR_H
#define VECTOR_H

#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

class Vector3
{
    public:
        float X;
        float Y;
        float Z;

        Vector3();
        Vector3(const Vector3 &vector);
        Vector3(float x, float y, float z);

        Vector3& operator +(const Vector3& v2);
        Vector3& operator -(const Vector3& v2);

        Vector3& operator *(const float S);
        Vector3& operator *(const Vector3& v2);
        Vector3& operator /(const float scale);
        Vector3& operator /(const Vector3& v2);

        float Dot(const Vector3& v2);
        Vector3& Cross(const Vector3& v2);
        Vector3& Normal(const Vector3& v2, const Vector3& v3);

        float Magnitude();
        Vector3& Unit();

        std::string toString();
};

#endif
