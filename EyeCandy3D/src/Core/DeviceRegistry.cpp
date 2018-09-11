#include "EC3D/Core/DeviceRegistry.h"
#include "EC3D/Core/Window.h"

namespace ec
{
	DeviceRegistry::DeviceRegistry(Window* window)
		: m_window{window}
	{
		m_keyboard = std::make_unique<Keyboard>();
		m_mouse = std::make_unique<Mouse>();
	}

	DeviceRegistry::~DeviceRegistry()
	= default;

	void DeviceRegistry::installAll() const
	{
		installKeyboard();
		installMouse();
	}

	void DeviceRegistry::uninstallAll() const
	{
		uninstallKeyboard();
		uninstallMouse();
	}

	void DeviceRegistry::installKeyboard() const
	{
		m_keyboard->install(m_window);
	}

	void DeviceRegistry::uninstallKeyboard() const
	{
		m_keyboard->uninstall();
	}

	Keyboard* DeviceRegistry::getKeyboard() const
	{
		return m_keyboard.get();
	}

	void DeviceRegistry::installMouse() const
	{
		m_mouse->install(m_window);
	}

	void DeviceRegistry::uninstallMouse() const
	{
		m_mouse->uninstall();
	}

	Mouse* DeviceRegistry::getMouse() const
	{
		return m_mouse.get();
	}
}
