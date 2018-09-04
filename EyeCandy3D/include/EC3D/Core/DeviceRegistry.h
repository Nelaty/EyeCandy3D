#pragma once
#include "EC3D/Core/Keyboard.h"
#include "EC3D/Core/Mouse.h"

#include <memory>

namespace ec
{
	class Window;

	class DeviceRegistry
	{
	public:
		explicit DeviceRegistry(Window* window);
		~DeviceRegistry();

		/** Install every device */
		void installAll();
		/** Uninstall every device */
		void uninstallAll();

		/** Install a keyboard device */
		void installKeyboard();
		/** Uninstall a keyboard device */
		void uninstallKeyboard();

		/** Install a mouse device */
		void installMouse();
		/** Uninstall a mouse device */
		void uninstallMouse();

	private:
		Window* m_window;

		Keyboard m_keyboard;
		Mouse m_mouse;
	};
}