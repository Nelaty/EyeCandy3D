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
	{
	}

	void DeviceRegistry::InstallAll()
	{
		InstallKeyboard();
		InstallMouse();
	}

	void DeviceRegistry::UninstallAll()
	{
		UninstallKeyboard();
		UninstallMouse();
	}

	void DeviceRegistry::InstallKeyboard()
	{
		m_keyboard.Install(m_window);
	}

	void DeviceRegistry::UninstallKeyboard()
	{
		m_keyboard.Uninstall();
	}

	void DeviceRegistry::InstallMouse()
	{
		m_mouse.Install(m_window);
	}

	void DeviceRegistry::UninstallMouse()
	{
		m_mouse.Uninstall();
	}
}