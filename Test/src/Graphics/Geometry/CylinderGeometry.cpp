#include "catch2/catch.hpp"

#include <EC3D/Core/Application.h>
#include <EC3D/Window/Window.h>
#include <EC3D/Graphics/Geometry/CylinderGeometry.h>

#include <stdexcept>

TEST_CASE("CylinderGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);

    SECTION("default values")
    {

    }
    SECTION("constructor positive")
    {

    }
    SECTION("constructor negative")
    {

    }
}