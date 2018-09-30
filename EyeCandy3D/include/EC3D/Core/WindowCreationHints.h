#pragma once

#include <GLFW/glfw3.h>

namespace ec
{
	struct WindowCreationHints
	{
		void setHints() const;

		int m_resizable = GLFW_TRUE; // GLFW_TRUE or GLFW_FALSE
		int m_visible = GLFW_TRUE; // GLFW_TRUE or GLFW_FALSE
		int m_decorated = GLFW_TRUE; // GLFW_TRUE or GLFW_FALSE
		int m_focused = GLFW_TRUE; // GLFW_TRUE or GLFW_FALSE
		int m_autoIconify = GLFW_TRUE; // GLFW_TRUE or GLFW_FALSE
		int m_floating = GLFW_FALSE; // GLFW_TRUE or GLFW_FALSE
		int m_maximized = GLFW_FALSE; // GLFW_TRUE or GLFW_FALSE

		int m_redBits = 8; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_greenBits = 8; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_blueBits = 8; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_alphaBits = 8; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_depthBits = 24; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_stencilBits = 8; // 0 to INT_MAX or GLFW_DONT_CARE

		int m_accumRedBits = 0; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_accumGreenBits = 0; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_accumBlueBits = 0; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_accumAlphaBits = 0; // 0 to INT_MAX or GLFW_DONT_CARE

		int m_auxBuffers = 0; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_samples = 0; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_refreshRate = GLFW_DONT_CARE; // 0 to INT_MAX or GLFW_DONT_CARE
		int m_stereo = GLFW_FALSE; // GLFW_TRUE or GLFW_FALSE
		int m_srgbCapable = GLFW_FALSE; // GLFW_TRUE or GLFW_FALSE
		int m_doubleBuffer = GLFW_TRUE; // GLFW_TRUE or GLFW_FALSE
		int m_clientApi = GLFW_OPENGL_API; // GLFW_OPENGL_API, GLFW_OPENGL_ES_API or GLFW_NO_API
	
		int m_contextCreationApi = GLFW_NATIVE_CONTEXT_API; // GLFW_NATIVE_CONTEXT_API or GLFW_EGL_CONTEXT_API
		int m_contextVersionMajor = 1; // Any valid major version number of the chosen client API
		int m_contextVersionMinor = 0; // Any valid major version number of the chosen client API
		int m_contextRobustness = GLFW_NO_ROBUSTNESS; // GLFW_NO_ROBUSTNESS, GLFW_NO_RESET_NOTIFICATION or GLFW_LOSE_CONTEXT_ON_RESET
		int m_contextReleaseBehavior = GLFW_ANY_RELEASE_BEHAVIOR; // GLFW_ANY_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH or GLFW_RELEASE_BEHAVIOR_NONE

		int m_openglForwardCompatible = GLFW_FALSE; // GLFW_TRUE or GLFW_FALSE
		int m_openglDebugContext = GLFW_FALSE; // GLFW_TRUE or GLFW_FALSE
		int m_openglProfile = GLFW_OPENGL_ANY_PROFILE; // GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_COMPAT_PROFILE or GLFW_OPENGL_CORE_PROFILE
	};
}
