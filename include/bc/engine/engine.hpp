#pragma once

#include <thread>

#include "bc/engine/application.hpp"
#include "bc/engine/graphics/renderer.hpp"
#include "bc/engine/platform/platform.hpp"
#include "bc/engine/platform/window.hpp"
#include "bc/experimental/attributes.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"
#include "bc/time/timer.hpp"
#include "bc/time/types.hpp"
#include "bc/time/utility.hpp"

namespace bc::engine
{
    class engine : public experimental::non_copyable, public experimental::non_movable
    {
    public:
        struct create_info
        {
            platform::window::create_info& window_info;
            graphics::renderer::create_info& renderer_info;

            usize max_framerate;
        };

        // ---

        explicit engine(const create_info& info) :
            target_frametime_{time::to_nanoseconds(time::seconds{1}) / info.max_framerate},
            logger_{log::console_logger("Engine")},
            platform_{},
            window_{platform_.create_window(info.window_info)},
            renderer_{info.renderer_info, window_.framebuffer_extent()},
            context_{window_, renderer_}    
        {
        }

        ~engine()
        {
            platform_.destroy_window(window_);
        }

        void run(application& application)
        {
            initialize(application);
            logger_.debug("Running..");

            while(!window_.should_close())
            {
                time::steady_duration delta_time{timer_.duration()};
                timer_.reset();

                update(application, delta_time);
                render(application);

                if(time::to_nanoseconds(delta_time) < target_frametime_)
                    std::this_thread::sleep_for(target_frametime_ - delta_time);
            }

            shutdown(application);
        }

    private:
        void initialize(application& application)
        {
            logger_.info("Initializing application..");
            application.initialize(context_);
            logger_.success("Initialized application.");

            window_.show();
        }

        void update(application& application, time::steady_duration delta_time)
        {
            platform_.poll_events();

            application.update(context_, delta_time);
        }

        void render(application& application)
        {
            renderer_.clear();

            application.render(context_);

            window_.swap_buffers();
        }

        void shutdown(application& application)
        {
            logger_.info("Shutting down application..");
            application.shutdown(context_);
            logger_.success("Shutdown application.");
        }  

        const time::nanoseconds target_frametime_;

        log::logger<log::console_sink<log::color_formatter>> logger_;
        time::timer timer_;

        platform::platform platform_;
        platform::window window_;
        graphics::renderer renderer_;

        context context_;
    };
}