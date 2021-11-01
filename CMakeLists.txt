cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(opengl-skeleton-2)

include(cmake/CPM.cmake)

CPMAddPackage("gh:gabime/spdlog@1.8.2")

configure_file("${PROJECT_SOURCE_DIR}/shaders/line.frag.hlsl" "${PROJECT_BINARY_DIR}/shaders/line.frag.hlsl" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/shaders/line.vert.hlsl" "${PROJECT_BINARY_DIR}/shaders/line.vert.hlsl" COPYONLY)

set(SOURCES
  src/app.cpp
  src/renderer.cpp
  src/shader.cpp
  src/line.cpp
)

if(EMSCRIPTEN)
  list(APPEND SOURCES src/main_emscripten.cpp)
else()
  list(APPEND SOURCES src/main.cpp)
endif()

add_executable(opengl-skeleton-2 ${SOURCES})
target_compile_features(opengl-skeleton-2 PRIVATE cxx_std_20)

set(SHADER_PATH \"${PROJECT_SOURCE_DIR}/shaders/\")

if(EMSCRIPTEN)
  message(STATUS "EMSCRIPTEN: 1")
  set(SHADER_PATH \"shaders/\")
  set_target_properties(opengl-skeleton-2
    PROPERTIES
      OUTPUT_NAME "opengl-skeleton-2"
      SUFFIX ".html"
      LINK_FLAGS "-s WASM=1 -s SINGLE_FILE=1 -s USE_SDL=2 -s FULL_ES2=1 --preload-file ${PROJECT_BINARY_DIR}/shaders/line.vert.hlsl --preload-file ${PROJECT_BINARY_DIR}/shaders/line.frag.hlsl"
  )
  target_link_libraries(opengl-skeleton-2 spdlog SDL2)

elseif(WIN32)
  message(STATUS "WIN32: 1")
  CPMAddPackage("gh:libsdl-org/SDL#release-2.0.16")

  CPMAddPackage(
    NAME glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
    GIT_TAG f456deace7b408655109aaeff71421ef2d3858c6
  )

  add_library(glad ext/glad/src/glad.c)
  target_include_directories(glad PUBLIC ext/glad/include)

  target_link_libraries(opengl-skeleton-2 spdlog SDL2::SDL2-static libglew_static glad opengl32)
  set_target_properties(opengl-skeleton-2
    PROPERTIES
      LINK_FLAGS "/SUBSYSTEM:WINDOWS"
  )

else() # Linux build
  CPMAddPackage("gh:libsdl-org/SDL#release-2.0.16")
  target_link_libraries(opengl-skeleton-2 spdlog SDL2::SDL2-static GL GLESv2 EGL)
endif()

configure_file (
  "${PROJECT_SOURCE_DIR}/src/path.h.in"
  "${PROJECT_SOURCE_DIR}/src/path.h"
)