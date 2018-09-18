# Fig Dev Log

## `${date} ${time}`

`${log_entry} [${log_entry} ...]`

## 2018.08.26

- Setup Git repo.
- Updated MSVS 2017.
- Installed extensions for MSVS and VSC.
- Created project in MSVS.
- Researched a bit about cross-platform dev and stuff.
- IMO this is a pretty good project to teach me about cross platform library development in C++. 

## 2018.08.29

- Researched cross-platform dev in C++.
- Ideas for project structure.
- Ideas for tool chain.

## 2018.08.30

- Researched CMake
- Chose to use CMake
- Initial CMake setup ongoing.

## 2018.08.31

- Started initial design doc (key abstractions/responsibilities).
- More research:
  1. Third party libraries for various functionality I know I’ll need.
  1. Exception handling pro/con.
  1. Unicode and string types.
  1. Cross-platform best practices.
  1. More CMake
- Boost vs. Poco (Poco wins for me, because higher level, but if I must use Boost for anything then I may switch).
- Documenting everything I can in .md for now.

## 2018-09-01

- Started a coding standards doc.
- More research to inform that:
  1. Error handling/exceptions.
  1. Coding standards to follow or model.
  1. Best practices.
- Thinking about starting a dev log for blog material, or just learning.
- Documenting everything I can in .md for now.

## 2018-09-02

- Started this dev log, with retro entries to the start of the project.
- Added MarkdownLint VS code plugin to improve docs.
- Continued coding standards doc, focusing on:
  1. C++ version
  1. Docs
  1. Cross-platform
  1. Error handling
  1. Memory and resource management
  1. Singletons
  1. Scoping
  1. Exposing types
  1. Compiler Settings
  1. Concurrency
- More research on error handling without exceptions:
  - Exploring the “Either” concept – a templatized return type with pointer semantics that contains a return value OR an error value.
  - Modeled after Rust `Result` type.
  - Inspired by these posts:
    - https://softwareengineering.stackexchange.com/questions/352702/error-handling-considerations
    - https://foonathan.net/blog/2017/12/04/exceptions-vs-expected.html
  - Examples include std::expected (proposed), also Boost.

## 2018-09-03

- Research:
  1. CMake with multiple projects.
  1. Unit testing with CMake.
