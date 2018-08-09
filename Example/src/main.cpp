#include <iostream>

#include "ExampleWindow.h"

using namespace ec;

int main(int argc, char** argv)
{
	unsigned int width = 1024;
	unsigned int height = 1024;
	const char* title = "EyeCandy Example Project";

	ExampleWindow window(width, height, title);
	window.StartMainLoop();
}