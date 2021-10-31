#include "shader.h"
#include "path.h"
#include <fstream>

std::string loadShaderString(std::string const& filename)
{
    std::string   shaderPath = SHADER_PATH;
    std::string   path       = shaderPath + filename;
    std::ifstream inputFile(path);
    return std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
}

Shader::Shader(std::string const& vertexFilename, std::string const& fragmentFilename)
{
    auto          vertStr   = loadShaderString(vertexFilename);
    const GLchar* vertChStr = vertStr.c_str();
    m_vertexShaderID        = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderID, 1, &vertChStr, NULL);
    glCompileShader(m_vertexShaderID);

    auto          fragStr   = loadShaderString(fragmentFilename);
    const GLchar* fragChStr = fragStr.c_str();
    m_fragmentShaderID      = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderID, 1, &fragChStr, NULL);
    glCompileShader(m_fragmentShaderID);

    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
    glLinkProgram(m_programID);
}

Shader::~Shader()
{
    unbind();

    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);

    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);

    glDeleteProgram(m_programID);
}

void Shader::bind()
{
    glUseProgram(m_programID);
}

void Shader::unbind()
{
    glUseProgram(0);
}

GLuint Shader::getId()
{
    return m_programID;
}
