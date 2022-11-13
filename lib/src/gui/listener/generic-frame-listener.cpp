#include "ec3/Gui/Listener/GenericFrameListener.h"

namespace ec
{
	GenericFrameListener::GenericFrameListener()
		: m_deathCb(nullptr),
		m_contentChildAddedCb(nullptr),
		m_contentChildRemovedCb(nullptr),
		m_topMarginChangedCb(nullptr),
		m_bottomMarginChangedCb(nullptr),
		m_leftMarginChangedCb(nullptr),
		m_rightMarginChangedCb(nullptr),
		m_resizableChangedCb(nullptr),
		m_movableChangedCb(nullptr)
	{
	}

	GenericFrameListener::~GenericFrameListener()
	= default;

	void GenericFrameListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericFrameListener::setContentChildAddedCallback(const ContentChildAdded_Callback& callback)
	{
		m_contentChildAddedCb = callback;
	}

	void GenericFrameListener::setContentChildRemovedCallback(const ContentChildRemoved_Callback& callback)
	{
		m_contentChildRemovedCb = callback;
	}

	void GenericFrameListener::setTopMarginChangedCallback(const TopMarginChanged_Callback& callback)
	{
		m_topMarginChangedCb = callback;
	}

	void GenericFrameListener::setBottomMarginChangedCallback(const BottomMarginChanged_Callback& callback)
	{
		m_bottomMarginChangedCb = callback;
	}

	void GenericFrameListener::setLeftMarginChangedCallback(const LeftMarginChanged_Callback& callback)
	{
		m_leftMarginChangedCb = callback;
	}

	void GenericFrameListener::setRightMarginChangedCallback(const RightMarginChanged_Callback& callback)
	{
		m_rightMarginChangedCb = callback;
	}

	void GenericFrameListener::setResizableChangedCallback(const ResizableChanged_Callback& callback)
	{
		m_resizableChangedCb = callback;
	}

	void GenericFrameListener::setMovableChangedCallback(const MovableChanged_Callback& callback)
	{
		m_movableChangedCb = callback;
	}

	void GenericFrameListener::death(agui::Frame* frame)
	{
		if(m_deathCb)
		{
			m_deathCb(frame);
		}
	}

	void GenericFrameListener::contentChildAdded(agui::Frame* frame, 
												 agui::Widget* widget)
	{
		if(m_contentChildAddedCb)
		{
			m_contentChildAddedCb(frame, widget);
		}
	}

	void GenericFrameListener::contentChildRemoved(agui::Frame* frame, 
												   agui::Widget* widget)
	{
		if(m_contentChildRemovedCb)
		{
			m_contentChildRemovedCb(frame, widget);
		}
	}

	void GenericFrameListener::topMarginChanged(agui::Frame* frame,
												const int topMargin)
	{
		if(m_topMarginChangedCb)
		{
			m_topMarginChangedCb(frame, topMargin);
		}
	}

	void GenericFrameListener::bottomMarginChanged(agui::Frame* frame, 
												   const int bottomMargin)
	{
		if(m_bottomMarginChangedCb)
		{
			m_bottomMarginChangedCb(frame, bottomMargin);
		}
	}

	void GenericFrameListener::leftMarginChanged(agui::Frame* frame, 
												 const int leftMargin)
	{
		if(m_leftMarginChangedCb)
		{
			m_leftMarginChangedCb(frame, leftMargin);
		}
	}

	void GenericFrameListener::rightMarginChanged(agui::Frame* frame, 
												  const int rightMargin)
	{
		if(m_rightMarginChangedCb)
		{
			m_rightMarginChangedCb(frame, rightMargin);
		}
	}

	void GenericFrameListener::resizableChanged(agui::Frame* frame,
												const int val)
	{
		if(m_resizableChangedCb)
		{
			m_resizableChangedCb(frame, val);
		}
	}

	void GenericFrameListener::movableChanged(agui::Frame* frame,
											  const int val)
	{
		if(m_movableChangedCb)
		{
			m_movableChangedCb(frame, val);
		}
	}
}
