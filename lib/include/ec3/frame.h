#pragma once
#include "ec3/common/common.h"

#include <vector>

namespace ec
{
	class Camera;

	/**
	 * \brief A Frame is a collection of cameras. The order in, which these
	 * cameras are stored, determines the order in which will be 
	 * rendered.
	 */
	class EC3D_DECLSPEC Frame
	{
	public:
		explicit Frame();
		~Frame();

		/** 
		 * \brief Add a given camera at the end (low priority camera).
		 * \param camera The camera to add.
		 */
		void addCameraBack(Camera* camera);
		/** 
		 * \brief Add a given camera at the front (high priority camera).
		 * \param camera The camera to add.
		 */
		void addCameraFront(Camera* camera);
		/** 
		 * \brief Add a given camera with a given priority. If there already.
		 * is a camera with the same priority registered, put the given. 
		 * camera before that camera.
		 * \param camera The camera to add.
		 * \param priority The priority of the camera.
		 */
		void addCamera(Camera* camera, unsigned int priority);
		/**
		 * \brief Add a given camera right before another given camera. 
		 * \details Camera doesn't get added if the given camera wasn't
		 * found.
		 * \param camera The camera to be added.
		 * \param nextCamera The camera before which the newly added
		 * camera should follow.
		 * \return True if nextCamera was found, false otherwise.
		 * */
		bool addCameraBefore(Camera* camera, Camera* nextCamera);
		/**
		* \brief Add a given camera right after another given camera.
		* \details Camera doesn't get added if the given camera wasn't
		* found.
		* \param camera The camera to be added.
		* \param prevCamera The camera after which the newly added.
		* camera should follow.
		* \return True if prevCamera was found, false otherwise.
		*/
		bool addCameraAfter(Camera* camera, Camera* prevCamera);

		/**
		 * \brief Remove a given camera from the frame.
		 * \param camera The camera to be removed.
		 * \return True if the given camera is registered, false otherwise.
		 */
		bool removeCamera(Camera* camera);

		/** 
		 * \brief Remove all registered cameras. 
		 */
		void clear();

		/** 
		 * \brief Get all registered cameras.
		 */
		std::vector<Camera*>& getCameras();
		/** 
		 * \brief Get all registered cameras.
		 */
		const std::vector<Camera*>& getCameras() const;

	private:
		std::vector<Camera*> m_cameras;
	};
}