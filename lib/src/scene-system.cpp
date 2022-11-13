#include "ec3/scene-system.h"

#include "ec3/graphics/shader/shader.h"
#include "ec3/input/scene-controller.h"
#include "ec3/scene.h"
#include "ec3/window/window.h"

#include  <algorithm>

namespace ec
{
	SceneSystem::SceneSystem(Window* window)
		: m_window{window}
	{
	}

	SceneSystem::~SceneSystem()	= default;

	void SceneSystem::tick(const float timeDelta)
	{
		for(auto& it : m_scenes)
		{
			if(it->isEnabled())
			{
				it->tick(timeDelta);
			}
		}
	}

	ec::Scene* SceneSystem::getScene(const std::string& sceneName) const
	{
		const auto foundScene = std::find_if(m_scenes.begin(),
											 m_scenes.end(),
											 [&](const Scene* it)
		{
			return it->getName() == sceneName;
		});

		return foundScene == m_scenes.end() ? nullptr : *foundScene;
	}

	bool SceneSystem::registerScene(Scene* scene)
	{
		if(getScene(scene->getName())) return false;

		scene->setSceneSystem(this);
		m_scenes.push_back(scene);

		return true;
	}

	ec::Scene* SceneSystem::unregisterScene(Scene* scene)
	{
		const auto removedScene = std::remove(m_scenes.begin(),
											  m_scenes.end(),
											  scene);

		if(removedScene == m_scenes.end()) return nullptr;

		return *removedScene;
	}

	void SceneSystem::addSceneController(std::unique_ptr<SceneController> sceneController)
	{
		m_sceneController.push_back(std::move(sceneController));
	}

	bool SceneSystem::removeSceneController(SceneController* controller)
	{
		const auto foundController = std::remove_if(m_sceneController.begin(),
													m_sceneController.end(),
													[&](const std::unique_ptr<SceneController>& it)
		{
			return it.get() == controller;
		});
		
		return foundController != m_sceneController.end();
	}

	ec::SceneController* SceneSystem::getSceneController(const char* controllerName)
	{
		const auto foundController = std::find_if(m_sceneController.begin(),
												  m_sceneController.end(),
												  [&](const std::unique_ptr<SceneController>& it)
		{
			return it->getName() == controllerName;
		});

		return foundController == m_sceneController.end() ? nullptr : foundController->get();
	}

	ec::Window* SceneSystem::getWindow() const
	{
		return m_window;
	}

}