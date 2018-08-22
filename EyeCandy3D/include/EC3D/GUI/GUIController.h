#pragma once
#include "EC3D/Core/InputListener.h"

/*
* Responsible to notify the currently active GUI about input events
*/
namespace ec_gui
{
	class GuiSystem;
	struct InputEvent;

	class GuiController : public ec::InputListener
	{
	public:
		explicit GuiController();
		~GuiController();

		/* Get, set the controlled GUI */
		GuiSystem* getGuiSystem() const;
		void setGuiSystem(GuiSystem* guiSystem);

	protected:
		void processEvent(const ec::InputEvent& event) override;

	private:
		GuiSystem* m_guiSystem;
	};
}