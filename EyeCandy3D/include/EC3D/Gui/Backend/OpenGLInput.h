#pragma once
#include "Agui/Input.hpp"
#include "EC3D/Core/InputListener.h"
#include "EC3D/Common/Common.h"

#include "EC3D/Core/InputEvent.h"

#include <vector>

namespace ec
{
	/**
	 * OpenGL GUI back end class for input. It needs to be a agui::Input
	 * for it to be usable with Agui and it needs to be a ec::InputListener,
	 * so it can actually receive input.
	 */

	class EC3D_DECLSPEC OpenGLInput : public agui::Input, public ec::InputListener
	{
		
	public:
		explicit OpenGLInput();
		virtual ~OpenGLInput();
		
		double getTime() const override;
		
	protected:
		void processEvent(const ec::InputEvent& event) override;

	private:
		static agui::MouseInput createMouse(const ec::InputEvent& event,
									 InputType inputType);
		static agui::KeyboardInput createKeyboard(const ec::InputEvent& event, 
										   InputType inputType,
										   bool isKeyDown,
										   bool isRepeat );

		static agui::ExtendedKeyEnum getExtendedKey(int key);
		static bool isModifierKey(int key);
		static agui::KeyEnum getKeyFromKeycode(int keycode);
	};
}
