cmake_minimum_required(VERSION 3.21)
project(Hexagon)

set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
        )
FetchContent_MakeAvailable(SFML)
add_executable(Project1 main.cpp headers/Board.h implementations/Board.cpp implementations/Display.cpp headers/Display.h implementations/Game.cpp headers/Game.h implementations/Robot.cpp headers/Robot.h implementations/GraphicsParameters.cpp headers/GraphicsParameters.h implementations/HighScores.cpp headers/HighScores.h)
target_link_libraries(Project1 PRIVATE sfml-graphics)