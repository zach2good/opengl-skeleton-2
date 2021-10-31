#include "app.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

#include <spdlog/spdlog.h>

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
    "    gl_FragColor = vec4 ( color, 1.0 );      \n"
    "}                                            \n";

App::App(std::string const& title, std::size_t width, std::size_t height)
{
    spdlog::info("App init");
    SDL_Init(SDL_INIT_VIDEO);

    m_Window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (m_Window == NULL)
    {
        spdlog::error("Could not create window: {}", SDL_GetError());
    }

#ifndef __EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif // !__EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_GLContext = SDL_GL_CreateContext(m_Window);

    SDL_GL_SetSwapInterval(0);

    spdlog::info("GL_VENDOR: {}", glGetString(GL_VENDOR));
    spdlog::info("GL_RENDERER: {}", glGetString(GL_RENDERER));
    spdlog::info("GL_VERSION: {}", glGetString(GL_VERSION));
    spdlog::info("GL_SHADING_LANGUAGE_VERSION: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    spdlog::info("GL_EXTENSIONS: {}", glGetString(GL_EXTENSIONS));

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArraysOES(1, &vao);
    glBindVertexArrayOES(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = { 0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

App::~App()
{
    spdlog::info("Shutting down App");
    SDL_GL_DeleteContext(m_GLContext);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

bool App::running()
{
    return !m_CloseRequested;
}

void App::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    // TODO: WSL2 + Windows 11 gets stuck on this
                    //spdlog::info("SDLK_ESCAPE -> SDL_QUIT requested");
                    //m_CloseRequested = true;
                }
            }
            break;
            case SDL_QUIT:
            {
                spdlog::info("SDL_QUIT requested");
                m_CloseRequested = true;
            }
            break;
            default:
                break;
        }
    }
}

void App::tick()
{
}

void App::render()
{
    // Clear
    glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Present
    SDL_GL_SwapWindow(m_Window);
}
