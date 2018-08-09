#include "EC3D/Core/SceneController.h"

#include <algorithm>

namespace ec
{
	SceneController::SceneController(const std::string& controllerName)
		: m_name{controllerName}
	{
	}

	SceneController::~SceneController()
	{
	}

	const std::string& SceneController::GetName() const
	{
		return m_name;
	}
}