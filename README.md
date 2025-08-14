# clipt

[![pre-commit](https://github.com/Ogoruwa/clipt/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/Ogoruwa/clipt/actions/workflows/pre-commit.yml)
[![CMake CI/CD](https://github.com/Ogoruwa/clipt/actions/workflows/cmake.yml/badge.svg)](https://github.com/Ogoruwa/clipt/actions/workflows/cmake.yml)
[![Documentation](https://github.com/Ogoruwa/clipt/actions/workflows/documentation.yml/badge.svg)](https://github.com/Ogoruwa/clipt/actions/workflows/documentation.yml)
[![CodeQL](https://github.com/Ogoruwa/clipt/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/Ogoruwa/clipt/actions/workflows/github-code-scanning/codeql)


Scripting language written in C.

## Overview

This is a project I'm working on to understand how programming languages working, and sharpen my C skills.

The end goal is to create a functional, interpreted programming language.

Based on the tutorial at [craftinginterpreters.com](https://craftinginterpreters.com).

## Features

- Interpreter
- REPL
- Lexer

## Tips

- Execute all cmake related under the `build` directory

- Tests are built by default, to disable, use the cmake option (when configuring) `-DBUILD_TESTING=OFF`

## Installation

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

- Use the cmake option `-DPACKAGE_SETUPS=ON` to package `NSIS`, `Innosetup` and `IFW` installers.

- Use the cmake option `-DPACKAGE_DISTROS=ON` to generate `RPM` and `DEB` packages.

```shell
    cd build
    cpack
```
