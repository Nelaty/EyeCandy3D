#include "EC3D/Core/SphereMesh.h"

#include <corecrt_math_defines.h>

namespace ec
{

	SphereMesh::SphereMesh(const float radius, const int latitude, const int longitude)
	{
		init(radius, latitude, longitude);
	}

	SphereMesh::~SphereMesh()
	= default;

	void SphereMesh::resize(const float radius, const int latitude, const int longitude)
	{
		init(radius, latitude, longitude);
	}

	float SphereMesh::getRadius() const
	{
		return m_radius;
	}

	float SphereMesh::getLatitude() const
	{
		return m_latitude;
	}

	float SphereMesh::getLongitude() const
	{
		return m_longitude;
	}

	void SphereMesh::init(const float radius, const int latitude, const int longitude)
	{
		m_radius = radius;
		m_latitude = latitude;
		m_longitude = longitude;

		if(latitude < 2 || longitude < 3)
		{
			printf("Can't initialize a sphere with less than 2 latitude or less than 3 longitude!\n");
			return;
		}
		
		initVerticesAndTexCoords();
		initIndices();
	
		recalculateNormals();
		setupMesh();
	}

	void SphereMesh::initVerticesAndTexCoords()
	{
		// Generate new vertex array
		const int numVertices = m_latitude * (m_longitude) + 2;
		m_vertices = std::vector<Vertex>(numVertices);

		// Create top and bottom vertices of the sphere separately
		Vertex top;
		top.m_position = glm::vec3(0.0f, m_radius, 0.0f);
		top.m_texCoords = glm::vec2(0, 1);
		m_vertices[0] = top;

		Vertex bot;
		bot.m_position = glm::vec3(0.0f, -m_radius, 0.0f);
		bot.m_texCoords = glm::vec2(0, 0);
		m_vertices[numVertices - 1] = bot;
		
		// +1.0f because there's a gap between the poles and the first parallel.
		const auto latitudeSpacing = 1.0f / (m_latitude + 1.0f);
		const auto longitudeSpacing = 1.0f / (m_longitude);

		// start writing new vertices at position 1
		auto v = 1;
		for(auto lat = 0; lat < m_latitude; ++lat)
		{
			for(auto lon = 0; lon < m_longitude; ++lon)
			{
				const glm::vec2 texcoords(lon * longitudeSpacing,
										  1.0f - (lat + 1) * latitudeSpacing);
				// Scale coordinates into the 0...1 texture coordinate range,
				// with north at the top (y = 1).
				m_vertices[v].m_texCoords = texcoords;

				// Convert to spherical coordinates:
				// theta is a longitude angle (around the equator) in radians.
				// phi is a latitude angle (north or south of the equator).
				const float theta = texcoords.x * 2.0f * M_PI;
				const float phi = (texcoords.y - 0.5f) * M_PI;

				// This determines the radius of the ring of this line of latitude.
				// It's widest at the equator, and narrows as phi increases/decreases.
				const auto c = cos(phi);

				// Usual formula for a vector in spherical coordinates.
				// You can exchange x & z to wind the opposite way around the sphere.
				
				glm::vec3 position(c * cos(theta),
								   sin(phi),
								   c * sin(theta));
				position *= m_radius;

				m_vertices[v].m_position = position;

				// Proceed to the next vertex.
				++v;
			}
		}
	}

	void SphereMesh::initIndices()
	{
		const int vertexNum = m_vertices.size();
		const int indexMax = vertexNum - 1;

		// Top row sectors only contain triangles
		for(auto i = 0; i < m_longitude; ++i)
		{
			if(i == m_longitude - 1)
			{
				m_indices.push_back(0);
				m_indices.push_back(1);
				m_indices.push_back(i + 1);
			}
			else
			{
				m_indices.push_back(0);
				m_indices.push_back(i + 2);
				m_indices.push_back(i + 1);
			}
		}

		// Middle sectors are quads
		const auto xOffset = 1;
		const int yOffset = m_longitude;

		for(auto i = 0; i < m_latitude - 1; ++i)
		{
			for(auto j = 0; j < m_longitude; ++j)
			{
				const auto index = i * yOffset + j + 1;

				auto tris0_0 = index;
				auto tris0_1 = index + yOffset;
				auto tris0_2 = index + xOffset;

				auto tris1_0 = index + xOffset;
				auto tris1_1 = index + xOffset + yOffset;
				auto tris1_2 = index + yOffset;

				if(j == m_longitude - 1)
				{
					tris0_2 -= m_longitude;
					tris1_0 -= m_longitude;
					tris1_1 -= m_longitude;
				}

				m_indices.push_back(tris0_0);
				m_indices.push_back(tris0_2);
				m_indices.push_back(tris0_1);

				m_indices.push_back(tris1_0);
				m_indices.push_back(tris1_1);
				m_indices.push_back(tris1_2);
			}
		}

		// Bottom row sectors only contain triangles	
		for(auto i = 0; i < m_longitude; ++i)
		{
			if(i == m_longitude - 1)
			{
				m_indices.push_back(indexMax);
				m_indices.push_back(indexMax - i - 2);
				m_indices.push_back(indexMax - i - 1);
			}
			else
			{
				m_indices.push_back(indexMax);
				m_indices.push_back(indexMax - i - 2);
				m_indices.push_back(indexMax - i - 1);
			}	
		}
	}
}