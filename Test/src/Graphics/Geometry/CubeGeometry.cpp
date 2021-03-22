#include "ThirdParty/catch.hpp"

#include <EC3D/Application.h>
#include <EC3D/Window/Window.h>
#include <EC3D/Graphics/Geometry/CubeGeometry.h>

#include <stdexcept>

TEST_CASE("CubeGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);

    SECTION("default values")
    {
        ec::CubeGeometry cube;
        CHECK(cube.getWidth() == Approx(1.0));
        CHECK(cube.getHeight() == Approx(1.0));
        CHECK(cube.getDepth() == Approx(1.0f));
        CHECK(cube.getEbo() != 0);
        CHECK(cube.getVao() != 0);
        CHECK(cube.getVbo() != 0);
    }
    SECTION("constructor positive")
    {
        {
            ec::CubeGeometry cube(2.5f);
            CHECK(cube.getWidth() == Approx(2.5));
            CHECK(cube.getHeight() == Approx(2.5));
            CHECK(cube.getDepth() == Approx(2.5));
        }
        {
            ec::CubeGeometry cube(1.7f, 9.2f, 12.2f);
            CHECK(cube.getWidth() == Approx(1.7f));
            CHECK(cube.getHeight() == Approx(9.2f));
            CHECK(cube.getDepth() == Approx(12.2f));
        }
    }
    SECTION("constructor negative")
    {
        CHECK_THROWS_AS(ec::CubeGeometry(0.0), std::invalid_argument);
        CHECK_THROWS_AS(ec::CubeGeometry(-0.01f), std::invalid_argument);
        CHECK_THROWS_AS(ec::CubeGeometry(-51.3f), std::invalid_argument);
        CHECK_THROWS_AS(ec::CubeGeometry(0.0f, 1.0, 1.0), std::invalid_argument);
        CHECK_THROWS_AS(ec::CubeGeometry(1.0f, 0.0, 1.0), std::invalid_argument);
        CHECK_THROWS_AS(ec::CubeGeometry(1.0f, 1.0, 0.0), std::invalid_argument);
        CHECK_THROWS_AS(ec::CubeGeometry(-0.01f, 1.0, 1.0), std::invalid_argument);
        CHECK_THROWS_AS(ec::CubeGeometry(1.0f, -1.0, 1.0), std::invalid_argument);
        CHECK_THROWS_AS(ec::CubeGeometry(1.0f, 1.0, -87.2), std::invalid_argument);
    }
}