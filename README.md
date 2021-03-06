# Fig 

A Generalized and Extensible Configuration Library writtten in Modern C++

## Project Goals

 1. Create the config system I would like to use.
 1. Develop a professional quality, open-source library in C++, suitable for use in modern C++ games, embedded systems, and other applications.
 1. During this process, I expect to:
    - Learn to code modern C++.
    - Learn cross-platform dev in C++.
    - Learn plugin dev in C++.
    - Learn component-based dev in C++.
    - Learn library dev in C++.

## Features

 1. Universal config semantics, independent of persistence format.
 1. Cross-platform:
    - Windows
    - Linux
    - MacOS and others as possible.
 1. Simple and flexible API(s):
    - Key/value with path-oriented keys.
    - Object-based.
    - Flat, C-style.
    - URI for data source.
 1. Dynamic:
    - Variables.
    - Token substitution.
    - Include files.
 1. Extensible:
    - Pluggable data source provider API.
    - Pluggable input provider API.
    - Pluggable variable provider API.
    - Pluggable output provider API.
 1. Prebuilt data source providers:
    - File.
    - HTTP.
    - Compressed file?
    - sqlite?
    - mmap file?
    - Windows Registry
 1. Prebuilt input (parser) and output (builder) providers: 
    - XML
    - INI
    - Yaml
    - JSON
 1. Prebuilt variable providers:
    - Environment.
    - Programmable.
    - Command-line.
    - Registry.
    - Multi-source.
 1. Other:
    - Scriptable (via wrappers).
    - Portable.
    - Async support.
    - Logging support. (delegate) 
    - Events/delegates (e.g. OnLoaded, OnChanged)
    - Refreshable/requeryable/updateable.
    - Convert from one input type to another output type.
    - Merge multiple input sources.
    - CLI for validation/manipulation/transformation.
    - Support C++ 11 and above.
    - Auto-reload changed files.
    - Read and write config data.

## Development Considerations

 1. Develop on Windows and Linux in parallel (i.e. containers/WSL)
 1. TDD.
 1. Git, but not GitHub (private repo to start).
 1. Builds on all platforms.
 1. Use 3rd party libs as needed for basic functionality.
 1. Support use by exception-free applications to facilitate use in games and embedded applications that don't use them.

## 3rd Party Libs to consider

 1. XML - [Poco](http://pocoproject.org/) | Tiny XML (2)
 1. JSON - [Poco](http://pocoproject.org/) | [taocpp/json](https://github.com/taocpp/json)
 1. Compression - zlib [Poco](http://pocoproject.org/)
 1. Misc utils - [Poco](http://pocoproject.org/)
 1. Network - [Poco](http://pocoproject.org/) | [cpp-netlib](http://cpp-netlib.org/)
 1. Cross-platform utilities - [Poco](http://pocoproject.org/) | [cubiclesoft/cross-platform-cpp](https://github.com/cubiclesoft/cross-platform-cpp)
 1. File system - [Poco](http://pocoproject.org/) | [Cppfs](https://github.com/cginternals/cppfs)
 1. Templating - [mstch (mustache)](https://mustache.github.io/)
 1. Unicode strings - [ICU - International Components for Unicode](http://site.icu-project.org/)
 1. Error Handling - [Outcome 2.0 Library](https://ned14.github.io/outcome/)
 1. Standards Compliance - [Guideline Support Library (GSL)](https://github.com/Microsoft/GSL)

## Project Structure

### Sub-folders

    /fig
        /bin
            /<platform>
        /build
            /<platform>
        /doc
            /<sub-topic>
        /extern
            /<product>
        /include
            /<platform>
        /lib
            /<platform>
        /proj
            /<sub-project>
                /<platform>
        /src
            /<sub-project>
                /<platform>
        /test
            /<sub-project>
                /<platform>

### Sub-folder Details

- [/bin](./bin/README.md)
- [/build](./build/README.md)
- [/doc](./doc/README.md)
- [/extern](./extern/README.md)
- [/include](./include/README.md)
- [/lib](./lib/README.md)
- [/proj](./proj/README.md)
- [/src](./src/README.md)
- [/test](./test/README.md)

## Related Documentation

- [Cross-Platform Notes](./doc/cross-platform.md)
- [Fig Coding Standards and Policies](./doc/coding-standards.md)
- [Fig Development Log](./doc/dev-log.md)

## Resources
