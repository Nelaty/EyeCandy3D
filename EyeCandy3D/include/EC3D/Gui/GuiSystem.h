#pragma once
#include "EC3D/Common/Common.h"

#include <memory>
#include "Backend/OpenGLInput.h"

namespace agui
{
	class Gui;
}

namespace ec
{
	class OpenGLInput;
	class OpenGLGraphics;

	class GuiController;
	class Camera;
	class Window;

	struct GuiRenderContext;
	
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
		void render(const GuiRenderContext& context) const;

		/** Set the model */
		void setModel(Gui_Ptr gui);

		/** Get the model, which contains gui data */
		Gui_Type* getModel() const;

		/** Get the OpenGl graphics handler. */
		GraphicsHandler_Type* getGraphicsHandler() const;
		/** Get the OpenGl input handler. */
		Controller_Type* getInputHandler() const;

		/** Enables the gui to receive events. */
		void registerInputListener() const;
		/** Disables events for this gui. */
		void unregisterInputListener() const;

	private:
		Camera* m_camera;
		Window* m_window;

		Gui_Ptr m_model;
		Controller_Ptr m_inputListener{};
		GraphicsHandler_Ptr m_graphicsHandler;
	};
}
