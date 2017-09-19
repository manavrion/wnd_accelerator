#pragma once
#include "afx.h"
#include "event_system/event.h"
#include "event_system/key_event.h"
#include "event_system/mouse_event.h"
#include "interfaces/i_rect.h"

#include <functional>
#include <list>
#include <mutex>

namespace wnd_accelerator {

    class Graphics;

    class Frame : public IRect {
    public:
        Frame();
        Frame(const Frame& abstructFrameObject) = delete;
        Frame(Frame&& abstructFrameObject) = delete;
        Frame& operator=(const Frame&) = delete;
        virtual ~Frame();

    public:

        // You must use Build() to create a frame object
        // if the frame object is a Window, use Run()
        void Build();

        // You must use Update() to apply the size and position changes
        virtual void Update();

        // You must use Repaint() to apply graphical changes
        virtual void Repaint();

        void MarkToRepaint() {
            paint = true;
            if (parent) {
                parent->MarkToRepaint();
            }
        }

        Frame* Add(Frame* child);

        Frame* Erase(Frame* child);

        std::list<Frame*>& GetChilds();
        Frame* GetParent();
        Frame* SetParent(Frame* parent);
        void ClearChilds();


        Frame* SetX(int x);
        Frame* SetY(int y);
        Frame* SetWidth(int width);
        Frame* SetHeight(int height);
        Frame* SetText(std::string text);
        Frame* SetBackground(Color background);
        Frame* SetStaticWidth();
        Frame* SetStaticHeight();
        Frame* SetDynamicWidth();
        Frame* SetDynamicHeight();

        Frame* SetPosition(int x, int y);
        Frame* SetPosition(const Point& point);
        Frame* SetSize(int width, int height);
        Frame* SetSize(const Size& size);
        Frame* SetRect(int x, int y, int width, int height);
        Frame* SetRect(const Rect& rect);
        Frame* SetProperty(int x, int y, int width, int height, std::string text, Color background);
        Frame* SetStaticSize();
        Frame* SetDynamicSize();

        int GetX() const;
        int GetY() const;
        int GetWidth() const;
        int GetHeight() const;
        std::string GetText() const;
        Color GetBackground() const;

        Point GetPosition() const;
        Size GetSize() const;
        Rect GetRect() const;

        int GetXAbs() {
            if (parent) {
                return x + parent->GetXAbs();
            }
            return 0;
        }

        int GetYAbs() {
            if (parent) {
                return y + parent->GetYAbs();
            }
            return 0;
        }

        bool IsStaticWidth() const;
        bool IsStaticHeight() const;
        
        virtual void Paint(Graphics graphics) = 0;

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

        void ClearMouseClickListeners();
        void ClearMouseMoveListeners();

        void ClearLeftMouseButtonPressListeners();
        void ClearMiddleMouseButtonPressListeners();
        void ClearRightMouseButtonPressListeners();

        void ClearLeftMouseButtonReleaseListeners();
        void ClearMiddleMouseButtonReleaseListeners();
        void ClearRightMouseButtonReleaseListeners();

        // TODO
        void ClearMouseEnterListeners();
        void ClearMouseExitListeners();
        void ClearMouseWheelMoveListeners();
        void ClearMouseDragListeners();

        void ClearKeyTypeListeners();
        void ClearKeyPressListeners();
        void ClearKeyReleaseListeners();

        
        void ClearMouseListeners();
        void ClearKeyListeners();
        void ClearAddListeners();

        virtual void NotifyKeyListeners(KeyEvent *keyEvent);
        virtual void NotifyMouseListeners(MouseEvent *mouseEvent);

    protected:

        void AddKeyListenerImpl(Event::Type type, Frame* frame, KeyEventFunction func);
        void AddMouseListenerImpl(Event::Type type, Frame* frame, MouseEventFunction func);

        void ClearKeyListenersImpl(Event::Type type, Frame* frame);
        void ClearMouseListenersImpl(Event::Type type, Frame* frame);

