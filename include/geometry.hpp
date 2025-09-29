#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "math.hpp"

#include <vector>

struct Point2D
{
    int x;
    int y;
    ColorRGB color;
};

struct Vertex
{
    Vector3 pos;
    ColorRGB color;
};

class Transform
{
    public:
    Transform(Vector3 p, Vector3 s, Quaternion r)
    : pos(p), scale(s), rotation(r) {}

    Matrix4x4 translationMatrix() const;
    Matrix4x4 scaleMatrix() const;
    Matrix4x4 rotationMatrix() const;
    Matrix4x4 transformMatrix() const;

    Vector3 pos;
    Vector3 scale;
    Quaternion rotation;
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

inline int getMeshLength(const Mesh& m)
{
    return m.indices.size() / 3;
}

#endif