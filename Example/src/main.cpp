#include "ExampleWindow.h"
#include "EC3D/Core/Application.h"
#include "EC3D/Gui/MiniAgui.h"

using namespace ec;

int main(int argc, char** argv)
{
	const unsigned int width = 1024;
	const unsigned int height = 1024;
	const char* title = "EyeCandy Example Project";

	ec::Application app(width, height, title, "asd");
	app.createWindow<ExampleWindow>(width, height, "Example Window", "example");
	//app.createWindow<ExampleWindow>(width, height, "Example Window 2", "example2");
	ec::MiniAgui::init();
	app.startMainLoop();
}