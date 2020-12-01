#include "ExampleWindow.h"
#include "EC3D/Application.h"
#include "EC3D/Gui/MiniAgui.h"

#include <iostream>
#include <filesystem>

using namespace ec;

int main(int argc, char** argv)
{
    const unsigned int width = 1024;
	const unsigned int height = 1024;
	const char* title = "EyeCandy Samples Project";

	ec::MiniAgui::init();

	ec::Application app;
	app.createWindow<ExampleWindow>(width, height, "Samples Window", "example");
	//app.createWindow<ExampleWindow>(width, height, "Samples Window 2", "example2");
	app.startMainLoop();
}