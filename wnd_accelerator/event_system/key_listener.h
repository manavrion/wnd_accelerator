#pragma once
#include "../afx.h"
#include "key_event.h"

#include <list>

namespace wnd_accelerator {

    class KeyListener {
    public:
        virtual void KeyTyped(const KeyEvent& keyEvent) {}

        virtual void KeyPressed(const KeyEvent& keyEvent) {}

        virtual void KeyReleased(const KeyEvent& keyEvent) {}
    };

}