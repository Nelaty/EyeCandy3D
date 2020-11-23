#include "EC3D/Core/Node.h"
#include "EC3D/Core/SceneRenderer.h"
#include "EC3D/Graphics/Geometry/IGeometryAccess.h"

#include <algorithm>

namespace ec
{
	Node::Node(Node* parent)
		: m_parent{parent},
		m_globalMat{1.0f}
	{
		if(parent && parent != this)
		{
			parent->addChild(this);
		}
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

	void Node::updateGlobalMatrices(const glm::mat4& parentMat, bool dirty)
	{
	    dirty |= isDirty();
	    if(dirty)
        {
            updateLocalMat();
            m_globalMat = parentMat * getLocalMat();
            unmarkDirty();
        }
		for(auto& it : m_children)
		{
			it->updateGlobalMatrices(m_globalMat, dirty);
		}
	}

	const glm::mat4& Node::getGlobalMat() const
	{
		return m_globalMat;
	}

	glm::vec3 Node::getGlobalPosition() const
	{
		return glm::vec3(m_globalMat[3]);
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
		//child->setParent(this);
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
			child->setParent(nullptr);
			return true;
		}
		return false;
	}

	void Node::removeChildren()
	{
		for(auto& it : m_children)
		{
			it->setParent(nullptr);
		}
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

	bool Node::removeDrawable(Drawable* drawable)
	{
		const auto removedEntry = std::remove(m_drawables.begin(),
											  m_drawables.end(),
											  drawable);
		return removedEntry != m_drawables.end();
	}

	void Node::removeDrawables()
    {
        m_drawables.clear();
    }
}