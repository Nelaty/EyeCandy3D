#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Freetype.h"
#include "SceneSystem.h"
#include "Shader/ShaderManager.h"
#include "InputObservable.h"
#include "EC3D/Utilities/Timer.h"

#include <string>
#include <glm/glm.hpp>

/**
* A window represents the base of every application. It creates a 
* os specific window. The application functionality can be executed
* in the provided main loop.
* It also supplies the user with input functionality and a scene system
*/
namespace ec
{
	class Window
	{
	public:
		explicit Window(const unsigned int windowWidth,
						const unsigned int windowHeight,
						const char* windowTitle);
		virtual ~Window();
		
		/* Should be called to start program */
		virtual void StartMainLoop();

		/* Update the window */
		virtual void Tick(const float timeDelta);
		/* Render to the window */
		virtual void Render();

		virtual void SetFrameRate(const double fps);

		/* GLFW Callbacks */
		static void ErrorCallback(int error, const char* description);
		virtual void ResizeCallback(GLFWwindow* window, int width, int height);

		/* Access to the input observer */
		InputObservable& GetInputObserver();

		/* Access to the shader manager */
		ShaderManager& GetShaderManager();

		/* Access to the scene system */
		SceneSystem& GetSceneSystem();

		/* Switch between face, wire frame and point mode */
		void SwitchToFaceMode();
		void SwitchToWireframeMode();
		void SwitchToPointMode();

		/* Switch between full screen and windowed */
		void GoWindowed();
		void GoFullscreen();
		void CloseWindow();

		/* Clear Color access */
		void SetClearColor(const glm::vec4& clearColor);
		const glm::vec4& GetClearColor() const;

		/** Access to window */
		GLFWwindow* GetWindow() const;
		glm::ivec2 GetWindowResolution() const;
		glm::ivec2 GetWindowPosition() const;

	protected:
		unsigned int m_windowWidth;
		unsigned int m_windowHeight;
		std::string m_windowTitle;

		GLFWwindow* m_window;

		Timer m_timer;
		SceneSystem m_sceneSystem;
		ShaderManager m_shaderManager;
		InputObservable m_inputObservable;

		Renderer m_renderer;

		double m_frameRate;
		double m_frameInterval;

	private:
		void Init();

		/* Init function implementation */
		virtual bool InitImpl();
		/* Main loop function implementation */
		virtual void MainLoopImpl();

		void WindowTick(float timeDelta);

		void InitCallbacks();
		void InitOpenGL();

		void PrintVersions() const;

		/** The windows resolution before changing to full screen */
		glm::ivec2 m_windowedResolutionLast;
		/** The windows position before changing to full screen */
		glm::ivec2 m_windowPositionLast;

		/** Background color */
		glm::vec4 m_clearColor;

		/** Indicator if this window has been successfully initialized */
		bool m_initSuccessful;
	};
}