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
Variable1
Variable2

target1: dependencies
<tab>command

target2: dependencies
<tab>command

target3: dependencies
<tab>command1
<tab>command2

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

### Example
Makefile
```makefile
greet:
	echo "Welcome to Makefile tutorials!"
```
output:
```bash
$ make
echo "Welcome to Makefile tutorials!"
Welcome to Makefile tutorials!
```

