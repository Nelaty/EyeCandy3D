#pragma once
#include "ec3/Common/Common.h"

#include <glm/glm.hpp>

namespace ec
{
	/** 
	 * \brief A viewport defines a rectangular area into which a 
	 * camera renders.
	 * For every point (x,y) inside this area: x = [0,1], y = [0,1]
	 * applies.
	 */
	class EC3D_DECLSPEC Viewport
	{
	public:
		explicit Viewport(const glm::vec2& position = glm::vec2(0.0f),
						  const glm::vec2& size = glm::vec2(1.0f));
		~Viewport();

		const glm::vec2& getPosition() const;
		float getPositionX() const;
		float getPositionY() const;

		void setPosition(float x, float y);
		void setPosition(const glm::vec2& position);
		void setPositionX(float x);
		void setPositionY(float y);

		const glm::vec2& getSize() const;
		float getSizeX() const;
		float getSizeY() const;

		void setSize(float x, float y);
		void setSize(const glm::vec2& size);
		void setSizeX(float x);
		void setSizeY(float y);

	private:
		glm::vec2 m_position;
		glm::vec2 m_size;
	};
}