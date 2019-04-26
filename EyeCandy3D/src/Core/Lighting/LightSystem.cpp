#include "EC3D/Core/Lighting/LightSystem.h"
#include "EC3D/Core/Lighting/Light.h"
#include "EC3D/Core/Shader/Shader.h"

#include <algorithm>
#include <cassert>

namespace ec
{
	LightSystem::LightSystem()
	{
	}

	LightSystem::~LightSystem()
	{
	}

	void LightSystem::enable(Shader* shader)
	{
	}

	bool LightSystem::registerLight(Light* light)
	{
		assert(light->m_type != LightType::count);

		auto& container = m_lights[int(light->m_type)];
		const auto foundEntry = std::find(container.begin(),
										  container.end(),
										  light);
		if(foundEntry != container.end())
		{
			return false;
		}

		container.emplace_back(light);
		return true;
	}

	bool LightSystem::unregisterLight(Light* light)
	{
		assert(light->m_type != LightType::count);

		auto& container = m_lights[int(light->m_type)];
		const auto foundEntry = std::remove(container.begin(),
											container.end(),
											light);
		return foundEntry != container.end();
	}
}
