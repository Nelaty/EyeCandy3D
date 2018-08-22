#include "EC3D/Core/Node.h"
#include "EC3D/Core/SceneRenderer.h"
#include "EC3D/Core/Geometry.h"

#include <algorithm>

namespace ec
{
	Node::Node(Node* parent)
		: m_parent{parent},
		m_globalMat{1.0f}
	{
	}

	Node::~Node()
	= default;

	void Node::render(SceneRenderer& renderer)
	{
		if(!m_drawables.empty())
		{
			renderer.addRenderingTarget(this);
		}
		for(auto& it : m_children)
		{
			it->render(renderer);
		}
	}

	void Node::updateGlobalMatrices(const glm::mat4& m_parentMat)
	{
		updateLocalMat();
		m_globalMat = m_parentMat * getLocalMat();
		for(auto& it : m_children)
		{
			it->updateGlobalMatrices(m_globalMat);
		}
	}

	const glm::mat4& Node::getGlobalMat() const
	{
		return m_globalMat;
	}

	const glm::vec3& Node::getGlobalPosition()
	{
		return glm::vec3(m_globalMat[4]);
	}

	ec::Node* Node::getParent() const
	{
		return m_parent;
	}

	void Node::setParent(Node* parent)
	{
		if(m_parent)
		{
			m_parent->removeChild(this);
		}
		m_parent = parent;
	}

	void Node::addChild(Node* child)
	{
		m_children.push_back(child);
	}

	bool Node::removeChild(Node* child)
	{
		const auto foundChild = std::find(m_children.begin(),
										  m_children.end(),
										  child);

		if(foundChild != m_children.end())
		{
			m_children.erase(foundChild);
			return true;
		}
		return false;
	}

	void Node::removeChildren()
	{
		m_children = std::vector<Node*>();
	}

	unsigned int Node::getChildrenCount() const
	{
		return m_children.size();
	}

	bool Node::hasChildren() const
	{
		return !m_children.empty();
	}

	const std::vector<Drawable*>& Node::getDrawables() const
	{
		return m_drawables;
	}

	void Node::addDrawable(Drawable* drawable)
	{
		m_drawables.push_back(drawable);
	}

	void Node::removeDrawable(Drawable* drawable)
	{
		std::remove(m_drawables.begin(),
					m_drawables.end(),
					drawable);
	}

	void Node::removeDrawables()
	{
		m_drawables = std::vector<Drawable*>();
	}
}