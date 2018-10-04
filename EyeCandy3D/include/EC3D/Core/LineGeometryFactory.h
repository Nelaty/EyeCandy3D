#pragma once
#include <memory>

namespace ec
{
	class LineStripGeometry;

	class LineGeometryFactory
	{
	public:
		using LineGeometry_Type = LineStripGeometry;
		using LineGeometry_Ptr = std::unique_ptr<LineGeometry_Type>;
		
		/**
		 * \brief Create the geometry of a rectangle's outline.
		 * \param width Should be > 0.0f
		 * \param height Should be > 0.0f
		 * \return Nullptr if parameters are invalid, a new line geometry otherwise.
		 */
		static LineGeometry_Ptr createRectangleOutlineGeometry(float width, float height);
		/**
		 * \brief Create the geometry of a circle's outline.
		 * \param radius Should be > 0.0f
		 * \return Nullptr if parameter is invalid, a new line geometry otherwise.
		 */
		static LineGeometry_Ptr createCircleOutlineGeometry(float radius);

	private:
		explicit LineGeometryFactory();
		~LineGeometryFactory();
	};
}