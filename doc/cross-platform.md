# Fig Cross-Platform Notes

## Target Platforms
- Windows (all currrently supported variants)
- Linux (test on Ubuntu and RH variants)
- OSX (in theory)
- 64 and 32 bit binaries.

## Target Deployments
- Headers + static libs.
- Headers + shared libs.
- Source code + project files.

## Resources
- https://www.backblaze.com/blog/10-rules-for-how-to-write-cross-platform-code/
- https://stackoverflow.com/questions/45232308/cross-platform-api-development-for-windows-linux-et-al
- https://marketplace.visualstudio.com/items?itemName=VisualCppDevLabs.VisualCforLinuxDevelopment
- https://docs.microsoft.com/en-us/cpp/linux/cmake-linux-project?view=vs-2017
- https://blogs.msdn.microsoft.com/vcblog/2017/04/11/linux-development-with-c-in-visual-studio/
- https://www.codepool.biz/cmake-cc-windows-linux-macos.html
- https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
- [C++ - Unicode Encoding Conversions with STL Strings and Win32 APIs](https://msdn.microsoft.com/en-us/magazine/mt763237.aspx?f=255&MSPPError=-2147217396)
- [Exceptions and Error Handling](https://isocpp.org/wiki/faq/exceptions)
- [Practical C++ Error Handling in Hybrid Environments (2007)](http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/DDJ/2007/0703/070201gs01/070201gs01.html)



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
    - UTF-8, not UTF-16 (windows specific).
    - However, as a library, we may need to support both (or all).
    - Support std::string/char and std::wstring/wchar_t.
- Avoid 3rd party "application frameworks":
    - e.g. Qt
    - If necessary use Boost only.

## Project Considerations
- Use Visual Studio + CMake for both Windows and Linux?
- What about clang?
- Use container for remote Linux target(s), and/or WSL.
- Consider Premake: https://premake.github.io/

## Library Considerations
- Both static (.lib, .a) and dynamic (.dll, .so)





 