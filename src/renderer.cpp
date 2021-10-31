#include "renderer.h"

#include "idrawable.h"
#include "randomf.h"

Renderer::Renderer(std::string const& title, std::size_t width, std::size_t height)
: m_Width(width)
, m_Height(height)
{
    SDL_Init(SDL_INIT_VIDEO);

    m_Window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (m_Window == nullptr)
    {
        spdlog::error("Could not create window: {}", SDL_GetError());
        std::exit(-1);
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

#ifdef WIN32
    GLenum err = glewInit();
    if (err)
    {
        spdlog::error("GLEW: {}", glewGetErrorString(err));
        std::exit(-1);
    }
#endif

    spdlog::info("GL_VENDOR: {}", glGetString(GL_VENDOR));
    spdlog::info("GL_RENDERER: {}", glGetString(GL_RENDERER));
    spdlog::info("GL_VERSION: {}", glGetString(GL_VERSION));
    spdlog::info("GL_SHADING_LANGUAGE_VERSION: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    spdlog::info("GL_EXTENSIONS: {}", glGetString(GL_EXTENSIONS));

    m_ClearR = randomf(0.0f, 0.5f);
    m_ClearG = randomf(0.0f, 0.5f);
    m_ClearB = randomf(0.0f, 0.5f);
}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(m_GLContext);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Renderer::clear()
{
    glClearColor(m_ClearR, m_ClearG, m_ClearB, 0.2f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(std::vector<std::unique_ptr<IDrawable>>& drawables)
{
    for (auto const& drawable : drawables)
    {
        drawable->draw(*this);
    }
}

void Renderer::present()
{
    SDL_GL_SwapWindow(m_Window);
}
