#include "../include/geometry.hpp"

Matrix4x4 Transform::translationMatrix() const
{
    return Matrix4x4{
        {1, 0, 0, pos.x()},
        {0, 1, 0, pos.y()},
        {0, 0, 1, pos.z()},
        {0, 0, 0, 1}
    };
}

Matrix4x4 Transform::scaleMatrix() const
{
    return Matrix4x4{
        {scale.x(), 0, 0, 0},
        {0, scale.y(), 0, 0},
        {0, 0, scale.z(), 0},
        {0, 0, 0, 1}
    };
}

Matrix4x4 Transform::rotationMatrix() const
{
    float w = rotation.w(), x = rotation.x(), y = rotation.y(), z = rotation.z();

    return Matrix4x4{
        {1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y), 0},
        {2 * (x * y + w * z), 1 - 2 * (x * x  + z * z), 2 * (y * z - 2 * x), 0},
        {2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y), 0},
        {0, 0, 0, 1},
    };
}

Matrix4x4 Transform::transformMatrix() const
{
    return translationMatrix().MatMult(rotationMatrix()).MatMult(scaleMatrix());
}