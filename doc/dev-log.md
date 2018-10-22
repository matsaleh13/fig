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

```cmake
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

```cmake
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

- Installed `llvm` via chocolatey to get clang-format. Also installed the VSCode clang-format extension.
- Started writing the fig-util Result<T,E> class, using TDD and GTest. Whee!
- Oh no, suddenly I'm getting duplicate output again, arg. This time restarting VSCode didn't fix it.
- Also, got this error:

  `CMake Error: CMake can not determine linker language for target: fig-util`

- According to [StackOverflow](https://stackoverflow.com/questions/11801186/cmake-unable-to-determine-linker-language-with-c), this was because all I have in that library is a header file, no .cpp.
- The fix is to use the `set_target_properties` command to explicitly set the language:

    `set_target_properties(hello PROPERTIES LINKER_LANGUAGE CXX)`

- Making more progress, until I hit another error, this time linker:

```bash
[build] LINK : fatal error LNK1181: cannot open input file 'fig-util\fig-util.lib'
[build] ninja: build stopped: subcommand failed.
[build] Build finished with exit code 1
```

- This one is for another day.

## 2018-09-18

- Yesterday's linker error was caused by the fact that the `fig-util` "library" has only one file, a .h file. Doh, it can't be linked because it produces no output at build time.
  - Solution was to treat it as a "header-only" library, and configure it using CMake's `INTERFACE` library option:

  ```cmake
    add_library(fig-util INTERFACE)
  ```

- In other news, I've been confused by VSCode output shown below when running my tests:

```vscode
  [build] Starting build
  [proc] Executing command: "C:\Program Files\CMake\bin\cmake.EXE" --build e:/dev/fig/fig/build --config Release --target fig-util-test -- -j 10
  [build] ninja: no work to do.
  [build] Build finished with exit code 0
```

- Turns out this was happening because a test was failing, but VSCode didn't bring the debug console tab into focus.
  - When I manually switched to that tab, I saw:

  ```vscode
    [==========] Running 2 tests from 1 test case.
    [----------] Global test environment set-up.
    [----------] 2 tests from result_class
    [ RUN      ] result_class.create_result_with_int_value
    [       OK ] result_class.create_result_with_int_value (0 ms)
    [ RUN      ] result_class.create_result_with_bool_error
    E:\Dev\Fig\fig\src\test\fig-util-test\fig-util-test.cpp(15): error: Expected equality of these values:
      r.value()
    E:\Dev\Fig\fig\src\test\fig-util-test\fig-util-test.cpp(15): error: Expected equality of these values:
      r.value()
        Which is: -2
      false    Which is: -2
      false
    [  FAILED  ] result_class.create_result_with_bool_error (1 ms)
    [----------] 2 tests from result_class (1 ms total)

    [----------] Global test environment tear-down
    [==========] 2 tests from 1 test case ran. (1 ms total)
    [  PASSED  ] 1 test.
    [  FAILED  ] 1 test, listed below:
    [  FAILED  ] result_class.create_result_with_bool_error

    1 FAILED TEST
  ```

  - So, yay! Tests FTW!
- Decided I needed more CMake debug output so refactored my `debug_message()` one into `debug_boilerplate()`, and created a new `debug_message` that takes an argument and prepends the debug info to it. Now `debug_boilerplate()` calls that. Better.
- Fleshed out the Result<T, E> implementation some more, with more TDD.
- Added -Wall compiler flag to the project, downgrading to -W3 only for GTests proper, and re-enabled -Wall for specific tests.
- Starting to think about how to implement support for building with both exceptions and without.

## 2018-09-22

- Implemented ResultError exception for handling unchecked results.
- Added tests for unchecked results.
- TODO: need an alternative for exception-free code.
- Created Error class for encapsulating rich error information for later reporting. Intended to be the default E template argument for Result<T, E>.
- Created string formatting helper functions.

## 2018-09-23

- Implemented two versions of string formatter helper functions:
  - One takes a std::string& and returns a std::string. This one uses a stack buffer if small, otherwise allocates one internally.
  - The other takes a const char array and returns a std::string. This one uses a stack buffer only.
  - Both use a MIN_BUF_SIZE constant to set the min stack buffer size, but may use a larger one if needed.
- Implemented tests for both functions:
  - Testing smaller format string.s
  - Special test fixture to test larger strings (exceeding MIN_BUF_SIZE).
- Having trouble testing with the large strings, because I can't see whether they're initialized right, and I can't get the debugger running in VScode atm.

## 2018-09-24

- I think I figured out the problem with the string_helpers tests:
  - My test large strings, used in the `StringHelpersLargeBufferFixture` class, contained a `\0` from where I failed to exclude it from the `memcpy` call I used to initialize the buffers.

## 2018-09-25

- String formatting tests now failing with large buffer, but for a different reason:
  - The generated formatted string gets larger as characters are inserted. 
  - But, the test string (intended to represent the final formatted value), doesn't, since I memcpy'ed the literal string into the (X-padded) buffer without increasing the size.
  - The size difference is equivalent to the number of chars inserted into the formatting tokens minus the number of characters that make up the formatting tokens.
  - Bottom line, the code is working perfectly, but I haven't designed the test correctly to verify it. Doh :|
- Fixed this by adding a param to the init_format() setup function, to pass a size_t equal to the delta between the format string and the expected size of the formatted string, in order to account for the growth of the test string.

## 2018-09-29

- Got macros to compile, finally:
  - Changed from this:

  ```c++
  #define FORMAT_STRING(msg, ...) \
    (fig::util::string_format(msg, __VA_OPT__(,) __VA_ARGS__));

  ```

  - to this:

  ```c++
  #define FORMAT_STRING(msg, ...) \
    (fig::util::string_format(msg, __VA_ARGS__))

  ```

  - Not sure why that fixed it though. I think C++ 11 supports `__VA_OPT__`. I'll probably find out soon enough ;).
- Started implementing the FigKey class:
  - At first thought I wanted to make it an abstract interface for extensibility. But IMO that's not really necessary, and adds vtable overhead to something that should be as lightweight as possible.
  - I did make it a template, taking a TString argument. This allows use of either std::string or std::wstring, since IMO that is still an open question, at least on Windows.
  - Also made a `std::hash<FigKey<TString>>` specialization.
  - Researched key requirements here: [C++ unordered_map using a custom class type as the key](https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key)
  - Also need to make it usable in `std::map` as well (TODO).
  - Also want to give it URI semantics.
- Looking into integrating [Poco](https://github.com/pocoproject) library (for URI).
- This forced me to start thinking about C++ package manager(s) to use:
  - [Conan](https://conan.io/)
  - [Vcpkg](https://github.com/microsoft/vcpkg)
  - Neither is available via Chocolatey.
  - Is this too much? Should I just use git?
  - To be continued.
- Decided I don't need to deal with this for now. I'll just flesh out the interface of the FigKey and implement key use cases for now. I'll add in the URI semantics when it's needed. Heh... or if.

## 2018-09-30

- Implemented `fig::util::tolower` helper to convert a `basic_string<T>`:
  - Unfortunately, it can't return; it must modify an in/out param to minimize copies.
- Used `fig::util::tolower` to init the FigKey::m_name.
  - Unfortunately, because `fig::util::tolower` doesn't return, I must call it in the ctor body.
- Trying to write [GTest Typed tests](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#typed-tests) for FigKey that handle multiple type parameters for the string type:
  - Unfortunately, I'm using string literals for test data, and with std::basic_string types, I can't think of a way to generically use the right literal type (e.g. "foo" vs L"foo"), based on my FigKey type param.
  - Finally figured it out, using template specialization, w00t. I simply created two methods of the templatatized fixture class to return the strings I wanted, with the return type specified by the template:

  ```C++
  template<TChar>
  class Fixture // gtest blah
  {
    const TChar* input_name();
    const TChar* test_name();
  }
  ```

  Then I specialzed each of them for `char` and `wchar_t` types:

  ```C++

  template<>
  const char* Fixture<char>::input_name() { return "foo"; }

  template<>
  const wchar_t* Fixture<wchar_t>::input_name() { return L"foo"; }

  ```

  After that, the types were driven by these GTest lines:

  ```C++
  using MyTypes = ::testing::Types<char, wchar_t>;
  TYPED_TEST_CASE(FigKeyTypedFixture, MyTypes);

  ```

  Pretty cool!

## 2018-10-11

- Recently learned about move semantics. So much new stuff since C++98! :P Maybe my problem requiring tolower() to take an in/out param is now a non-issue.
  - [How to use move semantics with std::string during function return?](https://stackoverflow.com/questions/12011426/how-to-use-move-semantics-with-stdstring-during-function-return)
  - Even better [C++11 rvalues and move semantics confusion (return statement)](https://stackoverflow.com/questions/4986673/c11-rvalues-and-move-semantics-confusion-return-statement)
  - So, as long as std::basic_string has a move constructor/assignment, we should be good. It's actually automatic, and I don't need to jump through hoops. RVO (return value optimization)  means that if a function returns a non-reference type, it does not incur either copy or move overhead (as an optimization, if possible). If not possible, then if the return type has move semantics, the compiler will invoke that. Only when both RVO fails and there is no move support will the compiler invoke the copy operation. It almost sounds too good to be true.
  
## 2018-10-13

- Resumed iterating on FigKey tests:
  - `operator==()` and `operator<()`
  - TODO: do we need other comparisons? Not for maps, we don't.
  - `std::hash()` overload - had a bit of trouble with template expansion; basically I couldn't see my problem until I typedefed a few things down to a manageable string. Turns out I had done:

    ```c++
    std::hash<KeyType>(myKey)();
    ```

  - instead of:

    ```c++
    std::hash<KeyType>()(myKey);
    ```
- Started working on FigValue:
  - Templatized class for native type (probalby some kind of basic_string<T>).
  - Template-specialized conversion versions of get<T>().
  - Iterating on tests.
  - Lots of template related compiler errors.
  - WIP.

## 2018-10-14

- Continued FigValue implementation.
- Having issues with template specialization:
  - Learned that a template class with a template member function cannot partially specialize the template member function.
  - Workaround is to add another level of indirection (of course) by creating a template struct(class) taking both template params, and then declaring a function in terms of both of the template params.
  - Example:

  ```c++
    template <typename T>
    class Foo {
    public:
      template <typename R>
      R foo ();
    };

    // Illegal
    template<typename T, int>
    int Foo<T>::foo<int>();

    // OK
    template<typename T>
    template<typename R>
    R Foo<T>::foo<R>() {
      return FooHelper<T>::help_foo<R>();
    }

    template<typename T, typename R>
    struct FooHelper {
      static R help_foo();
    };

    // specialized for int
    template<typename T>
    struct FooHelper<T, int> {
      static int help_foo();
    }

  ```

  - Added tests for all combinations of FigValue<TValue> in std::string, std::wstring with conversions for [un]signed int, long, and float/double/long double.
- Trying to be more consistent with template param names, now e.g. TValue, TError, TResult instead of T, E, R. 
- Also thinking it's good to have a using value_type = TValue in at least FigKey and FigValue.

## 2018-10-20

- Switched back to C++ 14, because reasons.
- Looking into FigValue conversions between char and wchar_t:
  - Using the std::mbsrtowcs/wcsrtombs variants (instead of the non-r ones) for thread safety.
  - Getting compiler warning (ergo, failure) on Windows:

  ```shell
  warning C4996: 'wcsrtombs': This function or variable may be unsafe. Consider using wcsrtombs_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
  ```

  - Seems the standard C++ implmentation doesn't have a "safe" version, but the C implementation does.
  - I don't want to use Windows-specific implementations, nor C if I can avoid it. Bah.
  - Ended up choosing the C implementation as the lesser of the evils. Wrapped it in some static functions in string_helpers.h, with tests. Works.
  - NOTE: for some reason these functions can't be constexpr because string and wstring "aren't literal types". Well I call BS on that, becuase other functions that take those types in that same file are constexpr. TODO: investigate.

## 2018-10-21

- Refactored the `FigValueConverter` out of `fig_value.h` and into its own header in `fig-util`.
- Also renamed it to `StringConverter`.
- Wrote dedicated test file: `string_converter-test.cpp`, and migrated much of the tests from `fig_value-test.cpp` to it, since the StringConverter is doing most of that work.
- Pulling my hair out because of a compiler error (that first showed up before the refactor):

  ```shell

  [build] E:\Dev\Fig\fig\src\test\fig-util-test\string_converter-test.cpp(87): error C2039: 'convert_safe': is not a member of 'fig::util::StringConverter<StringType,int>'
  [build] E:\Dev\Fig\fig\src\test\fig-util-test\string_converter-test.cpp(84): note: see declaration of 'fig::util::StringConverter<StringType,int>'

  ```

  - However, tell me where `convert_safe` isn't declared, dammit:

  ```c++
  template <typename TValue, typename TRValue>
  struct StringConverter {

    constexpr static TRValue convert(const TValue& value);

    // Exception safe version.
    constexpr static Result<TRValue, Error> convert_safe(const TValue& value) noexcept {
      try {
        return convert<TRValue>(value);
      } catch (std::exception e) {
        return FIG_ERROR("Invalid conversion of value: [%s]", e.what());
      }
    }
  };
  ```

  - After much debugging, I finally figured out that it was (incomplete) template specialization that was causing the error. 
  - The StringConverter<>::convert_safe() had an implementation already, so I didn't consider that at all. However, experimenting showed me that the generic implementation wasn't being called at all. I had to write a specialized version for <TValue, int> to get it to compile. 
  - Not sure why the generic implementation wasn't being called, because, IMO the signature should have matched.
  - Could it be that, because I had specialized the convert() method, I also had to specialize the convert_safe() one? TODO: look into this some more.