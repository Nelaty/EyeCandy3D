# EyeCandy3D
## 1. Building

### CMake ###

**include directories**:
* *EyeCandy3D/include*
* *External/include*
* < freetype2-dir > (usually /usr/include/freetype2)

**dependencies**:
* agui (included in build)
* glfw
* GLEW
* GLU
* GL
* X11
* Xrandr
* Xinerama
* Xi
* Xxf86vm
* Xcursor
* pthread
* dl
* freetype

**example: Ubuntu 16.04**
Install the following packages:
```
apt-get install \
  cmake \
  g++ \
  libglm-dev \
  libglfw3-dev \
  libglew-dev \
  libfreetype6-dev \
  libxcursor-dev \
  libxi-dev \
  libxinerama-dev
```
The glfw lib has to be at version 3.2.1 or newer.

(As of writing, Ubuntu 16.04 only has version 3.1.2 in its official repositories. glfw can be downloaded and compiled from https://github.com/glfw/glfw)

The libraries are linked in EyeCandy3D/src/Core/CMakeLists.txt

**building**

Create and navigate to your desired build directory (in this example `./build`) and run cmake:
```
mkdir build
cd build
cmake ..
```

Run `make` in your build directory.

The library will be created in the `lib` subdirectory (`./build/lib`)

The example will be created in the `bin` subdirectory (`./build/bin`)


## 2. Installation
The built library can be installed using the command
```
make install
```
in the build directory (here ./build).

## 3. Documentation
* [Doxygen](https://nelaty.github.io/EyeCandy3D/DoxygenDoc/html/index.html)
* [User manual](https://nelaty.github.io/EyeCandy3D/UserManual/EyeCandy3D_UserManual.pdf)


**Doxygen note:**

1. To generate you're own documentation with doxygen, you need to have "Dot" installed (included in the graphviz package). Otherwise collaboration graphs will not be generated!
2. Navigate to ./Docs/ and execute the command: "doxygen Doxyfile"
