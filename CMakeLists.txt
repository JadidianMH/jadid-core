cmake_minimum_required(VERSION 3.10)
project(SDL_Engine)


set(CMAKE_CXX_STANDARD 17)


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


include_directories(${PROJECT_SOURCE_DIR}/includes)

file(GLOB_RECURSE SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)


add_executable(engine ${SRC_FILES})
target_link_libraries(engine ${SDL2_LIBRARIES})