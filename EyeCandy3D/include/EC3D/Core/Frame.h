#pragma once
#include "FrameSlot.h"

#include <memory>
#include <vector>

namespace ec
{
	struct InputEvent;

	class IFrameLayout;
	class Window;

	/** \brief Defines which cameras are used for rendering
	 * and which area they occupy on a window.
	 */
	class Frame
	{
	public:
		using FrameLayout_Ptr = std::shared_ptr<IFrameLayout>;
		
		explicit Frame(Window* window);
		~Frame();

		/** \brief Inform the focused frame slot about new events. */
		void inform(const InputEvent& event);

		/** \brief Register a given frame slot. */
		void addFrameSlot(const FrameSlot& frameSlot);
		/** \brief Remove the first frame slot with a given
		 * camera.
		 * \return True if the frame slot exists, false otherwise. */
		bool removeFrameSlot(Camera* camera);
		/** \brief Remove the frame slot at a given index.
		 * \return True if the frame slot exists, false otherwise. */
		bool removeFrameSlot(int frameSlotIndex);

		/** \brief Set the frame layout, which automatically 
		 * formats position and size of new frame slots. */
		void setFrameLayout(const FrameLayout_Ptr& layout);
		/** \brief Stop using layouts. */
		void removeLayout();

		/** \brief Get all currently registered frame slots. */
		const std::vector<FrameSlot>& getFrameSlots() const;

	private:
		/** \brief Reorganize all registered frame slots by using the
		 * current layout. */
		void applyLayout();

		int m_focusedSlot{-1};

		Window* m_window;

		FrameLayout_Ptr m_frameLayout;
		std::vector<FrameSlot> m_frameSlots;
	};
}