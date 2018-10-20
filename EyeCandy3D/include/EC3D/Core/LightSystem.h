#pragma once

#include <vector>

namespace ec
{
	class Light;
	class Shader;

	class LightSystem
	{	
	public:
		explicit LightSystem();
		~LightSystem();
		
		/** Pass lights to given shader. */
		void enable(Shader* shader);
		
		void registerLight(Light* light);
		bool unregisterLight(Light* light);
		
	private:
		std::vector<Light*> m_lights;
	};
}