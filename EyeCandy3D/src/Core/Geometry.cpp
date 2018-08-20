#include "EC3D/Core/Geometry.h"
#include "EC3D/Core/Shader/Shader.h"

#include "EC3D/Utilities/UtilitiesFile.h"

#include <gl/glew.h>

#include <string>
#include <sstream>

namespace ec
{
	Geometry::~Geometry()
	{
	}

	void Geometry::Render(Shader* shader, const glm::mat4& model)
	{
		BeginRender();
		OnRender();
		EndRender();
	}

	Geometry::Geometry()
	{
	}

	void Geometry::BeginRender()
	{
	}

	void Geometry::OnRender()
	{
	}

	void Geometry::EndRender()
	{
	}
}