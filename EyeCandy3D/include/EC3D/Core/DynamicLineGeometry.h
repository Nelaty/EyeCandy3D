#pragma once
#include <GL/glew.h>

#include "EC3D/Core/DynamicGeometry.h"

namespace ec
{
	class Node;

	class DynamicLineGeometry : public DynamicGeometry
	{
	public:
		explicit DynamicLineGeometry(Node* start, Node* end, float lineWidth = 1.0f);
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

		void beginRender() override;
		void onRender() override;
		void endRender() override;

	private:
		Node* m_start;
		Node* m_end;

		float m_lineWidth;
	};
}