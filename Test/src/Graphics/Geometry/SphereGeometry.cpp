#include "catch2/catch.hpp"

#include <ec3/Application.h>
#include <ec3/Window/Window.h>
#include <ec3/Graphics/Geometry/SphereGeometry.h>

#include <stdexcept>

TEST_CASE("SphereGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);

    SECTION("default values")
    {
        ec::SphereGeometry sphere;
        CHECK(sphere.getRadius() == Approx(0.5));
        CHECK(sphere.getLatitude() == 20);
        CHECK(sphere.getLongitude() == 20);
        CHECK(sphere.getEbo() != 0);
        CHECK(sphere.getVao() != 0);
        CHECK(sphere.getVbo() != 0);
    }
    SECTION("constructor positive")
    {
        {
            ec::SphereGeometry sphere(0.01f, 31, 17);
            CHECK(sphere.getRadius() == Approx(0.01));
            CHECK(sphere.getLatitude() == 31);
            CHECK(sphere.getLongitude() == 17);
        }
        {
            ec::SphereGeometry sphere(2.0f, 2, 15);
            CHECK(sphere.getRadius() == Approx(2.0));
            CHECK(sphere.getLatitude() == 2);
            CHECK(sphere.getLongitude() == 15);
        }
        {
            ec::SphereGeometry sphere(13.0f, 72, 3);
            CHECK(sphere.getRadius() == Approx(13.0f));
            CHECK(sphere.getLatitude() == 72);
            CHECK(sphere.getLongitude() == 3);
        }
    }
    SECTION("constructor negative")
    {
        CHECK_THROWS_AS(ec::SphereGeometry(0.0f, 10, 15), std::domain_error);
        CHECK_THROWS_AS(ec::SphereGeometry(2.0f, 1, 15), std::domain_error);
        CHECK_THROWS_AS(ec::SphereGeometry(12.0f, 10, 2), std::domain_error);

        CHECK_THROWS_AS(ec::SphereGeometry(-4.0f, 0, 2), std::domain_error);
        CHECK_THROWS_AS(ec::SphereGeometry(1.0f, 10, 0), std::domain_error);

        CHECK_THROWS_AS(ec::SphereGeometry(1.0f, -1, 5), std::domain_error);
        CHECK_THROWS_AS(ec::SphereGeometry(1.0f, 10, -1), std::domain_error);
    }
    SECTION("resize positive")
    {
        ec::SphereGeometry sphere;
        sphere.resize(2.5f, 40, 3);
        CHECK(sphere.getRadius() == Approx(2.5));
        CHECK(sphere.getLatitude() == 40);
        CHECK(sphere.getLongitude() == 3);

        sphere.resize(43.0f, 2, 17);
        CHECK(sphere.getRadius() == Approx(43.0));
        CHECK(sphere.getLatitude() == 2);
        CHECK(sphere.getLongitude() == 17);

        sphere.resize(0.8f);
        CHECK(sphere.getRadius() == Approx(0.8));
        CHECK(sphere.getLatitude() == 2);
        CHECK(sphere.getLongitude() == 17);

        // TODO: check for memory leak when resizing -> ogl buffer still the same?
    }
    SECTION("resize negative")
    {
        ec::SphereGeometry sphere(2.7f, 14, 28);

        CHECK_THROWS_AS(sphere.resize(0.0f, 6, 9), std::domain_error);
        CHECK_THROWS_AS(sphere.resize(3.1f, 1, 9), std::domain_error);
        CHECK_THROWS_AS(sphere.resize(8.0f, 6, 2), std::domain_error);

        CHECK(sphere.getRadius() == Approx(2.7));
        CHECK(sphere.getLatitude() == 14);
        CHECK(sphere.getLongitude() == 28);
    }
}