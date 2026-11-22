#pragma once

#include "bc/engine/application.hpp"
#include "bc/engine/graphics/renderer.hpp"
#include "bc/engine/platform/platform.hpp"
#include "bc/engine/platform/window.hpp"
#include "bc/experimental/attributes.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"

namespace bc::engine
{
    class engine : public experimental::non_copyable, public experimental::non_movable
    {
    public:
        struct create_info
        {
            platform::window::create_info& window_info;
            graphics::renderer::create_info& renderer_info;
        };

        // ---

        explicit engine(const create_info& info) :
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
                update(application);
                render(application);
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

        void update(application& application)
        {
            platform_.poll_events();

            application.update(context_);
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

        log::logger<log::console_sink<log::color_formatter>> logger_;
        
        platform::platform platform_;
        platform::window window_;
        graphics::renderer renderer_;

        context context_;
    };
}