#include "EC3D/Core/DynamicLineGeometry.h"
#include "EC3D/Core/Node.h"

#include <glm/glm.hpp>

namespace ec
{

	DynamicLineGeometry::DynamicLineGeometry(Node* start, Node* end, float linewidth)
		: m_start{start},
		m_end{end},
		m_linewidth{linewidth}
	{
	}

	DynamicLineGeometry::~DynamicLineGeometry()
	{
	}

	void DynamicLineGeometry::SetStart(Node* start)
	{
		m_start = start;
	}

	ec::Node* DynamicLineGeometry::GetStart() const
	{
		return m_start;
	}

	void DynamicLineGeometry::SetEnd(Node* end)
	{
		m_end = end;
	}

	ec::Node* DynamicLineGeometry::GetEnd() const
	{
		return m_end;
	}

	void DynamicLineGeometry::SetLinewidth(float linewidth)
	{
		m_linewidth = linewidth;
	}

	float DynamicLineGeometry::GetLinewidth() const
	{
		return m_linewidth;
	}

	void DynamicLineGeometry::OnRender()
	{
		if(!m_start || !m_end) return;

		const auto& startPos = m_start->GetGlobalPosition();
		const auto& endPos = m_end->GetGlobalPosition();

		glLineWidth(m_linewidth);
		glBegin(GL_LINE);
		glVertex3f(startPos.x, startPos.y, startPos.z);
		glVertex3f(endPos.x, endPos.y, endPos.z);
		glEnd();
		glLineWidth(1.0f);
	}
}