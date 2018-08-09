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
		using Drawable_TP = std::unique_ptr<ec::Drawable>;
		using Material_TP = std::unique_ptr<ec::Material>;

	public:
		explicit Theme(ec::Shader* shader);
		virtual ~Theme();

		/* Buttons */
		Drawable_TP m_radioButtonOn;
		Drawable_TP m_radioButtonOff;

		Drawable_TP m_checkboxOn;
		Drawable_TP m_checkboxOff;

	protected:
		void AddNewMaterial(const std::string& key, const std::string& texturePath);
		Drawable_TP CreateDrawable(const std::string& materialKey);

		std::map<std::string, Material_TP> m_materials;

	private:
		ec::Shader* m_guiShader;
		std::unique_ptr<ec::RectangleMesh> m_widgetGeometry;
	};
}