#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/SceneRenderer.h"

#include <map>

namespace ec
{
	class Window;
	class Freetype;

	/**
	 * \brief A Renderer is responsible for rendering storing and using
	 * scene renderers.
	 */
	class EC3D_DECLSPEC Renderer
	{
	public:
		/**
		 * \brief Renderer constructor
		 * \param window The window to render into
		 */
		explicit Renderer();
		~Renderer();

		void init(Shader* guiShader, Shader* textShader) const;

		/**
		 * \brief Update all gui systems.
		 */
		void tick();
		/**
		 * \brief Render to the currently active window.
		 */
		void render(Window* window) const;

		/** 
		 * \brief Change to an active renderer with the given name. 
		 * \details The renderer has to be registered.
		 */
		void changeRenderer(const std::string& name);
		/**
		* \brief Change the current scene renderer to a given one.
		* The given renderer doesn't have to be registered
		*/
		void changeRenderer(SceneRenderer* renderer);

		/** 
		 * \brief Register a new scene renderer. 
		 * \param name The id of the new registered renderer.
		 * \param renderer The new renderer to register.
		 */
		void registerSceneRenderer(const std::string& name, SceneRenderer* renderer);
		/**
		 * \brief Unregister an already registered scene renderer 
		 * with the given name.
		 * \return The unregistered scene renderer if it exist, 
		 * nullptr otherwise. 
		 */
		SceneRenderer* unregisterSceneRenderer(const std::string& name);

		/**
		* \brief Get a scene renderer with the given name.
		* \return The found scene renderer if it exist, nullptr 
		* otherwise. 
		*/
		SceneRenderer* getSceneRenderer(const std::string& name);

	protected:
		Window* m_window;

		SceneRenderer* m_activeRenderer;
		SceneRenderer* m_lastRenderer;

		std::map<std::string, SceneRenderer*> m_renderer;
	};
}
