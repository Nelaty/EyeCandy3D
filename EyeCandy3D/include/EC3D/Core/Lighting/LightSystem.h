#pragma once
#include "LightType.h"

#include <vector>
#include <array>

namespace ec
{
	class Light;
	class Shader;

	/**
	 * \brief Contains a collection of different light sources.
	 * \todo: not implemented yet
	 */
	class LightSystem
	{	
	public:
		explicit LightSystem();
		~LightSystem();
		
		/** 
		 * \brief Pass lights to given shader. 
		 * \param shader The shader to pass the light information to.
		 */
		void enable(Shader* shader);

		/**
		 * \brief Register a new light source.
		 * \param light The light source to register.
		 * \return False if the lights source is already registered,
		 * true otherwise.
		 */
		bool registerLight(Light* light);
		/**
		 * \brief Unregister an already registered light source.
		 * \param light The light source to unregister.
		 * \return False if the lights source wasn't found, true
		 * otherwise.
		 */
		bool unregisterLight(Light* light);
		
	private:
		std::array<std::vector<Light*>, int(LightType::count)> m_lights;
	};
}