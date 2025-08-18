cmake_minimum_required(VERSION 3.10)
project(SDL_Engine)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/includes)
include_directories(/usr/include/SDL2)

add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data/")

file(GLOB_RECURSE SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)
message(STATUS "Source files:")
foreach(file ${SRC_FILES})
    message(STATUS "  ${file}")
endforeach()

add_executable(engine ${SRC_FILES}
        src/engine/render/renderer.cpp
        includes/renderer.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(sdl2_ttf REQUIRED)

target_link_libraries(engine
        PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
)