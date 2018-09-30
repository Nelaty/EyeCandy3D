#pragma once
#include "EC3D/Core/StaticGeometry.h"
#include "EC3D/Common/Common.h"

/*
* Specialized geometry for rectangles
*/
namespace ec
{
	class EC3D_DECLSPEC RectangleGeometry : public StaticGeometry
	{
	public:
		explicit RectangleGeometry(float uniform = 1.0f);
		explicit RectangleGeometry(float width, float height);
		virtual ~RectangleGeometry();

		void init(float width, float height);

		float getWidth() const;
		float getHeight() const;

	private:
		float m_width;
		float m_height;
	};
}