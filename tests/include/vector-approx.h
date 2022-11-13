#pragma once

#include <glm/glm.hpp>

namespace test
{
    bool approx(const glm::vec2& a, const glm::vec2& b);
    bool approx(const glm::vec3& a, const glm::vec3& b);
    bool approx(const glm::vec4& a, const glm::vec4& b);
}