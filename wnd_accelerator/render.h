#pragma once

namespace wnd_accelerator {

    class Render {
    public:
        Render();
        virtual void Paint(Frame*) = 0;
        virtual ~Render();
    };

}