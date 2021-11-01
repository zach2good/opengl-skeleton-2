# 💀 OpenGL Skeleton 2

A no-fuss skeleton for creating OpenGL applications. Following on from my [2016 OpenGL Skeleton](https://github.com/zach2good/opengl-skeleton).

# Work Log

## Where I spent most of my time

I was quite excited to start up this project, so I spent a long time trying to make sure it could easily target Linux, Windows, and Browser. I've started using CPM.cmake for package manager and it's excellent.

The Windows build in particular took a long time.

As with all code projects I do, I use `.clang-format` and `.clang-tidy` files to keep things clean. I set up basic Linux builds in CI using GitHub Actions.

Once I had a Triangle drawing on all platforms, I refactored the project to be a little cleaner and got to the point where I only needed to adjust logic inside the shaders and `line.h/.cpp`.

I spend a _lot_ of time trying to do the maths that ended up in `utils::getRotatedPoints` by hand, but eventually found a solution online.

After that, a little additional cleanup, removing old code, and then this write-up.

## Given more time, I would...

### Architecture & Build

- Clean up the CMake files. They're a bit all-over-the-place right now.
- Remove GLAD GL loader. Using GLEW has made it irrelevant.
- Shader validation and hot-reloading.
- Move drawing logic out of `line.cpp`, turn it into a data-only representation.
- Stop hard-coding 1280x720 as the resolution. Should also handle resizing.
- I had wanted to experiment using coroutines for this project, but I didn't end up having time.

### Drawing

- Compact all lines into a single draw call. Currently, each line gets its own draw call -> wasteful.
- There are some good resources online for drawing high-quality lines, implementing some/any of these methods would improve quality greatly:
  - https://blog.mapbox.com/drawing-antialiased-lines-with-opengl-8766f34192dc
  - https://www.codeproject.com/Articles/199525/Drawing-nearly-perfect-2D-line-segments-in-OpenGL
  - https://mattdesl.svbtle.com/drawing-lines-is-hard
  - https://vitaliburkov.wordpress.com/2016/09/17/simple-and-fast-high-quality-antialiased-lines-with-opengl/
  - https://gfx.cs.princeton.edu/pubs/Cole_2010_TFM/cole_tfm_preprint.pdf
- A lot of these rely on passing additional attributes to the shader and very little additional work on the CPU.

# Screenshots

## Starting Triangle
![](img/em_triangle.png)

## Line Rendering
![](img/em_lines.png)

## Build

### Windows

```ps
mkdir build
cd build
cmake ..
cmake --build .
.\Debug\opengl-skeleton-2.exe
```

### Browser (via Emscripten on Windows)

```ps
choco install ninja make
mkdir build
cd build
emcmake cmake -G Ninja ..
cmake --build .
emrun .\opengl-skeleton-2.html
```
### Ubuntu 20.04 (via WSL2 on Windows 11)

```bash
sudo apt-get install mesa-common-dev libgles2-mesa-dev
mkdir build
cd build
cmake ..
make
./opengl-skeleton-2
```

### Code dependencies

[CPM.cmake](https://github.com/cpm-cmake/CPM.cmake/tree/v0.34.0) will handle code dependencies at CMake configure time.

## License

[MIT License](LICENSE)
