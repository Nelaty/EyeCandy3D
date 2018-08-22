#include "EC3D/Core/DeviceRegistry.h"
#include "EC3D/Core/Window.h"

#include <GLFW/glfw3.h>


namespace ec
{
	DeviceRegistry::DeviceRegistry(Window* window)
		: m_window{window}
	{		
	}

	DeviceRegistry::~DeviceRegistry()
	= default;

	void DeviceRegistry::installAll()
	{
		installKeyboard();
		installMouse();
	}

	void DeviceRegistry::uninstallAll()
	{
		uninstallKeyboard();
		uninstallMouse();
	}

	void DeviceRegistry::installKeyboard()
	{
		m_keyboard.install(m_window);
	}

	void DeviceRegistry::uninstallKeyboard()
	{
		m_keyboard.uninstall();
	}

	void DeviceRegistry::installMouse()
	{
		m_mouse.install(m_window);
	}

	void DeviceRegistry::uninstallMouse()
	{
		m_mouse.uninstall();
	}
}