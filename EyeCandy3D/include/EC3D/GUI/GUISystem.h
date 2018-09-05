#pragma once
#include "EC3D/Common/Common.h"

#include <memory>

namespace agui
{
	class Gui;
	class OpenGLInput;
}


namespace ec_gui
{
	class GuiController;

	class EC3D_DECLSPEC GuiSystem
	{
	public:
		using Gui_Type = agui::Gui;
		using Gui_Ptr = std::unique_ptr<Gui_Type>;
		using Controller_Type = agui::OpenGLInput;
		using Controller_Ptr = std::unique_ptr<Controller_Type>;

		explicit GuiSystem();
		GuiSystem(const GuiSystem& guiSystem) = delete;
		GuiSystem& operator=(const GuiSystem& guiSystem) = delete;
		GuiSystem(GuiSystem&& guiSystem) = default;
		GuiSystem& operator=(GuiSystem&& guiSystem) = default;
		~GuiSystem();

		/** Get the model, which contains gui data */
		Gui_Type* getModel() const;

	private:
		Gui_Ptr m_model;
		Controller_Ptr m_inputListener{};
	};
}