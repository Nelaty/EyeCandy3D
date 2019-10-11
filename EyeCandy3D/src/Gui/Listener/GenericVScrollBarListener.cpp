#include "EC3D/Gui/Listener/GenericVScrollBarListener.h"

namespace ec
{
	GenericVScrollBarListener::GenericVScrollBarListener()
		: m_valueChangedCb(nullptr),
		m_minValueChangedCb(nullptr),
		m_maxValueChangedCb(nullptr),
		m_arrowHeightChangedCb(nullptr),
		m_largeAmountChangedCb(nullptr),
		m_topAmountChangedCb(nullptr),
		m_bottomAmountChangedCb(nullptr),
		m_minThumbHeightChangedCb(nullptr),
		m_deathCallback(nullptr)
	{
	}

	GenericVScrollBarListener::~GenericVScrollBarListener()
	= default;

	void GenericVScrollBarListener::setValueChangedCallback(const ValueChanged_Callback& callback)
	{
		m_valueChangedCb = callback;
	}

	void GenericVScrollBarListener::setMinValueChangedCallback(const MinValueChanged_Callback& callback)
	{
		m_minValueChangedCb = callback;
	}

	void GenericVScrollBarListener::setMaxValueChangedCallback(const MaxValueChanged_Callback& callback)
	{
		m_maxValueChangedCb = callback;
	}

	void GenericVScrollBarListener::setArrowHeightChangedCallback(const ArrowHeightChanged_Callback& callback)
	{
		m_arrowHeightChangedCb = callback;
	}

	void GenericVScrollBarListener::setLargeAmountChangedCallback(const LargeAmountChanged_Callback& callback)
	{
		m_largeAmountChangedCb = callback;
	}

	void GenericVScrollBarListener::setTopAmountChangedCallback(const TopAmountChanged_Callback& callback)
	{
		m_topAmountChangedCb = callback;
	}

	void GenericVScrollBarListener::setBottomAmountChangedCallback(const BottomAmountChanged_Callback& callback)
	{
		m_bottomAmountChangedCb = callback;
	}

	void GenericVScrollBarListener::setMinThumbHeightChangedCallback(const MinThumbHeightChanged_Callback& callback)
	{
		m_minThumbHeightChangedCb = callback;
	}

	void GenericVScrollBarListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCallback = callback;
	}

	void GenericVScrollBarListener::valueChanged(agui::VScrollBar* source, 
												 const int val)
	{
		if(m_valueChangedCb)
		{
			m_valueChangedCb(source, val);
		}
	}

	void GenericVScrollBarListener::minValueChanged(agui::VScrollBar* source,
													const int val)
	{
		if(m_minValueChangedCb)
		{
			m_minValueChangedCb(source, val);
		}
	}

	void GenericVScrollBarListener::maxValueChanged(agui::VScrollBar* source, 
													const int val)
	{
		if(m_maxValueChangedCb)
		{
			m_maxValueChangedCb(source, val);
		}
	}

	void GenericVScrollBarListener::arrowHeightChanged(agui::VScrollBar* source, 
													   const int val)
	{
		if(m_arrowHeightChangedCb)
		{
			m_arrowHeightChangedCb(source, val);
		}
	}

	void GenericVScrollBarListener::largeAmountChanged(agui::VScrollBar* source,
													   const int val)
	{
		if(m_largeAmountChangedCb)
		{
			m_largeAmountChangedCb(source, val);
		}
	}

	void GenericVScrollBarListener::topAmountChanged(agui::VScrollBar* source,
													 const int val)
	{
		if(m_topAmountChangedCb)
		{
			m_topAmountChangedCb(source, val);
		}
	}

	void GenericVScrollBarListener::bottomAmountChanged(agui::VScrollBar* source, 
														const int val)
	{
		if(m_bottomAmountChangedCb)
		{
			m_bottomAmountChangedCb(source, val);
		}
	}

	void GenericVScrollBarListener::minThumbHeightChanged(agui::VScrollBar* source, 
														  const int val)
	{
		if(m_minThumbHeightChangedCb)
		{
			m_minThumbHeightChangedCb(source, val);
		}
	}

	void GenericVScrollBarListener::death(agui::VScrollBar* source)
	{
		if(m_deathCallback)
		{
			m_deathCallback(source);
		}
	}
}
