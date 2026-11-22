#pragma once

#include "bc/engine/graphics/renderer.hpp"
#include "bc/engine/platform/window.hpp"

namespace bc::engine
{
    struct context
    {
        platform::window& window;
        graphics::renderer& renderer;
    };
}