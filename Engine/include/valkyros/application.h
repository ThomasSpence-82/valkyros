#pragma once

#include "valkyros/core/window.h"

namespace Valkyros {

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        WindowPtr m_Window;
    };

}
