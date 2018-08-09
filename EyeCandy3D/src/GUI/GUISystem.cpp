#include "EC3D/GUI/GUISystem.h"
#include "EC3D/GUI/GUI.h"

#include <algorithm>

namespace ec_gui
{

	GUISystem::GUISystem()
	{
	}

	GUISystem::~GUISystem()
	{
	}

	ec_gui::GUIModel* GUISystem::GetModel()
	{
		return m_guiModel.get();
	}
}