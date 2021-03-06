#pragma once

#include "common.h"

class IDrawable;

class Renderer
{
public:
    Renderer(std::string const& title, std::size_t width, std::size_t height);
    ~Renderer();

    void clear();
    void draw(std::vector<std::unique_ptr<IDrawable>>& drawables);
    void present();

private:
    SDL_Window*   m_Window;
    SDL_GLContext m_GLContext;

    std::size_t m_Width;
    std::size_t m_Height;

    float m_ClearR;
    float m_ClearG;
    float m_ClearB;
};
