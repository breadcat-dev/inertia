#pragma once

namespace bc::engine
{
    class application
    {
    public:
        virtual ~application() = default;

        virtual void initialize() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void shutdown() = 0;
    };
}