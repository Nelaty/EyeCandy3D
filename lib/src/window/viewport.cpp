#include "ec3/window/viewport.h"

#include <cassert>

namespace ec
{
	Viewport::Viewport(const glm::vec2& position, const glm::vec2& size)
		: m_position{position},
		m_size{size}
	{
		setPosition(position);
		setSize(size);
	}

	Viewport::~Viewport()
	= default;

	const glm::vec2& Viewport::getPosition() const
	{
		return m_position;
	}

	float Viewport::getPositionX() const
	{
		return m_position.x;
	}

	float Viewport::getPositionY() const
	{
		return m_position.y;
	}

	void Viewport::setPosition(const glm::vec2& position)
	{
		assert(position.x >= 0.0f && position.x <= 1.0f
			   && position.y >= 0.0f && position.y <= 1.0f);

		m_position = position;
	}

	void Viewport::setPosition(float x, float y)
	{
		setPositionX(x);
		setPositionY(y);
	}

	void Viewport::setPositionX(float x)
	{
		assert(x >= 0.0f && x <= 1.0f);

		m_position.x = x;
	}

	void Viewport::setPositionY(float y)
	{
		assert(y >= 0.0f && y <= 1.0f);

		m_position.y = y;
	}

	const glm::vec2& Viewport::getSize() const
	{
		return m_size;
	}

	float Viewport::getSizeX() const
	{
		return m_size.x;
	}

	float Viewport::getSizeY() const
	{
		return m_size.y;
	}

	void Viewport::setSize(const glm::vec2& size)
	{
		assert(size.x >= 0.0f && size.x <= 1.0f
			   && size.y >= 0.0f && size.y <= 1.0f);

		m_size = size;
	}

	void Viewport::setSize(float x, float y)
	{
		setSizeX(x);
		setSizeY(y);
	}

	void Viewport::setSizeX(float x)
	{
		assert(x >= 0.0f && x <= 1.0f);

		m_size.x = x;
	}

	void Viewport::setSizeY(float y)
	{
		assert(y >= 0.0f && y <= 1.0f);

		m_size.y = y;
	}
}