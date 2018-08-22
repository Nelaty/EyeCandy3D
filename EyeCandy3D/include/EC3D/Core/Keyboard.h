#pragma once
#include <memory>

struct GLFWwindow;

namespace ec
{
	class Window;
	class EventSource;
	class EventQueue;

	class Keyboard
	{
	public: 
		using EventSource_Ptr = std::unique_ptr<EventSource>;

		explicit Keyboard();
		~Keyboard();

		/** Install the keyboard, which generates keyboard events. */
		void install(Window* window);
		/** Uninstall the keyboard. */
		void uninstall();
	
		EventSource* getEventSource() const;
		GLFWwindow* getWindow() const;

	private:
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);

		EventSource_Ptr m_eventSource = nullptr;
		EventQueue* m_eventQueue = nullptr;		
		GLFWwindow* m_window = nullptr;
	};
}