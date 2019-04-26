#pragma once
#include "EC3D/Core/Node.h"
#include "EC3D/Core/Color.h"
#include "LightType.h"

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

			ec::Color m_color;
			float m_intensity;

			/** \brief Type is needed, so it can be correctly passed
			 * to the shader. 
			 */
			const LightType m_type;
			
		protected:
			/**
			 * \brief Light constructor.
			 * \param type The light source type.
			 * \param intensity Determines brightness.
			 * \param color Emission color.
			 */
			explicit Light(LightType type,
						   float intensity = 1.0f,
						   const ec::Color& color = ec::Color());
	};
}