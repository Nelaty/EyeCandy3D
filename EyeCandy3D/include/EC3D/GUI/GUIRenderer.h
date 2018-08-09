#pragma once
#include <vector>
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

	class GUIModel;

	/*
	* Parameter object
	* Contains viable information for rendering a GUI
	*/
	struct GUIRenderingParameterList
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
	class GUIRenderingContext
	{
	public:
		GUIRenderingContext();
		~GUIRenderingContext();

		const glm::mat4& Top() const;

		void Save(const glm::mat4& mat);
		void Restore();

		/* Get the current global matrix */
		const glm::mat4& GetGlobalMat();

		/*
		* Calculate the global matrix of the specified widget and 
		* save it inside the context
		*/
		void UpdateGlobalMat(Widget* widget);

		GUIRenderingParameterList m_params;

	private:
		glm::mat4 m_globalMat;

		std::stack<glm::mat4> m_mats;
	};
	
	/*
	* A GUIRenderer is responsible for rendering the currently active
	* GUI.
	*/
	class GUIRenderer
	{
	public:
		explicit GUIRenderer();
		~GUIRenderer();

		/** Initialize the renderer with a given model */
		void Init(GUIModel* guiModel);

		/* Render the currently active GUI */
		void Render(GUIRenderingParameterList params);

		/* Shader access. Will be used to render everything */
		ec::Shader* GetShader();
		void SetShader(ec::Shader* shader);

		/* Visitor rendering functions */
		void Render(Widget* widget, GUIRenderingContext& context);
		void Render(Text* text, GUIRenderingContext& context);
		void Render(Screen* screen, GUIRenderingContext& context);
		void Render(Window* window, GUIRenderingContext& context);

	private:
		/* Accepts a widget and renders its hierarchy */
		void RenderGUI(Widget* widget, GUIRenderingContext& context);
		/* Renders the core elements every widgets possesses */
		void RenderCoreElements(Widget* widget, GUIRenderingContext& context);

		GUIModel* m_guiModel;
		ec::Shader* m_shader;
	};
}