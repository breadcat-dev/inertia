#pragma once

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "bc/core/exceptions.hpp"
#include "bc/experimental/geometry/extent.hpp"
#include "bc/experimental/color.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"

namespace bc::engine::graphics
{
    struct renderer_create_info
    {
        
    };

    // ---

    class renderer
    {
    public:
        explicit constexpr renderer(const renderer_create_info& info, experimental::geometry::extent2d framebuffer_extent) :
            logger_{log::console_logger("Renderer")}
        {
            logger_.info("Initializing renderer..");
            logger_.indent();

            if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                logger_.success("Initialized GLAD.");
            else
                throw runtime_exception("Failed to initialize GLAD.");

            glEnable(GL_DEPTH_TEST);
            logger_.debug("Enabled depth testing.");

            glViewport(0, 0, framebuffer_extent.width, framebuffer_extent.height);
            logger_.debug("Set viewport size to <{}x{}>", framebuffer_extent.width, framebuffer_extent.height);

            logger_.unindent();
            logger_.success("Initialized renderer.");
        }

        void clear_color(const experimental::color& color) noexcept
        {
            glClearColor(color.red, color.green, color.blue, color.alpha);
        }

        void clear() const noexcept
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

    private:
        log::logger<log::console_sink<log::color_formatter>> logger_;
    };
}