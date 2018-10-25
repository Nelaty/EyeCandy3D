#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include "EC3D/Core/DynamicGeometry.h"
#include "EC3D/Core/CubeGeometry.h"

namespace ec
{
	class Node;

	/**
	 * \brief Line geometry that adapts to a given start and end
	 * point.
	 */
	class EC3D_DECLSPEC DynamicLineGeometry : public DynamicGeometry
	{
	public:
		/**
		 * \brief DynamicLineGeometry constructor.
		 * \param start The start point of the line.
		 * \param end The end point of the line.
		 * \param lineWidth The width of the line.
		 */
		explicit DynamicLineGeometry(Node* start, Node* end, float lineWidth = 0.05f);
		~DynamicLineGeometry();

		/**
		 * \brief Set the start point of the line.
		 */
		void setStart(Node* start);
		/**
		 * \brief Get the start point of the line.
		 */
		Node* getStart() const;

		/**
		 * \brief Set the end point of the line.
		 */
		void setEnd(Node* end);
		/**
		 * \brief Get the end point of the line.
		 */
		Node* getEnd() const;

		/**
		 * \brief Set the current line width.
		 */
		void setLineWidth(float lineWidth);
		/**
		 * \brief Get the current line width.
		 */
		float getLineWidth() const;

	protected:
		void onRender() override;

		/**
		 * \brief Initialize the geometry data.
		 */
		void init();
		/**
		 * \brief Initialize vertex data.
		 * \return False if start and end positions are identical.
		 */
		bool initVertices();
		/**
		 * \brief Initialize texture coordinates.
		 */
		void initTexCoords();
		/**
		 * \brief Initialize index data.
		 */
		void initIndices();

	private:
		Node* m_start;
		Node* m_end;

		float m_lineWidth;
	};
}