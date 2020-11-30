#include "catch2/catch.hpp"

#include <EC3D/Window/Window.h>

TEST_CASE("CubeGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);
}