cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(opengl-skeleton-2)

include(cmake/CPM.cmake)

CPMAddPackage("gh:gabime/spdlog@1.8.2")

set(SOURCES
  src/app.cpp
)

if(EMSCRIPTEN)
  list(APPEND SOURCES src/main_emscripten.cpp)
else()
  list(APPEND SOURCES src/main.cpp)
endif()

add_executable(opengl-skeleton-2 ${SOURCES})
target_compile_features(opengl-skeleton-2 PRIVATE cxx_std_20)

if(EMSCRIPTEN)
  message(STATUS "EMSCRIPTEN: 1")
  set_target_properties(opengl-skeleton-2
    PROPERTIES
      OUTPUT_NAME "opengl-skeleton-2"
      SUFFIX ".html"
      LINK_FLAGS "-s WASM=1 -s SINGLE_FILE=1 -s USE_SDL=2 -s FULL_ES2=1"
  )
  target_link_libraries(opengl-skeleton-2 spdlog SDL2)
else()
  CPMAddPackage("gh:libsdl-org/SDL#release-2.0.16")
  target_link_libraries(opengl-skeleton-2 spdlog SDL2::SDL2-static GL GLESv2 EGL)
endif(EMSCRIPTEN)

