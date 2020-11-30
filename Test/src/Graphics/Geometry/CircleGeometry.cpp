#include "catch2/catch.hpp"

#include <EC3D/Core/Application.h>
#include <EC3D/Window/Window.h>
#include <EC3D/Graphics/Geometry/CircleGeometry.h>

#include <stdexcept>

TEST_CASE("CircleGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);

    SECTION("default values")
    {
        ec::CircleGeometry circle;
        const Approx radius(0.5);
        CHECK(circle.getRadius() == radius);
        CHECK(circle.getEbo() != 0);
        CHECK(circle.getVao() != 0);
        CHECK(circle.getVbo() != 0);
        CHECK(circle.getSectionCount() == 20);
    }
    SECTION("constructor positive")
    {
        {
            ec::CircleGeometry circle(2.0, 10);
            CHECK(circle.getRadius() == Approx(2.0));
            CHECK(circle.getSectionCount() == 10);
        }
        {
            ec::CircleGeometry circle(0.1, 50);
            CHECK(circle.getRadius() == Approx(0.1));
            CHECK(circle.getSectionCount() == 50);
        }
        {
            ec::CircleGeometry circle(24.9, 3);
            CHECK(circle.getRadius() == Approx(24.9));
            CHECK(circle.getSectionCount() == 3);
        }
    }
    SECTION("constructor negative")
    {
        CHECK_THROWS_AS(ec::CircleGeometry(-4.4, 20), std::domain_error);
        CHECK_THROWS_AS(ec::CircleGeometry(2.0, 2), std::domain_error);
        CHECK_THROWS_AS(ec::CircleGeometry(-0.1, -5), std::domain_error);
    }
    SECTION("init positive")
    {
        ec::CircleGeometry circle;
        circle.init(1.0f, 20);
        CHECK(circle.getRadius() == Approx(1.0f));
        CHECK(circle.getSectionCount() == 20);
    }
    SECTION("init negative")
    {
        ec::CircleGeometry circle(15.0, 30);
        CHECK_THROWS_AS(circle.init(-1.0, 20), std::domain_error);
        CHECK_THROWS_AS(circle.init(1.0, -20), std::domain_error);
        CHECK(circle.getRadius() == Approx(15.0));
        CHECK(circle.getSectionCount() == 30);
    }
}
