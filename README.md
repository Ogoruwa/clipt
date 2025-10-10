# clipt

[![pre-commit.ci status](https://results.pre-commit.ci/badge/github/Ogoruwa/clipt/main.svg)](https://results.pre-commit.ci/latest/github/Ogoruwa/clipt/dev.svg)
[![CMake CI/CD](https://github.com/Ogoruwa/clipt/actions/workflows/cmake.yml/badge.svg)](https://github.com/Ogoruwa/clipt/actions/workflows/cmake.yml)
[![CodeQL](https://github.com/Ogoruwa/clipt/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/Ogoruwa/clipt/actions/workflows/github-code-scanning/codeql)


Scripting language written in C.

## Overview

This is a project I'm working on to understand how programming languages working, and sharpen my C skills.

The end goal is to create a functional, interpreted programming language.

Based on the tutorial at [craftinginterpreters.com](https://craftinginterpreters.com).

CDash link: https://my.cdash.org/index.php?project=Clipt

## Features

- Token
- Lexer
- Interpreter
- REPL
- Error handling

## Tips

- Run all `cmake`, `cpack` and `ctest` related commands from the `build` directory

## Configuration Options

Options can be enabled and disabled when configuring, using the `-D` flag

```shell
   cmake -DEXAMPLE=ON
```

The avaiable options are listed below, in this format -> `OPTIONNAME` (`DEFAULT VALUE`): `DESCRIPTION`

- `BUILD_INTERPRETER` (`ON`): Build the interpreter

- `ENABLE_ASAN` (`OFF`): Enable compilation of address sanitizer

- `ENABLE_CLANG_TIDY` (`OFF`): Enable clang-tidy checks, requires `clang-tidy` on your path

- `CLANG_TIDY_WARNINGS_AS_ERRORS` (`OFF`): Take clang-tidy warnings as errors

- `PACKAGE_SETUPS` (`OFF`): Package `NSIS`, `Innosetup` and `IFW` installers, when using `cpack`

- `PACKAGE_DISTROS` (`OFF`): Generate `RPM` and `DEB` packages, when using `cpack`

## Building

1. Clone this repository and enter the directory

```shell
    git clone https://github.com/Ogoruwa/clipt.git
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
    ctest
```

## Packaging

```shell
    cpack
```


## CTest Script Generation and Usage

Follow the steps below to generate a ctest script for cmake workflows and cdash uploads

- Change to the project's directory

- Configure the project, with the `GENERATE_CTEST_SCRIPT` option enabled. This generates the script as `CTestScript.cmake` in the build directory.

- You can then run the script

    ```shell
        ctest -S build/CTestScript.cmake -DCDASH_MODEL=<YOUR_DASHBOARD_MODEL>
    ```

    Where <YOUR_DASHBOARD_MODEL> is either Continuous (for CI-CD), Experimental (for debugging), Nightly (for daily builds)

### Environment Variables

- `CDASH_TOKEN`: The token to use for authentication

### Configuration Options

- `CTEST_UPDATE` (`OFF`): Whether to run the update step, in order words, retrieve the latest source code
