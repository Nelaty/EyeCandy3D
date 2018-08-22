#pragma once
#include <memory>

#include "GuiRenderer.h"
#include "GuiModel.h"

/*
* A GUISystem is a collection of GUIs and enables the switching thereof
*/
namespace ec_gui
{
	class Gui;
	class GuiController;

	class GuiSystem
	{
	public:
		explicit GuiSystem();
		GuiSystem(const GuiSystem& guiSystem) = delete;
		GuiSystem& operator=(const GuiSystem& guiSystem) = delete;
		GuiSystem(GuiSystem&& guiSystem) = default;
		GuiSystem& operator=(GuiSystem&& guiSystem) = default;
		~GuiSystem();

		/** Get the model, which contains GUI data */
		GuiModel* getModel() const;

	private:
		std::unique_ptr<GuiModel> m_guiModel;
		GuiRenderer m_guiRenderer{};
		GuiController* m_guiController{};
	};
}