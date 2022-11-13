#pragma once
#include "ec3/common/common.h"
#include "ec3/scene-renderer.h"

#include <vector>
#include <memory>
#include <string>

/*
* \brief A scene system manages a collection of scenes and enables 
* switching of scenes.
*/
namespace ec
{
	class Scene;
	class Shader;
	class SceneController;
	class Window;

	class EC3D_DECLSPEC SceneSystem
	{
	public:
		explicit SceneSystem(Window* window);
		~SceneSystem();
		
		/**
		 * \brief Update the currently active scene.
		 */
		void tick(float timeDelta);

		/* Scene access */
		/**
		 * \brief Register a new scene.
		 * \return False if the scene is already registered, true
		 * otherwise.
		 */
		bool registerScene(Scene* scene);
		/**
		 * \brief Unregister an already registered scene.
		 * \return The scene if it was found, nullptr otherwise.
		 */
		ec::Scene* unregisterScene(Scene* scene);

		/** 
		 * \brief Get the scene with the given name 
		 * \return The requested scene if it exists, nullptr otherwise.  
		 */
		Scene* getScene(const std::string& sceneName) const;

		/**
		 * \brief Add a new scene controller.
		 */
		void addSceneController(std::unique_ptr<SceneController> sceneController);
		/**
		 * \brief Remove a given scene controller.
		 * \return True if the controller was found, false otherwise.
		 */
		bool removeSceneController(SceneController* controller);
		/**
		 * \brief Get a scene controller by name.
		 * \return The controller if it was found, nullptr otherwise.
		 */
		SceneController* getSceneController(const char* controllerName);

		/**
		 * \brief Get the window associated with this scene system.
		 */
		Window* getWindow() const;

	private:
		Window* m_window;

		std::vector<std::unique_ptr<SceneController>> m_sceneController;
		std::vector<Scene*> m_scenes;
	};
}