#pragma once

#include <GLFW/glfw3.h>
#include <algorithm>
#include <stdexcept>
#include <vector>

#include "bc/core/verification.hpp"
#include "bc/engine/platform/window.hpp"
#include "bc/experimental/attributes.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"

namespace bc::engine::platform
{
    class platform : public experimental::noncopyable, public experimental::nonmovable
    {
    public:
        platform() :
            logger_{log::console_logger("Platform")}
        {
            if(!glfwInit())
                throw std::runtime_error("GLFW initialization failed.");
            else
                logger_.success("Initialized GLFW.");
        }

        ~platform()
        {
            for(GLFWwindow* handle : handles_)
            {
                glfwDestroyWindow(handle);
                logger_.debug("Destroying GLFW window handle: {}", static_cast<void*>(handle));
            }

            glfwTerminate();
            logger_.success("Destroyed GLFW windows.");
        }

        window create_window(const window_create_info& info)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            int width = static_cast<int>(info.width);
            int height = static_cast<int>(info.height);

            GLFWwindow* handle = glfwCreateWindow(width, height, info.title.data(), nullptr, nullptr);
            if(!handle)
                throw std::runtime_error("GLFW window initialization failed.");
            
            glfwMakeContextCurrent(handle);

            handles_.push_back(handle);
            return window{handle};
        }

        void destroy_window(window& window)
        {
            std::vector<GLFWwindow*>::iterator iterator = std::find(handles_.begin(), handles_.end(), window.handle_);
            verify(iterator != handles_.end(), "Unknown window.");

            glfwDestroyWindow(*iterator);
            handles_.erase(iterator);
            window.handle_ = nullptr;
        }

    private:
        log::logger<log::console_sink<log::color_formatter>> logger_;

        std::vector<GLFWwindow*> handles_;
    };
}