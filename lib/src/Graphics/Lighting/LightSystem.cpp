#include "ec3/Graphics/Lighting/LightSystem.h"
#include "ec3/Graphics/Lighting/Light.h"
#include "ec3/Graphics/Shader/Shader.h"

#include <algorithm>

namespace ec
{
	LightSystem::LightSystem()
		= default;

	LightSystem::~LightSystem()
		= default;

	void LightSystem::enable(Shader* shader)
	{
	}

	bool LightSystem::registerLight(Light* light)
	{
		const auto foundEntry = std::find(m_lights.begin(),
										  m_lights.end(),
										  light);
		if(foundEntry != m_lights.end())
		{
			return false;
		}

		m_lights.emplace_back(light);
		return true;
	}

	bool LightSystem::unregisterLight(Light* light)
	{
		const auto foundEntry = std::remove(m_lights.begin(),
											m_lights.end(),
											light);
		return foundEntry != m_lights.end();
	}
}
