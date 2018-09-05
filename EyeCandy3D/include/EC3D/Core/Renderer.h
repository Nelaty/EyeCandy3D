#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/Core/SceneRenderer.h"

#include <map>

namespace ec
{
	class Window;

	/**
	 * A Renderer is responsible for rendering storing and using
	 * scene renderers.
	 */
	class EC3D_DECLSPEC Renderer
	{
	public:
		explicit Renderer();
		~Renderer();

		void render(Window* window) const;

		/** 
		 * Change to an active renderer with the given name. 
		 * The renderer has to be registered.
		 */
		void changeRenderer(const std::string& name);
		/**
		* Change the current scene renderer to a given on.
		* The given renderer doesn't have to be registered
		*/
		void changeRenderer(SceneRenderer* renderer);

		/** Register a new scene renderer. */
		void registerSceneRenderer(const std::string& name, SceneRenderer* renderer);
		/**
		 * Unregister an already registered scene renderer with the given name.
		 * \return The unregistered scene renderer if it exist, nullptr otherwise. 
		 */
		SceneRenderer* unregisterSceneRenderer(const std::string& name);

		/**
		* Get a scene renderer with the given name.
		* \return The found scene renderer if it exist, nullptr otherwise. 
		*/
		SceneRenderer* getSceneRenderer(const std::string& name);

	protected:		
		SceneRenderer* m_activeRenderer;
		SceneRenderer* m_lastRenderer;

		std::map<std::string, SceneRenderer*> m_renderer;
	};
}