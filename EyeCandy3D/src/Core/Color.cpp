#include "EC3D/Core/Color.h"

#include <iostream>

namespace ec
{

	Color::Color(const glm::vec4& color)
		: m_color(color)
	{
	}

	Color::Color(float r, float g, float b, float a)
		: m_color(r, g, b, a)
	{
	}

	Color::~Color()
	{
	}

	Color Color::createRgb(int r, int g, int b, int a)
	{
		return Color(float(r) / s_rgbMax,
					 float(g) / s_rgbMax,
					 float(b) / s_rgbMax,
					 float(a) / s_rgbMax);
	}

	Color Color::createRgbF(float r, float g, float b, float a)
	{
		return Color(r, g, b, a);
	}

	Color Color::createHexRgb(unsigned int hex)
	{
		return createRgb(
			(hex << 8) >> 24,
			(hex << 16) >> 24,
			(hex << 24) >> 24);
	}

	Color Color::createHexRgb(const std::string& hex)
	{
		auto hexToInt = [](char c)
		{
			if(c >= 'A')
			{
				return c - 'A' + 10;
			}
			else
			{
				return c - '0';
			}
		};

		auto extractInt = [&](int pos)
		{
			return (hexToInt(hex[pos]) << 4) + hexToInt(hex[pos + 1]);
		};

		try
		{
			if(hex.size() == 8)
			{
				return createRgb(extractInt(2),
								 extractInt(4),
								 extractInt(6));
			}
			else if(hex.size() == 6)
			{
				return createRgb(extractInt(0),
								 extractInt(2),
								 extractInt(4));
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << "ERROR: Invalid hex color format: " << hex << "\n";
		}
		return Color();
	}

	Color Color::createHexRgba(unsigned int hex)
	{
		return createRgb(
			hex >> 24,
			(hex << 8) >> 24,
			(hex << 16) >> 24,
			(hex << 24) >> 24);
	}

	Color Color::createHexRgba(const std::string& hex)
	{
		auto hexToInt = [](char c)
		{
			if(c >= 'A')
			{
				return c - 'A' + 10;
			}
			else
			{
				return c - '0';
			}
		};

		auto extractInt = [&](int pos)
		{
			return (hexToInt(hex[pos]) << 4) + hexToInt(hex[pos + 1]);
		};

		try
		{
			if(hex.size() == 10)
			{
				return createRgb(extractInt(2),
								 extractInt(4),
								 extractInt(6),
								 extractInt(8));
			}
			else if(hex.size() == 8)
			{
				return createRgb(extractInt(0),
								 extractInt(2),
								 extractInt(4),
								 extractInt(6));
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << "ERROR: Invalid hex color format: " << hex << "\n";
		}
		return Color();
	}

	void Color::setColor(const glm::vec4& color)
	{
		m_color = color;
	}

	const glm::vec4& Color::getColor() const
	{
		return m_color;
	}

	void Color::setR(float r)
	{
		m_color.r = r;
	}

	float Color::getR() const
	{
		return m_color.r;
	}

	void Color::setG(float g)
	{
		m_color.g = g;
	}

	float Color::getG() const
	{
		return m_color.g;
	}

	void Color::setB(float b)
	{
		m_color.b = b;
	}

	float Color::getB() const
	{
		return m_color.b;
	}

	void Color::setA(float a)
	{
		m_color.a = a;
	}

	float Color::getA() const
	{
		return m_color.a;
	}

}