#include "ExampleWindow.h"
#include "EC3D/Core/Application.h"
#include "EC3D/Gui/MiniAgui.h"

#include <iostream>
#include <filesystem>

using namespace ec;

int main(int argc, char** argv)
{
    std::cout << "Current working dir: " << std::filesystem::current_path() << "\n";

	const unsigned int width = 1024;
	const unsigned int height = 1024;
	const char* title = "EyeCandy Example Project";

	ec::MiniAgui::init();

	ec::Application app;
	app.createWindow<ExampleWindow>(width, height, "Example Window", "example");
	//app.createWindow<ExampleWindow>(width, height, "Example Window 2", "example2");
	app.startMainLoop();
}