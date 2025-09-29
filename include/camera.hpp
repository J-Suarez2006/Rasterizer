#ifndef CAMERA_HPP
#define CAMERA_HPP

#define PI 3.14159263f

#include "math.hpp"
#include "rast.hpp"
#include "geometry.hpp"

struct PointNDC
{
    PointNDC() : pos(Vector2()), color(ColorRGB{}) {}
    PointNDC(Vector2 p, ColorRGB c) : pos(p), color(c) {}

    Vector2 pos;
    ColorRGB color;

    inline float x() const {return pos.x();}
    inline float y() const {return pos.y();} 
};

class Camera
{
    public:
    Vector3 position;
    Quaternion orientation {1, 0, 0, 0};
    float fov;
    float aspect_ratio;
    float near_plane;
    float far_plane;

    Camera(Vector3 pos, float fov, float ar, float np = 0.1, float fp = 1000.0)
    : position(pos), fov(fov), aspect_ratio(ar), near_plane(np), far_plane(fp) {}

    Matrix4x4 viewMatrix();
    PointNDC getNDC(Vertex point);

    void pitch(float angle);
    void yaw(float angle);
};

void takeInput(const bool *keyStates, Camera& camera);

#endif