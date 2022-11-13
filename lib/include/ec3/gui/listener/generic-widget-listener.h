#pragma once
#include "Agui/WidgetListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle events by
	 * widgets.
	 */
	class GenericWidgetListener : public agui::WidgetListener
	{
	public:
		using ChildAdded_Callback = std::function<void(agui::Widget* source, agui::Widget* widget)>;
		using ChildRemoved_Callback = std::function<void(agui::Widget* source, agui::Widget* widget)>;
		using FontChanged_Callback = std::function<void(agui::Widget* source, const agui::Font* font)>;
		using TextChanged_Callback = std::function<void(agui::Widget* source, const std::string& text)>;
		using EnabledChanged_Callback = std::function<void(agui::Widget* source, bool enabled)>;
		using VisibilityChanged_Callback = std::function<void(agui::Widget* source, bool visible)>;
		using LocationChanged_Callback = std::function<void(agui::Widget* source, const agui::Point& position)>;
		using Death_Callback = std::function<void(agui::Widget* source)>;
		using SizeChanged_Callback = std::function<void(agui::Widget* source, const agui::Dimension& size)>;
		using MinSizeChanged_Callback = std::function<void(agui::Widget* source, const agui::Dimension& size)>;
		using MaxSizeChanged_Callback = std::function<void(agui::Widget* source, const agui::Dimension& size)>;
		using ParentSizeChanged_Callback = std::function<void(agui::Widget* source, const agui::Dimension& size)>;

		void setChildAddedCallback(const ChildAdded_Callback& callback);
		void setChildRemovedCallback(const ChildRemoved_Callback& callback);
		void setFontChangedCallback(const FontChanged_Callback& callback);
		void setTextChangedCallback(const TextChanged_Callback& callback);
		void setEnabledChangedCallback(const EnabledChanged_Callback& callback);
		void setVisibilityChangedCallback(const VisibilityChanged_Callback& callback);
		void setLocationChangedCallback(const LocationChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);
		void setSizeChangedCallback(const SizeChanged_Callback& callback);
		void setMinSizeChangedCallback(const MinSizeChanged_Callback& callback);
		void setMaxSizeChangedCallback(const MaxSizeChanged_Callback& callback);
		void setParentSizeChangedCallback(const ParentSizeChanged_Callback& callback);

		explicit GenericWidgetListener();
		~GenericWidgetListener();

		void childAdded(agui::Widget* source, agui::Widget* widget) override;
		void childRemoved(agui::Widget* source, agui::Widget* widget) override;
		void fontChanged(agui::Widget* source, const agui::Font* font) override;
		void textChanged(agui::Widget* source, const std::string& text) override;
		void enabledChanged(agui::Widget* source, bool enabled) override;
		void visibilityChanged(agui::Widget* source, bool visible) override;
		void locationChanged(agui::Widget* source, const agui::Point& position) override;
		void death(agui::Widget* source) override;
		void sizeChanged(agui::Widget* source, const agui::Dimension& size) override;
		void minSizeChanged(agui::Widget* source, const agui::Dimension& size) override;
		void maxSizeChanged(agui::Widget* source, const agui::Dimension& size) override;
		void parentSizeChanged(agui::Widget* source, const agui::Dimension& size) override;

	private:
		ChildAdded_Callback m_childAddedCb;
		ChildRemoved_Callback m_childRemovedCb;
		FontChanged_Callback m_fontChangedCb;
		TextChanged_Callback m_textChangedCb;
		EnabledChanged_Callback m_enabledChangedCb;
		VisibilityChanged_Callback m_visibilityChangedCb;
		LocationChanged_Callback m_locationChangedCb;
		Death_Callback m_deathCb;
		SizeChanged_Callback m_sizeChangedCb;
		MinSizeChanged_Callback m_minSizeChangedCb;
		MaxSizeChanged_Callback m_maxSizeChangedCb;
		ParentSizeChanged_Callback m_parentSizeChangedCb;
	};
}