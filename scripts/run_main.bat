@echo off

if not exist build (
    mkdir build
)
cd build


echo Running cmake ..
cmake ..

echo Build completed.


echo Building project in Release mode..
cmake --build . --config Release

echo Running Main


.\Release\main_executable.exe

cd ..
