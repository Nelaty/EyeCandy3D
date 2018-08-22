#pragma once
#include <stack>

#include <glm/glm.hpp>


namespace ec
{
	class Shader;
	class Freetype;
}

namespace ec_gui
{
	class Widget;
	class Text;
	class Screen;
	class Window;

	class GuiModel;

	/*
	* Parameter object
	* Contains viable information for rendering a GUI
	*/
	struct GuiRenderingParameterList
	{
		ec::Freetype* m_freetype;
		float m_scaleX;
		float m_scaleY;

		int m_windowWidth;
		int m_windowHeight;
	};

	/*
	* A rendering context saves intermediate state while rendering.
	* This is necessary, since the GUI itself is very lightweight and
	* shouldn't know anything about rendering.
	*/
	class GuiRenderingContext
	{
	public:
		explicit GuiRenderingContext();
		~GuiRenderingContext();

		const glm::mat4& top() const;

		void save(const glm::mat4& mat);
		void restore();

		/* Get the current global matrix */
		const glm::mat4& getGlobalMat() const;

		/*
		* Calculate the global matrix of the specified widget and 
		* save it inside the context
		*/
		void updateGlobalMat(Widget* widget);

		GuiRenderingParameterList m_params;

	private:
		glm::mat4 m_globalMat;

		std::stack<glm::mat4> m_mats;
	};
	
	/*
	* A GUIRenderer is responsible for rendering the currently active
	* GUI.
	*/
	class GuiRenderer
	{
	public:
		explicit GuiRenderer();
		~GuiRenderer();

		/** Initialize the renderer with a given model */
		void init(GuiModel* guiModel);

		/* Render the currently active GUI */
		void render(GuiRenderingParameterList params);

		/* Shader access. Will be used to render everything */
		ec::Shader* getShader() const;
		void setShader(ec::Shader* shader);

		/* Visitor rendering functions */
		void render(Widget* widget, GuiRenderingContext& context);
		void render(Text* text, GuiRenderingContext& context);
		void render(Screen* screen, GuiRenderingContext& context);
		void render(Window* window, GuiRenderingContext& context);

	private:
		/* Accepts a widget and renders its hierarchy */
		void renderGui(Widget* widget, GuiRenderingContext& context);
		/* Renders the core elements every widgets possesses */
		void renderCoreElements(Widget* widget, GuiRenderingContext& context);

		GuiModel* m_guiModel;
		ec::Shader* m_shader;
	};
}