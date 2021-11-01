#pragma once

#include "common.h"
#include "idrawable.h"
#include "randomf.h"
#include "renderer.h"
#include "shader.h"

class Line : public IDrawable
{
public:
    Line(Renderer& renderer, std::size_t x0, std::size_t y0, std::size_t x1, std::size_t y1, std::size_t thicknessPixels);
    virtual ~Line() = default;

    void draw(Renderer& renderer) override;

    GLuint                  vao;
    GLuint                  vbo;
    GLint                   posLocation;
    GLint                   colLocation;
    std::unique_ptr<Shader> m_Shader;

    std::size_t m_x0;
    std::size_t m_y0;
    std::size_t m_x1;
    std::size_t m_y1;
    std::size_t m_thickness;
    float       m_r;
    float       m_g;
    float       m_b;
};