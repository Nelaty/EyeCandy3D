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
	{
	}

	void Node::Render(SceneRenderer& renderer)
	{
		if(!m_drawables.empty())
		{
			renderer.AddRenderingTarget(this);
		}
		for(auto& it : m_children)
		{
			it->Render(renderer);
		}
	}

	void Node::UpdateGlobalMatrices(const glm::mat4& m_parentMat)
	{
		UpdateLocalMat();
		m_globalMat = m_parentMat * GetLocalMat();
		for(auto& it : m_children)
		{
			it->UpdateGlobalMatrices(m_globalMat);
		}
	}

	const glm::mat4& Node::GetGlobalMat() const
	{
		return m_globalMat;
	}

	const glm::vec3& Node::GetGlobalPosition()
	{
		return glm::vec3(m_globalMat[4]);
	}

	ec::Node* Node::GetParent()
	{
		return m_parent;
	}

	void Node::SetParent(Node* parent)
	{
		if(m_parent)
		{
			m_parent->RemoveChild(this);
		}
		m_parent = parent;
	}

	void Node::AddChild(Node* child)
	{
		m_children.push_back(child);
	}

	bool Node::RemoveChild(Node* child)
	{
		auto foundChild = std::find(m_children.begin(),
									m_children.end(),
									child);

		if(foundChild != m_children.end())
		{
			m_children.erase(foundChild);
			return true;
		}
		else
		{
			return false;
		}
	}

	void Node::RemoveChildren()
	{
		m_children = std::vector<Node*>();
	}

	unsigned int Node::GetChildrenCount(void) const
	{
		return m_children.size();
	}

	bool Node::HasChildren() const
	{
		return !m_children.empty();
	}

	const std::vector<Drawable*>& Node::GetDrawables() const
	{
		return m_drawables;
	}

	void Node::AddDrawable(Drawable* drawable)
	{
		m_drawables.push_back(drawable);
	}

	void Node::RemoveDrawable(Drawable* drawable)
	{
		std::remove(m_drawables.begin(),
					m_drawables.end(),
					drawable);
	}

	void Node::RemoveDrawables()
	{
		m_drawables = std::vector<Drawable*>();
	}
}