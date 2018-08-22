#pragma once

#include <memory>
#include <map>
#include <string>

namespace ec
{
	class Drawable;
	class RectangleMesh;
	class Material;
	class Shader;
}

/*
 * Contains a common visual style.
 */
namespace ec_gui
{
	class Theme
	{
	public:
		using Drawable_Ptr = std::unique_ptr<ec::Drawable>;
		using Material_Ptr = std::unique_ptr<ec::Material>;

		explicit Theme(ec::Shader* shader);
		virtual ~Theme();

		/* Buttons */
		Drawable_Ptr m_radioButtonOn;
		Drawable_Ptr m_radioButtonOff;

		Drawable_Ptr m_checkboxOn;
		Drawable_Ptr m_checkboxOff;

	protected:
		void addNewMaterial(const std::string& key, const std::string& texturePath);
		Drawable_Ptr createDrawable(const std::string& materialKey);

		std::map<std::string, Material_Ptr> m_materials;

	private:
		ec::Shader* m_guiShader;
		std::unique_ptr<ec::RectangleMesh> m_widgetGeometry;
	};
}