#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <string_view>

#include "bc/experimental/attributes.hpp"
#include "bc/experimental/geometry/extent.hpp"
#include "bc/core/types.hpp"
#include "bc/binary/bitwise.hpp"

namespace bc::engine::platform
{
    class window : public experimental::non_copyable
    {
    public:
        friend class platform;

        enum class flag : uint32
        {
            none = 0,
            decorated = binary::bit_mask<uint32>(0),
            resizable = binary::bit_mask<uint32>(1)
        };

        struct create_info
        {
            std::string_view title;
            experimental::geometry::extent2d extent;
            flag flags;
        };

        // ---

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

    private:
        constexpr explicit window(GLFWwindow* handle) :
            handle_{handle}
        {
        }

        GLFWwindow* handle_;
    };
}