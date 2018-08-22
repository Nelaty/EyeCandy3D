#pragma once
#include "Agui/Input.hpp"
#include "EC3D/Core/InputListener.h"

#include "EC3D/Core/InputEvent.h"

#include <vector>

namespace agui
{
	/**
	 * OpenGL GUI back end class for input. It needs to be a agui::Input
	 * for it to be usable with Agui and it needs to be a ec::InputListener,
	 * so it can actually receive input.
	 */

	class OpenGLInput : public Input, public ec::InputListener
	{
		
	public:
		explicit OpenGLInput();
		virtual ~OpenGLInput();
		
		double getTime() const override;
		
	protected:
		void processEvent(const ec::InputEvent& event) override;

	private:
		bool shift;
		bool control;
		bool alt;
		bool meta;

		ec::KeyboardEvent prevEvent;
		std::vector<ec::KeyboardEvent> keyEvents;

		MouseInput createMouse(const ec::InputEvent& event);
		KeyboardInput createKeyboard(const ec::KeyboardEvent& event,
									 bool isKeyDown,
									 bool isRepeat );

		ExtendedKeyEnum getExtendedKey(int key) const;
		bool isModifierKey(int key);
		KeyEnum getKeyFromKeycode(int keycode) const;
	};
}
