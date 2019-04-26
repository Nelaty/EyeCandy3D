#pragma once
#include <memory>

#include <glm/glm.hpp>

namespace ec
{
	class Camera;

	class FrameSlot
	{
	public:
		using Camera_Ptr = std::shared_ptr<Camera>;

		explicit FrameSlot(const glm::vec2& position = glm::vec2(0.0),
						   const glm::vec2& sizeRelative = glm::vec2(1.0));
		~FrameSlot();

		/** \brief Get the current camera. */
		void setCamera(const Camera_Ptr& camera);
		/** \brief Set the current camera. */
		Camera* getCamera() const;

		/** \brief Set the position relative to the lower left corner. */
		void setPosition(const glm::vec2& position);
		/** \brief Get the position relative to the lower left corner. */
		const glm::vec2& getPosition() const;

		/** \brief Set the relative size. */
		void setSizeRelative(const glm::vec2& sizeRelative);
		/** \brief Get the relative size. */
		const glm::vec2& getSizeRelative() const;

		/** \brief Check if a given point is contained in this frame
		 * slot. */
		bool contains(const glm::vec2& point) const;

	private:
		glm::vec2 m_position;
		glm::vec2 m_sizeRelative;

		std::shared_ptr<Camera> m_camera;
	};
}