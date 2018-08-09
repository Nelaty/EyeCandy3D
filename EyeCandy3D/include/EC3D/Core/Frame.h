#pragma once

#include <vector>

namespace ec
{
	class Camera;

	class Frame
	{
	public:
		explicit Frame();
		~Frame();

		void AddCamera(Camera* camera);
		bool RemoveCamera(Camera* camera);

		void Clear();

		const std::vector<Camera*> GetCameras() const;

	private:
		std::vector<Camera*> m_cameras;
	};
}