#include "../afx.h"
#include "mouse_event.h"

namespace wnd_accelerator {

    class MouseListener {
    public:
        virtual void MouseClicked(const MouseEvent& mouseEvent) {}

        virtual void MousePressed(const MouseEvent& mouseEvent) {}

        virtual void MouseReleased(const MouseEvent& mouseEvent) {}

        virtual void MouseEntered(const MouseEvent& mouseEvent) {}

        virtual void MouseExited(const MouseEvent& mouseEvent) {}

        virtual void MouseWheelMoved(const MouseEvent& mouseEvent) {}

        virtual void MouseDragged(const MouseEvent& mouseEvent) {}

        virtual void MouseMoved(const MouseEvent& mouseEvent) {}
    };

}