#include "EC3D/GUI/Bounds2D.h"

namespace ec_gui
{
	Bounds2D::Bounds2D()
	{
	}

	Bounds2D::~Bounds2D()
	{
	}

	bool Bounds2D::FullyContains(const Bounds2D& bounds)
	{
		// Check if the bounds corner is above or to the left of this bounds
		if(bounds.m_leftUpperCorner.x > m_leftUpperCorner.x)
		{
			return false;
		}
		// Check if the bounds corner is below or to the right of this bounds
		// or to big to be contained
		glm::vec2 cornerDiff = m_leftUpperCorner - bounds.m_leftUpperCorner - m_size;
		if(cornerDiff.x < 0.0f || cornerDiff.y < 0.0f)
		{
			return false;
		}

		return true;
	}

	void Bounds2D::Translate(const glm::vec2& val)
	{
		m_leftUpperCorner += val;
	}

	void Bounds2D::SetTranslation(const glm::vec2& val)
	{
		m_leftUpperCorner = val;
	}

	void Bounds2D::Scale(const glm::vec2& val)
	{
		m_size += val;
	}

	void Bounds2D::SetScale(const glm::vec2& val)
	{
		m_size = val;
	}
}