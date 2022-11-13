#pragma once
#include "ec3/common/common.h"
#include "ec3/scene-renderer.h"

#include <string>
#include <memory>

namespace ec
{
	class SceneController;
	class SceneSystem;
	class Node;
	
	/// A scene defines a scene graph and swapping of such
	class EC3D_DECLSPEC Scene
	{
	public:
		/// \param name The name of the scene.
		explicit Scene(std::string name);
		virtual ~Scene();

		/// Update routine.
		virtual void tick(float timeDelta);

		/// Get the name of the scene.
		const std::string& getName() const;

		/// Get the root node
		Node* getRoot() const;

		/// Set the scene system, in which the scene is contained.
		void setSceneSystem(SceneSystem* sceneSystem);
		/// Get the scene system, in which the scene is contained.
		SceneSystem* getSceneSystem() const;

		/// Enable this scene.
		void enable();
		/// Disable this scene.
		void disable();
		/// Check if this scene is enabled.
		bool isEnabled() const;

	protected:
		bool m_enabled = true;

		std::string m_name;

		std::unique_ptr<Node> m_root;

		SceneSystem* m_sceneSystem;
		SceneRenderer m_sceneRenderer;
	};
}
