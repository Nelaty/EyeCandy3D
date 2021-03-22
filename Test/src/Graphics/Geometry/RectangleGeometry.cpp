#include "ThirdParty/catch.hpp"

#include <EC3D/Application.h>
#include <EC3D/Window/Window.h>
#include <EC3D/Graphics/Geometry/RectangleGeometry.h>

#include <stdexcept>

TEST_CASE("RectangleGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);

    SECTION("default values")
    {
        ec::RectangleGeometry rectangle;
        CHECK(rectangle.getEbo() != 0);
        CHECK(rectangle.getVao() != 0);
        CHECK(rectangle.getVbo() != 0);
        CHECK(rectangle.getHeight() == Approx(1.0));
        CHECK(rectangle.getWidth() == Approx(1.0));
    }
    SECTION("constructor positive")
    {
        {
            ec::RectangleGeometry rectangle(0.1);
            CHECK(rectangle.getWidth() == Approx(0.1));
            CHECK(rectangle.getHeight() == Approx(0.1));
        }
        {
            ec::RectangleGeometry rectangle(2.0);
            CHECK(rectangle.getWidth() == Approx(2.0));
            CHECK(rectangle.getHeight() == Approx(2.0));
        }
        {
            ec::RectangleGeometry rectangle(0.01, 431.5);
            CHECK(rectangle.getWidth() == Approx(0.01));
            CHECK(rectangle.getHeight() == Approx(431.5));
        }
        {
            ec::RectangleGeometry rectangle(42.0, 12.3);
            CHECK(rectangle.getWidth() == Approx(42.0));
            CHECK(rectangle.getHeight() == Approx(12.3));
        }
    }
    SECTION("constructor negative")
    {
        CHECK_THROWS_AS(ec::RectangleGeometry(0.0),
                        std::invalid_argument);
        CHECK_THROWS_AS(ec::RectangleGeometry(-0.01),
                        std::invalid_argument);
        CHECK_THROWS_AS(ec::RectangleGeometry(-12.4),
                        std::invalid_argument);
        CHECK_THROWS_AS(ec::RectangleGeometry(0.0, 0.0),
                        std::invalid_argument);
        CHECK_THROWS_AS(ec::RectangleGeometry(0.0, 21.0),
                        std::invalid_argument);
        CHECK_THROWS_AS(ec::RectangleGeometry(-0.01, 0.01),
                        std::invalid_argument);
        CHECK_THROWS_AS(ec::RectangleGeometry(0.01, -0.01),
                        std::invalid_argument);
        CHECK_THROWS_AS(ec::RectangleGeometry(-0.01, -0.01),
                        std::invalid_argument);
        CHECK_THROWS_AS(ec::RectangleGeometry(-125.2, -104.5),
                        std::invalid_argument);
    }
    SECTION("init positive")
    {
        ec::RectangleGeometry geometry;
        geometry.init(1.0, 2.0);
        CHECK(geometry.getWidth() == Approx(1.0));
        CHECK(geometry.getHeight() == Approx(2.0));
        geometry.init(1.4, 9.2);
        CHECK(geometry.getWidth() == Approx(1.4));
        CHECK(geometry.getHeight() == Approx(9.2));
    }
    SECTION("init negative")
    {
        ec::RectangleGeometry geometry(1.9, 1.1);
        CHECK_THROWS_AS(geometry.init(1.0, 0.0),
            std::invalid_argument);
        CHECK_THROWS_AS(geometry.init(-1.0, 0.0),
                        std::invalid_argument);
        CHECK(geometry.getWidth() == Approx(1.9));
        CHECK(geometry.getHeight() == Approx(1.1));
    }
}