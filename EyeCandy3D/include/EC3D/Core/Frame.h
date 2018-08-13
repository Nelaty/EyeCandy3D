#pragma once

#include <vector>

namespace ec
{
	class Camera;

	/**
	 * A Frame is a collection of cameras. The order in, which these
	 * cameras are stored, determines the order in which will be 
	 * rendered.
	 */
	class Frame
	{
	public:
		explicit Frame();
		~Frame();

		/** Add a given camera at the end (low priority camera) */
		void AddCameraBack(Camera* camera);
		/** Add a given camera at the front (high priority camera) */
		void AddCameraFront(Camera* camera);
		/** 
		 * Add a given camera with a given priority. If there already
		 * is a (multiple) camera[s] with the same priority registered,
		 * put the given camera before those.
		 */
		void AddCamera(Camera* camera, unsigned int priority);
		/**
		 * Add a given camera right before another given camera 
		 * \param camera The camera to be added.
		 * \param prevCamera The camera before which the newly added
		 * camera should follow.
		 * \return True if nextCamera was found, false otherwise.
		 * */
		bool AddCameraBefore(Camera* camera, Camera* nextCamera);
		/**
		* Add a given camera right after another given camera
		* \param camera The camera to be added.
		* \param prevCamera The camera after which the newly added
		* camera should follow.
		* \return True if prevCamera was found, false otherwise.
		*/
		bool AddCameraAfter(Camera* camera, Camera* prevCamera);

		/**
		 * Remove a given camera from the frame.
		 * \return True if the given camera is registered, false otherwise.
		 */
		bool RemoveCamera(Camera* camera);

		/** Remove all registered cameras. */
		void Clear();

		/** Get all registered cameras */
		const std::vector<Camera*> GetCameras() const;

	private:
		std::vector<Camera*> m_cameras;
	};
}