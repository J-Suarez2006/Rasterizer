#include "../include/renderer.hpp"

SDL_Vertex getSDLVertex(const PointNDC& point)
{
    float x_screen {((point.x() + 1.0f) / 2.0f) * RAST::SCREEN_WIDTH};
    float y_screen {(1.0f - (1.0f + point.y()) * 0.5f) * RAST::SCREEN_HEIGHT};

    return SDL_Vertex{
        {x_screen, y_screen},
        {
            point.color.r(),
            point.color.g(),
            point.color.b(),
            1.0f
        }
    };
}

bool Renderer::inFrustrum(const Vertex& v, const CachedCamera& c)
{
    return (
        v.pos.z() <= -c.near_plane && v.pos.z() >= -c.far_plane
    );
};

bool Renderer::inScreen(const PointNDC& p)
{
    return (
        p.x() >= -1.0f && p.x() <= 1.0f &&
        p.y() >= -1.0f && p.y() <= 1.0f
    );
}

CachedCamera Renderer::cacheCamera()
{
    return CachedCamera{
        camera->far_plane,
        camera->near_plane,
        camera->fov,
        camera->viewMatrix()
    };
}

PointNDC Renderer::getNDC(const Vertex& point, const CachedCamera& c)
{
    float aspect_ratio {(float)m_width / (float)m_height};

    float f = 1.0f / std::tan(c.fov * 0.5f * PI / 180.0f);
    float x_ndc {point.pos.x() / point.pos.z() * f / aspect_ratio};
    float y_ndc {point.pos.y() / point.pos.z() * f};

    return PointNDC(Vector2(x_ndc, y_ndc), point.color);
};

void Renderer::Rendermesh(const Mesh& m)
{
    CachedCamera cam_data {cacheCamera()};
    
    for (int i = 0; i < getMeshLength(m); ++i)
    {
        Vertex v1 {m.vertices[m.indices[i * 3 + 0]]};
        Vertex v2 {m.vertices[m.indices[i * 3 + 1]]};
        Vertex v3 {m.vertices[m.indices[i * 3 + 2]]};

        // Global to camera transform
        v1.pos = cam_data.view_matrix.MatMult(v1.pos);
        v2.pos = cam_data.view_matrix.MatMult(v2.pos);
        v3.pos = cam_data.view_matrix.MatMult(v3.pos);

        // Frustrum cull
        if (!inFrustrum(v1, cam_data) && !inFrustrum(v2, cam_data) && !inFrustrum(v3, cam_data)) continue;

        // NDC conversion
        PointNDC p1 {getNDC(v1, cam_data)};
        PointNDC p2 {getNDC(v2, cam_data)};
        PointNDC p3 {getNDC(v3, cam_data)};

        // Cull triangles fully offscreen
        if (!inScreen(p1) && !inScreen(p2) && !inScreen(p3)) continue;

        // Viewport transform
        SDL_Vertex vertices[] = {getSDLVertex(p1), getSDLVertex(p2), getSDLVertex(p3)};

        // Render
        SDL_RenderGeometry(m_renderer, nullptr, vertices, 3, nullptr, 0);
    }
}

void Renderer::RenderObject(const Renderable& r)
{
    CachedCamera cam_data {cacheCamera()};
    Matrix4x4 transform_matrix = r.transform.transformMatrix();
    const auto& m = *r.mesh;

    for (int i = 0; i < getMeshLength(m); ++i)
    {
        Vertex v1 {m.vertices[m.indices[i * 3 + 0]]};
        Vertex v2 {m.vertices[m.indices[i * 3 + 1]]};
        Vertex v3 {m.vertices[m.indices[i * 3 + 2]]};

        // Local to global transform
        v1.pos = transform_matrix.MatMult(v1.pos);
        v2.pos = transform_matrix.MatMult(v2.pos);
        v3.pos = transform_matrix.MatMult(v3.pos);

        // Global to camera transform
        v1.pos = cam_data.view_matrix.MatMult(v1.pos);
        v2.pos = cam_data.view_matrix.MatMult(v2.pos);
        v3.pos = cam_data.view_matrix.MatMult(v3.pos);

        // Frustrum cull
        if (!inFrustrum(v1, cam_data) && !inFrustrum(v2, cam_data) && !inFrustrum(v3, cam_data)) continue;

        // NDC conversion
        PointNDC p1 {getNDC(v1, cam_data)};
        PointNDC p2 {getNDC(v2, cam_data)};
        PointNDC p3 {getNDC(v3, cam_data)};

        // Cull triangles fully offscreen
        if (!inScreen(p1) && !inScreen(p2) && !inScreen(p3)) continue;

        // Viewport transform
        SDL_Vertex vertices[] = {getSDLVertex(p1), getSDLVertex(p2), getSDLVertex(p3)};

        // Render
        SDL_RenderGeometry(m_renderer, nullptr, vertices, 3, nullptr, 0);
    }
}