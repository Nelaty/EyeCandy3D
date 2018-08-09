#include "EC3D/GUI/GUIModel.h"
#include "EC3D/GUI/GUI.h"

#include <algorithm>

namespace ec_gui 
{
	
	GUIModel::GUIModel()
	{
	}

	GUIModel::~GUIModel()
	{
	}

	bool GUIModel::AddGUI(GUI* gui)
	{
		if(GetGUI(gui->GetName())) return false;

		m_guis.push_back(gui);
	}

	bool GUIModel::RemoveGUI(GUI* gui)
	{
		auto foundGUI = std::remove(m_guis.begin(),
									m_guis.end(),
									gui);

		return foundGUI != m_guis.end();
	}

	bool GUIModel::RemoveGUI(const std::string& name)
	{
		auto foundGUI = std::find_if(m_guis.begin(),
									 m_guis.end(),
									 [&](const GUI* gui)
		{
			return gui->GetName() == name;
		});

		return foundGUI != m_guis.end();
	}

	ec_gui::GUI* GUIModel::GetGUI(const std::string& name)
	{
		auto foundGUI = std::find_if(m_guis.begin(),
									 m_guis.end(),
									 [&](const GUI* gui)
		{
			return gui->GetName() == name;
		});

		if(foundGUI == m_guis.end()) return nullptr;

		return *foundGUI;
	}

	const std::vector<GUI*>& GUIModel::GetAllGUIs() const
	{
		return m_guis;
	}

}