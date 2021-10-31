#include <emscripten.h>
#include "app.h"

App app("OpenGL Skeleton 2", 1280, 720);

void main_loop()
{
    app.handleInput();
    app.tick();
    app.render();
}

int main()
{
    emscripten_set_main_loop(main_loop, 0, true);
    return 0;
}
