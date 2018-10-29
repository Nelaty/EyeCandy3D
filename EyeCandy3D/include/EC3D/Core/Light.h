#pragma once
#include "EC3D/Core/Node.h"
#include "EC3D/Core/LightType.h"

#include <glm/glm.hpp>

namespace ec
{
	/**
	 * \brief Abstract light source.
	 */
	class Light : public Node
	{
		public:
			virtual ~Light();

			/** 
			 * \brief Set the emissive color. 
			 */
			void setColor(const glm::vec3& color);
			/** 
			 * \brief Set the emissive color. 
			 */
			void setColor(float r, float g, float b);
			/** 
			 * \brief Get the emissive color. 
			 */
			const glm::vec3& getColor() const;

			/**
			 * \brief Set the intensity of this light source. 
			 */
			void setIntensity(float intensity);
			/** 
			 * \brief Get the intensity of this light source. 
			 */
			float getIntensity() const;
			
		protected:
			/**
			 * \brief Light constructor.
			 * \param type The light source type.
			 * \param intensity Determines brightness.
			 * \param color Emission color.
			 */
			explicit Light(LightType type,
						   float intensity = 1.0f,
						   const glm::vec3& color = glm::vec3(1.0f));

			glm::vec3 m_color;
			float m_intensity;

			const LightType m_type;
	};
}