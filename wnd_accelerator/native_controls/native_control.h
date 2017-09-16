#pragma once
#include "../afx.h"
#include "../frame.h"
#include "../gdi_render/gdi_control.h"

#include <list>
#include <utility>

namespace wnd_accelerator {

    class NativeControl : public GdiControl {
    public:
        NativeControl();
        virtual ~NativeControl();

    protected:
        // Build real frame
        virtual void BuildImpl();

        // Apply resize and reposition
        virtual void UpdateImpl();
    
        virtual void InitPre();
        virtual void Init();
        // static
		friend LRESULT CALLBACK windowProcMapper(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

        virtual LRESULT WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

        virtual void DrawBuffer() final;

        virtual void PaintPre(Graphics* graphics) {}
        virtual void PaintPost(Graphics* graphics) {}


        void OnChangeControlSize(int width, int height) {
            SetSize(width, height);
            Update();
        }

    protected:

        // OS_WIN
        HWND hWindow;
        std::string windowInternalId;
    };

}