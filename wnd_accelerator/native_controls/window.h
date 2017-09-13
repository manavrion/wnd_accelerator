#pragma once
#include "../afx.h"
#include "native_control.h"
#include "../event_system/event.h"
#include "../event_system/key_event.h"
#include "../event_system/mouse_event.h"

#include <functional>
#include <list>
#include <unordered_map>

namespace wnd_accelerator {

    class Window : public NativeControl {
    public:
        Window();
        virtual ~Window();

    protected:
        // OS_WIN
        virtual LRESULT WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) final;

    };

}
