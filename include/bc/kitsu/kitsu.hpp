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
        void initialize() override
        {
            logger_.indent();
            logger_.debug("Initialized Kitsu.");
            // show window
            // glViewport(0, 0, width, height);
        }

        void update() override
        {
            logger_.debug("Updated Kitsu");
        }

        void render() override
        {
            logger_.debug("Rendered Kitsu.");
        }

        void shutdown() override
        {
            // hide window

            logger_.debug("Shutdown Kitsu.");
            logger_.unindent();
        }

    private:
        log::logger<log::console_sink<log::color_formatter>> logger_{log::console_logger("Kitsu")};
    };
}