#include "ec3/Gui/Listener/GenericHScrollBarListener.h"

namespace ec
{
	GenericHScrollBarListener::GenericHScrollBarListener()
		: m_valueChangedCb(nullptr),
		m_minValueChangedCb(nullptr),
		m_maxValueChangedCb(nullptr),
		m_arrowWidthChangedCb(nullptr),
		m_largeAmountChangedCb(nullptr),
		m_leftAmountChangedCb(nullptr),
		m_rightAmountChangedCb(nullptr),
		m_minThumbWidthChangedCb(nullptr),
		m_deathCallback(nullptr)
	{
	}

	GenericHScrollBarListener::~GenericHScrollBarListener()
	= default;

	void GenericHScrollBarListener::setValueChangedCallback(const ValueChanged_Callback& callback)
	{
		m_valueChangedCb = callback;
	}

	void GenericHScrollBarListener::setMinValueChangedCallback(const MinValueChanged_Callback& callback)
	{
		m_minValueChangedCb = callback;
	}

	void GenericHScrollBarListener::setMaxValueChangedCallback(const MaxValueChanged_Callback& callback)
	{
		m_maxValueChangedCb = callback;
	}

	void GenericHScrollBarListener::setArrowWidthChangedCallback(const ArrowWidthChanged_Callback& callback)
	{
		m_arrowWidthChangedCb = callback;
	}

	void GenericHScrollBarListener::setLargeAmountChangedCallback(const LargeAmountChanged_Callback& callback)
	{
		m_largeAmountChangedCb = callback;
	}

	void GenericHScrollBarListener::setLeftAmountChangedCallback(const LeftAmountChanged_Callback& callback)
	{
		m_leftAmountChangedCb = callback;
	}

	void GenericHScrollBarListener::setRightAmountChangedCallback(const RightAmountChanged_Callback& callback)
	{
		m_rightAmountChangedCb = callback;
	}

	void GenericHScrollBarListener::setMinThumbWidthChangedCallback(const MinThumbWidthChanged_Callback& callback)
	{
		m_minThumbWidthChangedCb = callback;
	}

	void GenericHScrollBarListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCallback = callback;
	}

	void GenericHScrollBarListener::valueChanged(agui::HScrollBar* source,
												 const int val)
	{
		if(m_valueChangedCb)
		{
			m_valueChangedCb(source, val);
		}
	}

	void GenericHScrollBarListener::minValueChanged(agui::HScrollBar* source,
													const int val)
	{
		if(m_minValueChangedCb)
		{
			m_minValueChangedCb(source, val);
		}
	}

	void GenericHScrollBarListener::maxValueChanged(agui::HScrollBar* source,
													const int val)
	{
		if(m_maxValueChangedCb)
		{
			m_maxValueChangedCb(source, val);
		}
	}

	void GenericHScrollBarListener::arrowWidthChanged(agui::HScrollBar* source,
													  const int val)
	{
		if(m_arrowWidthChangedCb)
		{
			m_arrowWidthChangedCb(source, val);
		}
	}

	void GenericHScrollBarListener::largeAmountChanged(agui::HScrollBar* source, 
													   const int val)
	{
		if(m_largeAmountChangedCb)
		{
			m_largeAmountChangedCb(source, val);
		}
	}

	void GenericHScrollBarListener::leftAmountChanged(agui::HScrollBar* source,
													  const int val)
	{
		if(m_leftAmountChangedCb)
		{
			m_leftAmountChangedCb(source, val);
		}
	}

	void GenericHScrollBarListener::rightAmountChanged(agui::HScrollBar* source, 
													   const int val)
	{
		if(m_rightAmountChangedCb)
		{
			m_rightAmountChangedCb(source, val);
		}
	}

	void GenericHScrollBarListener::minThumbWidthChanged(agui::HScrollBar* source,
														 const int val)
	{
		if(m_minThumbWidthChangedCb)
		{
			m_minThumbWidthChangedCb(source, val);
		}
	}

	void GenericHScrollBarListener::death(agui::HScrollBar* source)
	{
		if(m_deathCallback)
		{
			m_deathCallback(source);
		}
	}
}
