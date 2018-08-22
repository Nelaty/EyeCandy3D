#pragma once

#include <vector>
#include <string>

namespace ec_gui
{
	class Gui;

	class GuiModel
	{
	public:
		explicit GuiModel();
		~GuiModel();

		/* Add a new gui */
		bool addGui(Gui* gui);
		bool removeGui(Gui* gui);
		bool removeGui(const std::string& name);

		/* GUI access */
		Gui* getGui(const std::string& name);
		const std::vector<Gui*>& getAllGuIs() const;

	private:
		std::vector<Gui*> m_guis;
	};
}