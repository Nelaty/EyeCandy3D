#pragma once
#include <vector>

namespace ec
{
	class Node;

	class RenderTargets
	{
	public:
		explicit RenderTargets();
		~RenderTargets();

		void addTarget(Node* target);

		int getValidTargetCount() const;
		const std::vector<Node*> getTargets() const;

		void clear();

	private:
		int m_freeIndex{0};

		std::vector<Node*> m_renderTargets;
	};
}
