#pragma once
#include <GL/glew.h>
#include "ec3/Common/Common.h"

#include "ec3/ResourceRegistry.h"
#include "ec3/Input/DeviceRegistry.h"
#include "ec3/Graphics/Render/Renderer.h"
#include "ec3/SceneSystem.h"
#include "ec3/Input/InputObservable.h"
#include "ec3/Input/EventSystem.h"
#include "ec3/Graphics/Shader/ShaderManager.h"

#include "ec3/Utilities/Timer.h"

#include "ec3/Graphics/Geometry/Geometry.h"
#include "ec3/Graphics/Material/Material.h"
#include "ec3/Graphics/Material/Texture.h"
#include "ec3/Graphics/Drawable.h"

#include "ec3/Window/WindowCallbacks.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <array>
#include <string>
#include <memory>


namespace ec
{
	/// A window is responsible for one os specific window, which
    /// can receive input events.
	class EC3D_DECLSPEC Window
	{
	public:
		explicit Window(unsigned int windowWidth,
						unsigned int windowHeight,
		                std::string windowTitle);
		virtual ~Window();

		/// Update the window
		void tickMeta();
		virtual void tick(float timeDelta);
		/// Render to the window
		virtual void render();

		virtual void setFrameRate(double fps);

		/// GLFW window error callback
		static void errorCallback(int error, const char* description);
		/// GLFW window resize callback
		virtual void resizeWindow(GLFWwindow* window, int width, int height);

		EventSystem& getEventSystem();
		ShaderManager& getShaderManager();
		SceneSystem& getSceneSystem();

		/// Render faces
		void switchToFaceMode() const;
        /// Render lines only
		void switchToWireFrameMode() const;
		/// Render vertices only
		void switchToPointMode() const;

		/// Switch to windowed mode.
		void goWindowed() const;
		/// Switch to fullscreen mode.
		void goFullscreen();

		/// Set the current clear color.
		void setClearColor(const glm::vec4& clearColor);
		/// Get the current clear color.
		const glm::vec4& getClearColor() const;

		/// Get the window backend
		GLFWwindow* getWindow() const;

		/// Access to the window associated with the currently active context.
		static Window* getCurrentWindow();

		/// Get the current resolution of this window.
		glm::ivec2 getResolution() const;
		/// Enforce a certain aspect ratio.
		void setAspectRatio(int numerator, int denominator) const;

		/// Specify a min/max width and height of this window to be enforced. 
		/// If a certain minimum/maximum should not be enforced, set the relevant 
		/// parameters to a negative value.
		void setSizeLimits(int widthMin, int heightMin, int widthMax, int heightMax) const;
		/// Get the current position of this window.
		glm::ivec2 getPosition() const;
		/// Set the current position of this window.
		void setPosition(int x, int y) const;
		/// Get the current size of the window.
		glm::ivec2 getSize() const;
		/// Set the size of the window.
		void setSize(int width, int height);
		/// Get the dimensions of the window (decorations included).
		/// \return Frame dimensions: (x, y, z, w) = (left, top, right, bottom)
		glm::ivec4 getFrameSize() const;
		/** Get the current size of this window's frame buffer. */
		glm::ivec2 getFrameBufferSize() const;

		/**
		 * \brief Set the icon for this window. 
		 * The resolution of the icons should preferably be one of 16x16, 32x32,
		 * 48x48, but can be any other. If no path is being provided, a default
		 * window icon will be loaded.
		 * \param iconPath File path to the icon image
		 * \param iconPathSmall File path to a small version of the icon image
		 */
		void setIcon(const char* iconPath = "", const char* iconPathSmall = "") const;
		/** Set the current title of this window. */
		void setTitle(const char* title) const;

		/** Set focus to this window. */
		void focus() const;
		/** Check if this window is currently focused. */
		bool isFocused() const;

		/** Check if the user can resize this window. */
		bool isResizable() const;
		/** Check if this window has decorations (border, close widget etc.). */
		bool isDecorated() const;
		/** Check if this window is always on-top. */
		bool isFloating() const;

		/** Restore this windows original video mode. */
		void restore() const;
		/** Minimize this window. */
		void minimize() const;
		/** Check if this window is currently minimized. */
		bool isMinimized() const;
		/** Check if this window is currently maximized. */
		bool isMaximized() const;

		/** Make this window visible. */
		void show() const;
		/** Make this window invisible. */
		void hide() const;
		/** Check if this window is visible. */
		bool isVisible() const;

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

		/** Buffer swapping */
		void swapBuffers() const;
		/** 
		 * Set the number of refreshes, that need to happen, before
		 * a refresh event occurs. 
		 */
		static void setSwapInterval(unsigned int interval);

		/** Set the current global clipboard string. */
		void setClipboardString(const char* str) const;
		/** Get the current global clipboard string. */
		const char* getClipboardString() const;

		/** Get the user's preferred monitor. */
		static GLFWmonitor* getPrimaryMonitor();
		/** Get all available monitors. */
		static GLFWmonitor** getMonitors(int* count);
		/** Get the currently used video mode used by a monitor. */
		static const GLFWvidmode* getVideoMode(GLFWmonitor* monitor);
		/** Get the supported video modes of a monitor. */
		static const GLFWvidmode* getVideoModes(GLFWmonitor* monitor, int* count);
		/** Get the physical size of a monitor in millimeters. */
		static glm::ivec2 getMonitorPhysicalSize(GLFWmonitor* monitor);
		/** Get the virtual position of a monitor in screen coordinates. */
		static glm::ivec2 getMonitorPosition(GLFWmonitor* monitor);
		/** Get the UTF-8 encoded monitor name. */
		static const char* getMonitorName(GLFWmonitor* monitor);
		/** Print information about all currently connected monitors to console. */
		static void printMonitorInformation();
		/** Set gamma correction. */
		static void setGammaRamp(GLFWmonitor* monitor, float exponent);
		/** Set gamma correction. */
		static void setGammaRamp(GLFWmonitor* monitor, 
								 int size, 
								 unsigned short* red,
								 unsigned short* green,
								 unsigned short* blue);

		/** Set the destruction flag of this window. */
		void closeWindow() const;
        /** Check if this window has successfully been initialized. */
        bool isInitialized() const;
		/** Check if this window's destruction flag is set. */
		bool shouldClose() const;
		/** Destroy this window. */
		void destroy() const;

	protected:
		unsigned int m_windowWidth;
		unsigned int m_windowHeight;
		std::string m_windowTitle;

		GLFWwindow* m_window;

		Timer m_timer;
		SceneSystem m_sceneSystem;
		EventSystem m_eventSystem;
		ShaderManager m_shaderManager;

		std::unique_ptr<Renderer> m_renderer;

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


		WindowCallbacks m_callbacks;


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