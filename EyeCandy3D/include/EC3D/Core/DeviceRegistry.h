#pragma once
#include "EC3D/Core/Keyboard.h"
#include "EC3D/Core/Mouse.h"

namespace ec
{
	class Window;

	class DeviceRegistry
	{
	public:
		explicit DeviceRegistry(Window* window);
		~DeviceRegistry();

		/** Install every device */
		void InstallAll();
		/** Uninstall every device */
		void UninstallAll();

		/** Install a keyboard device */
		void InstallKeyboard();
		/** Uninstall a keyboard device */
		void UninstallKeyboard();

		/** Install a mouse device */
		void InstallMouse();
		/** Uninstall a mouse device */
		void UninstallMouse();

	private:
		Window* m_window;

		Keyboard m_keyboard;
		Mouse m_mouse;
	};
}