#pragma once

#include <array>

struct GLFWwindow;

namespace ec
{
	class Window;

	class VideoMode
	{
	public:
		explicit VideoMode(Window* window);
		~VideoMode();
	
		/** Window attribute function (context related attributes) */
		///@{	
		int getContextApi() const;
		int getContextCreationApi() const;
		std::array<int, 3> getContextVersion() const;
		bool isOpenGlForwardCompatible() const;
		bool isOpenGlDebugContext() const;
		int getOpenGlProfile() const;
		int getContextRobustnessStrategies() const;
		///@}

		/** Window attribute function (frame buffer related attributes) */
		///@{	
		static int getRedBits();
		static int getGreenBits();
		static int getBlueBits();
		static int getAlphaBits();
		static int getDepthBits();
		static int getStencilBits();
		static int getMsaaSamples();
		///@}

	private:
		Window* m_window;
		GLFWwindow* m_glfwWindow;
	};
}