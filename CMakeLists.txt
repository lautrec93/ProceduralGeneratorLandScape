cmake_minimum_required(VERSION 3.16)

project(TerrainEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(TBB REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE src)

target_link_libraries(app PRIVATE TBB::tbb)