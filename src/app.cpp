#include "app.h"

#include "idrawable.h"
#include "renderer.h"
#include "triangle.h"
#include "line.h"

App::App(std::string const& title, std::size_t width, std::size_t height)
: m_Renderer(std::make_unique<Renderer>(title, width, height))
{
    //m_Drawables.emplace_back(std::make_unique<Triangle>());

    // Angled + Fat/Single Pixel
    m_Drawables.emplace_back(std::make_unique<Line>(*m_Renderer, 10, 10, 310, 310, 20));
    m_Drawables.emplace_back(std::make_unique<Line>(*m_Renderer, 310, 310, 620, 620, 1));

    // Vertical + Fat/Single Pixel
    //m_Drawables.emplace_back(std::make_unique<Line>());
    //m_Drawables.emplace_back(std::make_unique<Line>());

    // Horizontal + Fat/Single Pixel
    //m_Drawables.emplace_back(std::make_unique<Line>());
    //m_Drawables.emplace_back(std::make_unique<Line>());
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
