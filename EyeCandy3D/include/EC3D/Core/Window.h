#pragma once

#include "EC3D/Core/DeviceRegistry.h"
#include "EC3D/Core/Renderer.h"
#include "EC3D/Core/Freetype.h"
#include "EC3D/Core/SceneSystem.h"
#include "EC3D/Core/InputObservable.h"
#include "EC3D/Core/Shader/ShaderManager.h"

#include "EC3D/Utilities/Timer.h"

#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

#include <string>
#include <memory>


/**
* A window is responsible for one os specific window, which can receive
* input events.
*/
namespace ec
{
	class EventQueue;
	class EventSource;

	class Window
	{
	public:
		using EventQueue_Ptr = std::unique_ptr<EventQueue>;
		using EventSource_Ptr = std::unique_ptr<EventSource>;


		explicit Window(unsigned int windowWidth,
						unsigned int windowHeight,
		                std::string windowTitle);
		virtual ~Window();
		
		/** Should be called to start program */
		virtual void startMainLoop();

		/** Update the window */
		void tickMeta();
		virtual void tick(float timeDelta);
		/** Render to the window */
		virtual void render();

		virtual void setFrameRate(double fps);

		/* GLFW Callbacks */
		static void errorCallback(int error, const char* description);
		virtual void resizeWindow(GLFWwindow* window, int width, int height);

		/** Access to the input observer */
		InputObservable& getInputObserver();

		/** Access to the shader manager */
		ShaderManager& getShaderManager();

		/** Access to the scene system */
		SceneSystem& getSceneSystem();

		/** Get the event queue of this window */
		EventQueue* getEventQueue();
		/** Get the event source of this window */
		EventSource* getEventSource() const;

		/* Switch between face, wire frame and point mode */
		void switchToFaceMode();
		void switchToWireframeMode();
		void switchToPointMode();

		/* Switch between full screen and windowed */
		void goWindowed();
		void goFullscreen();
		void closeWindow();

		/* Clear Color access */
		void setClearColor(const glm::vec4& clearColor);
		const glm::vec4& getClearColor() const;

		/** Access to window */
		GLFWwindow* getWindow() const;
		glm::ivec2 getWindowResolution() const;
		glm::ivec2 getWindowPosition() const;

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

		DeviceRegistry m_deviceRegistry;

		double m_frameRate;
		double m_frameInterval;

	private:
		void init();

		/* Init function implementation */
		virtual bool initImpl();
		/* Main loop function implementation */
		virtual void mainLoopImpl();

		void windowTick(float timeDelta);
		
		/** Callback initialization */
		void initCallbacks();

		/** 
		 * The drop callback is called when one or multiple files are 
		 * dragged into the window 
		 */
		static void dropCallback(GLFWwindow* window, int count, const char** paths);
		/** 
		 * The resize callback is called when the window's width or height
		 * has changed.
		 */
		static void resizeCallback(GLFWwindow* window, int width, int height);
		/**
		 * The focus callback is called when a window, which previously was
		 * unfocused, receives focus.
		 */
		static void focusCallback(GLFWwindow* window, int focused);
		/**
		 * The close callback is called when a window is being destroyed.
		 */
		static void closeCallback(GLFWwindow* window);


		void initOpenGl();
		void initAgui();

		void printVersions() const;

		EventQueue_Ptr m_eventQueue;
		EventSource_Ptr m_eventSource;

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