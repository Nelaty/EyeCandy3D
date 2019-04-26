#pragma once
#include "StaticGeometry.h"

namespace ec
{
	class GeometryData;

	/** \brief A TriangleMesh can have any kind of shape. */
	class TriangleMesh : public StaticGeometry
	{
	public:
		explicit TriangleMesh();
		explicit TriangleMesh(const GeometryData& data);
		~TriangleMesh();

		void setData(const GeometryData& data);
		
	private:
		void init();
	};
}