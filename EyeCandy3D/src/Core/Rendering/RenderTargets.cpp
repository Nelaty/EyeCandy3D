#include "EC3D/Core/Rendering/RenderTarget.h"

namespace ec
{
	RenderTargets::RenderTargets()
	{
	}

	RenderTargets::~RenderTargets()
	{
	}

	void RenderTargets::addTarget(Node* target)
	{
		if(m_freeIndex < m_renderTargets.size())
		{
			m_renderTargets[m_freeIndex] = target;
			++m_freeIndex;
		}
		else
		{
			m_renderTargets.emplace_back(target);
		}
	}

	int RenderTargets::getValidTargetCount() const
	{
		return m_freeIndex;
	}

	const std::vector<Node*> RenderTargets::getTargets() const
	{
		return m_renderTargets;
	}

	void RenderTargets::clear()
	{
		m_freeIndex = 0;
	}
}