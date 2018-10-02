#pragma once

namespace ec
{
	struct Vertex;

	class LineStripGeometry
	{
	public:
		explicit LineStripGeometry();
		~LineStripGeometry();

		void init();

		void addVertex(const Vertex& vertex);
		void setData(Vertex* vertices, int count);

		void reset();
	};
}