cmake_minimum_required(VERSION 3.5)

project(JeuEchecs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add GLFW
find_package(glfw3 3.3 REQUIRED)

add_executable(JeuEchecs
    main.cpp
    ChessBoard.cpp
    ChessPiece.cpp
    GameController.cpp
    Texture.cpp

    ChessBoard.h
    ChessPiece.h
    GameController.h
    Texture.h
    stb_image.h
)

# Link libraries
target_link_libraries(JeuEchecs PRIVATE OpenGL::GL glfw)
