#include "ThirdParty/catch.hpp"
#include <VectorApprox.h>

#include <EC3D/Application.h>
#include <EC3D/Window/Window.h>
#include <EC3D/Graphics/Geometry/LineGeometry.h>

#include <glm/glm.hpp>

#include <stdexcept>

TEST_CASE("LineGeometry")
{
    ec::Application app;
    ec::Window* window = app.createWindow<ec::Window>(100, 100, "test", "test");
    REQUIRE(window != nullptr);

    SECTION("default values")
    {
        ec::LineGeometry line(glm::vec3(0.0), glm::vec3(1.0));
        CHECK(line.getVbo() != 0);
        CHECK(line.getVao() != 0);
        CHECK(line.getEbo() != 0);
    }
    SECTION("constructor positive")
    {
        {
            ec::LineGeometry line(glm::vec3(1.0), glm::vec3(-1.0));
            CHECK(test::approx(line.getStart(), glm::vec3(1.0)));
            CHECK(test::approx(line.getEnd(), glm::vec3(-1.0)));
        }
        {
            ec::LineGeometry line(glm::vec3(0.0), glm::vec3(4.2));
            CHECK(test::approx(line.getStart(), glm::vec3(0.0)));
            CHECK(test::approx(line.getEnd(), glm::vec3(4.2)));
        }
        {
            ec::LineGeometry line(glm::vec3(-6.1), glm::vec3(0.0));
            CHECK(test::approx(line.getStart(), glm::vec3(-6.1)));
            CHECK(test::approx(line.getEnd(), glm::vec3(0.0)));
        }
        {
            ec::LineGeometry line(glm::vec3(0.0, 1.0, -5.2),
                glm::vec3(4.2, 2.5, 90.3));
            CHECK(test::approx(line.getStart(), glm::vec3(0.0, 1.0, -5.2)));
            CHECK(test::approx(line.getEnd(), glm::vec3(4.2, 2.5, 90.3)));
        }
    }
    SECTION("constructor negative")
    {
        CHECK_THROWS_AS(
            ec::LineGeometry(glm::vec3(0.0), glm::vec3(0.0)),
            std::invalid_argument);
        CHECK_THROWS_AS(
            ec::LineGeometry(glm::vec3(15.0), glm::vec3(15.0)),
            std::invalid_argument);
        CHECK_THROWS_AS(
            ec::LineGeometry(glm::vec3(-6.0), glm::vec3(-6.0)),
            std::invalid_argument);
        CHECK_THROWS_AS(
            ec::LineGeometry(glm::vec3(-2.0, 1.8, 21.9),
                glm::vec3(-2.0, 1.8, 21.9)),
            std::invalid_argument);
    }
}