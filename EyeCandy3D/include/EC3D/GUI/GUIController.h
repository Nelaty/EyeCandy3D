#pragma once
#include "EC3D/Core/InputListener.h"

/*
* Responsible to notify the currently active GUI about input events
*/
namespace ec_gui
{
	class GUISystem;
	class InputEvent;

	class GUIController : public ec::InputListener
	{
	public:
		explicit GUIController();
		~GUIController();

		/* Get, set the controlled GUI */
		GUISystem* GetGUISystem();
		void SetGUISystem(GUISystem* guiSystem);

	private:
		GUISystem* m_guiSystem;
	protected:
		virtual void ProcessEvent(const ec::InputEvent& event) override;

	};
}