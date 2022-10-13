#include <utility>
#include "ec3/Scene.h"
#include "ec3/Node.h"
#include "ec3/SceneSystem.h"
#include "ec3/Window/Window.h"

namespace ec
{
	Scene::Scene(std::string name)
		: m_name{std::move(name)}
	{
		m_root = std::make_unique<Node>(nullptr);
	}

	Scene::~Scene()
	= default;

	void Scene::tick(const float timeDelta)
	{
	}

	const std::string& Scene::getName() const
	{
		return m_name;
	}
	
	ec::Node* Scene::getRoot() const
	{
		return m_root.get();
	}

	void Scene::setSceneSystem(SceneSystem* sceneSystem)
	{
		m_sceneSystem = sceneSystem;
	}

	ec::SceneSystem* Scene::getSceneSystem() const
	{
		return m_sceneSystem;
	}

	void Scene::enable()
	{
		m_enabled = true;
	}

	void Scene::disable()
	{
		m_enabled = false;
	}

	bool Scene::isEnabled() const
	{
		return m_enabled;
	}
}