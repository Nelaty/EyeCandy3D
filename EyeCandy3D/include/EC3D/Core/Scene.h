#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/Core/SceneRenderer.h"

#include <string>
#include <memory>



namespace ec
{
	class SceneController;
	class SceneSystem;
	class Node;
	
	/**
	 * \brief A scene enables an easy switching of root nodes.
	 * \details It is possible to define an own scene controller, 
	 * to influence a scene through user input.
	 */
	class EC3D_DECLSPEC Scene
	{
	public:
		/**
		 * \brief Scene constructor.
		 * \param name The name of the scene.
		 */
		explicit Scene(std::string name);
		virtual ~Scene();

		/**
		 * \brief Update routine.
		 */
		virtual void tick(float timeDelta);

		/**
		 * \brief Get the name of the scene.
		 */
		const std::string& getName() const;

		/**
		 * \brief Get the root node
		 */
		Node* getRoot() const;

		/**
		 * \brief Set the scene system, in which the scene is 
		 * contained.
		 */
		void setSceneSystem(SceneSystem* sceneSystem);
		/**
		 * \brief Get the scene system, in which the scene is
		 * contained.
		 */
		SceneSystem* getSceneSystem() const;

		/** 
		 * \brief Enable this scene.
		 */
		void enable();
		/** 
		 * \brief Disable this scene.
		 */
		void disable();
		/** 
		 * \brief Check if this scene is enabled.
		 */
		bool isEnabled() const;

	protected:
		bool m_enabled = true;

		std::string m_name;

		std::unique_ptr<Node> m_root{};

		SceneSystem* m_sceneSystem{};
		SceneRenderer m_sceneRenderer;
	};
}