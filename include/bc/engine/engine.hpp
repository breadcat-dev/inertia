#pragma once

#include "bc/engine/application.hpp"
#include "bc/engine/platform/platform.hpp"
#include "bc/engine/platform/window.hpp"
#include "bc/experimental/attributes.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/level.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"

namespace bc::engine
{
    struct engine_create_info
    {
        platform::window_create_info& window_info;
    };

    // ---

    class engine : public experimental::noncopyable, public experimental::nonmovable
    {
    public:
        explicit engine(const engine_create_info& info) :
            logger_{log::console_logger("Engine")},
            platform_{},
            window_{platform_.create_window(info.window_info)}
        {
        }

        ~engine()
        {
            platform_.destroy_window(window_);
        }

        void run(application& application)
        {
            initialize(application);
            logger_.separator(log::level::info, "Running");

            while(true)
            {
                break;
            }

            shutdown(application);
        }

    private:
        void initialize(application& application)
        {
            logger_.separator(log::level::success, "Initialization");
            //logger_.info("Initializing engine..");

            logger_.info("Initializing application..");
            application.initialize();

            logger_.success("Initialization complete.");
        }

        void update(application& application)
        {
            application.update();
        }

        void render(application& application)
        {
            application.render();
        }

        void shutdown(application& application)
        {
            logger_.separator(log::level::error, "Shutting down");
            logger_.info("Shutting down application..");

            application.shutdown();

            logger_.success("Shutdown complete.");
        }  

        log::logger<log::console_sink<log::color_formatter>> logger_;
        
        platform::platform platform_;
        platform::window window_;
    };
}