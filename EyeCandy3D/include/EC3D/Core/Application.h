#pragma once

#include <memory>
#include <map>
#include <string>

#include <type_traits>

namespace ec
{
	class Window;

	/**
	 * An application is the main class of a program.
	 * .....
	 */
	class Application
	{
	public:
		using Window_Ptr = std::unique_ptr<Window>;


		explicit Application(unsigned int windowWidth,
							 unsigned int windowHeight,
							 const std::string& windoTitle,
							 const std::string& windowName);
		~Application();

		/** Should be called to start the application */
		virtual void startMainLoop();

		/** Update all windows */
		virtual void tick();
		/** Render all windows */
		virtual void render();

		void init();
		void cleanup();

		/* Init function implementation */
		virtual bool initImpl();

		void initOpenGl();
		void initAgui();

		/* Main loop function implementation */
		virtual void mainLoopImpl();
		
		void printVersions() const;

		/**
		 * Create a new window and add it to the current list of windows.
		 * \return nullptr if a window with the given name already exists, pointer to the newly created window otherwise.
		 */
		template<class WindowClass>
		typename std::enable_if < std::is_constructible<
			WindowClass, unsigned int, unsigned int, const std::string&>::value, WindowClass>::type*
		createWindow(unsigned int width,
					 unsigned int height,
					 const std::string& title,
					 const std::string& name)
		{
			if(m_windows.find(name) != m_windows.end())
			{
				printf("ERROR: Couldn't create window!\n");
				printf("       A window with name \"%s\" already exists!\n", name.c_str());
				return nullptr;
			}

			Window_Ptr window = std::make_unique<WindowClass>(width, height, title);
			m_windows[name] = std::move(window);

			return m_windows[name].get();
		}

	private:
		bool m_running;

		std::map<std::string, Window_Ptr> m_windows;
	};
}