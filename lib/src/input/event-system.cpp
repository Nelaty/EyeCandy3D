#include "ec3/input/event-system.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ec
{
	EventSystem::EventSystem(Window* window)
		: m_window{window},
		m_deviceRegistry{window}
	{
	}

	EventSystem::~EventSystem()
	= default;

	void EventSystem::dispatchEvent(const InputEvent& event)
	{
		m_inputObservable.receiveEvent(event);
	}

	void EventSystem::informAll()
	{
		m_inputObservable.informAll();
	}

	void EventSystem::registerInputListener(InputListener* inputListener)
	{
		m_inputObservable.registerInputListener(inputListener);
	}

	bool EventSystem::unregisterInputListener(InputListener* inputListener)
	{
		return m_inputObservable.unregisterInputListener(inputListener);
	}

	bool EventSystem::contains(InputListener* inputListener)
	{
		return m_inputObservable.contains(inputListener);
	}

	void EventSystem::unregisterAllInputListeners()
	{
		m_inputObservable.unregisterAllInputListeners();
	}

	Window* EventSystem::getWindow() const
	{
		return m_window;
	}

	DeviceRegistry& EventSystem::getDeviceRegistry()
	{
		return m_deviceRegistry;
	}

	void EventSystem::pollEvents()
	{
		glfwPollEvents();
	}
}
