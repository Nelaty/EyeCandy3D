#pragma once
#include <glm/glm.hpp>

/*
* Used like an AABB for widgets
*/
namespace ec_gui
{
	class Bounds2D
	{
	public:
		explicit Bounds2D();
		virtual ~Bounds2D();

		/* Check if another Bounds2D is fully contained in this bounds */
		bool FullyContains(const Bounds2D& bounds);

		/* Translation */
		void Translate(const glm::vec2& val);
		void SetTranslation(const glm::vec2& val);

		/* Scaling */
		void Scale(const glm::vec2& val);
		void SetScale(const glm::vec2& val);

	private:
		glm::vec2 m_leftUpperCorner;
		glm::vec2 m_size;
	};
}