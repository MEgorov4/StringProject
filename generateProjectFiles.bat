@echo off

set CC=clang-cl
set CXX=clang-cl
echo Generating project...

conan install . --output-folder=build --build=missing --profile=conanProfileDebug --profile:b=conanProfileDebug

cd build

cmake .. -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake 

copy compile_commands.json .. > nul
cd ..

