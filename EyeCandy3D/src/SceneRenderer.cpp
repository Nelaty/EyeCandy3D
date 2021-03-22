#include "EC3D/Common/Config.h"

#include "EC3D/SceneRenderer.h"
#include "EC3D/Scene.h"
#include "EC3D/Node.h"
#include "EC3D/Graphics/Camera.h"
#include "EC3D/Graphics/Drawable.h"
#include "EC3D/Window/Window.h"

#include "EC3D/Graphics/Shader/Shader.h"
#include "EC3D/Graphics/Shader/ShaderManager.h"

namespace ec
{
	SceneRenderer::SceneRenderer()
		: m_globalTransformation{1.0f}
	{
	}

	SceneRenderer::~SceneRenderer() = default;

	void SceneRenderer::tick()
	{
	}

	void SceneRenderer::onBeginRender(RenderContext& context)
	{
		const auto& scenes = context.m_uniqueScenes;
		const auto& cameras = m_frame.getCameras();

		// Temp
		for(const auto& it : cameras)
		{
			it->updateGlobalMatrices(glm::mat4(1.0f));
		}

		// Update matrices of all relevant nodes
		for(const auto& it : scenes)
		{
			auto* rootNode = it->getRoot();
			rootNode->updateGlobalMatrices(m_globalTransformation);
		}
		clear();
	}

	void SceneRenderer::onRender(RenderContext& context)
	{
		auto& shaderManager = context.m_window->getShaderManager();
		const auto& cameras = m_frame.getCameras();

		for(const auto& it : cameras)
		{
			auto* scene = it->getScene();
			if(scene == nullptr) continue;

			auto* rootNode = scene->getRoot();
			rootNode->render(*this);

			updateViewport(context, it);
			updateShaders(shaderManager, it);
			renderTargets();
		}
	}

	void SceneRenderer::onEndRender(RenderContext& context)
	{
	}

	void SceneRenderer::addRenderingTarget(Node* node)
	{
		m_renderingTargets.push_back(node);
	}

	void SceneRenderer::renderTargets()
	{
		for(const auto& target : m_renderingTargets)
		{
			const auto& mat = target->getGlobalMat();
			const auto& drawables = target->getDrawables();

			for(const auto& it : drawables)
			{
				it->render(mat);
			}
		}
	}

	void SceneRenderer::updateShaders(ShaderManager& shaderManager, Camera* camera)
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

	void SceneRenderer::updateViewport(RenderContext& context, Camera* camera) const
	{
		const auto windowSize = context.m_window->getResolution();
		if(windowSize.x <= 0 || windowSize.y <= 0) return;
		
		const auto ratio = float(windowSize.x) / float(windowSize.y);

		auto viewportCamera = camera->getViewport();
		camera->changeAspectRatio(ratio);

		const auto adjustedPositionX = viewportCamera.getPositionX() * windowSize.x;
		const auto adjustedPositionY = viewportCamera.getPositionY() * windowSize.y;

		const auto adjustedWidth = viewportCamera.getSizeX() * windowSize.x;
		const auto adjustedHeight = viewportCamera.getSizeY() * windowSize.y;

		glViewport(adjustedPositionX, adjustedPositionY,
				   adjustedWidth, adjustedHeight);
	}

	void SceneRenderer::clear()
	{
		m_renderingTargets.clear();
	}

	void SceneRenderer::render(Window* window)
	{
		const auto& cameras = m_frame.getCameras();
		auto& shaderManager = window->getShaderManager();

		// Collect all unique cameras, since a scene only needs to updated
		// once.
		std::set<Scene*> uniqueScenes;
		for(const auto& it : cameras)
		{		
			auto* scene = it->getScene();
			if(scene)
			{
				uniqueScenes.insert(scene);
			}
		}

		RenderContext context;
		context.m_window = window;
		context.m_uniqueScenes = uniqueScenes;

		onBeginRender(context);
		onRender(context);
		onEndRender(context);
	}

	ec::Frame& SceneRenderer::getFrame()
	{
		return m_frame;
	}

	const ec::Frame& SceneRenderer::getFrame() const
	{
		return m_frame;
	}

	void SceneRenderer::setFrame(const Frame& frame)
	{
		m_frame = frame;
	}

	SceneRenderer::RenderContext::RenderContext()
		: m_window{nullptr}
	{
	}

}