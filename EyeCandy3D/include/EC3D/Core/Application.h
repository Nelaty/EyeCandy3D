#pragma once

#include <memory>
#include <map>

namespace ec
{
	class Window;

	class Application
	{
	public:
		using Window_Ptr = std::unique_ptr<Window>;

	public:
		explicit Application(const unsigned int windowWidth,
							 const unsigned int windowHeight,
							 const std::string& windoTitle,
							 const std::string& windowName);
		~Application();

		/**
		 * Create a new window and add it to the current list of windows.
		 * \return False it a window with the given name already exists, true otherwise.
		 */
		bool CreateWindow(unsigned int width,
						  unsigned int height,
						  const std::string& title,
						  const std::string& name);

	private:
		std::map<std::string, Window_Ptr> m_windows;
	};
}