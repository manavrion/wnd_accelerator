#include "../afx.h"

namespace wnd_accelerator {

    class MouseEvent {
    public:
        enum class EventType {
            mouseClick,
            mousePress,
            mouseRelease,
            mouseEnter,
            mouseExit,
            mouseMove,
            mouseDrag,
            mouseWheel
        };
        enum class MouseButton {
            middle,
            left,
            right
        };
        int x;
        int y;
        int xAbs;
        int yAbs;
        EventType type;
        MouseButton button;

        bool isCtrlPressed;
        bool controlDown;
        bool leftButtonDown;
        bool midButtonDown;
        bool rightButtonDown;
        bool shiftDown;
    };

}