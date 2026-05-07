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

# GLAD
add_library(GLAD STATIC external/glad/src/glad.c)
target_include_directories(GLAD PUBLIC external/glad/include)

# Пакеты
find_package(glfw3 REQUIRED)
find_package(TBB REQUIRED)
find_package(OpenMP REQUIRED)

# Все исходники
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Executable — должен быть ДО любых target_* вызовов для него
add_executable(TerrainGen ${SOURCES})

# Include dirs — ПОСЛЕ add_executable
target_include_directories(TerrainGen PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/external/glad/include/glm"
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
        OpenMP::OpenMP_CXX
    )
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(TerrainGen PRIVATE
        GLAD
        glfw
        TBB::tbb
        range-v3::range-v3
        OpenGL::GL
        OpenMP::OpenMP_CXX
    )
endif()

target_compile_definitions(TerrainGen PRIVATE
    OUTPUT_DIR="${CMAKE_BINARY_DIR}"
)