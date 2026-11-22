#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <string_view>

#include "bc/experimental/attributes.hpp"
#include "bc/experimental/geometry/extent.hpp"
#include "bc/core/types.hpp"

namespace bc::engine::platform
{
    struct window_create_info
    {
        std::string_view title;
        experimental::geometry::extent2d extent;
    };

    // ---

    class window : public experimental::non_copyable
    {
    public:
        void show() const noexcept
        {
            glfwShowWindow(handle_);
        }

        void hide() const noexcept
        {
            glfwHideWindow(handle_);
        }

        bool should_close() const noexcept
        {
            return glfwWindowShouldClose(handle_);
        }

        void close() const noexcept
        {
            glfwSetWindowShouldClose(handle_, 1);
        }

        experimental::geometry::extent2d framebuffer_extent() const noexcept
        {
            int width;
            int height;

            glfwGetFramebufferSize(handle_, &width, &height);

            return {static_cast<uint32>(width), static_cast<uint32>(height)};
        }

        void swap_buffers() noexcept
        {
            glfwSwapBuffers(handle_);
        }

        friend class platform;

    private:
        constexpr explicit window(GLFWwindow* handle) :
            handle_{handle}
        {
        }

        GLFWwindow* handle_;
    };
}