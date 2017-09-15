#include "native_control.h"

#include "window.h"

#include <string>

#include <Windows.h>
#include <windowsx.h>
#include <unordered_map>

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

    void Window::InitPre() {

        windowInternalId = "window" + std::to_string(int(this));

        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wcex.lpfnWndProc = windowProcMapper;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = GetInstanceModule(nullptr);
        //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_METAFRAME));
        wcex.hIcon = nullptr;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = nullptr;
        //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_METAFRAME);
        wcex.lpszMenuName = nullptr;

        wcex.lpszClassName = windowInternalId.c_str();
        //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
        wcex.hIconSm = nullptr;

        RegisterClassEx(&wcex);
    }

    void NativeControl::Init() {

        DWORD staticFlag = (staticWidth && staticHeight) ? 0 : WS_THICKFRAME | WS_MAXIMIZEBOX;

        DWORD dwStyle = WS_OVERLAPPED |
            WS_CAPTION |
            WS_SYSMENU |
            WS_MINIMIZEBOX |
            staticFlag;


        hWindow = CreateWindow(windowInternalId.c_str(),
                               text.c_str(), 
                               dwStyle,
                               CW_USEDEFAULT, 
                               0, 
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