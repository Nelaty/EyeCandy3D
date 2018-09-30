#include "EC3D/Core/WindowCreationHints.h"

namespace ec
{
	void WindowCreationHints::setHints() const
	{
		glfwWindowHint(GLFW_RESIZABLE, m_resizable);
		glfwWindowHint(GLFW_VISIBLE, m_visible);
		glfwWindowHint(GLFW_DECORATED, m_decorated);
		glfwWindowHint(GLFW_FOCUSED, m_focused);
		glfwWindowHint(GLFW_AUTO_ICONIFY, m_autoIconify);
		glfwWindowHint(GLFW_FLOATING, m_floating);
		glfwWindowHint(GLFW_MAXIMIZED, m_maximized);

		glfwWindowHint(GLFW_RED_BITS, m_redBits);
		glfwWindowHint(GLFW_GREEN_BITS, m_greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, m_blueBits);
		glfwWindowHint(GLFW_ALPHA_BITS, m_alphaBits);
		glfwWindowHint(GLFW_DEPTH_BITS, m_depthBits);
		glfwWindowHint(GLFW_STENCIL_BITS, m_stencilBits);

		glfwWindowHint(GLFW_ACCUM_RED_BITS, m_accumRedBits);
		glfwWindowHint(GLFW_ACCUM_GREEN_BITS, m_accumGreenBits);
		glfwWindowHint(GLFW_ACCUM_BLUE_BITS, m_accumBlueBits);
		glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, m_accumAlphaBits);

		glfwWindowHint(GLFW_AUX_BUFFERS, m_auxBuffers);
		glfwWindowHint(GLFW_SAMPLES, m_samples);
		glfwWindowHint(GLFW_REFRESH_RATE, m_refreshRate);
		glfwWindowHint(GLFW_STEREO, m_stereo);
		glfwWindowHint(GLFW_SRGB_CAPABLE, m_srgbCapable);
		glfwWindowHint(GLFW_DOUBLEBUFFER, m_doubleBuffer);
		glfwWindowHint(GLFW_CLIENT_API, m_clientApi);

		glfwWindowHint(GLFW_CONTEXT_CREATION_API, m_contextCreationApi);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_contextVersionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_contextVersionMinor);
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, m_contextRobustness);
		glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, m_contextReleaseBehavior);

		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, m_openglForwardCompatible);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, m_openglDebugContext);
		glfwWindowHint(GLFW_OPENGL_PROFILE, m_openglProfile);
	}
}