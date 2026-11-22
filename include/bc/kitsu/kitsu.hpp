#pragma once

#include "bc/engine/application.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"

namespace bc::kitsu
{
    class kitsu : public engine::application
    {
    public:
        void initialize(const engine::context& context) override
        {
            logger_.indent();
            logger_.debug("Initialized Kitsu.");

            context.renderer.clear_color({1.0f, 0.0f, 0.0f, 1.0f});
            // show window
        }

        void update(const engine::context& context) override
        {
            logger_.debug("Updated Kitsu");
        }

        void render(const engine::context& context) override
        {
            logger_.debug("Rendered Kitsu.");
        }

        void shutdown(const engine::context& context) override
        {
            // hide window

            logger_.debug("Shutdown Kitsu.");
            logger_.unindent();
        }

    private:
        log::logger<log::console_sink<log::color_formatter>> logger_{log::console_logger("Kitsu")};
    };
}