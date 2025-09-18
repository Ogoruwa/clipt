# clipt

[![pre-commit.ci status](https://results.pre-commit.ci/badge/github/Ogoruwa/clipt/main.svg)](https://results.pre-commit.ci/latest/github/Ogoruwa/clipt/dev.svg)
[![CMake CI/CD](https://github.com/Ogoruwa/clipt/actions/workflows/cmake.yml/badge.svg)](https://github.com/Ogoruwa/clipt/actions/workflows/cmake.yml)
[![CodeQL](https://github.com/Ogoruwa/clipt/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/Ogoruwa/clipt/actions/workflows/github-code-scanning/codeql)


Scripting language written in C.

## Overview

This is a project I'm working on to understand how programming languages working, and sharpen my C skills.

The end goal is to create a functional, interpreted programming language.

Based on the tutorial at [craftinginterpreters.com](https://craftinginterpreters.com).

## Features

- Token
- Lexer
- Interpreter
- REPL
- Error types

## Tips

- Execute all `cmake` related commands under the `build` directory

## Configuration Options

Options can be enabled and disabled when configuring, using the `-D` flag

```shell
   cmake -DEXAMPLE=ON
```

The avaiable options are listed below, in this format -> `OPTIONNAME` (`DEFAULT VALUE`)

- `BUILD_INTERPRETER` (`ON`): Build the interpreter

- `ENABLE_CLANG_TIDY` (`OFF`): Enable clang-tidy checks, requires `clang-tidy` on your path

- `CLANG_TIDY_WARNINGS_AS_ERRORS` (`OFF`): Take clang-tidy warnings as errors

- `PACKAGE_SETUPS` (`OFF`): Package `NSIS`, `Innosetup` and `IFW` installers, when using `cpack`

- `PACKAGE_DISTROS` (`OFF`): Generate `RPM` and `DEB` packages, when using `cpack`

## Building

1. Clone this repository and enter the directory

```shell
    git clone https://github.com/Ogoruwa/clipt.git`
    cd clipt
```

2. Configure the project using cmake

```shell
    mkdir build
    cd build
    cmake ..
```

3. Build the project. Files wil be generated under `bin` and `lib` folders.

```shell
    cmake --build . --target all --
```

## Testing

```shell
    cd build
    ctest
```

## Packaging

```shell
    cd build
    cpack
```
