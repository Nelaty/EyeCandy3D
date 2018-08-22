#pragma once
#include "EC3D/Core/DynamicGeometry.h"

namespace ec
{
	class Node;

	class DynamicLineGeometry : public DynamicGeometry
	{
	public:
		explicit DynamicLineGeometry(Node* start, Node* end, float linewidth = 1.0f);
		~DynamicLineGeometry();

		/* Start node access */
		void setStart(Node* start);
		Node* getStart() const;

		/* End node access */
		void setEnd(Node* end);
		Node* getEnd() const;

		/* Line width access */
		void setLinewidth(float linewidth);
		float getLinewidth() const;

	protected:
		void onRender() override;

	private:
		Node* m_start;
		Node* m_end;

		float m_linewidth;
	};
}