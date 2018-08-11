#include "EC3D/Common/Config.h"

#include "EC3D/Core/SceneRenderer.h"
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Node.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Drawable.h"
#include "EC3D/Core/Window.h"

#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Shader/ShaderManager.h"


namespace ec
{
	SceneRenderer::SceneRenderer()
		: m_globalTransformation{1.0f}
	{
	}

	SceneRenderer::~SceneRenderer()
	{
	}

	void SceneRenderer::OnBeginRender(RenderContext& context)
	{
		const auto& scenes = context.m_uniqueScenes;
		const auto& cameras = m_frame.GetCameras();

		// Temp
		for(const auto& it : cameras)
		{
			it->UpdateGlobalMatrices(glm::mat4(1.0f));
		}

		// Update matrices of all relevant nodes
		for(const auto& it : scenes)
		{
			auto* rootNode = it->GetRoot();
			rootNode->UpdateGlobalMatrices(m_globalTransformation);
		}
		Clear();
	}

	void SceneRenderer::OnRender(RenderContext& context)
	{
		auto& shaderManager = context.m_window->GetShaderManager();
		const auto& cameras = m_frame.GetCameras();

		for(const auto& it : cameras)
		{
			auto* scene = it->GetScene();
			auto* rootNode = scene->GetRoot();
			rootNode->Render(*this);

			UpdateViewport(context, it);
			UpdateShaders(shaderManager, it);
			RenderTargets();
		}
	}

	void SceneRenderer::OnEndRender(RenderContext& context)
	{
	}

	void SceneRenderer::AddRenderingTarget(Node* node)
	{
		m_renderingTargets.push_back(node);
	}

	void SceneRenderer::RenderTargets()
	{
		for(const auto& target : m_renderingTargets)
		{
			const auto& mat = target->GetGlobalMat();
			const auto& drawables = target->GetDrawables();

			for(const auto& it : drawables)
			{
				it->Render(mat);
			}
		}
	}

	void SceneRenderer::UpdateShaders(ShaderManager& shaderManager, Camera* camera)
	{
		auto& shaders = shaderManager.GetAllShader();

		for(auto& it : shaders)
		{
			auto* shader = it.second.get();

			shader->Bind();
			shader->SetMat4(conf_shader::g_viewKey, camera->GetView());
			shader->SetMat4(conf_shader::g_projectionKey, camera->GetProjection());
			shader->Unbind();
		}
	}

	void SceneRenderer::UpdateViewport(RenderContext& context, Camera* camera)
	{
		glm::ivec2 windowSize = context.m_window->GetWindowResolution();
		float ratio = static_cast<float>(windowSize.x) / 
			static_cast<float>(windowSize.y);

		auto viewportCamera = camera->GetViewport();
		camera->ChangeAspectRatio(ratio);

		float adjustedPositionX = viewportCamera.GetPositionX() * windowSize.x;
		float adjustedPositionY = viewportCamera.GetPositionY() * windowSize.y;

		float adjustedWidth = viewportCamera.GetSizeX() * windowSize.x;
		float adjustedHeight = viewportCamera.GetSizeY() * windowSize.y;

		glViewport(adjustedPositionX, adjustedPositionY,
				   adjustedWidth, adjustedHeight);
	}

	void SceneRenderer::Clear()
	{
		m_renderingTargets.clear();
	}

	void SceneRenderer::Render(Window* window)
	{
		const auto& cameras = m_frame.GetCameras();
		auto& shaderManager = window->GetShaderManager();

		// Collect all unique cameras, since a scene only needs to updated
		// once.
		std::set<Scene*> uniqueScenes;
		for(const auto& it : cameras)
		{		
			auto* scene = it->GetScene();
			if(scene)
			{
				uniqueScenes.insert(scene);
			}
		}

		RenderContext context;
		context.m_window = window;
		context.m_uniqueScenes = uniqueScenes;

		OnBeginRender(context);
		OnRender(context);
		OnEndRender(context);
	}

	void SceneRenderer::SetScene(Scene* scene)
	{
		m_scene = scene;
	}

	ec::Scene* SceneRenderer::GetScene()
	{
		return m_scene;
	}

	ec::Frame& SceneRenderer::GetFrame()
	{
		return m_frame;
	}

	const ec::Frame& SceneRenderer::GetFrame() const
	{
		return m_frame;
	}

	void SceneRenderer::SetFrame(const Frame& frame)
	{
		m_frame = frame;
	}
}