#pragma once
#include "../afx.h"
#include "event.h"

namespace wnd_accelerator {

    struct MouseEvent : public Event {
        int x = 0;
        int y = 0;
        // Its position in window
        int xAbs = 0;
        int yAbs = 0;
    };

}