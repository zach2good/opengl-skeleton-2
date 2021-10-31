#pragma once

#include "renderer.h"

class IDrawable
{
public:
    virtual void draw(Renderer& renderer) = 0;
};
