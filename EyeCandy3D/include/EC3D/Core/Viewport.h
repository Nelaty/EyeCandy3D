#pragma once
#include <glm/glm.hpp>

namespace ec
{
	/** 
	 * A viewport defines a rectangular area into which a camera renders.
	 * For every point (x,y) inside this area: x = [0,1], y = [0,1] applies.
	 */
	class Viewport
	{
	public:
		explicit Viewport(const glm::vec2& position = glm::vec2(0.0f),
						  const glm::vec2& size = glm::vec2(1.0f));
		~Viewport();

		const glm::vec2& GetPosition() const;
		float GetPositionX() const;
		float GetPositionY() const;
		void SetPosition(const glm::vec2& position);
		void SetPositionX(float x);
		void SetPositionY(float y);

		const glm::vec2& GetSize() const;
		float GetSizeX() const;
		float GetSizeY() const;
		void SetSize(const glm::vec2& size);
		void SetSizeX(float x);
		void SetSizeY(float y);

	private:
		glm::vec2 m_position;
		glm::vec2 m_size;
	};
}