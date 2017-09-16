#pragma once
#include "../afx.h"

namespace wnd_accelerator {

    struct Event {
        enum class Type {
            mouse,
            key,

            mouseClick,
            mouseMove,

            leftMouseButtonPress,
            middleMouseButtonPress,
            rightMouseButtonPress,

            leftMouseButtonRelease,
            middleMouseButtonRelease,
            rightMouseButtonRelease,

            // TODO
            mouseEnter,
            mouseExit,
            mouseDrag,
            mouseWheel,
                        
            keyType,
            keyPress,
            keyRelease
        };
        Type type;
        bool altDown;
        bool controlDown;
        bool shiftDown;
        bool leftMouseButtonDown;
        bool middleMouseButtonDown;
        bool rightMouseButtonDown;
    };

}