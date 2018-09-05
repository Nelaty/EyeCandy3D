#pragma once
#include "EC3D/Core/Transform3D.h"
#include "EC3D/Common/Common.h"

#include <vector>

#include <glm/glm.hpp>

/**
* Nodes make up the scene graph
* They can have multiple child nodes and can point to drawables
*/
namespace ec
{
	class SceneRenderer;
	class IGeometryAccess;
	class Drawable;

	class EC3D_DECLSPEC Node : public Transform3D
	{
	public:
		explicit Node(Node* parent = nullptr);
		virtual ~Node();

		/** Adds drawables to the given scene renderer visitor. */
		virtual void render(SceneRenderer& renderer);
		
		/** Recursively update global matrices */
		virtual void updateGlobalMatrices(const glm::mat4& parentMat);

		/**
		 * Get the current global matrix. This node needs to be
		 * rendered at least once, for the matrix to be something
		 * else than the unit matrix. 
		 */
		const glm::mat4& getGlobalMat() const;

		/** 
		 * Get the current global position
		 * Global matrix has to be updated before calling this function!
		 * If not, the position will be from the last frame.
		 */
		glm::vec3 getGlobalPosition() const;

		/** Get this node's parent node. */
		Node* getParent() const;
		/** Set this node's parent node. */
		void setParent(Node* parent);

		/** Add a new child to this node */
		void addChild(Node* child);
		/** Remove an existing child from this node. */
		bool removeChild(Node* child);
		/** Remove all child nodes from this node. */
		void removeChildren();
		/** Get the number of children nodes. */
		unsigned int getChildrenCount() const;
		/** Check if this node has one or more child nodes. */
		bool hasChildren() const;

		/** Get all drawables related to this node. */
		virtual const std::vector<Drawable*>& getDrawables() const;
		/** Add a given drawable to this node. */
		void addDrawable(Drawable* drawable);
		/** Remove a given drawable from this node. */
		void removeDrawable(Drawable* drawable);
		/** Remove all drawables from this node. */
		void removeDrawables();

	protected:
		Node* m_parent;
		std::vector<Node*> m_children;
		std::vector<Drawable*> m_drawables;

	private:
		glm::mat4 m_globalMat;
	};
}