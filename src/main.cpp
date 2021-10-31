#ifdef WIN32
#define SDL_MAIN_HANDLED 1
#define main             WinMain
#endif

#include "app.h"

int main(int argc, char* argv[])
{
    App app("OpenGL Skeleton 2", 1280, 720);

    while (app.running())
    {
        app.handleInput();
        app.tick();
        app.render();
    }

    return 0;
}
