# Lunet Programming Language

A simple programming language implementation.

## Building

### Using CMake (Recommended for Linux/macOS)

```bash
# Build using the provided script
./build.sh

# Or manually:
mkdir build
cd build
cmake ..
make
```

### Using the existing Makefile (requires Premake)

```bash
# If you need to regenerate project files
premake5 gmake2

# Then build
make
```

## Running

```bash
./build/Lunet <path_to_lunet_file>
```

For example:
```bash
./build/Lunet ../src/examples/Lunet.lt
```