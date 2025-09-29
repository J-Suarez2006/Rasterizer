#include "../include/math.hpp"

#include <iostream>

Vector3 Matrix4x4::MatMult(Vector3 v)
{
    std::array<float, 4> v4 = v.V4();
    Vector3 result;

    for (int i = 0; i < 3; ++i)
    {
        float to_add {0.0f};
        for (int j = 0; j < 4; ++j)
        {
            to_add += m[i][j] * v4[j];
        }
        result.v[i] = to_add;
    }

    return result;
}

Matrix4x4 Matrix4x4::MatMult(Matrix4x4 other)
{
    Matrix4x4 result {};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k)
                result.m[i][j] += m[i][k] * other.m[k][j];
        }
    return result;  
}

Matrix4x4::row operator+(Matrix4x4::row r1, Matrix4x4::row r2)
{
    Matrix4x4::row res;

    for (int i = 0; i < 4; ++i)
    {
        res[i] = r1[i] + r2[i];
    }

    return res;
}

Matrix4x4::row operator-(Matrix4x4::row r)
{
    Matrix4x4::row res;

    for (int i = 0; i < 4; ++i)
    {
        res[i] = -r[i];
    }

    return res;
}

Matrix4x4::row operator-(Matrix4x4::row r1, Matrix4x4::row r2)
{
    return r1 + (-r2);
}


Matrix4x4::row operator*(Matrix4x4::row r, float scalar)
{
    Matrix4x4::row res;

    for (int i = 0; i < 4; ++i)
    {
        res[i] = scalar * r[i];
    }

    return res;
}

Matrix4x4::row operator/(Matrix4x4::row r, float scalar)
{
    return r * (1 / scalar);
}

Matrix4x4::row operator+=(Matrix4x4::row& r1, Matrix4x4::row r2)
{
    return r1 = r1 + r2;
}

Matrix4x4::row operator-=(Matrix4x4::row& r1, Matrix4x4::row r2)
{
    return r1 = r1 - r2;
}

Matrix4x4::row operator*=(Matrix4x4::row& r1, float scalar)
{
    return {
        r1[0] *= scalar,
        r1[1] *= scalar,
        r1[2] *= scalar,
        r1[3] *= scalar
    };
}

Matrix4x4::row operator/=(Matrix4x4::row& r1, float scalar)
{
    return r1 *= (1 / scalar);
}

Matrix4x4 identity()
{
    return Matrix4x4{
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
}

Matrix4x4 getInverse(Matrix4x4 matrix)
{
    auto& mat = matrix.m;
    Matrix4x4 I = identity();

    for (int r = 0; r < mat.size(); ++r)
    {
        for (int i = r; i < mat.size(); ++i)
        {
            float factor = 1 / mat[i][r];

            mat[i] *= factor;
            I.m[i] *= factor;
        }

        for (int i = r + 1; i < mat.size(); ++i)
        {
            mat[i] -= mat[r];
            I.m[i] -= I.m[r];
        }
    }

    for (int r = mat.size() - 1; r >= 0; --r)
    {
        for (int i = r - 1; i >= 0; --i)
        {
            float factor = mat[i][r];

            mat[i] -= (mat[r] * factor);
            I.m[i] -= (I.m[r] * factor);
        }
    }

    return I;
}

// Quaternions
Vector3 rotate(const Vector3& rotate_me, const Vector3& axis, float angle)
{
    #define PI 3.14159263f

    Quaternion pure {0, rotate_me};
    float angle_rad = angle * PI / 180.0f;

    Quaternion q {
        std::cos(angle_rad / 2),
        axis.unit() * std::sin(angle_rad / 2)
    };

    q = q.normalize();

    return (q * pure * q.conjugate()).v();
}

Vector3 rotate(const Vector3& rotate_me, const Quaternion& q)
{
    Quaternion pure {0, rotate_me};
    return (q * pure * q.conjugate()).v();
}

Quaternion fromAxisAngle(const Vector3& axis, float angle)
{
    #define PI 3.14159263f

    float angle_rad = angle * PI / 180.0f;

    Quaternion q {
        std::cos(angle_rad / 2),
        axis.unit() * std::sin(angle_rad / 2)
    };

    return q.normalize();
}
