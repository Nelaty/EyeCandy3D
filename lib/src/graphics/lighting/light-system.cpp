#include "ec3/graphics/lighting/light-system.h"
#include "ec3/graphics/lighting/light.h"
#include "ec3/graphics/shader/shader.h"

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
