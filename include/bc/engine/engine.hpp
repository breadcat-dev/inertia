#pragma once

#include "bc/engine/application.hpp"

namespace bc::engine
{
    class engine
    {
    public:
        void run(application& application)
        {
            application.initialize();
            application.update();
            application.render();
            application.shutdown();

            
        }

    private:
        
    };
}