#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/Core/SceneRenderer.h"

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

	class EC3D_DECLSPEC Scene
	{
	public:
		explicit Scene(std::string name);
		virtual ~Scene();

		/* Update routine */
		virtual void tick(float timeDelta);

		/* Access to this scene's name */
		const std::string& getName() const;

		/* Node access */
		Node* getRoot() const;

		/* Scene controller access */
		void setSceneController(SceneController* sceneController);
		SceneController* getSceneController() const;

		/* Scene renderer access */
		void setSceneRenderer(const SceneRenderer& sceneRenderer);
		SceneRenderer& getSceneRenderer();

		/* Set the containing scene system */
		void setSceneSystem(SceneSystem* sceneSystem);
		SceneSystem* getSceneSystem() const;

		/** Enable this scene */
		void enable();
		/** Disable this scene */
		void disable();
		/** Check if this scene is enabled */
		bool isEnabled() const;

	protected:
		void initSceneRenderer();

		bool m_enabled = true;

		std::string m_name;

		std::unique_ptr<Node> m_root = nullptr;

		SceneSystem* m_sceneSystem = nullptr;
		SceneRenderer m_sceneRenderer;
		SceneController* m_sceneController = nullptr;
	};
}