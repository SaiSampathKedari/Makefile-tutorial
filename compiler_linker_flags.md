---
layout: default
title: Compiler & Linker Flags
nav_order: 2
---

# C++ Compilation and Linking: Flags, Targets, and Fundamentals for Writing Makefiles

## These are the 4 essential stages that convert C++ source code into an executable.

### **1. Preprocessing**
Expands `#include`, `#define`, and macros; removes comments; produces an intermediate `.i` file.

```bash
>> g++ -E source.cpp -o source.i
```

### 2. **Compilation**
Converts preprocessed code into assembly (`.s` file).

```bash
>> g++ -S source.i -o source.s
```

### 3. **Assembly**
Converts assembly into machine code (`.o` object file).

```bash
>> g++ -c source.s -o source.o
```

### 4. **Linking**
Combines object files and libraries into a final executable.

```bash
>> g++ source1.o source2.o -o output
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
    >> g++ main.o -lutilities -o output
    ```
  - This works because `g++` adds the `lib` prefix and `.so/.a` suffix automatically.
- But when you're creating the library yourself, you must use the full name like:
  - `libutilities.so` (for shared libraries)
  - `libutilities.a` (for static libraries)

---

### **2. `-I` -- Add Header File Search Path**
- The `-I` option tell the compiler where to look for header files (`.h` or `.hpp`) during compilation.
- Why use `-I`?
  - Sometimes your project uses custom headers that are not in the default system folders like `/usr/include/`. You use `-I` to tell the compiler where to find them.
  - How to use it:
    - ```bash
      >> g++ -I/path/to/headers main.cpp -o output
      ```
    - No space between `-I` and the path
    - You can use multiple `-I` options if you have headers in different folders
    - Example
    - ```bash
      >> g++ -I./include -I../shared_headers main.cpp -o app
      ```
    - This tell the compiler to look in:
      - `./include`
      - `../shared_headers` ... in addition to the system's default include path.
