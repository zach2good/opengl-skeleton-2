#pragma once

#include "common.h"

class Renderer;
class IDrawable;

class App
{
public:
    App(std::string const& title, std::size_t width, std::size_t height);
    ~App();

    bool running() const;

    void handleInput();
    void tick();
    void render();

protected:
    std::unique_ptr<Renderer>               m_Renderer;
    std::vector<std::unique_ptr<IDrawable>> m_Drawables;

    bool m_CloseRequested = false;
};
