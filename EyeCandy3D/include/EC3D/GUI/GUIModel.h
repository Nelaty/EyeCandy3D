#pragma once

#include <vector>
#include <string>

namespace ec_gui
{
	class GUI;

	class GUIModel
	{
	public:
		explicit GUIModel();
		~GUIModel();

		/* Add a new gui */
		bool AddGUI(GUI* gui);
		bool RemoveGUI(GUI* gui);
		bool RemoveGUI(const std::string& name);

		/* GUI access */
		GUI* GetGUI(const std::string& name);
		const std::vector<GUI*>& GetAllGUIs() const;

	private:
		std::vector<GUI*> m_guis;
	};
}