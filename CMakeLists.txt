cmake_minimum_required(VERSION 3.10)
project(Awakening VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_VERSION 5.5)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG ${RAYLIB_VERSION}
    )
  FetchContent_MakeAvailable(raylib)
endif ()

add_executable(Awakening ./src/main.cpp
./src/Game.cpp
./src/Menu.cpp
./src/Player.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
