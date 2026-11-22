#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <algorithm>
#include <vector>

#include "bc/core/exceptions.hpp"
#include "bc/core/verification.hpp"
#include "bc/core/casts.hpp"
#include "bc/engine/platform/window.hpp"
#include "bc/experimental/attributes.hpp"
#include "bc/binary/flagwise.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"

namespace bc::engine::platform
{
    class platform : public experimental::non_copyable, public experimental::non_movable
    {
    public:
        platform() :
            logger_{log::console_logger("Platform")}
        {
            logger_.info("Initializing platform..");
            logger_.indent();

            if(glfwInit())
                logger_.success("Initialized GLFW.");
            else
                throw runtime_exception("Failed to initialize GLFW.");

            logger_.unindent();
            logger_.success("Initialized platform.");
        }

        ~platform()
        {
            logger_.info("Shutting down platform..");
            logger_.indent();

            for(GLFWwindow* handle : handles_)
            {
                logger_.warning("Destroying GLFW window: <{}>..", void_cast(handle));
                glfwDestroyWindow(handle);
            }

            glfwTerminate();
            logger_.success("Shutdown GLFW.");

            logger_.unindent();
            logger_.success("Shutdown platform.");
        }

        window create_window(const window::create_info& info)
        {
            logger_.info("Creating window..");
            logger_.indent();

            // ---

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // ---

            bool decorated{binary::test_flag(info.flags, window::flag::decorated)};
            bool resizable{binary::test_flag(info.flags, window::flag::resizable)};

            glfwWindowHint(GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

            logger_.debug("Decorated: <{}>.", decorated);
            logger_.debug("Resizable: <{}>.", resizable);

            // ---

            int width = static_cast<int>(info.extent.width);
            int height = static_cast<int>(info.extent.height);

            GLFWwindow* handle = glfwCreateWindow(width, height, info.title.data(), nullptr, nullptr);
            if(!handle)
                throw runtime_exception("Failed to create GLFW window.");
            logger_.debug("Created GLFW window ({}x{}): <{}>.", width, height, void_cast(handle));

            // ---

            void* last{glfwGetCurrentContext()};
            glfwMakeContextCurrent(handle);
            logger_.debug("Changed context from <{}> to <{}>.", last, void_cast(handle));

            // ---

            handles_.push_back(handle);
            logger_.unindent();
            logger_.success("Created window.");
            return window{handle};
        }

        void destroy_window(window& window)
        {
            logger_.info("Destroying window..");
            logger_.indent();

            std::vector<GLFWwindow*>::iterator iterator = std::find(handles_.begin(), handles_.end(), window.handle_);
            verify(iterator != handles_.end(), "Failed to destroy: unknown window.");

            glfwDestroyWindow(*iterator);
            logger_.debug("Destroyed GLFW window: <{}>.", void_cast(*iterator));
            handles_.erase(iterator);
            window.handle_ = nullptr;

            logger_.unindent();
            logger_.success("Destroyed window.");
        }

        void poll_events()
        {
            glfwPollEvents();
        }

    private:
        log::logger<log::console_sink<log::color_formatter>> logger_;

        std::vector<GLFWwindow*> handles_;
    };
}