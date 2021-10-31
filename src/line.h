#pragma once

#include "common.h"
#include "renderer.h"
#include "shader.h"
#include "idrawable.h"

class Line : public IDrawable
{
public:
    Line(Renderer& renderer, std::size_t x0, std::size_t y0, std::size_t x1, std::size_t y1, std::size_t thicknessPixels)
    : m_x0(x0)
    , m_y0(y0)
    , m_x1(x1)
    , m_y1(y1)
    , m_thickness(thicknessPixels)
    {
        GLuint vao;
        glGenVertexArraysOES(1, &vao);
        glBindVertexArrayOES(vao);

        GLuint vbo;
        glGenBuffers(1, &vbo);

        float normalX0 = renderer.normalizeWidth(m_x0);
        float normalY0 = renderer.normalizeHeight(m_y0);
        float normalX1 = renderer.normalizeWidth(m_x1);
        float normalY1 = renderer.normalizeHeight(m_y1);

        float pixelSizeX = renderer.normalizeWidth(1);
        float pixelSizeY = renderer.normalizeHeight(1);

        GLfloat vertices[] = { normalX0, normalY0, 0, // bottom left corner
                               normalX0, normalY1, 0, // top left corner
                               normalX1, normalY1, 0, // top right corner
                               normalX1, normalY0, 0}; // bottom right corner

        GLubyte indices[] = {0,1,2, // first triangle (bottom left - top left - top right)
                            0,2,3}; // second triangle (bottom left - top right - bottom right)

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        m_Shader = std::make_unique<Shader>("", "");

        GLint posAttrib = glGetAttribLocation(m_Shader->getId(), "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    ~Line()
    {
    }

    void draw(Renderer& renderer) override
    {
        m_Shader->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_Shader->unbind();
    }

    std::unique_ptr<Shader> m_Shader;

    std::size_t m_x0;
    std::size_t m_y0;
    std::size_t m_x1;
    std::size_t m_y1;
    std::size_t m_thickness;
};