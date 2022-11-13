#pragma once
#include "Agui/Widgets/Frame/FrameListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle events by Frame
	 * widgets.
	 */
	class GenericFrameListener : public agui::FrameListener
	{
	public:
		using Death_Callback = std::function<void(agui::Frame* frame)>;
		using ContentChildAdded_Callback = std::function<void(agui::Frame* frame, agui::Widget* widget)>;
		using ContentChildRemoved_Callback = std::function<void(agui::Frame* frame, agui::Widget* widget)>;
		using TopMarginChanged_Callback = std::function<void(agui::Frame* frame, int topMargin)>;
		using BottomMarginChanged_Callback = std::function<void(agui::Frame* frame, int bottomMargin)>;
		using LeftMarginChanged_Callback = std::function<void(agui::Frame* frame, int leftMargin)>;
		using RightMarginChanged_Callback = std::function<void(agui::Frame* frame, int rightMargin)>;
		using ResizableChanged_Callback = std::function<void(agui::Frame* frame, int val)>;
		using MovableChanged_Callback = std::function<void(agui::Frame* frame, int val)>;

		explicit GenericFrameListener();
		~GenericFrameListener();

		void setDeathCallback(const Death_Callback& callback);
		void setContentChildAddedCallback(const ContentChildAdded_Callback& callback);
		void setContentChildRemovedCallback(const ContentChildRemoved_Callback& callback);
		void setTopMarginChangedCallback(const TopMarginChanged_Callback& callback);
		void setBottomMarginChangedCallback(const BottomMarginChanged_Callback& callback);
		void setLeftMarginChangedCallback(const LeftMarginChanged_Callback& callback);
		void setRightMarginChangedCallback(const RightMarginChanged_Callback& callback);
		void setResizableChangedCallback(const ResizableChanged_Callback& callback);
		void setMovableChangedCallback(const MovableChanged_Callback& callback);

		void death(agui::Frame* frame) override;
		void contentChildAdded(agui::Frame* frame, agui::Widget* widget) override;
		void contentChildRemoved(agui::Frame* frame, agui::Widget* widget) override;
		void topMarginChanged(agui::Frame* frame, int topMargin) override;
		void bottomMarginChanged(agui::Frame* frame, int bottomMargin) override;
		void leftMarginChanged(agui::Frame* frame, int leftMargin) override;
		void rightMarginChanged(agui::Frame* frame, int rightMargin) override;
		void resizableChanged(agui::Frame* frame, int val) override;
		void movableChanged(agui::Frame* frame, int val) override;

	private:
		Death_Callback m_deathCb;
		ContentChildAdded_Callback m_contentChildAddedCb;
		ContentChildRemoved_Callback m_contentChildRemovedCb;
		TopMarginChanged_Callback m_topMarginChangedCb;
		BottomMarginChanged_Callback m_bottomMarginChangedCb;
		LeftMarginChanged_Callback m_leftMarginChangedCb;
		RightMarginChanged_Callback m_rightMarginChangedCb;
		ResizableChanged_Callback m_resizableChangedCb;
		MovableChanged_Callback m_movableChangedCb;
	};
}