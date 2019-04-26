#pragma once
#include "IRenderer.h"
#include "RenderTarget.h"

#include <glm/glm.hpp>

namespace ec
{
	class ShaderManager;
	class Camera;

	class ForwardRenderer : public IRenderer
	{
	public:
		explicit ForwardRenderer();
		~ForwardRenderer();

		void render(const RenderingContext& context) override;

	private:
		void updateMatrices(const RenderingContext& context);
		void updateShaders(ShaderManager& shaderManager, Camera* camera);
		void updateViewport(const RenderingContext& context,
							Camera* camera,
							const glm::vec2& position,
							const glm::vec2& size) const;

		void renderTargets();

		RenderTargets m_renderTargets;

		glm::mat4 m_globalTransform{1.0};
	};
}