#include <iostream>
#include <math.h>

#include <classes/Vector.hpp>

/**
 * Creates a zero vector.
 */
Vector3::Vector3()
{
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
}

/**
 * Creates a vector with an x, y, and z value.
 */
Vector3::Vector3(float x, float y, float z)
{
    this->X = x;
    this->Y = y;
    this->Z = z;
}

/**
 * Create a vector using another vector (Copy)
 */
Vector3::Vector3(const Vector3 &vector)
{
    this->X = vector.X;
    this->Y = vector.Y;
    this->Z = vector.Z;
}

// * Standard Overrides for Methods * //

/**
 * Overrides to make vector addition.
 */
Vector3& Vector3::operator+ (const Vector3& v2) 
{
    Vector3 *result = new Vector3();

    result->X = this->X + v2.X;
    result->Y = this->Y + v2.Y;
    result->Z = this->Z + v2.Z;

    return *result;
}

/**
 * Overrides to make vector subtraction
 */
Vector3& Vector3::operator- (const Vector3& v2)
{
    Vector3 *result = new Vector3();

    result->X = this->X - v2.X;
    result->Y = this->Y - v2.Y;
    result->Z = this->Z - v2.Z;

    return *result;
}

/**
 * Overrides to make vector multiplication by scalar
 */
Vector3& Vector3::operator* (const float value)
{
    Vector3 *result = new Vector3();

    result->X = this->X * value;
    result->Y = this->Y * value;
    result->Z = this->Z * value;

    return *result;
}

/**
 * Overrides vector multiplication.
 */
Vector3& Vector3::operator* (const Vector3& v2)
{
    Vector3 *result = new Vector3();

    result->X = this->X * v2.X;
    result->Y = this->Y * v2.Y;
    result->Z = this->Z * v2.Z;

    return *result;
}

/**
 * Overrides the division operator for vector with scalar.
 */
Vector3& Vector3::operator/ (const float scale)
{
    Vector3 *result = new Vector3(0, 0, 0);
    
    result->X = this->X / scale;
    result->Y = this->Y / scale;
    result->Z = this->Z / scale;

    return *result;
}

/**
 * Overrides division for vectors.
 */
Vector3& Vector3::operator/ (const Vector3& v2)
{
    Vector3 *result = new Vector3(0, 0, 0);
    
    result->X = this->X / v2.X;
    result->Y = this->Y / v2.Y;
    result->Z = this->Z / v2.Z;

    return *result;
}

// * Functions * //

/**
 * Calculates the dot product of two vectors.
 * * Recommended that the two vectors are in unit vector form!
 */
float Vector3::Dot(const Vector3& v2) {
    return (this->X * v2.X) + (this->Y * v2.Y) + (this->Z * v2.Z);
}

/**
 * Calculates the cross product of the given two vectors
 * * Recommended that the two vectors are in unit vector form!
 */
Vector3& Vector3::Cross(const Vector3& v2) {
    float x = this->Y * v2.Z - this->Z * v2.Y;
    float y = this->Z * v2.X - this->X * v2.Z;
    float z = this->X * v2.Y - this->Y * v2.X;

    return *(new Vector3(x, y, z));
}

/**
 * Determines the magnitude of the vector given
 */
float Vector3::Magnitude() {
    return sqrtf(pow(this->X, 2) + pow(this->Y, 2) + pow(this->Z, 2));
}

/**
 * Calculates the unit vector for the given vector.
 * * Recomended to only use if on a look vector!
 */
Vector3& Vector3::Unit() {
    float magnitude = this->Magnitude();
    return *this / magnitude;
}

/**
 * Calculates the normal on a plane with vectors
 */
Vector3& Vector3::Normal(const Vector3& v2, const Vector3& v3) {
    Vector3 vec_a = (*this - v2).Unit();
    Vector3 vec_b = (*new Vector3(v2.X, v2.Y, v2.Z) - v3).Unit();

    return vec_a.Cross(vec_b);
}

// * Object Helpers * //

/**
 * Converts the vector into a string
 */
std::string Vector3::toString()
{
    return "X: " + std::to_string(this->X) + 
        ", Y: " + std::to_string(this->Y) + 
        ", Z: " + std::to_string(this->Z);
}