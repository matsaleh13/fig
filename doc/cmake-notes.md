# Fig CMake Notes

## Resources
- https://www.codeproject.com/Articles/1181455/A-CMake-tutorial-for-Visual-Cplusplus-developers
- https://cmake.org/cmake/help/v3.7/manual/cmake-variables.7.html
- http://preshing.com/20170511/how-to-build-a-cmake-based-project/
- https://cmake.org/cmake-tutorial/
- https://docs.microsoft.com/en-us/cpp/ide/cmake-tools-for-visual-cpp
- https://www.3dgep.com/cmake-visual-studio-2017/
- https://blogs.msdn.microsoft.com/vcblog/2017/08/25/visual-c-for-linux-development-with-cmake/



## Visual Studio Specific
- CMakeSettings.json contains properties that define certain variables used by CMake. Be **careful**. These are not used by CMake outside of Visual Studio.
  - `"buildRoot"` maps to CMake's `PROJECT_BINARY_DIR` variable.
  - `"installRoot"` maps to CMake's `XXX` variable.
- MSVS uses its own install of CMake, located at 

## General
