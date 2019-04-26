#include "EC3D/Core/Geometry/LineGeometryFactory.h"
#include "EC3D/Core/Geometry/LineStripGeometry.h"

namespace ec
{
	LineGeometryFactory::LineGeometry_Ptr 
	LineGeometryFactory::createRectangleOutlineGeometry(const float width, 
														const float height)
	{
		if(width <= 0.0f || height <= 0.0f)
		{
			return nullptr;
		}

		const glm::vec2 halfSizes(0.5f * width, 0.5f * height);

		auto geo = std::make_unique<LineGeometry_Type>();
		geo->addVertex(glm::vec3(-halfSizes.x, -halfSizes.y, 0.0f));
		geo->addVertex(glm::vec3(halfSizes.x, -halfSizes.y, 0.0f));
		geo->addVertex(glm::vec3(halfSizes.x, halfSizes.y, 0.0f));
		geo->addVertex(glm::vec3(-halfSizes.x, halfSizes.y, 0.0f));
		geo->init();

		return geo;

		/*glVertex2i(rect.getLeft(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getTop());
		glVertex2i(rect.getLeft(), rect.getTop());*/
	}

	LineGeometryFactory::LineGeometry_Ptr 
	LineGeometryFactory::createCircleOutlineGeometry(const float radius)
	{
		if(radius <= 0.0f)
		{
			return nullptr;
		}

		return nullptr;
	}

	LineGeometryFactory::LineGeometryFactory()
	= default;

	LineGeometryFactory::~LineGeometryFactory()
	= default;
}
