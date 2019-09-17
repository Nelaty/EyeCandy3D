#include "EC3D/Core/WindowMode.h"

#include <GLFW/glfw3.h>
#include <cassert>

namespace ec
{

	ec::WindowMode::Mode WindowMode::getCurrentMode(GLFWwindow* window)
	{
		auto monitor = glfwGetWindowMonitor(window);
		if(monitor != nullptr)
		{
			auto videoMode = glfwGetVideoMode(monitor);
			

			return Mode::fullscreen;
		}
		else
		{
			if(glfwGetWindowAttrib(window, GLFW_DECORATED))
			{
				return Mode::windowed;
			}
			else
			{
				return Mode::borderless_windowed;
			}
		}
	}

	const std::string& WindowMode::modeToString(WindowMode::Mode mode)
	{
		assert(mode >= 0 && mode < count);
		return s_modeStr[mode];
	}

	const std::array<std::string, WindowMode::Mode::count> WindowMode::s_modeStr =
	{
		"fullscreen",
		"windowed",
		"borderless_windowed",
		"borderless_fullscreen"
	};
}
