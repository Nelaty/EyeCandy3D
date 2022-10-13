#include "ec3/Gui/Listener/GenericWidgetListener.h"

namespace ec
{
	GenericWidgetListener::GenericWidgetListener()
		: m_childAddedCb(nullptr),
		m_childRemovedCb(nullptr),
		m_fontChangedCb(nullptr),
		m_textChangedCb(nullptr),
		m_enabledChangedCb(nullptr),
		m_visibilityChangedCb(nullptr),
		m_locationChangedCb(nullptr),
		m_deathCb(nullptr),
		m_sizeChangedCb(nullptr),
		m_minSizeChangedCb(nullptr),
		m_maxSizeChangedCb(nullptr),
		m_parentSizeChangedCb(nullptr)
	{
	}

	GenericWidgetListener::~GenericWidgetListener()
	= default;

	void GenericWidgetListener::setChildAddedCallback(const ChildAdded_Callback& callback)
	{
		m_childAddedCb = callback;
	}

	void GenericWidgetListener::setChildRemovedCallback(const ChildRemoved_Callback& callback)
	{
		m_childRemovedCb = callback;
	}

	void GenericWidgetListener::setFontChangedCallback(const FontChanged_Callback& callback)
	{
		m_fontChangedCb = callback;
	}

	void GenericWidgetListener::setTextChangedCallback(const TextChanged_Callback& callback)
	{
		m_textChangedCb = callback;
	}

	void GenericWidgetListener::setEnabledChangedCallback(const EnabledChanged_Callback& callback)
	{
		m_enabledChangedCb = callback;
	}

	void GenericWidgetListener::setVisibilityChangedCallback(const VisibilityChanged_Callback& callback)
	{
		m_visibilityChangedCb = callback;
	}

	void GenericWidgetListener::setLocationChangedCallback(const LocationChanged_Callback& callback)
	{
		m_locationChangedCb = callback;
	}

	void GenericWidgetListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericWidgetListener::setSizeChangedCallback(const SizeChanged_Callback& callback)
	{
		m_sizeChangedCb = callback;
	}

	void GenericWidgetListener::setMinSizeChangedCallback(const MinSizeChanged_Callback& callback)
	{
		m_minSizeChangedCb = callback;
	}

	void GenericWidgetListener::setMaxSizeChangedCallback(const MaxSizeChanged_Callback& callback)
	{
		m_maxSizeChangedCb = callback;
	}

	void GenericWidgetListener::setParentSizeChangedCallback(const ParentSizeChanged_Callback& callback)
	{
		m_parentSizeChangedCb = callback;
	}	

	void GenericWidgetListener::childAdded(agui::Widget* source,
										   agui::Widget* widget)
	{
		if(m_childAddedCb)
		{
			m_childAddedCb(source, widget);
		}
	}

	void GenericWidgetListener::childRemoved(agui::Widget* source,
											 agui::Widget* widget)
	{
		if(m_childRemovedCb)
		{
			m_childRemovedCb(source, widget);
		}
	}

	void GenericWidgetListener::fontChanged(agui::Widget* source, 
											const agui::Font* font)
	{
		if(m_fontChangedCb)
		{
			m_fontChangedCb(source, font);
		}
	}

	void GenericWidgetListener::textChanged(agui::Widget* source, 
											const std::string& text)
	{
		if(m_textChangedCb)
		{
			m_textChangedCb(source, text);
		}
	}

	void GenericWidgetListener::enabledChanged(agui::Widget* source, 
											   const bool enabled)
	{
		if(m_enabledChangedCb)
		{
			m_enabledChangedCb(source, enabled);
		}
	}

	void GenericWidgetListener::visibilityChanged(agui::Widget* source, 
												  const bool visible)
	{
		if(m_visibilityChangedCb)
		{
			m_visibilityChangedCb(source, visible);
		}
	}

	void GenericWidgetListener::locationChanged(agui::Widget* source, 
												const agui::Point& position)
	{
		if(m_locationChangedCb)
		{
			m_locationChangedCb(source, position);
		}
	}

	void GenericWidgetListener::death(agui::Widget* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}

	void GenericWidgetListener::sizeChanged(agui::Widget* source, 
											const agui::Dimension& size)
	{
		if(m_sizeChangedCb)
		{
			m_sizeChangedCb(source, size);
		}
	}

	void GenericWidgetListener::minSizeChanged(agui::Widget* source, 
											   const agui::Dimension& size)
	{
		if(m_minSizeChangedCb)
		{
			m_minSizeChangedCb(source, size);
		}
	}

	void GenericWidgetListener::maxSizeChanged(agui::Widget* source, 
											   const agui::Dimension& size)
	{
		if(m_maxSizeChangedCb)
		{
			m_maxSizeChangedCb(source, size);
		}
	}

	void GenericWidgetListener::parentSizeChanged(agui::Widget* source, 
												  const agui::Dimension& size)
	{
		if(m_parentSizeChangedCb)
		{
			m_parentSizeChangedCb(source, size);
		}
	}
}