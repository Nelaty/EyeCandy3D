# EyeCandy3D
## 1. Building

**Visual Studio 2017**

To build the library, open the visual studio solution, select the desired platform and configuration and press <kbd>F7</kbd>.

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

Additional dependencies directories:
* *Build*

## 3. Documentation
* [Doxygen](https://nelaty.github.io/EyeCandy3D/Doc/DoxygenDoc/html/index.html)
* [User manual](https://nelaty.github.io/EyeCandy3D/Doc/UserManual/EyeCandy3D_UserManual.pdf)


**Doxygen note:**

1. To generate you're own documentation with doxygen, you need to have "Dot" installed (included in the graphviz package). Otherwise collaboration graphs will not be generated!
* Navigate to ./Docs/ and execute the command: "doxygen Doxyfile"
