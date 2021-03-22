#include "EC3D/Graphics/Geometry/CylinderGeometry.h"

#include <cmath>
#include <stdexcept>

namespace ec
{
	CylinderGeometry::CylinderGeometry(const float radius,
	                                   const float height,
	                                   const int latitude,
	                                   const int longitude)
	{
		init(radius, height, latitude, longitude);
	}

	CylinderGeometry::~CylinderGeometry()
	= default;

	void CylinderGeometry::resize(const float radius, 
								  const float height,
								  const int latitude,
								  const int longitude)
	{
		init(radius, height, latitude, longitude);
	}

	void CylinderGeometry::init(const float radius, 
								const float height, 
								const int latitude, 
								const int longitude)
	{
	    if(radius <= 0.0f) throw std::invalid_argument("radius must be > 0!");
	    if(height <= 0.0f) throw std::invalid_argument("height must be > 0!");
	    if(latitude <= 1) throw std::invalid_argument("latitude must be > 1!");
	    if(longitude <= 2) throw std::invalid_argument("longitude must be > 2!");

		m_radius = radius;
		m_height = height;
		m_latitude = latitude;
		m_longitude = longitude;

		initVerticesAndTexCoords();
		initIndices();

		recalculateNormals();
		setupMesh();
	}

	void CylinderGeometry::initVerticesAndTexCoords()
	{
		auto& vertices = m_data.m_vertices;
		const auto numVertices = m_latitude * (m_longitude)+2;
		vertices.resize(numVertices);

		// Top and bottom vertices
		m_data.m_vertices[0].m_position = {0.0f, m_height / 2.0f, 0.0f};
		m_data.m_vertices[numVertices - 1].m_position = {0.0f, -m_height / 2.0f, 0.0f};

		const float yStart = m_height / 2.0f;
		const float yStep = m_height / static_cast<float>(m_latitude - 1);

		const auto latitudeSpacing = 1.0f / (m_latitude + 1.0f);
		const auto longitudeSpacing = 1.0f / (m_longitude);

		// x-z coordinates are the same for vertices in a vertical line
		std::vector<glm::vec3> positions(m_longitude);
		const float circleStep = 2.0f * float(M_PI) / float(m_longitude);
		for(auto i = 0; i < m_longitude; ++i)
		{
			positions[i].x = m_radius * cos(circleStep * i);
			positions[i].z = m_radius * sin(circleStep * i);
		}

		auto v = 1;
		for(auto lat = 0; lat < m_latitude; ++lat)
		{
			for(auto lon = 0; lon < m_longitude; ++lon)
			{
				vertices[v].m_texCoords = glm::vec2(lon * longitudeSpacing,
													1.0f - (lat + 1) * latitudeSpacing);
				vertices[v].m_position = glm::vec3(positions[lon].x,
												   yStart - lat * yStep,
												   positions[lon].z);
				++v;
			}
		}
	}

	void CylinderGeometry::initIndices()
	{
		auto& indices = m_data.m_indices;
		
		const auto vertexNum = m_data.m_vertices.size();
		const unsigned indexMax = unsigned(vertexNum - 1);
		indices.reserve(vertexNum * 3);

		// Top row sectors only contain triangles
		for(auto i = 0; i < m_longitude; ++i)
		{
			if(i == m_longitude - 1)
			{
				indices.push_back(0);
				indices.push_back(1);
				indices.push_back(i + 1);
			}
			else
			{
				indices.push_back(0);
				indices.push_back(i + 2);
				indices.push_back(i + 1);
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

				indices.push_back(tris0_0);
				indices.push_back(tris0_2);
				indices.push_back(tris0_1);

				indices.push_back(tris1_0);
				indices.push_back(tris1_1);
				indices.push_back(tris1_2);
			}
		}

		// Bottom row sectors only contain triangles	
		for(auto i = 0; i < m_longitude; ++i)
		{
			if(i == m_longitude - 1)
			{
				indices.push_back(indexMax);
				indices.push_back(indexMax - 1);
				indices.push_back(indexMax - i - 1);
			}
			else
			{
				indices.push_back(indexMax);
				indices.push_back(indexMax - i - 2);
				indices.push_back(indexMax - i - 1);
			}
		}
	}

    float CylinderGeometry::getRadius() const
    {
        return m_radius;
    }

    float CylinderGeometry::getHeight() const
    {
        return m_height;
    }

    int CylinderGeometry::getLatitude() const
    {
        return m_latitude;
    }

    int CylinderGeometry::getLongitude() const
    {
        return m_longitude;
    }
}
