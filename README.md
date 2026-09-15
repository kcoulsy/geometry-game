# C++ Project Template

Copy this folder, rename it, then update `APP` in the `Makefile` to the name
of your program.

```bash
cp -R cpp-template my-project
cd my-project
make
make run
```

Requirements: GNU Make and a C++20-capable compiler such as `g++` or `clang++`.

Put implementation files in `src/`. The Makefile automatically finds every
`src/*.cpp` file, compiles its matching object file under `build/`, and links
them into `build/<APP>`.

Useful commands:

```bash
make        # Compile the program.
make run    # Compile, then run it.
make clean  # Remove generated build files.
```

