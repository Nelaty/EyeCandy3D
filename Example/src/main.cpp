#include "ExampleWindow.h"
#include "EC3D/Core/Application.h"

using namespace ec;

int main(int argc, char** argv)
{
	const unsigned int width = 1024;
	const unsigned int height = 1024;
	const char* title = "EyeCandy Example Project";

	//ec::Application app(width, height, title, "asd");
	//app.StartMainLoop();

	ExampleWindow window(width, height, title);
	window.startMainLoop();
}