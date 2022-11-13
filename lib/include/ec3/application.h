#pragma once
#include <GL/glew.h>
#include "ec3/common/common.h"
#include "ec3/common/logging.h"
#include "ec3/window/window-creation-hints.h"

#include <functional>
#include <memory>
#include <map>
#include <string>
#include <type_traits>

namespace ec
{
	class Window;

	/**
	 * An application is the main class of a program.
	 */
	class EC3D_DECLSPEC Application
	{
	public:
		using Window_Ptr = std::unique_ptr<Window>;

		/** \brief Application constructor. */
		explicit Application();
		~Application();

		/// Should be called to start the application.
		virtual void startMainLoop();

		/// Stop the application. 
		virtual void kill();

		/// Update all windows. 
		virtual void tick();
		/// Render all windows.
		virtual void render();

		/// Init function implementation. 
		/// \return True if implementation is successful, false
		///         otherwise.
		virtual bool initImpl();

		/// Initialize OpenGL.
		static void initOpenGl();

		/// Main loop function implementation.
		virtual void mainLoopImpl();

		/// Print the versions of used libraries to console.
		static void printVersions();

		/// Set the callback for when a new monitor connects.
		/// \param cb The new monitor connected callback.
		static void setMonitorConnectedCallback(const std::function<void(GLFWmonitor*)>& cb);

		/// Set the callback for when a monitor disconnects. 
		/// \param cb The new monitor disconnected callback.
		static void setMonitorDisconnectedCallback(const std::function<void(GLFWmonitor*)>& cb);

		/// Create a new window and add it to the current list of windows.
		/// \tparam WindowClass Needs to have constructor with a signature of: (unsigned, unsigned, const std::string&)
		/// \param width Width of the window in pixels.
		/// \param height Height of the window in pixels.
		/// \param title Title of the window.
		/// \param name Identifier of the window.
		/// \param hints Hints for the window to be created.
		/// \return nullptr if a window with the given name already exists, pointer to the newly created window otherwise.
		template<class WindowClass>
		typename std::enable_if<std::is_constructible<
			WindowClass, unsigned int, unsigned int, const std::string&>::value, WindowClass>::type*
		createWindow(unsigned int width,
		             unsigned int height,
		             const std::string& title,
		             const std::string& name,
					 WindowCreationHints hints = WindowCreationHints());

	protected:
		/// Destroy all windows, which shall be closed. 
		virtual void closeDeadWindows();

		/// The monitor callback is called when a monitor is 
		/// connected or disconnected.
		/// \param monitor The monitor that was (dis)connected.
		/// \param event Whether the monitor was turned on or off.
		static void monitorCallback(GLFWmonitor* monitor, int event);
	
	private:
		/// Initialize this application.
		void init();
		/// Cleanup remaining resources.
		static void cleanup();

		static std::function<void(GLFWmonitor*)> s_monitorConnectedCallback;
		static std::function<void(GLFWmonitor*)> s_monitorDisconnectedCallback;

		bool m_running;

		std::map<std::string, Window_Ptr> m_windows;
	};
	
	template <class WindowClass>
	typename std::enable_if<std::is_constructible<
		WindowClass, unsigned int, unsigned int, const std::string&>::value, WindowClass>::type*
	Application::createWindow(unsigned width, 
							  unsigned height, 
							  const std::string& title,
							  const std::string& name,
							  WindowCreationHints hints)
	{
		using WindowClass_Ptr = std::unique_ptr<WindowClass>;

		if (m_windows.find(name) != m_windows.end())
		{
            Logger::error(std::string("Failed to create window with name '") + name + "' (already exists)");
			return nullptr;
		}

		hints.setHints();
		WindowClass_Ptr window = std::make_unique<WindowClass>(width, height, title);
		m_windows[name] = std::move(window);

		if(m_windows.size() == 1)
		{
			init();
		}

		return static_cast<WindowClass*>(m_windows[name].get());
	}
}
