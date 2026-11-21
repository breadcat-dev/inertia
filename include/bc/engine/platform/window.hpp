#pragma once

#include <GLFW/glfw3.h>
#include <string_view>

#include "bc/core/types.hpp"
#include "bc/experimental/attributes.hpp"

namespace bc::engine::platform
{
    struct window_create_info
    {
        std::string_view title;
        usize width;
        usize height;
    };

    // ---

    class window : public experimental::noncopyable
    {
    public:
        friend class platform;

    private:
        constexpr explicit window(GLFWwindow* handle) :
            handle_{handle}
        {
        }

        GLFWwindow* handle_;
    };
}