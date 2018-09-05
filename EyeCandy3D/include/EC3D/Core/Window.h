#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include "EC3D/Core/ResourceRegistry.h"
#include "EC3D/Core/DeviceRegistry.h"
#include "EC3D/Core/Renderer.h"
#include "EC3D/Core/SceneSystem.h"
#include "EC3D/Core/InputObservable.h"
#include "EC3D/Core/EventSystem.h"
#include "EC3D/Core/Shader/ShaderManager.h"

#include "EC3D/Utilities/Timer.h"

#include "EC3D/Core/Geometry.h"
#include "EC3D/Core/Material.h"
#include "EC3D/Core/Texture.h"
#include "EC3D/Core/Drawable.h"


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
	class EC3D_DECLSPEC Window
	{
	public:
		using EventQueue_Ptr = std::unique_ptr<EventQueue>;
		using EventSource_Ptr = std::unique_ptr<EventSource>;


		/**
		 * \brief Window contructor
		 * \param windowWidth Width of this window in pixels.
		 * \param windowHeight Height of this window in pixels.
		 * \param windowTitle Title of this window.
		 */
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

		/** Error callback */
		static void errorCallback(int error, const char* description);
		/** Window resize callback */
		virtual void resizeWindow(GLFWwindow* window, int width, int height);

		/** Get this window's event system. */
		EventSystem& getEventSystem();

		/** Access to the shader manager */
		ShaderManager& getShaderManager();

		/** Access to the scene system */
		SceneSystem& getSceneSystem();

		/* Switch between face, wire frame and point mode */
		void switchToFaceMode() const;
		void switchToWireFrameMode() const;
		void switchToPointMode() const;

		/** Switch to windowed mode. */
		void goWindowed() const;
		/** Switch to fullscreen mode. */
		void goFullscreen();
		/** Close this window. */
		void closeWindow() const;

		/** Set the current clear color. */
		void setClearColor(const glm::vec4& clearColor);
		/** Get the current clear color. */
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
		EventSystem m_eventSystem;
		ShaderManager m_shaderManager;

		Renderer m_renderer;

		double m_frameRate;
		double m_frameInterval;

		

		ResourceRegistry<Geometry> m_geometryRegistry;
		ResourceRegistry<Material> m_materialRegistry;
		ResourceRegistry<Texture> m_textureRegistry;
		ResourceRegistry<Drawable> m_drawableRegistry;
	private:
		void init();

		void makeContextCurrent() const;

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