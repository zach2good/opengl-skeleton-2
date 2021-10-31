#pragma once

#ifdef __EMSCRIPTEN__
#include <SDL.h>
#else
#include <SDL.h>
#endif

#include <string>

class App
{
public:
    App(std::string const& title, std::size_t width, std::size_t height);
    ~App();

    bool running();

    void handleInput();
    void tick();
    void render();

protected:
    SDL_Window*   m_Window;
    SDL_GLContext m_GLContext;

    bool m_CloseRequested = false;
};
