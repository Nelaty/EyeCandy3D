# EyeCandy3D
## 1. Building

### Visual Studio 2017 ###

To build the library, open the visual studio solution, select the desired platform and configuration and press <kbd>F7</kbd>.

### CMake ###
**required libraries**

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

**Visual Studio 2017**

Nuget packages:
* glew.v140
* glfw
* freetype
* glm

Additional include directories:
* *EyeCandy3D/include*
* *External/include*

Additional dependencies:
* EyeCandy3D.lib
* opengl32.lib
* agui.lib

If compiled with cmake, the library will already include agui.

Additional dependencies directories:
* *Build*

## 3. Documentation
* [Doxygen](https://nelaty.github.io/EyeCandy3D/DoxygenDoc/html/index.html)
* [User manual](https://nelaty.github.io/EyeCandy3D/UserManual/EyeCandy3D_UserManual.pdf)


**Doxygen note:**

1. To generate you're own documentation with doxygen, you need to have "Dot" installed (included in the graphviz package). Otherwise collaboration graphs will not be generated!
* Navigate to ./Docs/ and execute the command: "doxygen Doxyfile"
