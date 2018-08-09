#pragma once
#include "EC3D/Core/Frame.h"
#include "EC3D/Core/SceneRenderer.h"

#include <map>

namespace ec
{
	class Window;

	/**
	 * A Renderer is responsible for rendering storing and using
	 * scene renderers.
	 */
	class Renderer
	{
	public:
		explicit Renderer();
		~Renderer();

		void Render(Window* window);

		/** 
		 * Change to an active renderer with the given name. 
		 * The renderer has to be registered.
		 */
		void ChangeRenderer(const std::string& name);

		/** Register a new scene renderer. */
		void RegisterSceneRenderer(const std::string& name, SceneRenderer* renderer);
		/**
		 * Unregister an already registered scene renderer with the given name.
		 * \return The unregistered scene renderer if it exist, nullptr otherwise. 
		 */
		SceneRenderer* UnregisterSceneRenderer(const std::string& name);

		/**
		* Get a scene renderer with the given name.
		* \return The found scene renderer if it exist, nullptr otherwise. 
		*/
		SceneRenderer* GetSceneRenderer(const std::string& name);

	protected:		
		SceneRenderer* m_activeRenderer;
		SceneRenderer* m_lastRenderer;

		std::map<std::string, SceneRenderer*> m_renderer;
	};
}