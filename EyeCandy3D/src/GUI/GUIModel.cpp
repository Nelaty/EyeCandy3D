#include "EC3D/Gui/GuiModel.h"
#include "EC3D/Gui/Gui.h"

#include <algorithm>

namespace ec_gui 
{
	
	GuiModel::GuiModel() = default;

	GuiModel::~GuiModel() = default;

	bool GuiModel::addGui(Gui* gui)
	{
		if(getGui(gui->getName()))
		{
			return false;
		}
		
		m_guis.push_back(gui);
		return true;
	}

	bool GuiModel::removeGui(Gui* gui)
	{
		const auto foundGui = std::remove(m_guis.begin(),
										  m_guis.end(),
										  gui);

		return foundGui != m_guis.end();
	}

	bool GuiModel::removeGui(const std::string& name)
	{
		const auto foundGui = std::find_if(m_guis.begin(),
										   m_guis.end(),
										   [&](const Gui* gui)
		{
			return gui->getName() == name;
		});

		return foundGui != m_guis.end();
	}

	ec_gui::Gui* GuiModel::getGui(const std::string& name)
	{
		const auto foundGui = std::find_if(m_guis.begin(),
										   m_guis.end(),
										   [&](const Gui* gui)
		{
			return gui->getName() == name;
		});

		if(foundGui == m_guis.end()) return nullptr;

		return *foundGui;
	}

	const std::vector<Gui*>& GuiModel::getAllGuIs() const
	{
		return m_guis;
	}

}