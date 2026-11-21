#pragma once

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
            /*glViewport(0, 0, width, height);
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                logger_.error("GLAD initialization failed.");
                return;
            }    */
        }

        void update() override
        {
            /*while(!glfwWindowShouldClose(window_))
            {
                glfwSwapBuffers(window_);
                glfwPollEvents();    
            }*/
        }

        void render() override
        {

        }

        void shutdown() override
        {

        }

    private:
        log::logger<log::console_sink<log::color_formatter>> logger_{log::console_logger("Kitsu")};
    };
}