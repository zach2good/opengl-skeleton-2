#include "shader.h"

// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position;                      \n"
    "varying vec3 color;                           \n"
    "void main()                                   \n"
    "{                                             \n"
    "    gl_Position = vec4(position.xyz, 1.0);    \n"
    "    color = gl_Position.xyz + vec3(0.5);      \n"
    "}                                             \n";

// Fragment/pixel shader
const GLchar* fragmentSource =
    "precision mediump float;                     \n"
    "varying vec3 color;                          \n"
    "void main()                                  \n"
    "{                                            \n"
    "    gl_FragColor = vec4 (color, 1.0);        \n"
    "}                                            \n";

Shader::Shader(std::string const& vertexFilename, std::string const& fragmentFilename)
{
    //std::ignore = vertexFilename;
    //std::ignore = fragmentFilename;

    // TODO: Read shader source from files
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(m_vertexShaderID);

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(m_fragmentShaderID);

    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
    glLinkProgram(m_programID);

    bind();
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
