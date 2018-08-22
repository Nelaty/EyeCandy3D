#pragma once
#include "SceneRenderer.h"

#include <vector>
#include <memory>

/*
* A scene system manages a collection of scenes and enables the switching
* thereof.
*/
namespace ec
{
	class Scene;
	class Shader;
	class SceneController;
	class Window;

	class SceneSystem
	{
	public:
		explicit SceneSystem(Window* window);
		~SceneSystem();
		
		/* Update the currently active scene */
		void tick(float timeDelta);

		/* Scene access */
		bool registerScene(Scene* scene);
		ec::Scene* unregisterScene(Scene* scene);

		/** 
		 * Get the scene with the given name 
		 * \return The requested scene if it exists, nullptr otherwise. 
		 * 
		*/
		Scene* getScene(const std::string& sceneName) const;

		/* Scene controller access */
		void addSceneController(std::unique_ptr<SceneController> sceneController);
		bool removeSceneController(SceneController* controller);
		SceneController* getSceneController(const char* controllerName);

		/* Window access */
		Window* getWindow() const;

	private:
		Window* m_window;

		std::vector<std::unique_ptr<SceneController>> m_sceneController;
		std::vector<Scene*> m_scenes;
	};
}