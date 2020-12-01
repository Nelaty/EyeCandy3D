#include "catch2/catch.hpp"
#include <EC3D/Application.h>
#include "EC3D/Window/Window.h"

#include "EC3D/Graphics/Material/Material.h"
#include "EC3D/Graphics/Material/Texture.h"
#include "EC3D/Common/Config.h"
#include "TestConfig.h"

#include <string>
#include <filesystem>
#include <iostream>

TEST_CASE("Material: texture changes")
{
    // Create window, so a OpenGL context exists
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);
    REQUIRE(window->isInitialized());

    ec::Material material;

    ec::Texture texture1;
    texture1.textureFromFile(TestConfig::getTexturePath("white_512.png"), conf_shader::g_textureDiffuse);
    ec::Texture texture2;
    texture2.textureFromFile(TestConfig::getTexturePath("white_512.png"), conf_shader::g_textureDiffuse);
    ec::Texture texture3;
    texture3.textureFromFile(TestConfig::getTexturePath("white_512.png"), conf_shader::g_textureDiffuse);

    SECTION( "initial state" )
    {
        CHECK_FALSE(material.hasTexture());
        CHECK(material.getTextures().size() == 0);
        UNSCOPED_INFO("Textures size: " << material.getTextures().size());
        CHECK(material.getTexture(0) == nullptr);
        CHECK(material.getTexture(1) == nullptr);
    }
    SECTION("adding and removing textures")
    {
        // Add textures
        material.addTexture(texture1);
        CHECK(material.hasTexture());
        material.addTexture(texture2);
        material.addTexture(texture3);

        const auto& textures = material.getTextures();
        REQUIRE(textures.size() == 3);
        CHECK(textures[0] == texture1);
        CHECK(textures[1] == texture2);
        CHECK(textures[2] == texture3);

        CHECK(*material.getTexture(0) == texture1);
        CHECK(*material.getTexture(1) == texture2);
        CHECK(*material.getTexture(2) == texture3);

        CHECK(material.getTexture(3) == nullptr);

        // Remove textures
        ec::Texture unregisteredTexture;
        unregisteredTexture.textureFromFile(TestConfig::getTexturePath("white_512.png"), conf_shader::g_textureDiffuse);
        CHECK_FALSE(material.removeTexture(unregisteredTexture));
        CHECK(material.hasTexture());

        CHECK(material.removeTexture(texture2));
        CHECK(*material.getTexture(0) == texture1);
        CHECK(*material.getTexture(1) == texture3);
        CHECK(material.getTexture(2) == nullptr);
        CHECK(material.hasTexture());

        CHECK(material.removeTexture(texture1));
        CHECK(material.removeTexture(texture3));
        CHECK_FALSE(material.hasTexture());
        CHECK_FALSE(material.hasTexture());
        CHECK_FALSE(material.removeTexture(texture1));
    }
    SECTION("add texture from path")
    {
        CHECK_FALSE(material.hasTexture());
        material.addDiffuseTextureFromPath(TestConfig::getTexturePath("white_512.png"));
        CHECK(material.hasTexture());
        CHECK(material.getTextures().size() == 1);
        material.addDiffuseTextureFromPath(TestConfig::getTexturePath("white_512.png"));
        CHECK(material.getTextures().size() == 2);
        material.addDiffuseTextureFromPath(TestConfig::getTexturePath("white_512.png"));
        CHECK(material.getTextures().size() == 3);
    }
    SECTION("add texture from invalid path")
    {
        material.addDiffuseTextureFromPath("          ");
        CHECK_FALSE(material.hasTexture());
    }
}

TEST_CASE("Material: color manipulation functions")
{
    ec::Material material;
    SECTION("ambient")
    {
        glm::vec4 colorAmbient(0.3, 0.7, 1.0, 0.0);
        CHECK(material.getColorAmbient() == glm::vec4(0.0));
        material.setColorAmbient(colorAmbient);
        CHECK(material.getColorAmbient() == colorAmbient);
        material.setColorAmbient(colorAmbient.r, colorAmbient.g, colorAmbient.b, colorAmbient.a);
        CHECK(material.getColorAmbient() == colorAmbient);
    }
    SECTION("diffuse")
    {
        glm::vec4 colorDiffuse(-0.1, 2.0, 0.0, 0.4);
        CHECK(material.getColorDiffuse() == glm::vec4(0.0));
        material.setColorDiffuse(colorDiffuse);
        CHECK(material.getColorDiffuse() == colorDiffuse);
        material.setColorDiffuse(colorDiffuse.r, colorDiffuse.g, colorDiffuse.b, colorDiffuse.a);
        CHECK(material.getColorDiffuse() == colorDiffuse);
    }
    SECTION("specular");
    {
        glm::vec4 colorSpecular(5.0, 0.3, -10.0, 0.2);
        CHECK(material.getColorSpecular() == glm::vec4(0.0));
        material.setColorSpecular(colorSpecular);
        CHECK(material.getColorSpecular() == colorSpecular);
        material.setColorSpecular(colorSpecular.r, colorSpecular.g, colorSpecular.b, colorSpecular.a);
        CHECK(material.getColorSpecular() == colorSpecular);
    }
    SECTION("emission")
    {
        glm::vec4 colorEmission(0.2, 0.0, 1.0, 0.8);
        CHECK(material.getColorEmission() == glm::vec4(0.0));
        material.setColorEmission(colorEmission);
        CHECK(material.getColorEmission() == colorEmission);
        material.setColorEmission(colorEmission.r, colorEmission.g, colorEmission.b, colorEmission.a);
        CHECK(material.getColorEmission() == colorEmission);
    }
    SECTION("shininess")
    {
        CHECK(material.getShininess() == 0.0f);
        material.setShininess(1.0f);
        CHECK(material.getShininess() == 1.0f);
        material.setShininess(24.5f);
        CHECK(material.getShininess() == 24.5f);
        material.setShininess(0.0f);
        CHECK(material.getShininess() == 0.0f);
        material.setShininess(-5.5f);
        CHECK(material.getShininess() == -5.5f);
    }
}