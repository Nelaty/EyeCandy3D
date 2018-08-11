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
		: m_up{conf::g_coordinate_system_up},
		m_position{position},
		m_scale{scale},
		m_forwardVector{orientation},
		m_localMat{1.0f}
	{
	}

	Transform3D::~Transform3D()
	{
	}

	void Transform3D::UpdateLocalMat()
	{
		m_localMat = glm::translate(glm::mat4(1.0f), m_position);

		glm::mat4 rotMat(1.0f);
		rotMat[0] = glm::vec4(glm::cross(m_forwardVector, m_up), 0.0f);
		rotMat[1] = glm::vec4(m_up, 0.0f);
		rotMat[2] = glm::vec4(m_forwardVector, 0.0f);		

		m_localMat *= rotMat;
		m_localMat = glm::scale(m_localMat, m_scale);
	}

	const glm::vec3& Transform3D::GetLocalPosition()
	{
		UpdateLocalMat();
		return m_localMat[4];
	}

	const glm::mat4& Transform3D::GetLocalMat() const
	{
		return m_localMat;
	}

	const glm::vec3& Transform3D::GetUpVector() const
	{
		return m_up;
	}

	const glm::vec3& Transform3D::GetForwardVector() const
	{
		return m_forwardVector;
	}

	const glm::vec3& Transform3D::GetTranslation() const
	{
		return m_position;
	}

	float Transform3D::GetTranslationX() const
	{
		return m_position.x;
	}

	float Transform3D::GetTranslationY() const
	{
		return m_position.y;
	}

	float Transform3D::GetTranslationZ() const
	{
		return m_position.z;
	}

	void Transform3D::Translate(const float x, const float y, const float z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;
	}

	void Transform3D::Translate(const glm::vec3& v)
	{
		m_position += v;
	}

	void Transform3D::TranslateX(const float x)
	{
		m_position.x += x;
	}

	void Transform3D::TranslateY(const float y)
	{
		m_position.y += y;
	}

	void Transform3D::TranslateZ(const float z)
	{
		m_position.z += z;
	}

	void Transform3D::SetTranslation(const glm::vec3& translation)
	{
		m_position = translation;
	}

	void Transform3D::SetTranslation(const float x, const float y, const float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	void Transform3D::SetTranslationX(const float x)
	{
		m_position.x = x;
	}

	void Transform3D::SetTranslationY(const float y)
	{
		m_position.y = y;
	}

	void Transform3D::SetTranslationZ(const float z)
	{
		m_position.z = z;
	}

	void Transform3D::TranslateLocal(const float x, const float y, const float z)
	{
		m_position += x * glm::cross(m_forwardVector, m_up);
		m_position += y * m_up;
		m_position += z * m_forwardVector;
	}

	void Transform3D::TranslateLocal(const glm::vec3& v)
	{
		m_position += v.x * glm::cross(m_forwardVector, m_up);
		m_position += v.y * m_up;
		m_position += v.z * m_forwardVector;
	}

	void Transform3D::Rotate(const glm::quat& rot)
	{
		m_forwardVector = glm::normalize(rot * m_forwardVector);
		m_up = glm::normalize(rot * m_up);
	}

	void Transform3D::Rotate(float angle, const glm::vec3& axis)
	{
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Transform3D::RotateX(const float angle)
	{
		glm::vec3 axis = glm::vec3(1.0f, 0.0f, 0.0f);
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Transform3D::RotateY(const float angle)
	{
		glm::vec3 axis = conf::g_coordinate_system_up;
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Transform3D::RotateZ(const float angle)
	{
		glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Transform3D::RotateXLocal(const float angle)
	{
		glm::vec3 axis = glm::cross(m_forwardVector, m_up);
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Transform3D::RotateYLocal(const float angle)
	{
		glm::vec3 axis = m_up;
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Transform3D::RotateZLocal(const float angle)
	{
		glm::vec3 axis = m_forwardVector;
		m_forwardVector = glm::normalize(glm::rotate(m_forwardVector, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	const glm::vec3& Transform3D::GetScale() const
	{
		return m_scale;
	}

	float Transform3D::GetScaleX() const
	{
		return m_scale.x;
	}

	float Transform3D::GetScaleY() const
	{
		return m_scale.y;
	}

	float Transform3D::GetScaleZ() const
	{
		return m_scale.z;
	}

	void Transform3D::Scale(const glm::vec3& val)
	{
		m_scale *= val;
	}

	void Transform3D::ScaleX(const float sx)
	{
		m_scale.x *= sx;
	}

	void Transform3D::ScaleY(const float sy)
	{
		m_scale.y *= sy;
	}

	void Transform3D::ScaleZ(const float sz)
	{
		m_scale.z *= sz;
	}

	void Transform3D::SetScale(const glm::vec3& val)
	{
		m_scale = val;
	}

	void Transform3D::SetScale(const float sx, const float sy, const float sz)
	{
		m_scale.x = sx;
		m_scale.y = sy;
		m_scale.z = sz;
	}

	void Transform3D::SetScaleX(const float sx)
	{
		m_scale.x = sx;
	}

	void Transform3D::SetScaleY(const float sy)
	{
		m_scale.y = sy;
	}

	void Transform3D::SetScaleZ(const float sz)
	{
		m_scale.z = sz;
	}
}