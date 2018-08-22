#include "EC3D/GUI/Theme.h"

#include "EC3D/Core/Drawable.h"
#include "EC3D/Core/RectangleMesh.h"
#include "EC3D/Core/Material.h"
#include "EC3D/Core/Shader/Shader.h"

#include <utility>

namespace ec_gui
{
	Theme::Theme(ec::Shader* shader)
		: m_guiShader{shader}
	{
		m_radioButtonOff = nullptr;
		m_radioButtonOn = nullptr;

		m_checkboxOff = nullptr;
		m_checkboxOn = nullptr;

		m_widgetGeometry = std::make_unique<ec::RectangleMesh>(1.0f);
	}

	Theme::~Theme()
	= default;

	void Theme::addNewMaterial(const std::string& key, const std::string& texturePath)
	{
		using Pair_Type = std::pair<std::string, Material_Ptr>;

		auto material = std::make_unique<ec::Material>();
		material->addDiffuseTextureFromPath(texturePath.c_str());
		m_materials.insert(Pair_Type(key, std::move(material)));
	}

	Theme::Drawable_Ptr Theme::createDrawable(const std::string& materialKey)
	{
		auto drawable = std::make_unique<ec::Drawable>();
		auto* material = m_materials[materialKey].get();
		if(material == nullptr)
		{
			printf("THEME: Material \"%s\" does not exist!", materialKey.c_str());
		}
		drawable->init(m_widgetGeometry.get(), material, m_guiShader);
		return std::move(drawable);
	}
}