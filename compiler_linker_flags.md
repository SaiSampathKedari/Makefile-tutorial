# C++ Compilation and Linking: Flags, Targets, and Fundamentals for Writing Makefiles

## These are the 4 essential stages that convert C++ source code into an executable.

### **1. Preprocessing**
Expands `#include`, `#define`, and macros; removes comments; produces an intermediate `.i` file.

```bash
g++ -E source.cpp -o source.i
```

### 2. **Compilation**
Converts preprocessed code into assembly (`.s` file).

```bash
g++ -S source.i -o source.s
```

### 3. **Assembly**
Converts assembly into machine code (`.o` object file).

```bash
g++ -c source.s -o source.o
```

### 4. **Linking**
Combines object files and libraries into a final executable.

```bash
g++ source1.o source2.o -o output
```

### 📋 Summary Table

| Stage         | Flag   | Input    | Output      |
|---------------|--------|----------|-------------|
| Preprocessing | `-E`   | `.cpp`    | `.i`        |
| Compilation   | `-S`   | `.i`      | `.s`        |
| Assembling    | `-c`   | `.s`      | `.o`        |
| Linking       | (none) | `.o`      | executable  |

--- 



## Using Libraries with g++

### **1. Library Naming Conventions**
- In C++(or C) projects, libraries follow a standard naming rule:
  - A library called `utilities` must be named either `libutilities.so` (for shared libraries) or `libfoo.a` (for static libraries).
  - The `lib` prefix and the `.so` or `.a` suffix are mandatory when creating library files.
- This naming convention is automatically understood by g++ when linking libraries using the `-l` flag.
  - You can just use `-lutilities`, and `g++` will search for `libutilities.so` or `libutilities.a` behind the scenes.
  - ```
    g++ main.o -lutilities -o output
    ```
  - This works because `g++` adds the `lib` prefix and `.so/.a` suffix automatically.
- But when you're creating the library yourself, you must use the full name like:
  - `libutilities.so` (for shared libraries)
  - `libutilities.a` (for static libraries)
