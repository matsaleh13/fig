# Fig Coding Standards and Policies

## General Guidelines

- Use an existing standard that has predefined tool-based enforcement via clang-format or similar tool set. That is, one of:
  - [WebKit A style complying with WebKit’s style guide](http://www.webkit.org/coding/coding-style.html)
    - Current first choice.
    - Pro: Simple, common-sense policies that should not require much customization.
    - Con: Implies acceptance of Singleton Pattern.
    - Con: may be Windows-specific (#pragma once advocacy).
  - [Google A style complying with Google’s C++ style guide](https://google.github.io/styleguide/cppguide.html)
    - Current second choice.
    - Pro: comprehensive and precise.
    - Pro: consistent with exception-free coding style.
    - Pro: prohibits static storage.
    - Con: wordy.
    - Con: requires non-standard .cc extension for source files.
  - [LLVM A style complying with the LLVM coding standards](http://llvm.org/docs/CodingStandards.html)
  - [Chromium A style complying with Chromium’s style guide](http://www.chromium.org/developers/coding-style)
  - [Mozilla A style complying with Mozilla’s style guide](https://developer.mozilla.org/en-US/docs/Developer_Guide/Coding_Style)
- If absolutely necessary, modify the existing standard using the most specific changes possible.

## C++ Standard Version

- All Fig code should target C++ 14.

## Documentation

- All Fig text-based documents are to be written using GitHub-flavored Markdown.
- All Fig text-based documents are expected to pass validation by [MarkdownLint](https://marketplace.visualstudio.com/items?itemName=DavidAnson.vscode-markdownlint) (or one of its alternates) with standard rules.
- All source code and header comments are to support dOxygen-style comments.

## Cross-Platform

- All Fig deployable libraries and internal plugins must support all cross-platform targets identified in [Fig Cross-Platform Development](./cross-platform.md).
- All externally-developed plugins must either support all cross-platform targets or clearly identify the specific platforms they do support, preferably at both compile-time and runtime.

## Error Handling

- All Fig deployable libraries should be safe to compile with `-fno-exceptions` or equivalent, where "safe" means std::terminate instead of invalid program state.
- Don't throw or catch exceptions (unfortunately).
  - This is so that Fig can be used in projects that do not use or explicitly disable exceptions, such as games and embedded applications.
- Before calling any library function (e.g. `std::`) code that throws exceptions, test for the error conditions first and don't call it.
- Consider using exception-free implementations of `std::`.
- Known limitations:
  - Any call to std:: function that throws will cause std::terminate.
- Consider wrapper interfaces that throw as an alternate for consumers who prefer it.
- Consider implementing a `Return<T E>` abstraction as described in [Exceptions vs expected: Let's find a compromise](https://foonathan.net/blog/2017/12/04/exceptions-vs-expected.html); also: [Outcome](https://ned14.github.io/outcome/) (NOTE: https://lists.boost.org/boost-announce/2017/06/0510.php)

## Object Initialization

- Prefer the "Resource-acquisition is initialization" (RAII) idiom wherever possible.
  - NOTE: Lack of support for exceptions may make this problematic.
- When RAII is not possible because of lack of exception support, then init as much as possible in the ctor, and supplement with a separate `Init()` method that supports the Fig [Error Handling](#Error_Handling) policy.
- When using a separate `Init()` method, use the `InitOnFirstUsePolicy` abstraction.

## Memory and Resource Management

- Do not use raw pointers. Use `std::shared_ptr` or `std::unique_ptr` and related `std::` features.
- Do not call `new` or `delete`. Use `std::make_shared<T>` or `std::make_unique<T>` and related `std::` features.
- Prefer stack allocation over heap allocation wherever possible.
- Avoid unnecessary object copies wherever possible.

## Singletons

- Do not use the Singleton Pattern in Fig development.

## Scoping

- Use namespaces instead of nested public class declarations to scope types.

## Exposing Types

- Do not expose non-standard external or platform-specific types in Fig public class or function interfaces, including public members that are not exposed to consumers of a Fig library. For example, if you use a third party library `FooLib`, which declares a type `FooLib::Bar`, do not declare any public class members in terms of that type.

  // BAD
  class MyClass
  {
  public:
    void setBar(FooLib::Bar);
  private:
    FooLib::Bar m_bar;
  }

- Exception: Constructors of classes that are not exported to consumers of a Fig library may declare parameters having non-standard external types in order to encapsulate the external types via wrapper classes. For example, you could declare an internal class MyBar with a ctor that takes FooLib::Bar as an argument.

  // OK
  class MyBar
  {
  public:
    MyBar(const FooLib::Bar&);
  }

  class MyClass
  {
  public:
    void setBar(const MyBar&);
  private:
    MyBar m_bar;
  }

## Compiler Settings

- Use the highest warning level practical (on Windows, that's at least level 3).
- Treat all warnings as errors.
- Address specific exceptions in file scope using #pragmas.

## Concurrency

- All Fig deployable libraries should be thread safe or provide optional thread-safe implementations.
- No Fig deployable library may create a new thread, thread pool, or executor.
- Consider using async semantics where appropriate, or writing alternate async implementations for sync functions.

## Testing

- All Fig classes and functions should have unit tests.
- Exception: trivial cases that cannot fail, such as getters, and possibly certain functions that are frequently called during routine execution of other code.
- Where possible, all units should be tested in isolation, using mocks or related techniques as necessary.

## Commit Policy

- All Fig code must pass static analysis before committing.
- All Fig code must compile without errors before committing.
- All Fig tests must pass before committing.

## Resources

- [Mozilla Coding Style Guide](https://developer.mozilla.org/en-US/docs/Mozilla/Developer_guide/Coding_Style#Naming_and_Formatting_code)
- [lefticus/cppbestpractices](https://github.com/lefticus/cppbestpractices)
- [lefticus/codingstandards-0-automatedanalysis.md](https://gist.github.com/lefticus/10191322#file-codingstandards-1-style-md)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html#introduction)
- [Exceptions and Error Handling](https://isocpp.org/wiki/faq/exceptions)
- [Practical C++ Error Handling in Hybrid Environments (2007)](http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/DDJ/2007/0703/070201gs01/070201gs01.html)
- [Exceptions vs expected: Let's find a compromise](https://foonathan.net/blog/2017/12/04/exceptions-vs-expected.html) for more information.
- [Outcome 2.0 Library](https://ned14.github.io/outcome/)
- [Handling STL errors without exceptions](https://code-examples.net/en/q/3b0ee3)