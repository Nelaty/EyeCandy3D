#include "EC3D/Core/Node.h"
#include "EC3D/Core/SceneRenderer.h"
#include "EC3D/Core/Geometry.h"

#include <algorithm>

namespace ec
{
	Node::Node(Node* parent)
		: m_parent{parent},
		m_localMat{1.0f},
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
		m_globalMat = m_parentMat * m_localMat;
		for(auto& it : m_children)
		{
			it->UpdateGlobalMatrices(m_globalMat);
		}
	}

	const glm::mat4& Node::GetGlobalMat() const
	{
		return m_globalMat;
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

	const glm::mat4& Node::GetLocalMatrix() const
	{
		return m_localMat;
	}

	const glm::mat4& Node::GetGlobalMatrix() const
	{
		return m_globalMat;
	}

	void Node::Translate(const glm::vec3& val)
	{
		m_localMat[3].x += val.x;
		m_localMat[3].y += val.y;
		m_localMat[3].z += val.z;
	}

	void Node::TranslateX(float x)
	{
		m_localMat[3].x += x;
	}

	void Node::TranslateY(float y)
	{
		m_localMat[3].y += y;
	}

	void Node::TranslateZ(float z)
	{
		m_localMat[3].z += z;
	}

	void Node::SetTranslation(const glm::vec3& val)
	{
		m_localMat[3].x = val.x;
		m_localMat[3].y = val.y;
		m_localMat[3].z = val.z;
	}

	glm::vec3 Node::GetTranslation() const
	{
		return m_localMat[3];
	}

	void Node::Rotate(const float angle, const glm::vec3& axis)
	{

	}

	void Node::SetOrientation(const glm::vec3& orientation)
	{

	}

	glm::vec3 Node::SetOrientation() const
	{
		return glm::vec3(0);
	}

	void Node::Scale(const glm::vec3& val)
	{
		m_localMat[0][0] *= val.x;
		m_localMat[1][1] *= val.y;
		m_localMat[2][2] *= val.z;
	}

	void Node::SetScale(const glm::vec3& val)
	{
		m_localMat[0][0] = val.x;
		m_localMat[1][1] = val.y;
		m_localMat[2][2] = val.z;
	}

	glm::vec3 Node::GetScale() const
	{
		return glm::vec3(0);
	}
}