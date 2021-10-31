#pragma once

#include "common.h"
#include "idrawable.h"
#include "randomf.h"
#include "renderer.h"
#include "shader.h"
#include "util.h"

class Line : public IDrawable
{
public:
    Line(Renderer& renderer, std::size_t x0, std::size_t y0, std::size_t x1, std::size_t y1, std::size_t thicknessPixels)
    : m_x0(x0)
    , m_y0(y0)
    , m_x1(x1)
    , m_y1(y1)
    , m_thickness(thicknessPixels)
    , m_r(randomf(0.0f, 1.0f))
    , m_g(randomf(0.0f, 1.0f))
    , m_b(randomf(0.0f, 1.0f))
    {
        //// Generic quad
        //GLfloat vertices[] = {
        //    0.5f, -0.5f,  // Bottom-right
        //    0.5f, 0.5f,   // Top-right
        //    -0.5f, -0.5f, // Bottom-left
        //    -0.5f, 0.5f,  // Top-left
        //};

        auto points = getRotatedPoints(Point(x0, y0), Point(x1, y1), thicknessPixels);

        GLfloat vertices[] = {
            normalizeWidth(points[1].x), normalizeHeight(points[1].y), // Top-right
            normalizeWidth(points[0].x), normalizeHeight(points[0].y), // Bottom-right
            normalizeWidth(points[2].x), normalizeHeight(points[2].y), // Bottom-left
            normalizeWidth(points[3].x), normalizeHeight(points[3].y), // Top-left
        };

        spdlog::info("m_r: {}, m_g: {}, m_b: {}", m_r, m_g, m_b);

        glGenVertexArraysOES(1, &vao);
        glBindVertexArrayOES(vao);

        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        m_Shader = std::make_unique<Shader>("line.vert.hlsl", "line.frag.hlsl");
        m_Shader->bind();

        posLocation = glGetAttribLocation(m_Shader->getId(), "position");
        glEnableVertexAttribArray(posLocation);
        glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

        colLocation = glGetUniformLocation(m_Shader->getId(), "color");
    }

    virtual ~Line()
    {
    }

    void draw(Renderer& renderer) override
    {
        glBindVertexArrayOES(vao);
        m_Shader->bind();

        std::array<GLfloat, 3> cols{ m_r, m_g, m_b };
        glUniform3fv(colLocation, 1, cols.data());

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        m_Shader->unbind();
        glBindVertexArrayOES(0);
    }

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