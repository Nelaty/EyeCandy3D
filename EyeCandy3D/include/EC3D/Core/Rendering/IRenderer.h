#pragma once

namespace ec
{
	struct RenderingContext;

	class IRenderer
	{
	public:
		virtual ~IRenderer() = 0;

		virtual void render(const RenderingContext& context) = 0;

	protected:
		explicit IRenderer();
	};
}