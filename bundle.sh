#!/bin/bash

cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

mkdir -p TerrainGen.app/Contents/MacOS
mkdir -p TerrainGen.app/Contents/libs
mkdir -p TerrainGen.app/Contents/assets

cp build/TerrainGen TerrainGen.app/Contents/MacOS/
cp -r src/assets/ TerrainGen.app/Contents/assets/

cp /opt/homebrew/opt/glfw/lib/libglfw.3.dylib TerrainGen.app/Contents/libs/
cp /opt/homebrew/opt/tbb/lib/libtbb.12.dylib TerrainGen.app/Contents/libs/
cp /opt/homebrew/opt/llvm/lib/libomp.dylib TerrainGen.app/Contents/libs/

install_name_tool -change /opt/homebrew/opt/glfw/lib/libglfw.3.dylib \
    @executable_path/../libs/libglfw.3.dylib \
    TerrainGen.app/Contents/MacOS/TerrainGen

install_name_tool -change /opt/homebrew/opt/tbb/lib/libtbb.12.dylib \
    @executable_path/../libs/libtbb.12.dylib \
    TerrainGen.app/Contents/MacOS/TerrainGen

install_name_tool -change /opt/homebrew/opt/llvm/lib/libomp.dylib \
    @executable_path/../libs/libomp.dylib \
    TerrainGen.app/Contents/MacOS/TerrainGen

echo "Done: TerrainGen.app"
