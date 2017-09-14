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

        // You must use Build() to create a frame object
        // if the frame object is a Window, use Run()
        void Build();

        // You must use Update() to apply the size and position changes
        virtual void Update();

        // You must use Repaint() to apply graphical changes
        virtual void Repaint();

        // You should use RepaintBackground() instead of Repaint()
        // if the childs does not need to Repaint()
        virtual void RepaintBackground();

        Frame* Add(Frame* child);

        std::list<Frame*>& GetChilds();
        Frame* GetParent();
        void ClearChilds();


        Frame* SetX(int x);
        Frame* SetY(int y);
        Frame* SetWidth(int width);
        Frame* SetHeight(int height);
        Frame* SetText(std::string text);
        Frame* SetBackground(Color background);

        Frame* SetPosition(int x, int y);
        Frame* SetPosition(const Point& point);
        Frame* SetSize(int width, int height);
        Frame* SetSize(const Size& size);
        Frame* SetRect(int x, int y, int width, int height);
        Frame* SetRect(const Rect& rect);
        Frame* SetProperty(int x, int y, int width, int height, std::string text, Color background);
        
        int GetX() const;
        int GetY() const;
        int GetWidth() const;
        int GetHeight() const;
        std::string GetText() const;
        Color GetBackground() const;

        Point GetPosition() const;
        Size GetSize() const;
        Rect GetRect() const;


        using KeyEventFunction = std::function<void(Frame*, KeyEvent*)>;
        using MouseEventFunction = std::function<void(Frame*, MouseEvent*)>;
        using EmptyEventFunction = std::function<void()>;

        Frame* AddMouseClickListener(MouseEventFunction func);
        Frame* AddMouseMoveListener(MouseEventFunction func);

        Frame* AddLeftMouseButtonPressListener(MouseEventFunction func);
        Frame* AddMiddleMouseButtonPressListener(MouseEventFunction func);
        Frame* AddRightMouseButtonPressListener(MouseEventFunction func);

        Frame* AddLeftMouseButtonReleaseListener(MouseEventFunction func);
        Frame* AddMiddleMouseButtonReleaseListener(MouseEventFunction func);
        Frame* AddRightMouseButtonReleaseListener(MouseEventFunction func);

        // TODO
        Frame* AddMouseEnterListener(MouseEventFunction func);
        Frame* AddMouseExitListener(MouseEventFunction func);
        Frame* AddMouseWheelMoveListener(MouseEventFunction func);
        Frame* AddMouseDragListener(MouseEventFunction func);

        Frame* AddKeyTypeListener(KeyEventFunction func);
        Frame* AddKeyPressListener(KeyEventFunction func);
        Frame* AddKeyReleaseListener(KeyEventFunction func);


        // Aliases
        Frame* AddMouseClickListener(EmptyEventFunction func);
        Frame* AddMouseMoveListener(EmptyEventFunction func);

        Frame* AddLeftMouseButtonPressListener(EmptyEventFunction func);
        Frame* AddMiddleMouseButtonPressListener(EmptyEventFunction func);
        Frame* AddRightMouseButtonPressListener(EmptyEventFunction func);

        Frame* AddLeftMouseButtonReleaseListener(EmptyEventFunction func);
        Frame* AddMiddleMouseButtonReleaseListener(EmptyEventFunction func);
        Frame* AddRightMouseButtonReleaseListener(EmptyEventFunction func);

        // TODO
        Frame* AddMouseEnterListener(EmptyEventFunction func);
        Frame* AddMouseExitListener(EmptyEventFunction func);
        Frame* AddMouseWheelMoveListener(EmptyEventFunction func);
        Frame* AddMouseDragListener(EmptyEventFunction func);

        Frame* AddKeyTypeListener(EmptyEventFunction func);
        Frame* AddKeyPressListener(EmptyEventFunction func);
        Frame* AddKeyReleaseListener(EmptyEventFunction func);

    protected:
        struct Listeners {
            using KeyEventFunctionsList = std::list<std::pair<Frame*, KeyEventFunction>>;
            using MouseEventFunctionsList = std::list<std::pair<Frame*, MouseEventFunction>>;
            Listeners() = default;
            Listeners(const Listeners&) = default;
            Listeners(Listeners&&) = default;
            ~Listeners() = default;

            std::unordered_map<Event::Type, KeyEventFunctionsList> keyEventsMap;
            std::unordered_map<Event::Type, MouseEventFunctionsList> mouseEventsMap;
        };

    protected:
        // Build real frame
        virtual void BuildImpl() = 0;
        // Apply resize and reposition
        virtual void UpdateImpl() = 0;
        // Some painting operations of this object
        virtual void Paint() = 0;

        void RepaintImpl();

        // Recursive packing childs
        void Pack();

        // Implementation of packing
        void PackImpl();

        void MergeListeners(std::unique_ptr<Listeners> listeners);


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

        Frame* parent;
        std::list<Frame*> childs;
        bool build;
        // Need to keep event listeners before parent set
        std::unique_ptr<Listeners> listeners;

    public:
        virtual ~Frame();
    };

}