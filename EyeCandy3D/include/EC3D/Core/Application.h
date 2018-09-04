#pragma once
#include <GL/glew.h>

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
	class Application
	{
	public:
		using Window_Ptr = std::unique_ptr<Window>;


		/**
		 * \brief Application constructor.
		 * \param windowWidth Width of the first window in pixels.
		 * \param windowHeight Height of the first window in pixels.
		 * \param windowTitle Title of the first window.
		 * \param windowName Identifier  of the first window.
		 */
		explicit Application(unsigned int windowWidth,
							 unsigned int windowHeight,
							 const std::string& windowTitle,
							 const std::string& windowName);
		~Application();

		/** Should be called to start the application */
		virtual void startMainLoop();

		/** Update all windows */
		virtual void tick();
		/** Render all windows */
		virtual void render();

		/** Init function implementation. */
		virtual bool initImpl();

		/** Initialize OpenGL. */
		void initOpenGl();

		/** Main loop function implementation */
		virtual void mainLoopImpl();

		/** Print the versions of used libraries to console. */
		void printVersions() const;

		/**
		 * Create a new window and add it to the current list of windows.
		 * \tparam WindowClass Needs to have constructor with a signature of: (unsigned, unsigned, const std::string&)
		 * \param width Width of the window in pixels.
		 * \param height Height of the window in pixels.
		 * \param title Title of the window.
		 * \param name Identifier of the window.
		 * \return nullptr if a window with the given name already exists, pointer to the newly created window otherwise.
		 */
		template<class WindowClass>
		typename std::enable_if<std::is_constructible<
			WindowClass, unsigned int, unsigned int, const std::string&>::value, WindowClass>::type*
		createWindow(unsigned int width,
		             unsigned int height,
		             const std::string& title,
		             const std::string& name);

	private:
		/** Initialize this application. */
		void init();
		/** Cleanup remaining resources. */
		static void cleanup();

		bool m_running;

		std::map<std::string, Window_Ptr> m_windows;
	};
	
	template <class WindowClass>
	typename std::enable_if<std::is_constructible<
		WindowClass, unsigned int, unsigned int, const std::string&>::value, WindowClass>::type*
	Application::createWindow(
		unsigned width, unsigned height, const std::string& title,
		const std::string& name)
	{
		using WindowClass_Ptr = std::unique_ptr<WindowClass>;

		if (m_windows.find(name) != m_windows.end())
		{
			printf("ERROR: Couldn't create window!\n");
			printf("       A window with name \"%s\" already exists!\n", name.c_str());
			return nullptr;
		}

		WindowClass_Ptr window = std::make_unique<WindowClass>(width, height, title);
		m_windows[name] = std::move(window);

		if(m_windows.size() == 1)
		{
			init();
		}

		return static_cast<WindowClass*>(m_windows[name].get());
	}
}