- Trying integration GoogleTests with CMake. Working through this: [Setting up CMake for Google Test](https://www.testcookbook.com/book/cpp/setting-up-cmake-google-test.html).
- Installed cmake via choco.

## 2018-09-08

- Installed Ninja on dev system via choco.

## 2018-09-15

- Finally got CMakeTools extension for VSCode (mostly) working.
  - Kept getting error: "You do not have a CMakeLists.txt file", even though I did.
  - CMakeTools looks for the CML.txt in the `${workspaceRoot}` folder by default.
  - You can override this in `.vscode/settings.json` with the `cmake.sourceDirectory` property. However, that did not work immediately.
  - I also had to create a VSCode "workspace" file, `fig.code-workspace` in the project root folder. Once I did that, CMakeTools correctly found my CML.txt file in `${workspaceRoot}/src`.
- CMake in some kind of infinite loop because of an error in my `fig/src/test/CMakeLists.txt` file.
  - Temporarily disabled by commenting out the `add_subdirectory(test)` command in the root CML.txt file.
- Also getting repeated debug output for some reason:

```
[cmake] DEBUG INFO FOR Fig...
[cmake] DEBUG INFO FOR Fig...
[cmake] DEBUG INFO FOR Fig...
[cmake] DEBUG INFO FOR Fig...
[cmake] DEBUG INFO FOR Fig...
[cmake] DEBUG INFO FOR Fig...
[cmake] CMAKE_SOURCE_DIR: e:/dev/fig/fig/src
[cmake] CMAKE_SOURCE_DIR: e:/dev/fig/fig/src
[cmake] CMAKE_SOURCE_DIR: e:/dev/fig/fig/src
[cmake] CMAKE_SOURCE_DIR: e:/dev/fig/fig/src
[cmake] CMAKE_SOURCE_DIR: e:/dev/fig/fig/src
[cmake] CMAKE_SOURCE_DIR: e:/dev/fig/fig/src
[cmake] PROJECT_SOURCE_DIR: E:/Dev/Fig/fig/src
[cmake] PROJECT_SOURCE_DIR: E:/Dev/Fig/fig/src
[cmake] PROJECT_SOURCE_DIR: E:/Dev/Fig/fig/src
[cmake] PROJECT_SOURCE_DIR: E:/Dev/Fig/fig/src
[cmake] PROJECT_SOURCE_DIR: E:/Dev/Fig/fig/src
[cmake] PROJECT_SOURCE_DIR: E:/Dev/Fig/fig/src
<snip>

```

## 2018-09-16

- Debugging CMakeFiles.txt strange output (see 2018-09-15)
  - When running CMake via CMakeTools in VSCode, I get the 6 repeated output lines for every operation.
  - When running CMake via MSVS integration, I get (mostly) correct behavior.
- Did same configuration in a nearly empty project. 
  - At first, with CMakeLists.txt in the project root, only one line output per operation.
  - Then, created a src subfolder and moved CMakeLists.txt and the .cpp file into it.
  - To get CMakeTools to build, had to modify workspace settings cmake.sourceDirectory as before, AND create a "workspace" for the folder.
  - However, when that was done, I started getting double line output (not 6 like with fig tho). Except, that seemed to happen only once; subsequent configures didn't cause it.
- Came back to the fig project proper, after restarting VSCode. This time the duplicate output didn't happen. Restart FTW?
- I think for now I'll forego doing this in MSVS as well as VSCode. Certain paths don't agree, and it's just confusing.
  - Deleted the CMakeSettings.json file (from MSVS).
  - Deleted the spurious folders that MSVS created.
- Added back the `add_subdirectory` calls one by one, leaving the `test` one for last. All was well, until I re-added it, then infinite looping again.
- Arg, did a "clean reconfigure" and now I'm getting dupe output again, only in threes this time. However, once again, restarting VSCode fixed it. Feh.
- Looks like the test/CMakeLists.txt code to download the googletests stuff was using the CMAKE_BINARY_DIR, but it was taking from a project that had everything in the root dir, so when I moved it into a subdir, CMAKE_BINAR_DIR was incorrect. Elsewhere, CMake used the PROJECT_BINARY_DIR by default (relative paths, actually), and calling CMake from the generated code ended up creating the infinite loop. 
- Fixed this by replacing CMAKE_BINARY_DIR with PROJECT_BINARY_DIR, and it works.
- Still other config errors, but not related. WIP.

## 2018-09-17

- Finally got GTests setup to configure with CMakeLists.txt in my project, yay.
- Followed examples at [Setting up CMake for Google Test](https://www.testcookbook.com/book/cpp/setting-up-cmake-google-test.html) and [Unit Test with Google Test](https://www.testcookbook.com/book/cpp/unit-test-with-google-test.html).
- Created dumb little test in fig-util-test.
- Following advice from CMakeTools docs, [Target Debugging and Launching](https://vector-of-bool.github.io/docs/vscode-cmake-tools/debugging.html#debugging), I clicked on the little bug in the taskbar, then selected `fig-util-test` from the drop-down list at the top of VSCode. It worked:

```bash
  -------------------------------------------------------------------
  You may only use the C/C++ Extension for Visual Studio Code with
  Visual Studio Code, Visual Studio or Visual Studio for Mac software
  to help you develop and test your applications.
  -------------------------------------------------------------------
  Loaded 'E:\Dev\Fig\fig\build\test\fig-util-test\fig-util-test.exe'. Module was built without symbols.
  Loaded 'C:\Windows\System32\ntdll.dll'. Cannot find or open the PDB file.
  Loaded 'C:\Windows\System32\kernel32.dll'. Cannot find or open the PDB file.
  Loaded 'C:\Windows\System32\KernelBase.dll'. Cannot find or open the PDB file.
  Loaded 'C:\Windows\System32\apphelp.dll'. Cannot find or open the PDB file.
  Loaded 'C:\Windows\System32\ucrtbase.dll'. Cannot find or open the PDB file.
  Loaded 'C:\Windows\System32\msvcp140.dll'. Cannot find or open the PDB file.
  Loaded 'C:\Windows\System32\vcruntime140.dll'. Cannot find or open the PDB file.
  The thread 15996 has exited with code 0 (0x0).
  [==========] Running 1 test from 1 test case.
  [----------] Global test environment set-up.
  [----------] 1 test from add_function
  [ RUN      ] add_function.Two_Plus_Two_Equals_Four
  [       OK ] add_function.Two_Plus_Two_Equals_Four (0 ms)
  [----------] 1 test from add_function (0 ms total)

  [----------] Global test environment tear-down
  [==========] 1 test from 1 test case ran. (1 ms total)
  [  PASSED  ] 1 test.
  Loaded 'C:\Windows\System32\kernel.appcore.dll'. Cannot find or open the PDB file.
  Loaded 'C:\Windows\System32\msvcrt.dll'. Cannot find or open the PDB file.
  Loaded 'C:\Windows\System32\rpcrt4.dll'. Cannot find or open the PDB file.
  The thread 22640 has exited with code 0 (0x0).
  The thread 25992 has exited with code 0 (0x0).
  The program '[14304] fig-util-test.exe' has exited with code 0 (0x0).
```

- Building without symbols might be a problem, but I'll deal for now.