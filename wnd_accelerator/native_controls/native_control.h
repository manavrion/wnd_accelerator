#pragma once
#include "../afx.h"
#include "../frame.h"
#include <list>

namespace wnd_accelerator {

    class NativeControl : public Frame {
    public:
        NativeControl();
        NativeControl(const NativeControl& abstructNativeControl) = delete;
        NativeControl(NativeControl&& abstructNativeControl) = delete;

        // Build real frame
        virtual void BuildImpl() = 0;
        // Apply resize and reposition
        virtual void UpdateImpl() = 0;
        // Some painting operations of this object
        virtual void Paint() = 0;

    protected:
        virtual void Init(NativeControl* parent) {}
        // static
		friend LRESULT CALLBACK windowProcMapper(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

        virtual LRESULT WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

    protected:

        // OS_WIN
        HWND hWindow = 0;

    public:
        virtual ~NativeControl();

    };

}