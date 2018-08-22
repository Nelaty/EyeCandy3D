#include "EC3D/Core/Renderer.h"
#include "EC3D/Core/Shader/ShaderManager.h"

namespace ec
{
	Renderer::Renderer()
		: m_activeRenderer{nullptr},
		m_lastRenderer{nullptr}
	{
	}

	Renderer::~Renderer()
	= default;

	void Renderer::render(Window* window) const
	{
		if(m_activeRenderer)
		{
			m_activeRenderer->render(window);
		}		
	}

	void Renderer::changeRenderer(const std::string& name)
	{
		auto* renderer = getSceneRenderer(name);
		if(!renderer) return;

		m_lastRenderer = m_activeRenderer;
		m_activeRenderer = renderer;
	}

	void Renderer::registerSceneRenderer(const std::string& name, SceneRenderer* renderer)
	{
		if(getSceneRenderer(name)) return;

		m_renderer.insert(std::make_pair(name, renderer));
	}

	ec::SceneRenderer* Renderer::unregisterSceneRenderer(const std::string& name)
	{
		const auto foundRenderer = m_renderer.find(name);
		if(foundRenderer == m_renderer.end())
		{
			return nullptr;
		}
		else
		{
			m_renderer.erase(foundRenderer);
			return foundRenderer->second;
		}
	}

	ec::SceneRenderer* Renderer::getSceneRenderer(const std::string& name)
	{
		const auto foundRenderer = m_renderer.find(name);

		if(foundRenderer == m_renderer.end())
		{
			return nullptr;
		}
		return foundRenderer->second;
	}

}