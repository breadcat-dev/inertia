#pragma once

#include <queue>

#include "bc/engine/application.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"
#include "bc/time/types.hpp"
#include "bc/time/utility.hpp"

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
        }

        void update(const engine::context& context, time::steady_duration delta_time) override
        {
            (void)context;

            if(frametimes_.size() > 100)
                frametimes_.pop();
            frametimes_.push(delta_time);

            logger_.debug("Updated Kitsu");
        }

        void render(const engine::context& context) override
        {
            (void)context;

            logger_.debug("Rendered Kitsu.");
        }

        void shutdown(const engine::context& context) override
        {
            (void)context;

            time::nanoseconds total{};
            usize count{};
            while(!frametimes_.empty())
            {
                total += frametimes_.front();
                ++count;
                frametimes_.pop();
            }

            time::nanoseconds average_frametime = total / count;
            usize average_framerate = time::to_count(time::to_nanoseconds(time::seconds{1})) / time::to_count(average_frametime);
            logger_.debug("Average FPS: <{}>.", average_framerate);

            logger_.debug("Shutdown Kitsu.");
            logger_.unindent();
        }

    private:
        log::logger<log::console_sink<log::color_formatter>> logger_{log::console_logger("Kitsu")};
    
        std::queue<time::nanoseconds> frametimes_;
    };
}