#pragma once
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

	class Node
	{
	public:
		explicit Node(Node* parent);
		virtual ~Node();

		/** Adds drawables to the given scene renderer visitor. */
		virtual void Render(SceneRenderer& renderer);
		
		/** Recursively update global matrices */
		void UpdateGlobalMatrices(const glm::mat4& m_parentMat);

		/**
		 * Get the current global matrix. This node needs to be
		 * rendered at least once, for the matrix to be something
		 * else than the unit matrix. 
		 */
		const glm::mat4& GetGlobalMat() const;

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

		/* Matrix access */
		const glm::mat4& GetLocalMatrix() const;
		const glm::mat4& GetGlobalMatrix() const;

		/* Translation */
		void Translate(const glm::vec3& val);
		void TranslateX(float x);
		void TranslateY(float y);
		void TranslateZ(float z);
		void SetTranslation(const glm::vec3& val);
		glm::vec3 GetTranslation() const;

		// TODO: IMPLEMENT!
		/* Rotation */
		void Rotate(const float angle, const glm::vec3& axis);
		void SetOrientation(const glm::vec3& orientation);
		glm::vec3 SetOrientation() const;

		/* Scaling */
		void Scale(const glm::vec3& val);
		void SetScale(const glm::vec3& val);
		glm::vec3 GetScale() const;

	protected:
		Node* m_parent;
		std::vector<Node*> m_children;

		std::vector<Drawable*> m_drawables;

		glm::mat4 m_localMat;

	private:
		glm::mat4 m_globalMat;
	};
}