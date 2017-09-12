#pragma once
#include "../afx.h"

namespace wnd_accelerator {

    class KeyEvent {
    public:
        enum class EventType {
            keyPressed,
            keyReleased,
            keyTyped
        };
        int  keyCode;
        EventType type;
    };

}