#include "EC3D/Core/Renderer.h"
#include "EC3D/Core/Shader/ShaderManager.h"

#include <algorithm>

namespace ec
{
	Renderer::Renderer()
		: m_activeRenderer{nullptr},
		m_lastRenderer{nullptr}
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Render(Window* window)
	{
		if(m_activeRenderer)
		{
			m_activeRenderer->Render(window);
		}		
	}

	void Renderer::ChangeRenderer(const std::string& name)
	{
		auto* renderer = GetSceneRenderer(name);
		if(!renderer) return;

		m_lastRenderer = m_activeRenderer;
		m_activeRenderer = renderer;
	}

	void Renderer::RegisterSceneRenderer(const std::string& name, SceneRenderer* renderer)
	{
		if(GetSceneRenderer(name)) return;

		m_renderer.insert(std::make_pair(name, renderer));
	}

	ec::SceneRenderer* Renderer::UnregisterSceneRenderer(const std::string& name)
	{
		auto foundRenderer = m_renderer.find(name);
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

	ec::SceneRenderer* Renderer::GetSceneRenderer(const std::string& name)
	{
		auto foundRenderer = m_renderer.find(name);

		if(foundRenderer == m_renderer.end())
		{
			return nullptr;
		}
		else
		{
			return foundRenderer->second;
		}
	}

}