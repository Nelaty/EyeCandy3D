#pragma once
#include "ec3/common/common.h"
#include "ec3/transform-3d.h"

#include <vector>

#include <glm/glm.hpp>

namespace ec
{
	class SceneRenderer;
	class IGeometryAccess;
	class Drawable;

	/**
	 * \brief Nodes make up the scene graph. They represent a directed
	 * acyclic graph.
	 * \details They can have multiple child nodes and can contains a number of
	 * drawables.
	 */
	class EC3D_DECLSPEC Node : public Transform3D
	{
	public:
		explicit Node(Node* parent = nullptr);
		virtual ~Node();

		/** 
		 * \brief Adds drawables to the given scene renderer visitor. 
		 */
		virtual void render(SceneRenderer& renderer);
		
		/**
		 * \brief Recursively update global matrices. 
		 */
		virtual void updateGlobalMatrices(const glm::mat4& parentMat, bool dirty=false);

		/**
		 * \brief Get the current global matrix. 
		 * \details This node needs to be rendered at least once for
		 * the matrix to be something else than the unit matrix. 
		 */
		const glm::mat4& getGlobalMat() const;

		/** 
		 * \brief Get the current global position.
		 * \details Global matrix has to be updated before calling 
		 * this function! If not, the position will be from the
		 * last frame.
		 */
		glm::vec3 getGlobalPosition() const;

		/** 
		 * \brief Get this node's parent node. 
		 * \return The parent node or nullptr if this node is a 
		 * root node.
		 */
		Node* getParent() const;
		

		/** 
		 * \brief Add a new child to this node.
		 * \details Important: Do not create cycles!
		 */
		void addChild(Node* child);
		/** 
		 * \brief Remove an existing child from this node.
		 * \return True if the child node was found, false otherwise.
		 */
		bool removeChild(Node* child);
		/** 
		 * \brief Remove all child nodes from this node. 
		 */
		void removeChildren();
		/** 
		 * \brief Get the number of child nodes.
		 */
		unsigned int getChildrenCount() const;
		/**
		 * \brief Check if this node has one or more child nodes. 
		 * \return True if there are child nodes, false otherwise.
		 */
		bool hasChildren() const;

		/** 
		 * \brief Get all drawables preiously added to this node.
		 */
		virtual const std::vector<Drawable*>& getDrawables() const;
		/**
		 * \brief Add a given drawable to this node. 
		 */
		void addDrawable(Drawable* drawable);
		/**
		 * \brief Remove a given drawable from this node.
		 */
		bool removeDrawable(Drawable* drawable);
		/**
		 * \brief Remove all drawables from this node.
		 */
		void removeDrawables();

	protected:
		Node* m_parent;
		std::vector<Node*> m_children;
		std::vector<Drawable*> m_drawables;

	private:
		/**
		 * \brief Set this node's parent node.
		 */
		void setParent(Node* parent);

		glm::mat4 m_globalMat;
	};
}