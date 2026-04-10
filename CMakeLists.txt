cmake_minimum_required(VERSION 3.16)

project(TerrainEngine)

include(FetchContent)

FetchContent_Declare(
  range_v3
  GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
  GIT_TAG        0.12.0 
)

FetchContent_MakeAvailable(range_v3)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(TBB REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE src)

target_compile_options(app PRIVATE -std=c++2c)

target_link_libraries(app PRIVATE
    TBB::tbb
    glfw
    range-v3::range-v3  
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

target_compile_definitions(app PRIVATE OUTPUT_DIR="${CMAKE_BINARY_DIR}")