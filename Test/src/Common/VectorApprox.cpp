#include "ThirdParty/catch.hpp"

#include <VectorApprox.h>

namespace test
{
    bool approx(const glm::vec2& a, const glm::vec2& b)
    {
        return a.x == Approx(b.x)
            && a.y == Approx(b.y);
    }

    bool approx(const glm::vec3& a, const glm::vec3& b)
    {
        return a.x == Approx(b.x)
            && a.y == Approx(b.y)
            && a.z == Approx(b.z);
    }

    bool approx(const glm::vec4& a, const glm::vec4& b)
    {
        return a.x == Approx(b.x)
            && a.y == Approx(b.y)
            && a.z == Approx(b.z)
            && a.w == Approx(b.w);
    }
}