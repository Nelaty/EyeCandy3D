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

	void Frame::AddCamera(Camera* camera)
	{
		m_cameras.push_back(camera);
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