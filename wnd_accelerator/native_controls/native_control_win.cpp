#include "native_control.h"

#include <windowsx.h>
#include <unordered_map>
#include <Windows.h>

namespace wnd_accelerator {

    static std::unordered_map<HWND, NativeControl*> nativeControlMap;

    LRESULT CALLBACK windowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) {
        if (nativeControlMap.count(hWindow) == 0) {
            return DefWindowProc(hWindow, message, wParam, lParam);
        }

        NativeControl* sender = nativeControlMap[hWindow];

        if (message == WM_MOUSEMOVE) {

            MouseEvent mouseEvent;

            mouseEvent.type = MouseEvent::EventType::mouseMove;

            mouseEvent.x = GET_X_LPARAM(lParam);
            mouseEvent.y = GET_Y_LPARAM(lParam);

            mouseEvent.xOnParent = mouseEvent.x + sender->GetX();
            mouseEvent.yOnParent = mouseEvent.y + sender->GetY();
            if (wParam & MK_CONTROL) mouseEvent.isCtrlPressed = true;
            if (wParam & MK_CONTROL) mouseEvent.controlDown = true;
            if (wParam & MK_LBUTTON) mouseEvent.leftButtonDown = true;
            if (wParam & MK_MBUTTON) mouseEvent.midButtonDown = true;
            if (wParam & MK_RBUTTON) mouseEvent.rightButtonDown = true;
            if (wParam & MK_SHIFT)   mouseEvent.shiftDown = true;

            //event.dx = nativeAbstructObject[hWnd].first->mousePos.x - event.xOnParent;
            //event.dy = nativeAbstructObject[hWnd].first->mousePos.y - event.yOnParent;

            //bool fl = true;
            //if (nativeAbstructObject[hWnd].first->mousePos.x == 0 && nativeAbstructObject[hWnd].first->mousePos.y == 0) {
            //    fl = false;
            //}

            //if (wParam & MK_LBUTTON != 0 && fl) {
            //    nativeAbstructObject[hWnd].first->runMouseDraggedEvent(event);
            //}
            //this->wmMouseEnter(event);
            //this->wmMouseExit(event);

            nativeAbstructObject[hWnd].first->runMouseMovedEvent(event);

            nativeAbstructObject[hWnd].first->mousePos = Point(event.xOnParent, event.yOnParent);
        }
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
        return DefWindowProc(hWindow, message, wParam, lParam);
    }



}