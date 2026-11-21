#include <cstdlib>
#include <exception>

#include "bc/engine/platform/window.hpp"
#include "bc/kitsu/kitsu.hpp"
#include "bc/log/logger.hpp"
#include "bc/engine/engine.hpp"

using namespace bc;

int main()
{
    log::logger logger{log::console_logger()};
    logger.separator(log::level::debug, "Kitsu");
    logger.debug("Made by breadcat <3");

    engine::platform::window_create_info window_info
    {
        .title = "Kitsu",
        .width = 800,
        .height = 600
    };

    engine::engine_create_info engine_info
    {
        .window_info = window_info
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