#include "EC3D/Core/Viewport.h"

#include <cassert>

namespace ec
{
	Viewport::Viewport(const glm::vec2& position, const glm::vec2& size)
		: m_position{position},
		m_size{size}
	{
		SetPosition(position);
		SetSize(size);
	}

	Viewport::~Viewport()
	{
	}

	const glm::vec2& Viewport::GetPosition() const
	{
		return m_position;
	}

	float Viewport::GetPositionX() const
	{
		return m_position.x;
	}

	float Viewport::GetPositionY() const
	{
		return m_position.y;
	}

	void Viewport::SetPosition(const glm::vec2& position)
	{
		assert(position.x >= 0.0f && position.x <= 1.0f
			   && position.y >= 0.0f && position.y <= 1.0f);

		m_position = position;
	}

	void Viewport::SetPositionX(float x)
	{
		assert(x >= 0.0f && x <= 1.0f);

		m_position.x = x;
	}

	void Viewport::SetPositionY(float y)
	{
		assert(y >= 0.0f && y <= 1.0f);

		m_position.y = y;
	}

	const glm::vec2& Viewport::GetSize() const
	{
		return m_size;
	}

	float Viewport::GetSizeX() const
	{
		return m_size.x;
	}

	float Viewport::GetSizeY() const
	{
		return m_size.y;
	}

	void Viewport::SetSize(const glm::vec2& size)
	{
		assert(size.x >= 0.0f && size.x <= 1.0f
			   && size.y >= 0.0f && size.y <= 1.0f);

		m_size = size;
	}

	void Viewport::SetSizeX(float x)
	{
		assert(x >= 0.0f && x <= 1.0f);

		m_size.x = x;
	}

	void Viewport::SetSizeY(float y)
	{
		assert(y >= 0.0f && y <= 1.0f);

		m_size.y = y;
	}
}