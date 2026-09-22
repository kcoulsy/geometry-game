cmake_minimum_required(VERSION 3.20)

project(geometry_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(app ${SOURCES})
target_link_libraries(app PRIVATE SFML::Graphics)
