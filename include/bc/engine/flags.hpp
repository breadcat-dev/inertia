#pragma once

#include <concepts>

#include "bc/engine/platform/window.hpp"
#include "bc/engine/graphics/renderer.hpp"

namespace bc::engine
{
    template<typename T>
    concept flag = std::same_as<T, platform::window::flag>
                || std::same_as<T, graphics::renderer::flag>;

    template<flag T>
    [[nodiscard]]
    constexpr T operator|(T lhs, T rhs) noexcept
    {
        return set_flag(lhs, rhs);
    }
}