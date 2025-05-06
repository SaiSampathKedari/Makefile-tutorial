---
layout: default
title: Makefile Tutorial
nav_order: 1
description: Learn how to write professional Makefiles by first understanding C++ compilation, linking, and the build process. Ideal for beginners and robotics engineers working with real-world C++ projects.
keywords: Makefile tutorial, how to write a Makefile, C++ Makefile guide, compiling and linking C++, static libraries, shared libraries, build systems, robotics, C++ projects
---


# 📘 Makefile Tutorial

This is a hands-on tutorial on how to write Makefiles from scratch — the way they are structured and used in real-world C++ and C projects.

Before diving into Makefiles, it's essential to understand **how to manually compile and link** your code using the `g++` (or `gcc`) compiler.

### 👉 Start Here:
To build a solid foundation, please begin with:

📄 [`compiler_linker_flags.md`](./compiler_linker_flags.md) 
*A complete guide to C++ compilation stages, compiler/linker flags, and how to manually build executables, static libraries, and shared libraries.*

This will help you truly appreciate and understand what a Makefile automates under the hood.

## What is a Makefile?
A **Makefile** is a plain text file that contains a series of rules used by the `make` build tool to automate compiling, linking, and building software.

### Structure of a Rule
Each rule in Makefile follows this format:

```make
target: prerequisites/dependencies
<tab>command1
<tab>command2
<tab>command3
.
.
.
```
### Basic Stucture of a Makefile

```make
CC = gcc # Defining a Variable in a Makefile
CXX = g++ # Use $(CXX) to access the value of the CXX variable in your Makefile.


target1: dependencies
	command

target2: dependencies
	command

target3: dependencies
	command1
	command2

.
.
.
```


### **1.`target`** 
  - The name of the file or label that `make` is trying to create or update.
  - Usually this is:
    - An output file like an executable ( `output` ), object file ( `.o` ), or library (`libmylib.a` or `libmylib.so` )
    - Or a spectial label like `all`, `clean`, or `install` (called `PHONY` targets, explained below)
💡 If the `target` is a real file, make checks whether it needs to be updated. If it's a label, it just runs the commands.

### **2.`prerequisites` (or `dependencies`)** 
  - These are the input files that the target depends on.
  - If any of these files are newer than the target, `make` will re-run the commands to rebuild the target.
  - For example:
    - An object file depends on a `.cpp` and `.h` file
    - An executable might depend on several `.o` files
💡 If a prerequisite file is missing, make will try to find a rule to build it.

### **2.`command` (or `recipe`)** 
  - This is the shell command used to build the target from the prerequisites.
  - It must begin with a tag (not spaces).
  - It can be any valid shell command: `g++`, `cp`, `rm`, `echo` etc.
  - If there are multiple lines, they are run one by one.

### Example1: No Dependencies 
Makefile
```makefile
greet:
	echo "Welcome to Makefile tutorials!"
```
* `target`: greet
* `Dependencies`: none
* `command`: print a messsage

output:
```bash
$ make
echo "Welcome to Makefile tutorials!"
Welcome to Makefile tutorials!
```

### Example2: Single Dependency
main.cpp
```cpp
#include <iostream>
int main()
{
    std::cout << "Hello World!\n" ;
    return 0;
}
```
Makefile
```makefile
output: main.cpp
	g++ main.cpp -o output
```
* `target`: output
* `Dependencies`: main.cpp
* `command`: generate executable

output:
```bash
$ make
g++ main.cpp -o output
$ ./output
Hello World!
```

### Example2: Multiple Dependencies
main.cpp
```cpp
#include <iostream>
int main()
{
    std::cout << "Hello World!\n" ;
    return 0;
}
```

utils.cpp
```cpp
#include <iostream>

// Function to print a message from the utils module
void printmessage()
{
    std::cout << "Message from utils.cpp\n";
}
```

Makefile
```Makefile
output: main.cpp utils.cpp
	g++ main.cpp utils.cpp -o output
```
* `target`: output
* `Dependencies`: main.cpp utils.cpp
* `command`: generate executable

output:
```bash
$ make
g++ main.cpp utils.cpp -o output
$ ./output
Hello World!
Message from utils.cpp
```

## 1. ⚙️ How `make` Works: Rule Selection and Execution Flow

When you run the `make` command, it reads the **Makefile** and follows a very predictable, logical process to decide **what to build**, **when to build it**, and **in what order**. Here's how it works:

### 1. Make Always Starts with the First Target
- make always beigns with the first rule it finds in the Makefile
- That rule becomes the default target(also called the entry point).
- Any other rules are ignored unless they are explicitly:
  - Specified as dependencies of the first target, or
  - Called manually (e.g., `make clean`)

#### Example01: Make always starts with the First Target
```makefile
first:
	echo "This is the first (default) target"

second:
	echo "This is the second target"

third:
	echo "This is the third target"
```

🔧 Run:
```bash
make
```
🖨️ Output:
```bash
echo "This is the first (default) target"
This is the first (default) target
```

#### 🧠 What happened?
* you ran `make` with no arguments
* So it looked for the first rule, which is `first`
* it ran only the `first` target
* it did not touch `second` and `third`

#### What if you wnat to run `second` ?
you must **expilicilty** tell `make`:
🔧 Run:
```bash
make second
```
Output:
```bash
echo "This is the second target"
This is the second target
```

✅ **Rule 1 takeaway:** Unless you override it, only the first target runs when you type `make`.

## 2. 🔄 How Make Follows Dependencies (Recursively)
Each rule in Makefile has:
* A target (the thing to build)
* A list of dependencies (other files or targets it relies on)
* A recipe (the command to build it)

When you run `make`, it doesn't blindly execute every rule.
instead, `make`:
1. Starts with the requested target (or the first rule if none specified)
2. Recursively checks whether each dependency (prerequisite) is:
   - Present
   - Up to date
3. If not, it finds a rule to build it and runs that first
4. This process continues until all dependencies are resolved

Example Makefile:
```makefile
output: main.o math.o
	g++ main.o math.o -o app

main.o: main.cpp
	g++ -c main.cpp -o main.o

math.o: math.cpp
	g++ -c math.cpp -o math.o
```

🛠️ Scenario
Let's assume this file setup:
* `main.cpp` and `math.cpp` exits
* `main.o`, `math.o`, and `output` do not exist yet

⏯️ Now run:
```bash
make
```

#### 🧠 What happens?
1. make see `output` is the target, but it needs `main.o` and `math.o`
2. It checks: Does `main.o` exist?
   - ❌ NO => it finds a rule to build `main.o` using `main.cpp`
   - ✔️ it runs: `g++ -c main.cpp -o main.o`
3. Same for `math.o`
   - ❌ Not present => rule found => builds it with: `g++ -c math.cpp -o math.o`
4. Now both `.o` files are up to date => `output` can be built
   - ✔️ it runs: `g++ main.o math.o -o app`
  
Second Build (Run `make` again)
```bash
make
```

This time:
1. `main.o`, `math.o`, and `output` already exist.
2. `make` check timestamps:
   - Are `main.o` and `math.o` newer than `main.cpp`, `math.cpp`?
     - ✔️ Yes => no need to build.
   - Is output newer than both `.o` files?
     - ✔️ Yes => everything is up to date
Result: make prints `make: 'output' is up to date`, nothing is rebild
