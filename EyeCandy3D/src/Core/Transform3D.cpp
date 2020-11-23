#include "EC3D/Core/Transform3D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ec
{

	Transform3D::Transform3D(const glm::vec3& position, 
							 const glm::vec3& scale,
							 const glm::vec3& orientation)
		: m_up{conf::g_coordinateSystemUp},
		m_position{position},
		m_forwardVector{orientation},
		m_scale{scale},
		m_localMat{1.0f}
	{
	}

	Transform3D::~Transform3D()
	= default;

	void Transform3D::updateLocalMat()
	{
		m_localMat = glm::translate(glm::mat4(1.0f), m_position);

		glm::mat4 rotMat(1.0f);
		rotMat[0] = glm::vec4(glm::cross(m_forwardVector, m_up), 0.0f);
		rotMat[1] = glm::vec4(m_up, 0.0f);

		#ifdef EC3D_RIGHT_HANDED_COORDINATE_SYSTEM
		rotMat[2] = glm::vec4(-m_forwardVector, 0.0f);		
		#else 
		#ifdef EC3D_LEFT_HANDED_COORDINATE_SYSTEM
		rotMat[2] = glm::vec4(m_forwardVector, 0.0f);
		#endif
		#endif

		m_localMat *= rotMat;
		m_localMat = glm::scale(m_localMat, m_scale);
	}

	const glm::vec3& Transform3D::getLocalPosition()
	{
		updateLocalMat();
		return m_localMat[3];
	}

	const glm::mat4& Transform3D::getLocalMat() const
	{
		return m_localMat;
	}

	void Transform3D::setLocalMat(const glm::mat4& mat)
	{
		m_localMat = mat;
	}

	const glm::vec3& Transform3D::getUpVector() const
	{
		return m_up;
	}

	const glm::vec3& Transform3D::getForwardVector() const
	{
		return m_forwardVector;
	}

	const glm::vec3& Transform3D::getTranslation() const
	{
		return m_position;
	}

	float Transform3D::getTranslationX() const
	{
		return m_position.x;
	}

	float Transform3D::getTranslationY() const
	{
		return m_position.y;
	}

	float Transform3D::getTranslationZ() const
	{
		return m_position.z;
	}

	void Transform3D::translate(const float x, const float y, const float z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;
		markDirty();
	}

	void Transform3D::translate(const glm::vec3& v)
	{
		m_position += v;
        markDirty();
	}

	void Transform3D::translateX(const float x)
	{
		m_position.x += x;
        markDirty();
	}

	void Transform3D::translateY(const float y)
	{
		m_position.y += y;
        markDirty();
	}

	void Transform3D::translateZ(const float z)
	{
		m_position.z += z;
        markDirty();
	}

	void Transform3D::setTranslation(const glm::vec3& translation)
	{
		m_position = translation;
        markDirty();
	}

	void Transform3D::setTranslation(const float x, const float y, const float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
        markDirty();
	}

	void Transform3D::setTranslationX(const float x)
	{
		m_position.x = x;
        markDirty();
	}

	void Transform3D::setTranslationY(const float y)
	{
		m_position.y = y;
        markDirty();
	}

	void Transform3D::setTranslationZ(const float z)
	{
		m_position.z = z;
        markDirty();
	}

	void Transform3D::translateLocal(const float x, const float y, const float z)
	{
		m_position += x * glm::cross(m_forwardVector, m_up);
		m_position += y * m_up;
		m_position += z * m_forwardVector;
        markDirty();
	}

	void Transform3D::translateLocal(const glm::vec3& v)
	{
		m_position += v.x * glm::cross(m_forwardVector, m_up);
		m_position += v.y * m_up;
		m_position += v.z * m_forwardVector;
        markDirty();
	}

	void Transform3D::rotate(const glm::quat& rot)
	{
		m_forwardVector = glm::normalize(rot * m_forwardVector);
		m_up = glm::normalize(rot * m_up);
        markDirty();
	}

	void Transform3D::rotate(const float angle, const glm::vec3& axis)
	{
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
        markDirty();
	}

	void Transform3D::rotateX(const float angle)
	{
		glm::vec3 axis = glm::vec3(1.0f, 0.0f, 0.0f);
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
        markDirty();
	}

	void Transform3D::rotateY(const float angle)
	{
		glm::vec3 axis = conf::g_coordinateSystemUp;
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
        markDirty();
	}

	void Transform3D::rotateZ(const float angle)
	{
		glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
        markDirty();
	}

	void Transform3D::rotateXLocal(const float angle)
	{
		const auto axis = glm::cross(m_forwardVector, m_up);
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
        markDirty();
	}

	void Transform3D::rotateYLocal(const float angle)
	{
		const auto axis = m_up;
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
        markDirty();
	}

	void Transform3D::rotateZLocal(const float angle)
	{
		const auto axis = m_forwardVector;
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
        markDirty();
	}

	void Transform3D::setRotation(const glm::mat3& rotationMatrix)
	{
		m_up = glm::normalize(rotationMatrix[1]);
		m_forwardVector = glm::normalize(rotationMatrix[2]);
        markDirty();
	}

	const glm::vec3& Transform3D::getScale() const
	{
		return m_scale;
	}

	float Transform3D::getScaleX() const
	{
		return m_scale.x;
	}

	float Transform3D::getScaleY() const
	{
		return m_scale.y;
	}

	float Transform3D::getScaleZ() const
	{
		return m_scale.z;
	}

	void Transform3D::scale(const glm::vec3& val)
	{
		m_scale *= val;
        markDirty();
	}

	void Transform3D::scale(const float uniform)
	{
		m_scale *= uniform;
        markDirty();
	}

	void Transform3D::scale(const float sx, const float sy, const float sz)
	{
		m_scale.x *= sx;
		m_scale.y *= sy;
		m_scale.z *= sz;
        markDirty();
	}

	void Transform3D::scaleX(const float sx)
	{
		m_scale.x *= sx;
        markDirty();
	}

	void Transform3D::scaleY(const float sy)
	{
		m_scale.y *= sy;
        markDirty();
	}

	void Transform3D::scaleZ(const float sz)
	{
		m_scale.z *= sz;
        markDirty();
	}

	void Transform3D::setScale(const glm::vec3& val)
	{
		m_scale = val;
        markDirty();
	}

	void Transform3D::setScale(const float sx, const float sy, const float sz)
	{
		m_scale.x = sx;
		m_scale.y = sy;
		m_scale.z = sz;
        markDirty();
	}

	void Transform3D::setScale(const float uniform)
	{
		m_scale.x = uniform;
		m_scale.y = uniform;
		m_scale.z = uniform;
        markDirty();
	}

	void Transform3D::setScaleX(const float sx)
	{
		m_scale.x = sx;
        markDirty();
	}

	void Transform3D::setScaleY(const float sy)
	{
		m_scale.y = sy;
        markDirty();
	}

	void Transform3D::setScaleZ(const float sz)
	{
		m_scale.z = sz;
        markDirty();
	}

    void Transform3D::markDirty()
    {
        m_dirty = true;
    }

    void Transform3D::unmarkDirty()
    {
        m_dirty = false;
    }

    bool Transform3D::isDirty()
    {
        return m_dirty;
    }
}
