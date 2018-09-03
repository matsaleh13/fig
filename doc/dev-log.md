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



