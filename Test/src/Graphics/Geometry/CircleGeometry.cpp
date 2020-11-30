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
        ec::CircleGeometry geometry;
        const Approx radius(1.0);
        CHECK(geometry.getRadius() == radius);
        CHECK(geometry.getEbo() != 0);
        CHECK(geometry.getVao() != 0);
        CHECK(geometry.getVbo() != 0);
        CHECK(geometry.getSectionCount() == 20);
    }
    SECTION("constructor positive")
    {
        {
            ec::CircleGeometry geometry(2.0, 10);
            CHECK(geometry.getRadius() == Approx(2.0));
            CHECK(geometry.getSectionCount() == 10);
        }
        {
            ec::CircleGeometry geometry(0.1, 50);
            CHECK(geometry.getRadius() == Approx(0.1));
            CHECK(geometry.getSectionCount() == 50);
        }
        {
            ec::CircleGeometry geometry(24.9, 3);
            CHECK(geometry.getRadius() == Approx(24.9));
            CHECK(geometry.getSectionCount() == 3);
        }
    }
    SECTION("constructor negative")
    {
        auto negative_0_1 = [](){
            ec::CircleGeometry geometry(-4.4, 20);
        };
        CHECK_THROWS_AS(negative_0_1(), std::out_of_range);

        auto negative_1_0 = [](){
            ec::CircleGeometry geometry(2.0, 2);
        };
        CHECK_THROWS_AS(negative_1_0(), std::out_of_range);

        auto negative_1_1 = [](){
            ec::CircleGeometry geometry(-0.1, -5);
        };
        CHECK_THROWS_AS(negative_1_1(), std::out_of_range);
    }
    SECTION("initialization after construction")
    {
        ec::CircleGeometry geometry;
    }
}
