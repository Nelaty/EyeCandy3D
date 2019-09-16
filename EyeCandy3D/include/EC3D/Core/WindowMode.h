#pragma once

#include <array>
#include <string>

struct GLFWwindow;

namespace ec
{
	class WindowMode
	{
	public:
		explicit WindowMode(GLFWwindow* window);
		~WindowMode();

		enum Mode
		{
			fullscreen = 0,
			windowed,
			borderless_windowed,
			borderless_fullscreen,
			count
		};

		

		static WindowMode::Mode getCurrentMode(GLFWwindow* window);
		
		const std::string& modeToString(WindowMode::Mode mode);
		
	private:
		static const std::array<std::string, WindowMode::Mode::count> s_modeStr;

	};
}