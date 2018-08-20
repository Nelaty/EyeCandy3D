#pragma once
#include "Transform3D.h"

#include <vector>

#include <glm/glm.hpp>

/*
* Nodes make up the scene graph
* They can have multiple child nodes and can point to drawables
*/
namespace ec
{
	class SceneRenderer;
	class Geometry;
	class Drawable;

	class Node : public Transform3D
	{
	public:
		explicit Node(Node* parent);
		virtual ~Node();

		/** Adds drawables to the given scene renderer visitor. */
		virtual void Render(SceneRenderer& renderer);
		
		/** Recursively update global matrices */
		virtual void UpdateGlobalMatrices(const glm::mat4& m_parentMat);

		/**
		 * Get the current global matrix. This node needs to be
		 * rendered at least once, for the matrix to be something
		 * else than the unit matrix. 
		 */
		const glm::mat4& GetGlobalMat() const;

		/** 
		 * Get the current global position
		 * Global matrix has to be updated before calling this function!
		 * If not, the position will be from the last frame.
		 */
		const glm::vec3& GetGlobalPosition();

		/* Parent */
		Node* GetParent();
		void SetParent(Node* parent);

		/* Children */
		void AddChild(Node* child);
		bool RemoveChild(Node* child);
		void RemoveChildren();
		unsigned int GetChildrenCount() const;
		bool HasChildren() const;

		/* Drawable access */
		virtual const std::vector<Drawable*>& GetDrawables() const;
		void AddDrawable(Drawable* drawable);
		void RemoveDrawable(Drawable* drawable);
		void RemoveDrawables();

	protected:
		Node* m_parent;
		std::vector<Node*> m_children;
		std::vector<Drawable*> m_drawables;

	private:
		glm::mat4 m_globalMat;
	};
}