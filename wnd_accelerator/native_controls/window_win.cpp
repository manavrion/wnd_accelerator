#include "window.h"

#include <Windows.h>
#include <windowsx.h>

namespace wnd_accelerator {

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
                mouseEvent.x -= this->xAbs;
                mouseEvent.y -= this->yAbs;

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

                for (auto& mouseEventFunctionData : this->listeners->mouseEventsMap[mouseEvent.type]) {
                    mouseEventFunctionData.second(mouseEventFunctionData.first, &mouseEvent);
                }
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
                for (auto& keyEventFunctionData : this->listeners->keyEventsMap[keyEvent.type]) {
                    keyEventFunctionData.second(keyEventFunctionData.first, &keyEvent);
                }
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
        RepaintImpl();
        InvalidateRect(hWindow, nullptr, true);
    }

    int Window::Run() {
        Build();
        Pack();

        bool nCmdShow = true;
        ShowWindow(hWindow, nCmdShow);
        UpdateWindow(hWindow);

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
