#include "native_control.h"

#include "window.h"

#include <windowsx.h>
#include <unordered_map>
#include <Windows.h>

namespace wnd_accelerator {

    static std::unordered_map<HWND, NativeControl*> nativeControlMap;

    // static
    LRESULT CALLBACK windowProcMapper(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) {
        if (nativeControlMap.count(hWindow) == 0) {
            return DefWindowProc(hWindow, message, wParam, lParam);
        }

        NativeControl* sender = nativeControlMap[hWindow];

		



#if 0
        if (message == WM_HSCROLL) {
            nativeAbstructObject[hWnd].first->wmNotify(wParam, lParam);
        }
        if (message == WM_COMMAND && nativeAbstructObject.count(hWnd) != 0) {
            nativeAbstructObject[hWnd].first->wmCommand(wParam, lParam);
        }
        /*if (message == WM_NOTIFY && nativeAbstructObject.count(hWnd) != 0) {
        nativeAbstructObject[hWnd].first->wmCommand(wParam, lParam);
        }*/

        if (message == WM_MOUSEMOVE && nativeAbstructObject.count(hWnd) != 0) {
            MouseEventInfo event(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            event.xOnParent += nativeAbstructObject[hWnd].first->getX();
            event.yOnParent += nativeAbstructObject[hWnd].first->getY();
            if (wParam & MK_CONTROL) event.isCtrlPressed = true;
            /*        MouseEventInfo event(GET_X_LPARAM(eventInfo.lParam), GET_Y_LPARAM(eventInfo.lParam));
            if (eventInfo.wParam & MK_CONTROL) event.controlDown = true;
            if (eventInfo.wParam & MK_LBUTTON) event.leftButtonDown = true;
            if (eventInfo.wParam & MK_MBUTTON) event.midButtonDown = true;
            if (eventInfo.wParam & MK_RBUTTON) event.rightButtonDown = true;
            if (eventInfo.wParam & MK_SHIFT)   event.shiftDown = true;*/

            event.dx = nativeAbstructObject[hWnd].first->mousePos.x - event.xOnParent;
            event.dy = nativeAbstructObject[hWnd].first->mousePos.y - event.yOnParent;

            bool fl = true;
            if (nativeAbstructObject[hWnd].first->mousePos.x == 0 && nativeAbstructObject[hWnd].first->mousePos.y == 0) {
                fl = false;
            }

            if (wParam & MK_LBUTTON != 0 && fl) {
                nativeAbstructObject[hWnd].first->runMouseDraggedEvent(event);
            }
            //this->wmMouseEnter(event);
            //this->wmMouseExit(event);

            nativeAbstructObject[hWnd].first->runMouseMovedEvent(event);

            nativeAbstructObject[hWnd].first->mousePos = Point(event.xOnParent, event.yOnParent);
        }

        if (message == WM_LBUTTONDOWN && nativeAbstructObject.count(hWnd) != 0) {
            MouseEventInfo event(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            event.xOnParent += nativeAbstructObject[hWnd].first->getX();
            event.yOnParent += nativeAbstructObject[hWnd].first->getY();

            if (wParam & MK_CONTROL) event.isCtrlPressed = true;
            //alt todo
            //event.causedby = MouseButton::LEFT;
            nativeAbstructObject[hWnd].first->runMousePressedEvent(event);
            //return 0;
        }
        if (message == WM_LBUTTONUP && nativeAbstructObject.count(hWnd) != 0) {
            MouseEventInfo event(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            event.xOnParent += nativeAbstructObject[hWnd].first->getX();
            event.yOnParent += nativeAbstructObject[hWnd].first->getY();

            if (wParam & MK_CONTROL) event.isCtrlPressed = true;
            //alt todo
            //event.causedby = MouseButton::LEFT;
            nativeAbstructObject[hWnd].first->runMouseReleasedEvent(event);
            //return 0;
        }
        if ((message == WM_LBUTTONDBLCLK || message == WM_RBUTTONDBLCLK) && nativeAbstructObject.count(hWnd) != 0) {
            MouseEventInfo event(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            event.xOnParent += nativeAbstructObject[hWnd].first->getX();
            event.yOnParent += nativeAbstructObject[hWnd].first->getY();

            if (wParam & MK_CONTROL) event.isCtrlPressed = true;
            //alt todo
            //event.causedby = MouseButton::LEFT;
            nativeAbstructObject[hWnd].first->runMouseDoubleClickedEvent(event);
        }
        if ((message == WM_KEYDOWN || message == WM_RBUTTONDBLCLK) && nativeAbstructObject.count(hWnd) != 0) {
            KeyEvent event;
            event.code = KeyCodes(wParam); //Code

            BYTE lpKeyState[256];
            GetKeyboardState(lpKeyState);
            ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, &event.key, 1, 0);

            if (lParam && (0x1 << 30) == 0) {
                //this->wmKeyDown(event);
                nativeAbstructObject[hWnd].first->runKeyPressedEvent(event);
            }
            nativeAbstructObject[hWnd].first->runKeyTypedEvent(event);
            //this->wmKeyTyped(event);            
        }
        if ((message == WM_KEYUP || message == WM_RBUTTONDBLCLK) && nativeAbstructObject.count(hWnd) != 0) {
            KeyEvent event;
            event.code = KeyCodes(wParam); //Code

            BYTE lpKeyState[256];
            GetKeyboardState(lpKeyState);
            ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, &event.key, 1, 0);
            nativeAbstructObject[hWnd].first->runKeyReleasedEvent(event);
            //this->wmKeyUp(event);
        }
#endif
        return sender->WindowProc(hWindow, message, wParam, lParam);
    }

    void NativeControl::InitPre() {}

    void Window::InitPre() {
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

        wcex.lpszClassName = text.c_str();
        //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
        wcex.hIconSm = nullptr;

        RegisterClassEx(&wcex);
    }

    void NativeControl::Init() {
        hWindow = CreateWindow(text.c_str(), 
                               text.c_str(), 
                               WS_OVERLAPPEDWINDOW,
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

    void NativeControl::CreateBuffer() {
        buffer = new Gdiplus::Bitmap(width, height);
        graphics = new Gdiplus::Graphics(buffer);
        /*// Init buffer
        buffer = new byte[width * height * 4];
        bufferHBitmap = CreateBitmap(width, height, 1, 32, buffer);

        // Init HDC and graphics
        bufferHDC = CreateCompatibleDC(nullptr);
        SelectObject(bufferHDC, bufferHBitmap);
        bufferGraphics = new Gdiplus::Graphics(bufferHDC);

        bufferSize = Size(width, height);*/
    }

    void NativeControl::DeleteBuffer() {
        delete[] buffer;
        DeleteObject(bufferHBitmap);

        DeleteDC(bufferHDC);
        delete bufferGraphics;
    }

    void NativeControl::ResizeBuffer() {
        if (!bufferSize.Equals(Size(width, height))) {
            DeleteBuffer();
            CreateBuffer();
        }
    }

    // Build real frame
    void NativeControl::BuildImpl() {
        InitPre();
        Init();
    }

    // Apply resize and reposition
    void NativeControl::UpdateImpl() {

    }

    // Some painting operations of this object
    void NativeControl::Paint() {

    }

    void NativeControl::PaintPre() {}

    void NativeControl::PaintBuffers() {}

    void NativeControl::PaintPost() {}

}