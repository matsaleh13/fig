# Fig 
A Generalized and Extensible Configuration Library writtten in Modern C++


## Project Goals
 1. Create the config system I would like to use.
 1. Learn to code modern C++.
 1. Use to develop a portfolio of my current work.
 1. Learn cross-platform dev in C++.
 1. Learn plugin dev in C++.
 1. Learn component-based dev in C++.

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
    * Windows Registry
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
    * Read and write config data.



## Development Considerations
 1. Develop on Windows and Linux in parallel (i.e. containers/WSL)
 1. TDD.
 1. Git, but not GitHub (private repo to start).
 1. Build with clang on all platforms.
 1. Use 3rd party libs for basic functionality.
 1. See Boost project for structure ideas.

## 3rd Party Libs to consider
 1. XML - Tiny XML (2)
 1. JSON - taocpp/json https://github.com/taocpp/json
 1. Compression - zlib
 1. Framework - Boost
 1. File system - Cppfs: https://github.com/cginternals/cppfs
 1. Templating - mstch (mustache): https://mustache.github.io/


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