- 📌 **Important Notes:**
  - `-I` only affect the compilation stage ( when `.cpp` files are being compiled.
  - System default include paths (like `/usr/include`) are alwasy checked automatically.
  - Use `-I` to add your project-specific or third-party header locations.

---
 
### 3. `-l` -- Link with a library
- The `-l` option tells the linker to link your executable with a precompiled library (either a static `.a` or a shared `.so` file).
- Why use `-l`?
  - Libraries contain code that has already been compiled (like math functions, robot control libraries, etc.). Instead of rewriting everything, you can just link these libraries into your program.
  - How to use it:
  - ```bash
    >> g++ main.o -lutilities -o app
    ```
  - `-lutilities` means link with `libutilities.so` or `libutilities.a`.
  - You don't write `lib` or `.so/.a` — just the short name after `-l`, the linker will automatically search for the correct file.
- 📌 **Important Notes:**
  - Linking happens during the final linking stage — after compiling `.cpp` files into `.o` files.
  - This option usually comes at the end of the `g++` command.
  - If you want to link multiple libraries, just use multiple `-l` options:
  - ```bash
    >> g++ main.o -lmath_utils -ltrajectory -lutilities -o app
    ```
  - Where are libraries located?
    - `/lib`
    - `/usr/lib`
  - Their files are named like:
    - `libmath_utils.so`, `libmath_utils.a` (for the math_utils library)
  - When you write `-lmath_utils`, the linker understands it should find `libmath_utils.so` or `libmath_utils.a`.

---

### 4. `-L` — Add Library Search Path
- The `-L` option tells the linker where to **look for libraries** (e.g., `libutilities.a` for static, `libutilities.so` for shared ) **during linking**.
- Why use `-L`?
  - By default, `g++` looks for libraries only in standard system directories like `/usr/lib` or `/lib`.
  - If your library is in a **custom folder**, you need to tell the linker where to find it using `-L`.
  - ```bash
    >> g++ main.o -L./libs -lutilities -o output
    ```
  - `L./libs` add the `./libs` folder to the library search path
  - Combined with `-lutilities`, the linker will try to find:
      - `libutilities.so` (for dynamics linking)
      - `libutilities.a` (for static linking)
  - If both exists, `g++` will prefer the shared (`.so`) version by default
- 📌 **Important Notes:**
  - There is no space between `-L` and the path.
  - You can specify multiple paths using multiple `-L` flags:
    - ```bash
      >> g++ -L./libs -L../external_libs -lutilities -o app
      ```
  - This is used only during the linking stage.
  - If you want to force static linking, use:
    - ``` bash
      >> g++ main.o -L./libs -Wl,-Bstatic -lutilities -Wl,-Bdynamic -o output
      ```
  -  :warning: `-L` only affects link-time lookup, not runtime.

---

### 5. Locating Shared Libraries at Runtime
- When your program is linked against a **shared library** (like `libutilities.so`), the library must be **found and loaded again at runtime** — not just during compilation.
- If the shared library is not in a **standard system directory** (like `/lib` or `/usr/lib`), you need to tell the program **where to find it**.
- If the library isn't in a standard location like `/lib` or `/usr/lib`, the program will fail with:
  - ```bash
    ./output: error while loading shared libraries: libutilities.so: cannot open shared object file: No such file or directory
    ```

There are two main options to solve this:

#### 1. Using LD_LIBRARY_PATH (Temporary, Environment-Based)

This environment variable tells the dynamic linker where to search for shared libraries at runtime.
```bash
>> export LD_LIBRARY_PATH=./libs:$LD_LIBRARY_PATH
```
⚠️ LD_LIBRARY_PATH is great for development and testing, but can interfere with other programs if not unset or reset properly.


#### 2. `rpath` — Embed Library Path at Link Time

You can embed the path to the shared library **into the executable itself** using the `-Wl,-rpath` option during linking:
  ```bash
  >> g++ main.o -L./libs -lutilities -Wl,-rpath=./libs -o output 
  ```
This method is more stable and program-specific — no need to set environment variables.

---

### 6. `-D` — Define Preprocessor Macros (Compiler Flags)

The `-D` flag is used to define **preprocessor macros** at compile time, without modifying the source code.

This is equivalent to writing `#define` statements directly in your code. It's commonly used for:

- Enabling or disabling features
- Toggling debug mode
- Setting configuration values
- Conditional compilation

#### ✅ Example Usages

main.cpp
```C++
#include <iostream>

int main()
{
  #ifdef DEBUG
  std::cout << ""Debug mode enabled\n";
  #endif

  #if LOG_LEVEL=2
  std::cout << "Verbose logging\n";
  #endif

  return 0;
}
```

```bash
>> g++ -DDEBUG -DLOG_LEVEL=1 main.cpp -o output     # same as #define DEBUG and #define LOG_LEVEL 1
>> ./output
>> Debug mode enabled
```

📌 Important Notes
- There should be no space between -D and the macro name.
- You can define macros with or without values.
- These flags are applied during the preprocessing stage, before compilation.


| Flag                      | Result in Code                  |
|---------------------------|----------------------------------|
| `-DDEBUG`                 | `#define DEBUG`                  |
| `-DMODE=1`                | `#define MODE 1`                 |
| `-DVERSION="1.0"`         | `#define VERSION "1.0"`          |

---

## 📋 Summary of Key Linking & Library Flags

| Flag               | Purpose                                        | When Used     |
|--------------------|------------------------------------------------|---------------|
| `-I<dir>`          | Add header file search path                    | Compilation   |
| `-D<name>[=value]` | Define preprocessor macro                      | Compilation   |
| `-L<dir>`          | Add library search path                        | Linking       |
| `-l<name>`         | Link with `lib<name>.so` or `lib<name>.a`      | Linking       |
| `-Wl,-rpath=<dir>` | Embed runtime path for shared libraries        | Linking       |
| `LD_LIBRARY_PATH`  | Set runtime shared library path (env variable) | Runtime       |

