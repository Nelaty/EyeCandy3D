#pragma once
#include <vector>
#include <memory>

#include "GUIRenderer.h"
#include "GUIModel.h"

/*
* A GUISystem is a collection of GUIs and enables the switching thereof
*/
namespace ec_gui
{
	class GUI;
	class GUIController;

	class GUISystem
	{
	public:
		explicit GUISystem();
		GUISystem(const GUISystem& guiSystem) = delete;
		GUISystem& operator=(const GUISystem& guiSystem) = delete;
		GUISystem(GUISystem&& guiSystem) = default;
		GUISystem& operator=(GUISystem&& guiSystem) = default;
		~GUISystem();

		/** Get the model, which contains GUI data */
		GUIModel* GetModel();

	private:
		std::unique_ptr<GUIModel> m_guiModel;
		GUIRenderer m_guiRenderer;
		GUIController* m_guiController;
	};
}