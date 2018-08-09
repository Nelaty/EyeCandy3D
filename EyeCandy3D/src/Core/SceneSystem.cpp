#include "EC3D/Core/SceneSystem.h"
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/SceneController.h"
#include "EC3D/Core/Window.h"

#include "EC3D/Core/Shader/Shader.h"

#include  <algorithm>

namespace ec
{
	SceneSystem::SceneSystem(Window* window)
		: m_window{window}
	{
	}

	SceneSystem::~SceneSystem()
	{
	}


	/// \todo implement tickíng of scenes -> currently active cameras?
	void SceneSystem::Tick(const float timeDelta)
	{
		
	}

	ec::Scene* SceneSystem::GetScene(const std::string& sceneName) const
	{
		auto foundScene = std::find_if(m_scenes.begin(),
								  m_scenes.end(),
								  [&](const Scene* it)
		{
			return it->GetName() == sceneName;
		});

		return foundScene == m_scenes.end() ? nullptr : *foundScene;
	}

	bool SceneSystem::RegisterScene(Scene* scene)
	{
		if(GetScene(scene->GetName())) return false;

		scene->SetSceneSystem(this);
		m_scenes.push_back(std::move(scene));

		return true;
	}

	ec::Scene* SceneSystem::UnregisterScene(Scene* scene)
	{
		auto removedScene = std::remove(m_scenes.begin(),
										m_scenes.end(),
										scene);

		if(removedScene == m_scenes.end()) return nullptr;

		return *removedScene;
	}

	void SceneSystem::AddSceneController(std::unique_ptr<SceneController> sceneController)
	{
		m_sceneController.push_back(std::move(sceneController));
	}

	bool SceneSystem::RemoveSceneController(SceneController* controller)
	{
		auto foundController = std::remove_if(m_sceneController.begin(),
											  m_sceneController.end(),
											  [&](const std::unique_ptr<SceneController>& it)
		{
			return it.get() == controller;
		});
		
		return foundController != m_sceneController.end();
	}

	ec::SceneController* SceneSystem::GetSceneController(const char* controllerName)
	{
		auto foundController = std::find_if(m_sceneController.begin(),
											m_sceneController.end(),
											[&](const std::unique_ptr<SceneController>& it)
		{
			return it->GetName() == controllerName;
		});

		return foundController == m_sceneController.end() ? nullptr : foundController->get();
	}

	ec::Window* SceneSystem::GetWindow()
	{
		return m_window;
	}

}