#include "catch2/catch.hpp"

TEST_CASE("CylinderGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);
}