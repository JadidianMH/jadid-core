cmake_minimum_required(VERSION 3.14)
project(SDL_Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ---------- Includes ----------
include_directories(${PROJECT_SOURCE_DIR}/includes)
include_directories(/usr/include/SDL2)

# ---------- Definitions ----------
add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/config/")

# ---------- Sources ----------
file(GLOB_RECURSE ENGINE_SRC_ALL
        ${PROJECT_SOURCE_DIR}/src/engine/*.cpp
)
set(MAIN_CPP ${PROJECT_SOURCE_DIR}/src/engine/main.cpp)
list(REMOVE_ITEM ENGINE_SRC_ALL ${MAIN_CPP})

file(GLOB_RECURSE BINDING_FILES
        ${PROJECT_SOURCE_DIR}/src/bindings/*.cpp
)

# ---------- Dependencies ----------
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(sdl2_ttf REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

# ---------- Engine Core Library ----------
add_library(engine_core SHARED ${ENGINE_SRC_ALL})
set_target_properties(engine_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(engine_core PRIVATE ${PROJECT_SOURCE_DIR}/includes)
target_link_libraries(engine_core
        PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        Python3::Python
)

# ---------- Executable (ELF) ----------
add_executable(engine_exe ${MAIN_CPP})
target_include_directories(engine_exe PRIVATE ${PROJECT_SOURCE_DIR}/includes)
target_link_libraries(engine_exe PRIVATE engine_core
    Python3::Python
)

set_target_properties(engine_exe PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        OUTPUT_NAME "engine"
)


# ---------- Python Module ----------
add_library(engine MODULE ${BINDING_FILES})
set_target_properties(engine PROPERTIES
        PREFIX ""
        OUTPUT_NAME "engine"
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
target_include_directories(engine PRIVATE
        ${Python3_INCLUDE_DIRS}
        /usr/include/python3.13
        ${pybind11_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/includes
)
target_link_libraries(engine
        PRIVATE
        engine_core
        pybind11::module
        Python3::Python
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
)

# ---------- Debug Info ----------
# message(STATUS "Engine core source count: ${ENGINE_SRC_ALL}")
# message(STATUS "Binding files count: ${BINDING_FILES}")
# foreach(f ${ENGINE_SRC_ALL})
#     message(STATUS "  engine_src: ${f}")
# endforeach()
# foreach(f ${BINDING_FILES})
#     message(STATUS "  binding: ${f}")
# endforeach()