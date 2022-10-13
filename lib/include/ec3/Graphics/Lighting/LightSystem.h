#pragma once
#include <vector>

namespace ec
{
	class Light;
	class Shader;

	/// Contains a collection of different light sources.
	/// \todo: not implemented yet
	class LightSystem
	{	
	public:
		explicit LightSystem();
		~LightSystem();
		 
		/// Pass lights to given shader. 
		/// \param shader The shader to pass the light information to.
		void enable(Shader* shader);

		/// Register a new light source.
		/// \param light The light source to register.
		/// \return False if the lights source is already registered,
		///         true otherwise.
		bool registerLight(Light* light);
		
		/// \brief Unregister an already registered light source.
		/// \param light The light source to unregister.
		/// \return False if the lights source wasn't found, true
	    ///         otherwise.
		bool unregisterLight(Light* light);
		
	private:
		std::vector<Light*> m_lights;
	};
}