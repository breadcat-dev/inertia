#include <cstdlib>

#include "bc/kitsu/kitsu.hpp"
#include "bc/log/logger.hpp"
#include "bc/engine/engine.hpp"

using namespace bc;

int main()
{
    log::logger logger{log::console_logger()};

    logger.separator(log::level::debug, "Kitsu");
    logger.debug("Made by breadcat <3");

    engine::engine engine{};
    kitsu::kitsu game{};

    logger.debug("Running game..");
    engine.run(game);

    logger.debug("Shutting down..");
    logger.separator(log::level::debug);
    return EXIT_SUCCESS;
}