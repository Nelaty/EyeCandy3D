#include <GL/glew.h>
#include "EC3D/Core/VideoMode.h"
#include "EC3D/Core/Window.h"

#include <GLFW/glfw3.h>

namespace ec
{

	VideoMode::VideoMode(Window* window)
		: m_window(window)
	{
		m_glfwWindow = m_window->getWindow();
	}

	VideoMode::~VideoMode()
	{
	}

	int VideoMode::getRedBits()
	{
		int value;
		glGetIntegerv(GL_RED_BITS, &value);
		return value;
	}

	int VideoMode::getGreenBits()
	{
		int value;
		glGetIntegerv(GL_GREEN_BITS, &value);
		return value;
	}

	int VideoMode::getBlueBits()
	{
		int value;
		glGetIntegerv(GL_BLUE_BITS, &value);
		return value;
	}

	int VideoMode::getAlphaBits()
	{
		int value;
		glGetIntegerv(GL_ALPHA_BITS, &value);
		return value;
	}

	int VideoMode::getDepthBits()
	{
		int value;
		glGetIntegerv(GL_DEPTH_BITS, &value);
		return value;
	}

	int VideoMode::getStencilBits()
	{
		int value;
		glGetIntegerv(GL_STENCIL_BITS, &value);
		return value;
	}

	int VideoMode::getMsaaSamples()
	{
		int value;
		glGetIntegerv(GL_SAMPLES, &value);
		return value;
	}

	int VideoMode::getContextApi() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_CLIENT_API);
	}

	int VideoMode::getContextCreationApi() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_CONTEXT_CREATION_API);
	}

	std::array<int, 3> VideoMode::getContextVersion() const
	{
		std::array<int, 3> version{};
		version[0] = glfwGetWindowAttrib(m_glfwWindow, GLFW_VERSION_MAJOR);
		version[1] = glfwGetWindowAttrib(m_glfwWindow, GLFW_VERSION_MINOR);
		version[2] = glfwGetWindowAttrib(m_glfwWindow, GLFW_VERSION_REVISION);
		return version;
	}

	bool VideoMode::isOpenGlForwardCompatible() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_OPENGL_FORWARD_COMPAT);
	}

	bool VideoMode::isOpenGlDebugContext() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_OPENGL_DEBUG_CONTEXT);
	}

	int VideoMode::getOpenGlProfile() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_OPENGL_CORE_PROFILE);
	}

	int VideoMode::getContextRobustnessStrategies() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_CONTEXT_ROBUSTNESS);
	}
}