#include "window.h"

#include <string>
#include <Windows.h>
#include <windowsx.h>
#include <chrono>

namespace wnd_accelerator {

    // static
    extern LRESULT CALLBACK windowProcMapper(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

    void Window::InitPre() {
        CreateBuffer();
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

    void Window::DrawBuffer() {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWindow, &ps);

        auto start = std::chrono::system_clock::now();


        this->Paint(Graphics(graphics, 0, 0));

        auto end = std::chrono::system_clock::now();
        auto tm = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        graphics->FillRectangle(&SolidBrush(Color::Red), Rect(0, 0, 80, 20));
        Font font(L"Arial", 12);
        SolidBrush b(Color(255, 255, 255));
        if (tm.count() == 0) {
            graphics->DrawString(L"1000 < fps", -1, &font, PointF(0, 0), &b);
        } else {
            graphics->DrawString((std::to_wstring(1000 / tm.count()) + L" fps").c_str(), -1, &font, PointF(0, 0), &b);
        }

        HBITMAP bufferHBitmap;
        buffer->GetHBITMAP(this->background, &bufferHBitmap);
        HDC bufferHDC = CreateCompatibleDC(nullptr);
        SelectObject(bufferHDC, bufferHBitmap);


        BitBlt(hdc, 0, 0, width, height, bufferHDC, 0, 0, SRCCOPY);

        DeleteObject(bufferHBitmap);
        DeleteDC(bufferHDC);

        EndPaint(hWindow, &ps);
    }

    LRESULT Window::WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MOUSEMOVE:
            {
                MouseEvent mouseEvent;

                mouseEvent.xAbs = GET_X_LPARAM(lParam);
                mouseEvent.yAbs = GET_Y_LPARAM(lParam);
                mouseEvent.x -= this->GetXAbs();
                mouseEvent.y -= this->GetYAbs();

                if (wParam & MK_CONTROL) mouseEvent.controlDown = true;
                if (wParam & MK_LBUTTON) mouseEvent.leftMouseButtonDown = true;
                if (wParam & MK_MBUTTON) mouseEvent.middleMouseButtonDown = true;
                if (wParam & MK_RBUTTON) mouseEvent.rightMouseButtonDown = true;
                if (wParam & MK_SHIFT)   mouseEvent.shiftDown = true;

                switch (message) {
                    case WM_LBUTTONDOWN: {
                        mouseEvent.type = MouseEvent::Type::leftMouseButtonPress;
                        break;
                    }
                    case WM_RBUTTONDOWN: {
                        mouseEvent.type = MouseEvent::Type::rightMouseButtonPress;
                        break;
                    }
                    case WM_LBUTTONUP: {
                        mouseEvent.type = MouseEvent::Type::leftMouseButtonRelease;
                        break;
                    }
                    case WM_RBUTTONUP: {
                        mouseEvent.type = MouseEvent::Type::rightMouseButtonRelease;
                        break;
                    }
                    case WM_MOUSEMOVE: {
                        mouseEvent.type = MouseEvent::Type::mouseMove;
                        break;
                    }
                }
                this->NotifyMouseListeners(&mouseEvent);
                break;
            }
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
                KeyEvent keyEvent;
                keyEvent.keyCode = KeyEvent::KeyCodes(wParam);

                BYTE lpKeyState[256];
                GetKeyboardState(lpKeyState);
                ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, &keyEvent.key, 1, 0);

                switch (message) {
                    case WM_KEYDOWN:
                        keyEvent.type = KeyEvent::Type::keyPress;
                        break;
                    case WM_KEYUP:
                        keyEvent.type = KeyEvent::Type::keyRelease;
                        break;
                }
                this->NotifyKeyListeners(&keyEvent);
                break;
            }
            case WM_PAINT:
            {
                this->DrawBuffer();
                break;
            }
        }
        return DefWindowProc(hWindow, message, wParam, lParam);
    }


    // You must use Repaint() to apply graphical changes
    void Window::Repaint() {
        paint = true;
        InvalidateRect(hWindow, nullptr, false);
    }

    void Window::Close() {
        DestroyWindow(hWindow);
        //PostQuitMessage(0);
    }

    int Window::Run() {
        Build();
        Pack();        

        bool nCmdShow = true;
        ShowWindow(hWindow, nCmdShow);
        UpdateWindow(hWindow);

        Repaint();

        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0)) {
            if (!TranslateAccelerator(msg.hwnd, nullptr, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        return (int)msg.wParam;
    }

}
