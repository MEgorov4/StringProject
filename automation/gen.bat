@echo off

echo ===Generate project files===
conan install . --output-folder=build --build=missing --profile=conanProfiles/gccDebug --profile:b=conanProfiles/gccDebug

cd build

cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake 

copy compile_commands.json .. > nul
cd ..

