#include "native_control.h"

#include "window.h"

#include <string>

#include <Windows.h>
#include <windowsx.h>
#include <unordered_map>
#include <chrono>

namespace wnd_accelerator {

    static std::unordered_map<HWND, NativeControl*> nativeControlMap;

    // static
    LRESULT CALLBACK windowProcMapper(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) {
        if (nativeControlMap.count(hWindow) == 0) {
            return DefWindowProc(hWindow, message, wParam, lParam);
        }

        NativeControl* sender = nativeControlMap[hWindow];

        switch (message) {
            case WM_DESTROY: {
                PostQuitMessage(0);
                break;
            }
            case WM_SIZE:
            {
                sender->OnChangeControlSize(LOWORD(lParam), HIWORD(lParam));
                break;
            }
        }

        // Can be overrided
        return sender->WindowProc(hWindow, message, wParam, lParam);
    }

    void NativeControl::InitPre() {}

    void NativeControl::Init() {

        DWORD staticFlag = (staticWidth && staticHeight) ? 0 : WS_THICKFRAME | WS_MAXIMIZEBOX;

        DWORD dwStyle = WS_OVERLAPPED |
            WS_CAPTION |
            WS_SYSMENU |
            WS_MINIMIZEBOX |
            staticFlag;

        hWindow = CreateWindowEx(0,
                                 windowInternalId.c_str(),
                                 text.c_str(), 
                                 dwStyle,
                                 CW_USEDEFAULT,
                                 CW_USEDEFAULT,
                                 width + 16, 
                                 height + 39, 
                                 nullptr, 
                                 nullptr, 
                                 GetInstanceModule(nullptr), 
                                 nullptr);
        nativeControlMap[hWindow] = this;

        CreateBuffer();
    }

    LRESULT NativeControl::WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) {
        return DefWindowProc(hWindow, message, wParam, lParam);
    }

    void NativeControl::DrawBuffer() {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWindow, &ps);

        auto start = std::chrono::system_clock::now();

        this->Paint();

        auto end = std::chrono::system_clock::now();
        auto tm = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        graphics->FillRectangle(&SolidBrush(Color::Red), Rect(0, 0, 50, 20));
        graphics->DrawString((std::to_wstring(1000 / tm.count()) + L" fps").c_str(), -1, &Font(L"Arial", 12), PointF(0, 0), &SolidBrush(Color(255, 255, 255)));

        HBITMAP bufferHBitmap;
        buffer->GetHBITMAP(this->background, &bufferHBitmap);
        HDC bufferHDC = CreateCompatibleDC(nullptr);
        SelectObject(bufferHDC, bufferHBitmap);


        BitBlt(hdc, 0, 0, width, height, bufferHDC, 0, 0, SRCCOPY);

        DeleteObject(bufferHBitmap);
        DeleteDC(bufferHDC);

        EndPaint(hWindow, &ps);
    }

    // Build real frame
    void NativeControl::BuildImpl() {
        InitPre();
        Init();
    }

    // Apply resize and reposition
    void NativeControl::UpdateImpl() {
        ResizeBuffer();
    }

}