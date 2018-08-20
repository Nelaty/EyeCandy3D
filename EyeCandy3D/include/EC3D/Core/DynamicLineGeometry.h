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
		void SetStart(Node* start);
		Node* GetStart() const;

		/* End node access */
		void SetEnd(Node* end);
		Node* GetEnd() const;

		/* Line width access */
		void SetLinewidth(float linewidth);
		float GetLinewidth() const;

	protected:
		virtual void OnRender() override;

	private:
		Node* m_start;
		Node* m_end;

		float m_linewidth;
	};
}