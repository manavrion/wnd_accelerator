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

        // Use Run() to display window on screen
        int Run();

        // You must use Update() to apply the size and position changes
        virtual void Update() final;

        // To apply graphical changes, you must use Repaint()
        virtual void Repaint() final;

    protected:
        // OS_WIN
        virtual LRESULT WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) final;

        virtual void InitPre() final;

        void DrawBuffer();

        void CreateBuffer();
        void DeleteBuffer();
        void ResizeBuffer();

    protected:
        Gdiplus::Bitmap* buffer;
        Gdiplus::Graphics* graphics;
    };

}
