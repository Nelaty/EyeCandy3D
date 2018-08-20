#include "EC3D/Core/Application.h"
#include "EC3D/Core/Window.h"

namespace ec
{
	Application::Application(const unsigned int windowWidth, 
							 const unsigned int windowHeight,
							 const std::string& windoTitle,
							 const std::string& windowName)
	{
		CreateWindow(windowWidth,
					 windowHeight,
					 windoTitle,
					 windowName);


		CreateWindow(windowWidth,
					 windowHeight,
					 windoTitle,
					 windowName + "asd");
	}

	Application::~Application()
	{
	}

	bool Application::CreateWindow(unsigned int width, 
								   unsigned int height, 
								   const std::string& title,
								   const std::string& name)
	{
		if(m_windows.find(name) != m_windows.end())
		{
			printf("ERROR: Couldn't create window!\n");
			printf("       A window with name \"%s\" already exists!\n", name.c_str());
			return false;
		}

		Window_Ptr window = std::make_unique<Window>(width, height, title.c_str());
		m_windows[name] = std::move(window);

		return true;
	}
}