#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "bc/engine/application.hpp"
#include "bc/log/formatter.hpp"
#include "bc/log/logger.hpp"
#include "bc/log/sink.hpp"

namespace bc::kitsu
{
    class kitsu : public engine::application
    {
    public:
        void initialize() override
        {
            logger_.debug("Initializing..");

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window_ = glfwCreateWindow(800, 600, "Kitsu", nullptr, nullptr);
            if(!window_)
            {
                logger_.error("GLFW initialization failed.");
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(window_);

            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                logger_.error("GLAD initialization failed.");
                return;
            }    

            glViewport(0, 0, 800, 600);
        }

        void update() override
        {
            logger_.debug("Updating..");

            while(!glfwWindowShouldClose(window_))
            {
                glfwSwapBuffers(window_);
                glfwPollEvents();    
            }
        }

        void render() override
        {
            logger_.debug("Rendering..");


        }

        void shutdown() override
        {
            logger_.debug("Shutting down..");
            
            glfwTerminate();
        }

    private:
        log::logger<log::console_sink<log::color_formatter>> logger_{log::console_logger("Kitsu")};
    
        GLFWwindow* window_;
    };
}