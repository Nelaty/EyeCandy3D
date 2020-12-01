#include "catch2/catch.hpp"

#include <EC3D/Application.h>
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
        ec::CylinderGeometry cylinder;
        CHECK(cylinder.getRadius() == Approx(0.5));
        CHECK(cylinder.getHeight() == Approx(1.0));
        CHECK(cylinder.getLatitude() == 2);
        CHECK(cylinder.getLongitude() == 20);
        CHECK(cylinder.getEbo() != 0);
        CHECK(cylinder.getVao() != 0);
        CHECK(cylinder.getVbo() != 0);
    }
    SECTION("constructor positive")
    {
        {
            ec::CylinderGeometry cylinder(0.001f, 0.001f, 2, 3);
            CHECK(cylinder.getRadius() == Approx(0.001f));
            CHECK(cylinder.getHeight() == Approx(0.001f));
            CHECK(cylinder.getLatitude() == 2);
            CHECK(cylinder.getLongitude() == 3);
        }
        {
            ec::CylinderGeometry cylinder(41.3f, 61.1f, 45, 23);
            CHECK(cylinder.getRadius() == Approx(41.3f));
            CHECK(cylinder.getHeight() == Approx(61.1f));
            CHECK(cylinder.getLatitude() == 45);
            CHECK(cylinder.getLongitude() == 23);
        }
        {
            CHECK_NOTHROW(ec::CylinderGeometry(0.001f, 14.0f, 20, 12));
            CHECK_NOTHROW(ec::CylinderGeometry(5.0f, 0.001f, 3, 52));
            CHECK_NOTHROW(ec::CylinderGeometry(52.0f, 12.2f, 2, 23));
            CHECK_NOTHROW(ec::CylinderGeometry(27.0f, 27.9f, 7, 3));
        }
    }
    SECTION("constructor negative")
    {
        CHECK_THROWS_AS(ec::CylinderGeometry(0.0f, 0.0f, 1, 2), std::domain_error);
        CHECK_THROWS_AS(ec::CylinderGeometry(0.0f, 2.2f, 5, 9), std::domain_error);
        CHECK_THROWS_AS(ec::CylinderGeometry(12.2f, 0.0f, 7, 5), std::domain_error);
        CHECK_THROWS_AS(ec::CylinderGeometry(6.0f, 4.2f, 1, 5), std::domain_error);
        CHECK_THROWS_AS(ec::CylinderGeometry(2.1f, 1.9f, 8, 2), std::domain_error);
    }
}