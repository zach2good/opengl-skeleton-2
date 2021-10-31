cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(opengl-skeleton-2)

include(cmake/CPM.cmake)

CPMAddPackage("gh:gabime/spdlog@1.8.2")

set(SOURCES
  src/main.cpp
)

add_executable(opengl-skeleton-2 ${SOURCES})
target_compile_features(opengl-skeleton-2 PRIVATE cxx_std_20)
target_link_libraries(opengl-skeleton-2 spdlog)
