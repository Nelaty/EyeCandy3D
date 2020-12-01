#include "EC3D/Frame.h"
#include "EC3D/Graphics/Camera.h"

#include <algorithm>

namespace ec
{
	Frame::Frame()
	= default;

	Frame::~Frame()
	= default;

	void Frame::addCameraBack(Camera* camera)
	{
		m_cameras.push_back(camera);
	}

	void Frame::addCameraFront(Camera* camera)
	{
		m_cameras.insert(m_cameras.begin(), camera);
	}

	void Frame::addCamera(Camera* camera, unsigned int priority)
	{
		auto insertionPosition = m_cameras.begin();
		if(priority < m_cameras.size())
		{
			insertionPosition += priority;
		}
		else if(!m_cameras.empty())
		{
			insertionPosition += m_cameras.size() - 1;
		}
		
		m_cameras.insert(insertionPosition, camera);
	}


	bool Frame::addCameraBefore(Camera* camera, Camera* nextCamera)
	{
		const auto foundCamera = std::find(m_cameras.begin(),
										   m_cameras.end(),
										   nextCamera);

		if(foundCamera == m_cameras.end()) return false;

		m_cameras.insert(foundCamera, camera);
		return true;
	}

	bool Frame::addCameraAfter(Camera* camera, Camera* prevCamera)
	{
		const auto foundCamera = std::find(m_cameras.begin(),
										   m_cameras.end(),
										   prevCamera);

		if(foundCamera == m_cameras.end()) return false;

		m_cameras.insert(foundCamera + 1, camera);
		return true;
	}

	bool Frame::removeCamera(Camera* camera)
	{
		const auto removedCamera = std::remove(m_cameras.begin(),
											   m_cameras.end(),
											   camera);

		if(removedCamera != m_cameras.end())
        {
		    m_cameras.erase(removedCamera);
		    return true;
		}
		return false;
	}

	void Frame::clear()
	{
		m_cameras.clear();
	}

	std::vector<Camera*>& Frame::getCameras()
	{
		return m_cameras;
	}

	const std::vector<Camera*>& Frame::getCameras() const
	{
		return m_cameras;
	}
}