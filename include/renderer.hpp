#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "geometry.hpp"
#include "camera.hpp"

#include <vector>

SDL_Vertex getSDLVertex(const PointNDC& point);

struct Renderable
{
    Mesh* mesh;
    Transform transform;
};

struct CachedCamera
{
    float far_plane;
    float near_plane;
    float fov;
    Matrix4x4 view_matrix;
};

class Renderer
{
    public:
    Renderer() = delete;
    Renderer(SDL_Window* w, SDL_Renderer* r, Camera* c) 
    : m_renderer(r), camera(c) 
    {
        int width = 0, height = 0;
        SDL_GetWindowSize(w, &width, &height);
        m_width = width;
        m_height = height;
    }

    void Rendermesh(const Mesh& m);
    void RenderObject(const Renderable& r);

    private:
    SDL_Renderer* m_renderer;
    Camera* camera;
    int m_width;
    int m_height;

    CachedCamera cacheCamera();
    PointNDC getNDC(const Vertex& point, const CachedCamera& c);
    bool inFrustrum(const Vertex& v, const CachedCamera& c);
    bool inScreen(const PointNDC& p);
};


#endif