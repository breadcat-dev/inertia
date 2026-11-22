#include <cstdlib>
#include <exception>

#include "bc/engine/platform/window.hpp"
#include "bc/engine/graphics/renderer.hpp"
#include "bc/kitsu/kitsu.hpp"
#include "bc/log/logger.hpp"
#include "bc/engine/engine.hpp"

using namespace bc;

int main()
{
    log::logger logger{log::console_logger()};
    logger.separator(log::level::debug, "Kitsu");
    logger.debug("Made by breadcat <3");

    engine::platform::window::create_info window_info
    {
        .title = "Kitsu",
        .extent = {800, 600},
        .flags = engine::platform::window::flag::none
    };

    engine::graphics::renderer::create_info renderer_info
    {
        .flags = engine::graphics::renderer::flag::vsync
    };

    engine::engine::create_info engine_info
    {
        .window_info = window_info,
        .renderer_info = renderer_info
    };

    try
    {
        engine::engine engine{engine_info};
        kitsu::kitsu game{};

        engine.run(game);
    }
    catch(const std::exception& exception)
    {
        logger.separator(log::level::error);
        logger.error("A fatal error occured: {}", exception.what());
        logger.separator(log::level::error);
    }

    logger.separator(log::level::debug);
    return EXIT_SUCCESS;
}