#pragma once

#include "common.h"
#include "renderer.h"
#include "shader.h"
#include "idrawable.h"

class Triangle : public IDrawable
{
public:
    Triangle()
    {
        GLuint vao;
        glGenVertexArraysOES(1, &vao);
        glBindVertexArrayOES(vao);

        GLuint vbo;
        glGenBuffers(1, &vbo);

        GLfloat vertices[] = { 0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        m_Shader = std::make_unique<Shader>("", "");

        GLint posAttrib = glGetAttribLocation(m_Shader->getId(), "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    ~Triangle()
    {
    }

    void draw(Renderer& renderer) override
    {
        m_Shader->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_Shader->unbind();
    }

    std::unique_ptr<Shader> m_Shader;
};