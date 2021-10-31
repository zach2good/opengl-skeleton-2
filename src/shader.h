#pragma once

#include "common.h"

class Shader
{
public:
    Shader(std::string const& vertexFilename, std::string const& fragmentFilename);
    ~Shader();

    void bind();
    void unbind();

    GLuint getId();

protected:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};
