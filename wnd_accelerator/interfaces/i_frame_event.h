#pragma once
#include "afx.h"
#include "../event_system/event.h"
#include "../event_system/key_event.h"
#include "../event_system/mouse_event.h"

#include <functional>
#include <list>

namespace wnd_accelerator {

    class Frame;

    class IFrameEvent {
    public:
        using KeyEventFunction = std::function<void(Frame*, KeyEvent*)>;
        using MouseEventFunction = std::function<void(Frame*, MouseEvent*)>;
        using EmptyEventFunction = std::function<void()>;

        virtual Frame* AddMouseClickListener(MouseEventFunction func) = 0;
        virtual Frame* AddMouseMoveListener(MouseEventFunction func) = 0;

        virtual Frame* AddLeftMouseButtonPressListener(MouseEventFunction func) = 0;
        virtual Frame* AddMiddleMouseButtonPressListener(MouseEventFunction func) = 0;
        virtual Frame* AddRightMouseButtonPressListener(MouseEventFunction func) = 0;

        virtual Frame* AddLeftMouseButtonReleaseListener(MouseEventFunction func) = 0;
        virtual Frame* AddMiddleMouseButtonReleaseListener(MouseEventFunction func) = 0;
        virtual Frame* AddRightMouseButtonReleaseListener(MouseEventFunction func) = 0;

        // TODO
        virtual Frame* AddMouseEnterListener(MouseEventFunction func) = 0;
        virtual Frame* AddMouseExitListener(MouseEventFunction func) = 0;
        virtual Frame* AddMouseWheelMoveListener(MouseEventFunction func) = 0;
        virtual Frame* AddMouseDragListener(MouseEventFunction func) = 0;

        virtual Frame* AddKeyTypeListener(KeyEventFunction func) = 0;
        virtual Frame* AddKeyPressListener(KeyEventFunction func) = 0;
        virtual Frame* AddKeyReleaseListener(KeyEventFunction func) = 0;


        // Aliases
        virtual Frame* AddMouseClickListener(EmptyEventFunction func) = 0;
        virtual Frame* AddMouseMoveListener(EmptyEventFunction func) = 0;

        virtual Frame* AddLeftMouseButtonPressListener(EmptyEventFunction func) = 0;
        virtual Frame* AddMiddleMouseButtonPressListener(EmptyEventFunction func) = 0;
        virtual Frame* AddRightMouseButtonPressListener(EmptyEventFunction func) = 0;

        virtual Frame* AddLeftMouseButtonReleaseListener(EmptyEventFunction func) = 0;
        virtual Frame* AddMiddleMouseButtonReleaseListener(EmptyEventFunction func) = 0;
        virtual Frame* AddRightMouseButtonReleaseListener(EmptyEventFunction func) = 0;

        // TODO
        virtual Frame* AddMouseEnterListener(EmptyEventFunction func) = 0;
        virtual Frame* AddMouseExitListener(EmptyEventFunction func) = 0;
        virtual Frame* AddMouseWheelMoveListener(EmptyEventFunction func) = 0;
        virtual Frame* AddMouseDragListener(EmptyEventFunction func) = 0;

        virtual Frame* AddKeyTypeListener(EmptyEventFunction func) = 0;
        virtual Frame* AddKeyPressListener(EmptyEventFunction func) = 0;
        virtual Frame* AddKeyReleaseListener(EmptyEventFunction func) = 0;



        virtual void ClearMouseClickListeners() = 0;
        virtual void ClearMouseMoveListeners() = 0;

        virtual void ClearLeftMouseButtonPressListeners() = 0;
        virtual void ClearMiddleMouseButtonPressListeners() = 0;
        virtual void ClearRightMouseButtonPressListeners() = 0;

        virtual void ClearLeftMouseButtonReleaseListeners() = 0;
        virtual void ClearMiddleMouseButtonReleaseListeners() = 0;
        virtual void ClearRightMouseButtonReleaseListeners() = 0;

        // TODO
        virtual void ClearMouseEnterListeners() = 0;
        virtual void ClearMouseExitListeners() = 0;
        virtual void ClearMouseWheelMoveListeners() = 0;
        virtual void ClearMouseDragListeners() = 0;

        virtual void ClearKeyTypeListeners() = 0;
        virtual void ClearKeyPressListeners() = 0;
        virtual void ClearKeyReleaseListeners() = 0;

        virtual void ClearAddListeners() = 0;

        virtual void NotifyKeyListeners(KeyEvent *keyEvent) = 0;
        virtual void NotifyMouseListeners(MouseEvent *mouseEvent) = 0;
    };

}