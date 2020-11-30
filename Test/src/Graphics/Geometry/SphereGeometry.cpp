#include "catch2/catch.hpp"

TEST_CASE("SphereGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);
}