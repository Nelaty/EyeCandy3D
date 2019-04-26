#include "EC3D/Core/Frame.h"
#include "EC3D/Core/IFrameLayout.h"
#include "EC3D/Core/Input/InputEvent.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Window.h"

#include <algorithm>

namespace ec
{

	Frame::Frame(Window* window)
		: m_window(window)
	{
	}

	Frame::~Frame()
	{
	}

	void Frame::inform(const InputEvent& event)
	{
		if(event.m_type == InputType::mouse_button_pressed)
		{
			for(int i = 0; i < m_frameSlots.size(); ++i)
			{
				auto& mouseEvent = event.m_event.m_mouse;
				auto windowSize = m_window->getSize();
				auto pos = glm::vec2(mouseEvent.m_x / windowSize.x, 
									 mouseEvent.m_y / windowSize.y);
				
				if(m_frameSlots[i].contains(pos))
				{
					m_focusedSlot = i;
				}
			}
		}

		if(m_focusedSlot != -1)
		{
			auto scene = m_frameSlots[m_focusedSlot].getCamera()->getScene();
			scene->getEventProcessor().receiveEvent(event);
		}
	}

	void Frame::addFrameSlot(const FrameSlot& frameSlot)
	{
		m_frameSlots.emplace_back(frameSlot);

		applyLayout();
	}

	bool Frame::removeFrameSlot(Camera* camera)
	{
		auto foundItem = std::find_if(
			m_frameSlots.begin(),
			m_frameSlots.end(),
			[&](const FrameSlot& slot)
			{
				return slot.getCamera() == camera;
			});

		if(foundItem != m_frameSlots.end())
		{
			int index = foundItem - m_frameSlots.begin();
			if(index == m_focusedSlot)
			{
				m_focusedSlot = -1;
			}
			m_frameSlots.erase(foundItem);
			return true;
		}

		return false;
	}

	bool Frame::removeFrameSlot(int frameSlotIndex)
	{
		if(m_frameSlots.empty()
		   || frameSlotIndex < m_frameSlots.size())
		{
			return false;
		}

		if(frameSlotIndex == m_focusedSlot)
		{
			m_focusedSlot = -1;
		}
		m_frameSlots.erase(m_frameSlots.begin() + frameSlotIndex);
		return true;
	}

	void Frame::removeLayout()
	{
		m_frameLayout = nullptr;
	}

	void Frame::setFrameLayout(const FrameLayout_Ptr& layout)
	{
		m_frameLayout = layout;
	}

	const std::vector<ec::FrameSlot>& Frame::getFrameSlots() const
	{
		return m_frameSlots;
	}

	void Frame::applyLayout()
	{
		if(m_frameLayout)
		{
			m_frameLayout->applyLayout(m_frameSlots);
		}
	}
}