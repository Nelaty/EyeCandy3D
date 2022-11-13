#pragma once
#include "ec3/node.h"
#include "ec3/graphics/lighting/light-type.h"

#include <glm/glm.hpp>

namespace ec
{
	/// Abstract light source.
	class Light : public Node
	{
		public:
			virtual ~Light();

			// Set the emissive color. 
			void setColor(const glm::vec3& color);
			// Set the emissive color. 
			void setColor(float r, float g, float b);
			// Get the emissive color. 
			const glm::vec3& getColor() const;

			// Set the intensity of this light source. 
			void setIntensity(float intensity);
			// Get the intensity of this light source. 
			float getIntensity() const;
			
		protected:
			/// \param type The light source type.
			/// \param intensity Determines brightness.
			/// \param color Emission color.
			explicit Light(LightType type,
						   float intensity = 1.0f,
						   const glm::vec3& color = glm::vec3(1.0f));

			glm::vec3 m_color;
			float m_intensity;

			const LightType m_type;
	};
}