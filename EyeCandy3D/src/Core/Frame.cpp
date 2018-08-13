#include "EC3D/Core/Frame.h"
#include "EC3D/Core/Camera.h"

#include <algorithm>

namespace ec
{
	Frame::Frame()
	{
	}

	Frame::~Frame()
	{
	}

	void Frame::AddCameraBack(Camera* camera)
	{
		m_cameras.push_back(camera);
	}

	void Frame::AddCameraFront(Camera* camera)
	{
		m_cameras.insert(m_cameras.begin(), camera);
	}

	void Frame::AddCamera(Camera* camera, unsigned int priority)
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


	bool Frame::AddCameraBefore(Camera* camera, Camera* nextCamera)
	{
		auto foundCamera = std::find(m_cameras.begin(),
									 m_cameras.end(),
									 nextCamera);

		if(foundCamera == m_cameras.end()) return false;

		m_cameras.insert(foundCamera, camera);
		return true;
	}

	bool Frame::AddCameraAfter(Camera* camera, Camera* prevCamera)
	{
		auto foundCamera = std::find(m_cameras.begin(),
									 m_cameras.end(),
									 prevCamera);

		if(foundCamera == m_cameras.end()) return false;

		m_cameras.insert(foundCamera + 1, camera);
		return true;
	}

	bool Frame::RemoveCamera(Camera* camera)
	{
		auto removedCamera = std::remove(m_cameras.begin(),
										 m_cameras.end(),
										 camera);

		return removedCamera != m_cameras.end();
	}

	void Frame::Clear()
	{
		m_cameras.clear();
	}

	const std::vector<Camera*> Frame::GetCameras() const
	{
		return m_cameras;
	}
}