#pragma once
#include "afx.h"
#include "event_system/event.h"
#include "event_system/key_event.h"
#include "event_system/mouse_event.h"

#include <functional>
#include <list>

namespace wnd_accelerator {

    class Frame {
    public:
        Frame();
        Frame(const Frame& abstructFrameObject) = delete;
        Frame(Frame&& abstructFrameObject) = delete;

    public:
        // You must use Pack() for applay changes and maybe Repaint()
        virtual void Pack() = 0;        

        Frame* SetX(int x) noexcept;
        Frame* SetY(int y) noexcept;
        Frame* SetWidth(int width) noexcept;
        Frame* SetHeight(int height) noexcept;
        Frame* SetText(std::string text) noexcept;
        Frame* SetBackground(Color background) noexcept;

        Frame* SetPosition(int x, int y) noexcept;
        Frame* SetPosition(const Point& point) noexcept;
        Frame* SetSize(int width, int height) noexcept;
        Frame* SetSize(const Size& size) noexcept;
        Frame* SetRect(int x, int y, int width, int height) noexcept;
        Frame* SetRect(const Rect& rect) noexcept;
        Frame* SetProperty(int x, int y, int width, int height, std::string text, Color background) noexcept;
        
        int GetX() const noexcept;
        int GetY() const noexcept;
        int GetWidth() const noexcept;
        int GetHeight() const noexcept;
        std::string GetText() const noexcept;
        Color GetBackground() const noexcept;

        Point GetPosition() const noexcept;
        Size GetSize() const noexcept;
        Rect GetRect() const noexcept;

        using KeyEventFunction = std::function<void(Frame*, KeyEvent*)>;
        using MouseEventFunction = std::function<void(Frame*, MouseEvent*)>;

        virtual Frame* AddMouseClickListener(MouseEventFunction func) noexcept = 0;
        virtual Frame* AddMouseMoveListener(MouseEventFunction func) noexcept = 0;

        virtual Frame* AddLeftMouseButtonPressListener(MouseEventFunction func) noexcept = 0;
        virtual Frame* AddMiddleMouseButtonPressListener(MouseEventFunction func) noexcept = 0;
        virtual Frame* AddRightMouseButtonPressListener(MouseEventFunction func) noexcept = 0;

        virtual Frame* AddLeftMouseButtonReleaseListener(MouseEventFunction func) noexcept = 0;
        virtual Frame* AddMiddleMouseButtonReleaseListener(MouseEventFunction func) noexcept = 0;
        virtual Frame* AddRightMouseButtonReleaseListener(MouseEventFunction func) noexcept = 0;

        // TODO
        virtual Frame* AddMouseEnterListener(MouseEventFunction func) noexcept = 0;
        virtual Frame* AddMouseExitListener(MouseEventFunction func) noexcept = 0;
        virtual Frame* AddMouseWheelMoveListener(MouseEventFunction func) noexcept = 0;
        virtual Frame* AddMouseDragListener(MouseEventFunction func) noexcept = 0;

        virtual Frame* AddKeyTypeListener(KeyEventFunction func) noexcept = 0;
        virtual Frame* AddKeyPressListener(KeyEventFunction func) noexcept = 0;
        virtual Frame* AddKeyReleaseListener(KeyEventFunction func) noexcept = 0;

    protected:
        // Location in parent
        int x;
        int y;

        int xAbs;
        int yAbs;

        int width;
        int height;

        std::string text;
        Color background;

    public:
        virtual ~Frame();
    };

}