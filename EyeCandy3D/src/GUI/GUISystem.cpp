#include "EC3D/Gui/GuiSystem.h"

#include "EC3D/Gui/Backend/OpenGLInput.h"
#include "Agui/Gui.hpp"

namespace ec_gui
{

	GuiSystem::GuiSystem()
	{
		m_model = std::make_unique<agui::Gui>();
		m_inputListener = std::make_unique<Controller_Type>();
	}

	GuiSystem::~GuiSystem()
	= default;

	GuiSystem::Gui_Type* GuiSystem::getModel() const
	{
		return m_model.get();
	}

	
}