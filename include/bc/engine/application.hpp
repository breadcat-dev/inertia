#pragma once

#include "bc/engine/context.hpp"

namespace bc::engine
{
    class application
    {
    public:
        virtual ~application() = default;

        virtual void initialize(const context& context) = 0;
        virtual void update(const context& context) = 0;
        virtual void render(const context& context) = 0;
        virtual void shutdown(const context& context) = 0;
    };
}