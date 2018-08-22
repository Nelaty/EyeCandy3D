#include "EC3D/GUI/Bounds2D.h"

namespace ec_gui
{
	Bounds2D::Bounds2D()
		: m_leftUpperCorner(0),
		m_size(0)
	{
	}

	Bounds2D::~Bounds2D()
	= default;

	bool Bounds2D::fullyContains(const Bounds2D& bounds) const
	{
		// Check if the bounds corner is above or to the left of this bounds
		if(bounds.m_leftUpperCorner.x > m_leftUpperCorner.x)
		{
			return false;
		}
		// Check if the bounds corner is below or to the right of this bounds
		// or to big to be contained
		const auto cornerDiff = m_leftUpperCorner - bounds.m_leftUpperCorner - m_size;

		return !(cornerDiff.x < 0.0f || cornerDiff.y < 0.0f);
	}

	void Bounds2D::translate(const glm::vec2& val)
	{
		m_leftUpperCorner += val;
	}

	void Bounds2D::setTranslation(const glm::vec2& val)
	{
		m_leftUpperCorner = val;
	}

	void Bounds2D::scale(const glm::vec2& val)
	{
		m_size += val;
	}

	void Bounds2D::setScale(const glm::vec2& val)
	{
		m_size = val;
	}
}