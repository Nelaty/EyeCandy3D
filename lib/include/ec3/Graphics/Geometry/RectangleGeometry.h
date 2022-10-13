#pragma once
#include "StaticGeometry.h"
#include "ec3/Common/Common.h"


namespace ec
{
	/**
	 * \brief Geometry that represents a filled rectangle.
	 */
	class EC3D_DECLSPEC RectangleGeometry : public StaticGeometry
	{
	public:
		/**
		 * \brief RectangleGeometry constructor.
		 * \param uniform Side length for all sides.
		 */
		explicit RectangleGeometry(float uniform = 1.0f);
		/**
		 * \brief RectangleGeometry constructor.
		 * \param width Horizontal side length.
		 * \param height Vertical side length.
		 */
		explicit RectangleGeometry(float width, float height);
		virtual ~RectangleGeometry();

		/** 
		 * \brief Change rectangle dimensions 
		 * \param width Horizontal side length.
		 * \param height Vertical side length.
		 */
		void init(float width, float height);

		/** 
		 * \brief Get the current width of the rectangle.
		 */
		float getWidth() const;
		/**
		 * \brief Get the current height of the rectangle.
		 */
		float getHeight() const;
		
	private:
		float m_width;
		float m_height;
	};
}