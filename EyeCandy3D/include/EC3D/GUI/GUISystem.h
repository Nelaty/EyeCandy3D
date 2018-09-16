#pragma once
#include "EC3D/Common/Common.h"

#include <memory>

namespace agui
{
	class Gui;
}

namespace ec
{
	class OpenGLInput;
	class OpenGLGraphics;

	class GuiController;
	class InputObservable;
	class Camera;
	
	class EC3D_DECLSPEC GuiSystem
	{
	public:
		using Gui_Type = agui::Gui;
		using Gui_Ptr = std::unique_ptr<Gui_Type>;
		using Controller_Type = OpenGLInput;
		using Controller_Ptr = std::unique_ptr<Controller_Type>;
		using GraphicsHandler_Type = OpenGLGraphics;
		using GraphicsHandler_Ptr = std::unique_ptr<GraphicsHandler_Type>;

		explicit GuiSystem(Camera* camera);
		GuiSystem(const GuiSystem& guiSystem) = delete;
		GuiSystem& operator=(const GuiSystem& guiSystem) = delete;
		GuiSystem(GuiSystem&& guiSystem) = default;
		GuiSystem& operator=(GuiSystem&& guiSystem) = default;
		~GuiSystem();

		/** Render the current gui or none if not existent */
		void render();

		/** Set the model */
		void setModel(Gui_Ptr gui);

		/** Get the model, which contains gui data */
		Gui_Type* getModel() const;

	private:
		void registerInputListener() const;
		void unregisterInputListener() const;

		Camera* m_camera;
		InputObservable* m_inputObservable;

		Gui_Ptr m_model;
		Controller_Ptr m_inputListener{};
		GraphicsHandler_Ptr m_graphicsHandler;
	};
}