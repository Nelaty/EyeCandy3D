#include "example-window.h"
#include "ec3/application.h"

#include <iostream>

using namespace ec;

int main(int argc, char** argv)
{
    const unsigned int width = 1024;
	const unsigned int height = 1024;
	const char* title = "EyeCandy Samples Project";

	ec::Application app;
	app.createWindow<ExampleWindow>(width, height, "Samples Window", "example");
	//app.createWindow<ExampleWindow>(width, height, "Samples Window 2", "example2");
	app.startMainLoop();
}