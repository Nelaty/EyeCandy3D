#include "EC3D/Core/FrameSlot.h"

namespace ec
{
	FrameSlot::FrameSlot(const glm::vec2& position,
						 const glm::vec2& sizeRelative)
		: m_position(position),
		m_sizeRelative(sizeRelative)
	{
	}

	FrameSlot::~FrameSlot()
	{
	}

	void FrameSlot::setCamera(const Camera_Ptr& camera)
	{
		m_camera = camera;
	}

	ec::Camera* FrameSlot::getCamera() const
	{
		return m_camera.get();
	}

	void FrameSlot::setPosition(const glm::vec2& position)
	{
		m_position = position;
	}

	const glm::vec2& FrameSlot::getPosition() const
	{
		return m_position;
	}

	void FrameSlot::setSizeRelative(const glm::vec2& sizeRelative)
	{
		m_sizeRelative = sizeRelative;
	}

	const glm::vec2& FrameSlot::getSizeRelative() const
	{
		return m_sizeRelative;
	}

	bool FrameSlot::contains(const glm::vec2& point) const
	{
		return point.x >= m_position.x
			&& point.x <= m_position.x + m_sizeRelative.x
			&& point.y >= m_position.y
			&& point.y <= m_position.y + m_sizeRelative.y;
	}

}