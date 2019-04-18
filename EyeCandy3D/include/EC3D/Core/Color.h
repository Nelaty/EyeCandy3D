#pragma once
#include <glm/glm.hpp>

#include <string>

namespace ec
{
	class Color
	{
	public:
		explicit Color(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		explicit Color(float r, float g, float b, float a = 1.0f);
		~Color();

		/** \brief Create a rgb color. Parameters are in range [0, 255]. */
		static Color createRgb(int r, int g, int b, int a = 255);
		/** \brief Create a rgb color. Parameters are in range[0.0, 1.0]. */
		static Color createRgbF(float r, float g, float b, float a = 1.0f);
		/** \brief Create a rgb color from a hex value. */
		static Color createHexRgb(unsigned int hex);
		/** \brief Create a rgb color from a hex string. 
		 * It must either have the form FFFFFF or 0xFFFFFF. 
		 * \return A new color with the given value, or a default color
		 * if the given hex code is invalid. 
		 */
		static Color createHexRgb(const std::string& hex);
		/** \brief Create a rgba color from a hex value. */
		static Color createHexRgba(unsigned int hex);
		/** \brief Create a rgba color from a hex string.
		 * It must either have the form FFFFFFFF or 0xFFFFFFFF.
		 * \return A new color with the given value, or a default color
		 * if the given hex code is invalid.
		 */
		static Color createHexRgba(const std::string& hex);

		/** \brief Set the color data. */
		void setColor(const glm::vec4& color);
		/** \brief Get the color data. */
		const glm::vec4& getColor() const;

		/** \brief Set the red component. */
		void setR(float r);
		/** \brief Get the red component. */
		float getR() const;

		/** \brief Set the green component. */
		void setG(float g);
		/** \brief Get the green component. */
		float getG() const;

		/** \brief Set the blue component. */
		void setB(float b);
		/** \brief Get the blue component. */
		float getB() const;

		/** \brief Set the alpha component. */
		void setA(float a);
		/** \brief Get the alpha component. */
		float getA() const;

	private:
		static constexpr float s_rgbMax = 255.0f;

		glm::vec4 m_color;
	};
}