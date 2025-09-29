#include "../include/camera.hpp"

Matrix4x4 Camera::viewMatrix()
{
    Vector3 forward {rotate({0, 0, 1}, orientation)};
    Vector3 up {rotate({0, 1, 0}, orientation)};
    Vector3 right {forward.cross(up)};

    Matrix4x4 rotation {
        {right.x(),      right.y(),        right.z(),            0.0},
        {up.x(),           up.y(),             up.z(),                 0.0},
        {-forward.x(),     -forward.y(),       -forward.z(),           0.0},
        {0.0,              0.0,                0.0,                    1.0}
    };

    Matrix4x4 translation {
        {1.0,       0.0,        0.0,        -position.x()},
        {0.0,       1.0,        0.0,        -position.y()},
        {0.0,       0.0,        1.0,        -position.z()},
        {0.0,       0.0,        0.0,        1.0}
    };

    return rotation.MatMult(translation);
}

PointNDC Camera::getNDC(Vertex point)
{
    // Camera transform
    Vertex camera_point {viewMatrix().MatMult(point.pos), point.color};

    // NDC transform
    float f = 1.0f / std::tan(fov * 0.5f * PI / 180.0f);
    float x_ndc {camera_point.pos.x() / camera_point.pos.z() * f / aspect_ratio};
    float y_ndc {camera_point.pos.y() / camera_point.pos.z() * f};

    return PointNDC(Vector2(x_ndc, y_ndc), camera_point.color);
}

void Camera::pitch(float angle)
{
    Quaternion pitchQ {fromAxisAngle(Vector3(1, 0, 0), angle)};
    orientation = orientation * pitchQ;
}

void Camera::yaw(float angle)
{
    Quaternion yawQ {fromAxisAngle(Vector3(0, 1, 0), angle)};
    orientation = yawQ * orientation;
}

void takeInput(const bool *keyStates, Camera& camera)
{
    Vector3 forward {rotate({0, 0, 1}, camera.orientation)};
    Vector3 up {rotate({0, 1, 0}, camera.orientation)};
    Vector3 right {forward.cross(up)};

    if (keyStates[SDL_SCANCODE_UP])
    {
        camera.position += forward * 0.01;
    }
    if (keyStates[SDL_SCANCODE_DOWN])
    {
        camera.position -= forward * 0.01;
    }
    if (keyStates[SDL_SCANCODE_LEFT])
    {
        camera.position += right * 0.01;
    }
    if (keyStates[SDL_SCANCODE_RIGHT])
    {
        camera.position -= right * 0.01;
    }
    if (keyStates[SDL_SCANCODE_SPACE])
    {
        camera.position -= up * 0.01;
    }
    if (keyStates[SDL_SCANCODE_LSHIFT])
    {
        camera.position += up * 0.01;
    }
    if (keyStates[SDL_SCANCODE_J])
    {
        camera.yaw(-.2f);
    }
    if (keyStates[SDL_SCANCODE_L])
    {
        camera.yaw(.2f);
    }
    if (keyStates[SDL_SCANCODE_I])
    {
        camera.pitch(.2f);
    }
    if (keyStates[SDL_SCANCODE_K])
    {
        camera.pitch(-.2f);
    }
}