#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include "EC3D/Core/DynamicGeometry.h"
#include "EC3D/Core/CubeGeometry.h"

namespace ec
{
	class Node;

	class EC3D_DECLSPEC DynamicLineGeometry : public DynamicGeometry
	{
	public:
		explicit DynamicLineGeometry(Node* start, Node* end, float lineWidth = 0.05f);
		~DynamicLineGeometry();

		/* Start node access */
		void setStart(Node* start);
		Node* getStart() const;

		/* End node access */
		void setEnd(Node* end);
		Node* getEnd() const;

		/* Line width access */
		void setLineWidth(float lineWidth);
		float getLineWidth() const;

	protected:
		void onRender() override;

		void init();
		bool initVertices();
		void initTexCoords();
		void initIndices();

	private:
		Node* m_start;
		Node* m_end;

		float m_lineWidth;
	};
}