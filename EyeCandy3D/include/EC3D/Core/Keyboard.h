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

	public:
		explicit Keyboard();
		~Keyboard();

		/** Install the keyboard, which generates keyboard events. */
		void Install(Window* window);
		/** Uninstall the keyboard. */
		void Uninstall();
	
		EventSource* GetEventSource();
		GLFWwindow* GetWindow();

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);

		EventSource_Ptr m_eventSource;
		EventQueue* m_eventQueue;		
		GLFWwindow* m_window;
	};
}