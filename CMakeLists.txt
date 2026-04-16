cmake_minimum_required(VERSION 3.16)

project(TerrainGen LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    range_v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(range_v3)

add_library(GLAD STATIC external/glad/src/glad.c)
target_include_directories(GLAD PUBLIC external/glad/include)

find_package(glfw3 REQUIRED)
find_package(TBB REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(TerrainGen ${SOURCES})

target_include_directories(TerrainGen PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

if(APPLE)
    target_link_libraries(TerrainGen PRIVATE
        GLAD
        glfw
        TBB::tbb
        range-v3::range-v3
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(TerrainGen PRIVATE
        GLAD
        glfw
        TBB::tbb
        range-v3::range-v3
        OpenGL::GL
    )
endif()

target_compile_definitions(TerrainGen PRIVATE
    OUTPUT_DIR="${CMAKE_BINARY_DIR}"
)