#pragma once
#include "EC3D/Common/Config.h"

#include <glm/glm.hpp>

namespace ec
{
	class Transform3D
	{
	public:
		explicit Transform3D(const glm::vec3& position = glm::vec3(0.0f),
							 const glm::vec3& scale = glm::vec3(1.0f),
							 const glm::vec3& orientation = conf::g_coordinate_system_orientation);
		~Transform3D();

		/** 
		 * This function should be called once before accessing the local
		 * matrix, if a prior transformation has been executed.
		 * Create a new local mat from the current position, rotation and
		 * scale. 
		 */
		virtual void UpdateLocalMat();

		/** 
		 * Get the current local position .
		 * Performance critical, since the local matrix has to be updated.
		 */
		const glm::vec3& GetLocalPosition();

		/** Get the current view matrix. */
		const glm::mat4& GetLocalMat() const;
		/** Get the current up vector. */
		const glm::vec3& GetUpVector() const;
		/** Get the current forward vector. */
		const glm::vec3& GetForwardVector() const;

		/** 
		 * Get the current translation 
		 * WITHOUT scale and rotation applied!
		 */
		const glm::vec3& GetTranslation() const;
		/** Get the x component of the current translation */
		float GetTranslationX() const;
		/** Get the y component of the current translation */
		float GetTranslationY() const;
		/** Get the z component of the current translation */
		float GetTranslationZ() const;

		/** Adds the given coordinates to the current position. */
		void Translate(const float x, const float y, const float z);
		/** Adds the given vector to the current position. */
		void Translate(const glm::vec3& v);
		/** Adds the given value to the current x-coordinate. */
		void TranslateX(const float x);
		/** Adds the given value to the current y-coordinate. */
		void TranslateY(const float y);
		/** Adds the given value to the current z-coordinate. */
		void TranslateZ(const float z);

		/** Assign the given position to the current position. */
		void SetTranslation(const glm::vec3& translation);
		/** Assign the given position to the current position. */
		void SetTranslation(const float x, const float y, const float z);
		/** Assign the given value to the current x-coordinate. */
		void SetTranslationX(const float x);
		/** Assign the given value to the current y-coordinate. */
		void SetTranslationY(const float y);
		/** Assign the given value to the current z-coordinate. */
		void SetTranslationZ(const float z);

		/** 
		 * Translate by the given coordinates and with respect to the
		 * current orientation.
		 */
		void TranslateLocal(const float x, const float y, const float z);
		/**
		* Translate by the given vector and with respect to the
		* current orientation.
		*/
		void TranslateLocal(const glm::vec3& v);

		/** Rotate with a quaternion. */
		void Rotate(const glm::quat& rot);
		/** Rotate around an axis by a given angle. */
		void Rotate(float angle, const glm::vec3& axis);
		/** Rotate around the x axis by a given angle. */
		void RotateX(const float angle);
		/** Rotate around the y axis by a given angle. */
		void RotateY(const float angle);
		/** Rotate around the z axis by a given angle. */
		void RotateZ(const float angle);

		/** Rotate around the local x axis by a given angle */
		void RotateXLocal(const float angle);
		/** Rotate around the local y axis by a given angle */
		void RotateYLocal(const float angle);
		/** Rotate around the local z axis by a given angle */
		void RotateZLocal(const float angle);

		/** Get the current scale. */
		const glm::vec3& GetScale() const;
		/** Get the x component of the scale. */
		float GetScaleX() const;
		/** Get the y component of the scale. */
		float GetScaleY() const;
		/** Get the z component of the scale. */
		float GetScaleZ() const;

		/** Multiplicatively scaling of the current scale. */
		void Scale(const glm::vec3& val);
		/** Multiplicatively scale the x scale component. */
		void ScaleX(const float sx);
		/** Multiplicatively scale the y scale component. */
		void ScaleY(const float sy);
		/** Multiplicatively scale the z scale component. */
		void ScaleZ(const float sz);

		/** Assign the given value to the current scale. */
		void SetScale(const glm::vec3& val);
		/** Assign the given value to the current scale. */
		void SetScale(const float sx, const float sy, const float sz);
		/** Assign the given value to the current x-scale component. */
		void SetScaleX(const float sx);
		/** Assign the given value to the current x-scale component. */
		void SetScaleY(const float sy);
		/** Assign the given value to the current x-scale component. */
		void SetScaleZ(const float sz);

	protected:
		glm::vec3 m_up;
		glm::vec3 m_position;
		glm::vec3 m_forwardVector;
		glm::vec3 m_scale;

	private:
		glm::mat4 m_localMat;
	};
}