# Incubator
This repository contains the source code, build scripts, and documentation for the Incubator project

Incubator itself does nothing. The project is a container for the development of a set of useful (certainly to me, maybe to you?) libraries and utilities. 

[[_TOC_]]

---
## Cloning
This repository uses does not use submodules:
```bash
~$ git clone git@https://github.com/mg4news/incubator.git
```

---
## Building

First, install build and runtime dependencies:
```bash
~/incubator$ sudo ./tools/install_dependencies.sh
```

This is tested on Linux Mint 21 and later. Be aware that alternative linux distributions may have different package names thus causing the script to fail. 

Run build. Only Ninja is supported. Other generators may well work. (You feeling lucky punk?) 
Use `CMAKE_GENERATOR=Ninja` to set `Ninja` as generator.

```bash
~incubator/$ mkdir build
~incubator/$ cd build
~incubator/$ cmake -DCMAKE_BUILD_TYPE=Release/Debug/etc -GNinja ..
~incubator/$ ninja
```

---
## Components
- [mgbase: a simple utilities and building blocks library](libraries/mgbase/README.md)