        void ClearAllKeyListenersImpl(Frame* frame);
        void ClearAllMouseListenersImpl(Frame* frame);
        void ClearAllListenersImpl(Frame* frame);

        void NotifyKeyListenersImpl(KeyEvent* keyEvent);
        void NotifyMouseListenersImpl(MouseEvent* mouseEvent);

    protected:
        struct Listeners {
            using KeyEventFunctionsList = std::list<KeyEventFunction>;
            using MouseEventFunctionsList = std::list<MouseEventFunction>;
            Listeners() = default;
            Listeners(const Listeners&) = default;
            Listeners(Listeners&&) = default;
            ~Listeners() = default;

            void AddKeyListenerToStore(Event::Type type, Frame* frame, KeyEventFunction func);
            void AddMouseListenerToStore(Event::Type type, Frame* frame, MouseEventFunction func);

            void ClearKeyListenersInStore(Event::Type type, Frame* frame);
            void ClearMouseListenersInStore(Event::Type type, Frame* frame);

            void ClearAllKeyListenersInStore(Frame* frame);
            void ClearAllMouseListenersInStore(Frame* frame);
            void ClearAllListenersInStore(Frame* frame);

            void NotifyKeyListenersInStore(KeyEvent* keyEvent);
            void NotifyMouseListenersInStore(MouseEvent* mouseEvent);

            void MouseMove(MouseEvent mouseEvent) {
                if (preMouseMoveEvent == nullptr) {
                    preMouseMoveEvent.reset(new MouseEvent(mouseEvent));
                    return;
                }

                auto contains = [](Frame *frame, MouseEvent* mouseEvent) {
                    Rect rect(frame->GetXAbs(), frame->GetYAbs(), frame->width, frame->height);
                    int x = mouseEvent->xAbs;
                    int y = mouseEvent->yAbs;
                    if (x >= rect.X && y >= rect.Y && x <= (rect.X + rect.Width) && y <= (rect.Y + rect.Height)) {
                        return true;
                    }
                    return false;
                };

                for (auto& key : mouseEventsMap[Event::Type::mouseEnter]) {
                    Frame* frame = key.first;
                    if (contains(frame, &mouseEvent) && !contains(frame, preMouseMoveEvent.get())) {
                        mouseEvent.type = Event::Type::mouseEnter;
                        NotifyMouseListenersInStore(&mouseEvent);
                    }
                }

                for (auto& key : mouseEventsMap[Event::Type::mouseExit]) {
                    Frame* frame = key.first;
                    if (!contains(frame, &mouseEvent) && contains(frame, preMouseMoveEvent.get())) {
                        mouseEvent.type = Event::Type::mouseExit;
                        NotifyMouseListenersInStore(&mouseEvent);
                    }
                }

                preMouseMoveEvent.reset(new MouseEvent(mouseEvent));
            }

            std::unique_ptr<MouseEvent> preMouseMoveEvent;

            std::unordered_map<Event::Type, std::unordered_map<Frame*, KeyEventFunctionsList>> keyEventsMap;
            std::unordered_map<Event::Type, std::unordered_map<Frame*, MouseEventFunctionsList>> mouseEventsMap;
        };

    protected:
        // Build real frame
        virtual void BuildImpl() = 0;
        // Apply resize and reposition
        virtual void UpdateImpl() = 0;

        // Recursive packing childs
        void Pack();

        // Implementation of packing
        void PackImpl();

        void MergeListeners(std::unique_ptr<Listeners> listeners);

    protected:
        // Location in parent
        int x;
        int y;

        int width;
        int height;

        bool staticWidth;
        bool staticHeight;

        std::string text;
        Color background;

        Frame* parent;
        std::list<Frame*> childs;
        std::mutex childsMutex;
        bool build;
        bool paint;
        // Need to keep event listeners before parent set
        std::unique_ptr<Listeners> listeners;
    };

}