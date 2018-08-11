#pragma once
#include "SceneRenderer.h"

#include <string>
#include <memory>

/**
* A scene enables an easy switching of root nodes
* It is possible to define an own scene controller, to influence
* a scene through user input.
*/

namespace ec
{
	class SceneController;
	class SceneSystem;
	class Node;

	class Scene
	{
	public:
		explicit Scene(const std::string& name);
		virtual ~Scene();

		/* Update routine */
		virtual void Tick(const float timeDelta);

		/* Access to this scene's name */
		const std::string& GetName() const;

		/* Node access */
		Node* GetRoot();

		/* Scene controller access */
		void SetSceneController(SceneController* sceneController);
		SceneController* GetSceneController();

		/* Scene renderer access */
		void SetSceneRenderer(const SceneRenderer& sceneRenderer);
		SceneRenderer& GetSceneRenderer();

		/* Set the containing scene system */
		void SetSceneSystem(SceneSystem* sceneSystem);
		SceneSystem* GetSceneSystem();

		/** Enable this scene */
		void Enable();
		/** Disable this scene */
		void Disable();
		/** Check if this scene is enabled */
		bool IsEnabled() const;

	protected:
		void InitSceneRenderer();

		bool m_enabled;

		std::string m_name;

		std::unique_ptr<Node> m_root;

		SceneSystem* m_sceneSystem;
		SceneRenderer m_sceneRenderer;
		SceneController* m_sceneController;
	};
}