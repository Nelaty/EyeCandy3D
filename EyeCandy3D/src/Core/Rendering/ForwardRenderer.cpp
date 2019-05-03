#include "EC3D/Core/Rendering/ForwardRenderer.h"
#include "EC3D/Core/Rendering/RenderingContext.h"

#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Shader/ShaderManager.h"

#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Frame.h"
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Window.h"

#include <unordered_set>

namespace ec
{

	ForwardRenderer::ForwardRenderer()
	{
	}

	ForwardRenderer::~ForwardRenderer()
	{
	}

	void ForwardRenderer::render(const RenderingContext& context)
	{
		const auto& frameSlots = context.m_window->getFrame().getFrameSlots();

		updateMatrices(context);

		auto& shaderManager = context.m_window->getShaderManager();
		
		for(const auto& it : frameSlots)
		{
			auto camera = it.getCamera();
			if(!camera) continue;

			auto scene = camera->getScene();
			if(scene == nullptr) continue;

			auto* rootNode = scene->getRoot();
			rootNode->render(m_renderTargets);

			updateViewport(context, camera, it.getPosition(), it.getSizeRelative());
			updateShaders(shaderManager, camera);
			renderTargets();
		}

		m_renderTargets.clear();
	}

	void ForwardRenderer::updateMatrices(const RenderingContext& context)
	{
		const auto& frameSlots = context.m_window->getFrame().getFrameSlots();

		std::unordered_set<Scene*> updatedScenes;
		for(auto& it : frameSlots)
		{
			auto camera = it.getCamera();
			if(camera)
			{
				camera->updateGlobalMatrices(m_globalTransform);
				auto scene = camera->getScene();
				if(scene)
				{
					if(updatedScenes.find(scene) == updatedScenes.end())
					{
						scene->getRoot()->updateGlobalMatrices(m_globalTransform);
						updatedScenes.insert(scene);
					}
				}
			}
		}
	}

	void ForwardRenderer::updateShaders(ShaderManager& shaderManager, Camera* camera)
	{
		auto& shaders = shaderManager.getAllShader();

		for(auto& it : shaders)
		{
			auto* shader = it.second.get();
			
			shader->bind();
			shader->setMat4(conf_shader::g_viewKey, camera->getView());
			shader->setMat4(conf_shader::g_projectionKey, camera->getProjection());
			shader->unbind();
		}
	}

	void ForwardRenderer::updateViewport(const RenderingContext& context,
										 Camera* camera,
										 const glm::vec2& position,
										 const glm::vec2& size) const
	{
		const auto windowSize = context.m_window->getResolution();
		const auto ratio = static_cast<float>(windowSize.x) /
			static_cast<float>(windowSize.y);

		camera->changeAspectRatio(ratio);

		const auto adjustedPositionX = position.x * windowSize.x;
		const auto adjustedPositionY = position.y * windowSize.y;

		const auto adjustedWidth = size.x * windowSize.x;
		const auto adjustedHeight = size.y * windowSize.y;

		glViewport(adjustedPositionX, adjustedPositionY,
				   adjustedWidth, adjustedHeight);
	}

	void ForwardRenderer::renderTargets()
	{
		auto targets = m_renderTargets.getTargets();
		for(int i = 0; i < m_renderTargets.getValidTargetCount(); ++i)
		{
			const auto& mat = targets[i]->getGlobalMat();
			const auto& drawables = targets[i]->getDrawables();

			for(const auto& it : drawables)
			{
				it->render(mat);
			}
		}
	}

}