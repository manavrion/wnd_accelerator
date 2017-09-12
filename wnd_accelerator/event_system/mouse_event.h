#include "../afx.h"

namespace wnd_accelerator {

    class MouseEvent {
    public:
        enum class EventType {
            mouseClicled,
            mousePressed,
            mouseReleased,
            mouseEntered,
            mouseExited,
            mouseMoved,
            mouseDragged,
            mouseWheel
        };
        int x;
        int y;
        int xParent;
        int yParent;
        int xAbs;
        int yAbs;
        EventType type;
    };

}