# Fig Cross-Platform Notes

## Target Platforms

- Windows (all currrently supported variants)
- Linux (test on Ubuntu and RH variants)
- OSX (in theory)


## Resources

- https://www.backblaze.com/blog/10-rules-for-how-to-write-cross-platform-code/
- https://stackoverflow.com/questions/45232308/cross-platform-api-development-for-windows-linux-et-al
- https://marketplace.visualstudio.com/items?itemName=VisualCppDevLabs.VisualCforLinuxDevelopment
- https://docs.microsoft.com/en-us/cpp/linux/cmake-linux-project?view=vs-2017



## Guiding Principles

- Simultaneously Develop for Different Platforms
    - See https://www.backblaze.com/blog/10-rules-for-how-to-write-cross-platform-code/
    - In practice, build regularly on both Windows and one Linux target.
    - Use standard 'C' types, not platform specific types:
        - e.g. `unsigned long` not `DWORD`
- Use only built-in #ifdef compiler flags:
    - e.g. `#ifdef _WIN32`, not `_MY_WIN32`
- Hide platform-specific code behind simple "base" APIs:
    - Abstract interfaces for high level stuff.
    - Concrete classes with platform-specific .cpp files, preferably in platform-specific folders.
    - Use PIMPL pattern.
- Use Unicode.
    - UTF-8, not UTF-16 (windows specific)
    - TODO: what character type? char or wchar_t?
- Avoid 3rd party "application frameworks":
    - e.g. Qt
    - If necessary use Boost only.

## Project Considerations
- Use Visual Studio + CMake for both Windows and Linux?
- What about clang?
- Use container for remote Linux target(s).
- Consider Premake: https://premake.github.io/




