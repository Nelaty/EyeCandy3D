#pragma once
#include "EC3D/Common/Common.h"

#include "EC3D/Core/Keyboard.h"
#include "EC3D/Core/Mouse.h"

#include <memory>

namespace ec
{
	class Window;

	class EC3D_DECLSPEC DeviceRegistry
	{
	public:
		explicit DeviceRegistry(Window* window);
		~DeviceRegistry();

		/** 
		 * \brief Install every device.
		 */
		void installAll() const;
		/** 
		 * \brief Uninstall every device.
		 */
		void uninstallAll() const;

		/** 
		 * \brief Install a keyboard device.
		 */
		void installKeyboard() const;
		/** 
		 * \brief Uninstall a keyboard device.
		 */
		void uninstallKeyboard() const;
		/** 
		 * \brief Get the currently used keyboard.
		 */
		Keyboard* getKeyboard() const;

		/** 
		 * \brief Install a mouse device.
		 */
		void installMouse() const;
		/** 
		 * \brief Uninstall a mouse device.
		 */
		void uninstallMouse() const;
		/** 
		 * \brief Get the currently used mouse.
		 */
		Mouse* getMouse() const;

	private:
		Window* m_window;

		std::unique_ptr<Keyboard> m_keyboard;
		std::unique_ptr<Mouse> m_mouse;
	};
}