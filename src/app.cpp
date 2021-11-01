#include "app.h"

#include "idrawable.h"
#include "line.h"
#include "randomf.h"
#include "renderer.h"

App::App(std::string const& title, std::size_t width, std::size_t height)
: m_Renderer(std::make_unique<Renderer>(title, width, height))
{
    // Seed randomness
    seed();

    // Angled + Fat/Single Pixel
    m_Drawables.emplace_back(std::make_unique<Line>(*m_Renderer, 500, 200, 700, 100, 100));
    m_Drawables.emplace_back(std::make_unique<Line>(*m_Renderer, 550, 200, 750, 100, 1));

    // Vertical + Fat/Single Pixel
    m_Drawables.emplace_back(std::make_unique<Line>(*m_Renderer, 300, 100, 300, 300, 10));
    m_Drawables.emplace_back(std::make_unique<Line>(*m_Renderer, 350, 100, 350, 300, 1));

    // Horizontal + Fat/Single Pixel
    m_Drawables.emplace_back(std::make_unique<Line>(*m_Renderer, 100, 100, 200, 100, 20));
    m_Drawables.emplace_back(std::make_unique<Line>(*m_Renderer, 100, 200, 200, 200, 1));
}

App::~App()
{
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
    m_Renderer->clear();
    m_Renderer->draw(m_Drawables);
    m_Renderer->present();
}
