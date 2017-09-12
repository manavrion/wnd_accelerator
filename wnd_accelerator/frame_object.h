#pragma once
#include "afx.h"
#include "event_system\key_listener.h"
#include "event_system\mouse_listener.h"

#include <functional>
#include <list>

namespace wnd_accelerator {

    class FrameObject {
    public:
        FrameObject();
        FrameObject(const FrameObject& abstructFrameObject) = delete;
        FrameObject(FrameObject&& abstructFrameObject) = delete;

    protected:
        virtual void PackImpl() = 0;

    public:
        // You must use Pack() for applay changes and maybe Repaint()
        virtual void Pack() = 0;        

        FrameObject* SetX(int x) noexcept;
        FrameObject* SetY(int y) noexcept;
        FrameObject* SetWidth(int width) noexcept;
        FrameObject* SetHeight(int height) noexcept;
        FrameObject* SetText(std::string text) noexcept;
        FrameObject* SetBackground(Color background) noexcept;

        FrameObject* SetPosition(int x, int y) noexcept;
        FrameObject* SetPosition(const Point& point) noexcept;
        FrameObject* SetSize(int width, int height) noexcept;
        FrameObject* SetSize(const Size& size) noexcept;
        FrameObject* SetRect(int x, int y, int width, int height) noexcept;
        FrameObject* SetRect(const Rect& rect) noexcept;
        FrameObject* SetProperty(int x, int y, int width, int height, std::string text, Color background) noexcept;
        
        int GetX() const noexcept;
        int GetY() const noexcept;
        int GetWidth() const noexcept;
        int GetHeight() const noexcept;
        std::string GetText() const noexcept;
        Color GetBackground() const noexcept;

        Point GetPosition() const noexcept;
        Size GetSize() const noexcept;
        Rect GetRect() const noexcept;
        
        FrameObject* AddMouseListener(const MouseListener& mouseListener) noexcept;
        FrameObject* AddKeyListener(const KeyListener& keyListener) noexcept;

        using KeyPressedFunction = std::function<void(FrameObject* sender, const KeyEvent& keyEvent)>;
        using MouseFunction = std::function<void(FrameObject* sender, const MouseEvent& keyEvent)>;

        FrameObject* AddKeyTypedListener(KeyPressedFunction func) noexcept;
        FrameObject* AddKeyPressedListener(KeyPressedFunction func) noexcept;
        FrameObject* AddKeyReleasedListener(KeyPressedFunction func) noexcept;
        FrameObject* AddMouseClickedListener(MouseFunction func) noexcept;
        FrameObject* AddMousePressedListener(MouseFunction func) noexcept;
        FrameObject* AddMouseReleasedListener(MouseFunction func) noexcept;
        FrameObject* AddMouseEnteredListener(MouseFunction func) noexcept;
        FrameObject* AddMouseExitedListener(MouseFunction func) noexcept;
        FrameObject* AddMouseWheelMovedListener(MouseFunction func) noexcept;
        FrameObject* AddMouseDraggedListener(MouseFunction func) noexcept;
        FrameObject* AddMouseMovedListener(MouseFunction func) noexcept;

    protected:
        struct FrameObjectKeyListener : public KeyListener {
            FrameObjectKeyListener(FrameObject *owner);

            virtual void KeyTyped(const KeyEvent& keyEvent);
            virtual void KeyPressed(const KeyEvent& keyEvent);
            virtual void KeyReleased(const KeyEvent& keyEvent);

            FrameObject *owner;
            std::list<KeyPressedFunction> keyTypedFunctions;
            std::list<KeyPressedFunction> keyPressedFunctions;
            std::list<KeyPressedFunction> keyReleasedFunctions;
        };

        struct FrameObjectMouseListener : public MouseListener {
            FrameObjectMouseListener(FrameObject *owner);

            virtual void MouseClicked(const MouseEvent& mouseEvent);
            virtual void MousePressed(const MouseEvent& mouseEvent);
            virtual void MouseReleased(const MouseEvent& mouseEvent);
            virtual void MouseEntered(const MouseEvent& mouseEvent);
            virtual void MouseExited(const MouseEvent& mouseEvent);
            virtual void MouseWheelMoved(const MouseEvent& mouseEvent);
            virtual void MouseDragged(const MouseEvent& mouseEvent);
            virtual void MouseMoved(const MouseEvent& mouseEvent);

            FrameObject *owner;
            std::list<MouseFunction> mouseClickedFunctions;
            std::list<MouseFunction> mousePressedFunctions;
            std::list<MouseFunction> mouseReleasedFunctions;
            std::list<MouseFunction> mouseEnteredFunctions;
            std::list<MouseFunction> mouseExitedFunctions;
            std::list<MouseFunction> mouseWheelMovedFunctions;
            std::list<MouseFunction> mouseDraggedFunctions;
            std::list<MouseFunction> mouseMovedFunctions;
        };

    protected:
        // Location in parent
        int x;
        int y;

        int width;
        int height;

        std::string text;
        Color background;

        std::list<KeyListener> keyListeners;
        std::list<MouseListener> mouseListeners;

        FrameObjectKeyListener frameObjectKeyListener;
        FrameObjectMouseListener frameObjectMouseListener;

    public:
        virtual ~FrameObject();
    };

}