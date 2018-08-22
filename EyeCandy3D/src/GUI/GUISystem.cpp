#include "EC3D/Gui/GUISystem.h"
#include "EC3D/Gui/Gui.h"

namespace ec_gui
{

	GuiSystem::GuiSystem()
	= default;

	GuiSystem::~GuiSystem()
	= default;

	ec_gui::GuiModel* GuiSystem::getModel() const
	{
		return m_guiModel.get();
	}
}