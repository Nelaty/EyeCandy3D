#pragma once

enum class OpenGlCullingMode : int
{
	front,
	back,
	none
};

enum class OpenGlPrimitiveMode : int
{
	wireframe,
	points,
	tris
};

enum class OpenGlRenderingProperty : int
{
	blend
};

enum class OpenGlDrawableProperty : int
{

};

template<class PropertyType>
class OpenGlProperty
{
public:
	explicit OpenGlProperty(PropertyType property);
	~OpenGlProperty();

	bool operator<(PropertyType rhs) const;
	bool operator<=(PropertyType rhs) const;
	bool operator==(PropertyType rhs) const;
	bool operator>(PropertyType rhs) const;
	bool operator>=(PropertyType rhs) const;

	void enable();
	void disable();

	PropertyType getProperty() const;
	void setProperty(PropertyType property);

private:
	bool m_enabled{false};

	PropertyType m_property;
};

template<class PropertyType>
bool OpenGlProperty<PropertyType>::operator<=(PropertyType rhs) const
{
	return m_property <= rhs;
}

template<class PropertyType>
bool OpenGlProperty<PropertyType>::operator>=(PropertyType rhs) const
{
	return m_property >= rhs;
}

template<class PropertyType>
void OpenGlProperty<PropertyType>::setProperty(PropertyType property)
{
	m_property = property;
}

template<class PropertyType>
PropertyType OpenGlProperty<PropertyType>::getProperty() const
{
	return m_property;
}

template<class PropertyType>
void OpenGlProperty<PropertyType>::disable()
{
	glDisable(m_property);
}

template<class PropertyType>
void OpenGlProperty<PropertyType>::enable()
{
	glEnable(m_property);
}

template<class PropertyType>
bool OpenGlProperty<PropertyType>::operator>(PropertyType rhs) const
{
	return m_property > rhs.m_property;
}

template<class PropertyType>
bool OpenGlProperty<PropertyType>::operator==(PropertyType rhs) const
{
	return m_property == rhs.m_property;
}

template<class PropertyType>
bool OpenGlProperty<PropertyType>::operator<(PropertyType rhs) const
{
	return m_property < rhs.m_property;
}

template<class PropertyType>
OpenGlProperty<PropertyType>::~OpenGlProperty()
{
}

template<class PropertyType>
OpenGlProperty<PropertyType>::OpenGlProperty(PropertyType property)
	: m_property(property)
{
}
