#pragma once
#include "../afx.h"
#include "../frame.h"

#include <list>
#include <utility>

namespace wnd_accelerator {

    class NativeControl : public Frame {
    public:
        NativeControl();
        NativeControl(const NativeControl&) = delete;
        NativeControl(NativeControl&&) = delete;

    protected:
        // Build real frame
        virtual void BuildImpl();

        // Apply resize and reposition
        virtual void UpdateImpl();

        // Some painting operations of this object
        virtual void Paint() final;

        virtual void PaintPre();
        virtual void PaintBuffers();
        virtual void PaintPost();

    
        virtual void InitPre();
        virtual void Init();
        // static
		friend LRESULT CALLBACK windowProcMapper(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

        virtual LRESULT WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

        void CreateBuffer();
        void DeleteBuffer();
        void ResizeBuffer();

        void SystemPaintBuffer() {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWindow, &ps);
            BitBlt(hdc, 0, 0, width, height, bufferHDC, 0, 0, SRCCOPY);            
            EndPaint(hWindow, &ps);
        }

        void PaintBuffer(Gdiplus::Graphics* graphics) {
            graphics->Draw
        }

    protected:

        // OS_WIN
        HWND hWindow;

        // Buffer
        //byte* buffer;
        //HBITMAP bufferHBitmap;
        //Size bufferSize;

        //HDC bufferHDC;
        Gdiplus::Bitmap* buffer;
        Gdiplus::Graphics* graphics;

    public:
        virtual ~NativeControl();

    };

}