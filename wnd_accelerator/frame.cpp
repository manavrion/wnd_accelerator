#include "frame.h"

namespace wnd_accelerator {

    Frame::Frame() :
        x(), y(),
        width(), height(),
        staticWidth(false),
        staticHeight(false),
        build(false),
        paint(true),
        parent(nullptr),
        listeners(new Listeners) {}

    // You must use Build() to create a frame object
    // if the frame object is a Window, use Run()
    void Frame::Build() {
        if (!build) {
            this->BuildImpl();
            build = true;
        }
        for (auto child : childs) {
            child->Build();
        }
    }

    // You must use Update() to apply the size and position changes
    void Frame::Update() {
        UpdateImpl();
        parent->Pack();
        Repaint();
    }

    // You must use Repaint() to apply graphical changes
    void Frame::Repaint() {
        paint = true;
        parent->Repaint();
    }

    Frame* Frame::Add(Frame* child) {
        child->parent = this;
        childs.push_back(child);
        this->MergeListeners(std::move(child->listeners));
        child->listeners.reset();
        return this;
    }

    std::list<Frame*>& Frame::GetChilds() {
        return childs;
    }

    Frame* Frame::GetParent() {
        return parent;
    }

    Frame* Frame::SetParent(Frame* parent) {
        this->parent = parent;
        return this;
    }

    void Frame::ClearChilds() {
        while (!childs.empty()) {
            delete childs.front();
            childs.erase(childs.begin());
        }
    }

    Frame* Frame::SetX(int x) {
        this->x = x;
        return this;
    }

    Frame* Frame::SetY(int y) {
        this->y = y;
        return this;
    }

    Frame* Frame::SetWidth(int width) {
        this->width = width;
        return this;
    }

    Frame* Frame::SetHeight(int height) {
        this->height = height;
        return this;
    }

    Frame* Frame::SetText(std::string text) {
        this->text = std::move(text);
        return this;
    }

    Frame* Frame::SetBackground(Color background) {
        this->background = std::move(background);
        return this;
    }

    Frame* Frame::SetStaticWidth() {
        staticWidth = true;
        return this;
    }

    Frame* Frame::SetStaticHeight() {
        staticHeight = true;
        return this;
    }

    Frame* Frame::SetDynamicWidth() {
        staticWidth = false;
        return this;
    }

    Frame* Frame::SetDynamicHeight() {
        staticHeight = false;
        return this;
    }

    Frame* Frame::SetPosition(int x, int y) {
        this->x = x;
        this->y = y;
        return this;
    }

    Frame* Frame::SetPosition(const Point& point) {
        return SetPosition(point.X, point.Y);
    }

    Frame* Frame::SetSize(int width, int height) {
        this->width = width;
        this->height = height;
        return this;
    }

    Frame* Frame::SetSize(const Size& size) {
        return SetSize(size.Width, size.Height);
    }

    Frame* Frame::SetRect(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        return this;
    }

    Frame* Frame::SetRect(const Rect& rect) {
        return SetRect(rect.X, rect.Y, rect.Width, rect.Height);
    }

    Frame* Frame::SetProperty(int x, int y, int width, int height, std::string text, Color background) {
        SetRect(x, y, width, height);
        SetText(std::move(text));
        SetBackground(std::move(background));
        return this;
    }

    Frame* Frame::SetStaticSize() {
        return SetStaticWidth()->SetStaticHeight();
    }

    Frame* Frame::SetDynamicSize() {
        return SetDynamicWidth()->SetDynamicHeight();
    }

    int Frame::GetX() const {
        return x;
    }

    int Frame::GetY() const {
        return y;
    }

    int Frame::GetWidth() const {
        return width;
    }

    int Frame::GetHeight() const {
        return height;
    }

    std::string Frame::GetText() const {
        return text;
    }

    Color Frame::GetBackground() const {
        return background;
    }

    Point Frame::GetPosition() const {
        return Point(x, y);
    }

    Size Frame::GetSize() const {
        return Size(width, height);
    }

    Rect Frame::GetRect() const {
        return Rect(x, y, width, height);
    }

    bool Frame::IsStaticWidth() const {
        return staticWidth;
    }

    bool Frame::IsStaticHeight() const {
        return staticHeight;
    }

    Frame* Frame::AddMouseClickListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::mouseClick, this, std::move(func));
        return this;
    }

    Frame* Frame::AddMouseMoveListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::mouseMove, this, std::move(func));
        return this;
    }

    Frame* Frame::AddLeftMouseButtonPressListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::leftMouseButtonPress, this, std::move(func));
        return this;
    }

    Frame* Frame::AddMiddleMouseButtonPressListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::middleMouseButtonPress, this, std::move(func));
        return this;
    }

    Frame* Frame::AddRightMouseButtonPressListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::rightMouseButtonPress, this, std::move(func));
        return this;
    }

    Frame* Frame::AddLeftMouseButtonReleaseListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::leftMouseButtonRelease, this, std::move(func));
        return this;
    }

    Frame* Frame::AddMiddleMouseButtonReleaseListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::middleMouseButtonRelease, this, std::move(func));
        return this;
    }

    Frame* Frame::AddRightMouseButtonReleaseListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::rightMouseButtonRelease, this, std::move(func));
        return this;
    }

    // TODO

    Frame* Frame::AddMouseEnterListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::mouseEnter, this, std::move(func));
        return this;
    }

    Frame* Frame::AddMouseExitListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::mouseExit, this, std::move(func));
        return this;
    }

    Frame* Frame::AddMouseWheelMoveListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::mouseWheel, this, std::move(func));
        return this;
    }

    Frame* Frame::AddMouseDragListener(MouseEventFunction func) {
        AddMouseListenerImpl(Event::Type::mouseDrag, this, std::move(func));
        return this;
    }

    Frame* Frame::AddKeyTypeListener(KeyEventFunction func) {
        AddKeyListenerImpl(Event::Type::keyType, this, std::move(func));
        return this;
    }

    Frame* Frame::AddKeyPressListener(KeyEventFunction func) {
        AddKeyListenerImpl(Event::Type::keyPress, this, std::move(func));
        return this;
    }

    Frame* Frame::AddKeyReleaseListener(KeyEventFunction func) {
        AddKeyListenerImpl(Event::Type::keyRelease, this, std::move(func));
        return this;
    }


    // Aliases

    Frame* Frame::AddMouseClickListener(EmptyEventFunction func) {
        return AddMouseClickListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddMouseMoveListener(EmptyEventFunction func) {
        return AddMouseMoveListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddLeftMouseButtonPressListener(EmptyEventFunction func) {
        return AddLeftMouseButtonPressListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddMiddleMouseButtonPressListener(EmptyEventFunction func) {
        return  AddMiddleMouseButtonPressListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddRightMouseButtonPressListener(EmptyEventFunction func) {
        return AddRightMouseButtonPressListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddLeftMouseButtonReleaseListener(EmptyEventFunction func) {
        return AddLeftMouseButtonReleaseListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddMiddleMouseButtonReleaseListener(EmptyEventFunction func) {
        return AddMiddleMouseButtonReleaseListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddRightMouseButtonReleaseListener(EmptyEventFunction func) {
        return AddRightMouseButtonReleaseListener([=](Frame*, MouseEvent*) { func(); });
    }

    // TODO

    Frame* Frame::AddMouseEnterListener(EmptyEventFunction func) {
        return AddMouseEnterListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddMouseExitListener(EmptyEventFunction func) {
        return AddMouseExitListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddMouseWheelMoveListener(EmptyEventFunction func) {
        return AddMouseWheelMoveListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddMouseDragListener(EmptyEventFunction func) {
        return AddMouseDragListener([=](Frame*, MouseEvent*) { func(); });
    }

    Frame* Frame::AddKeyTypeListener(EmptyEventFunction func) {
        return AddKeyTypeListener([=](Frame*, KeyEvent*) { func(); });
    }

    Frame* Frame::AddKeyPressListener(EmptyEventFunction func) {
        return AddKeyPressListener([=](Frame*, KeyEvent*) { func(); });
    }

    Frame* Frame::AddKeyReleaseListener(EmptyEventFunction func) {
        return AddKeyReleaseListener([=](Frame*, KeyEvent*) { func(); });
    }

    void Frame::ClearMouseClickListeners() {
        ClearMouseListenersImpl(Event::Type::mouseClick, this);
    }

    void Frame::ClearMouseMoveListeners() {
        ClearMouseListenersImpl(Event::Type::mouseMove, this);
    }

    void Frame::ClearLeftMouseButtonPressListeners() {
        ClearMouseListenersImpl(Event::Type::leftMouseButtonPress, this);
    }

    void Frame::ClearMiddleMouseButtonPressListeners() {
        ClearMouseListenersImpl(Event::Type::middleMouseButtonPress, this);
    }

    void Frame::ClearRightMouseButtonPressListeners() {
        ClearMouseListenersImpl(Event::Type::rightMouseButtonPress, this);
    }

    void Frame::ClearLeftMouseButtonReleaseListeners() {
        ClearMouseListenersImpl(Event::Type::leftMouseButtonRelease, this);
    }

    void Frame::ClearMiddleMouseButtonReleaseListeners() {
        ClearMouseListenersImpl(Event::Type::middleMouseButtonRelease, this);
    }

    void Frame::ClearRightMouseButtonReleaseListeners() {
        ClearMouseListenersImpl(Event::Type::rightMouseButtonRelease, this);
    }

    // TODO

    void Frame::ClearMouseEnterListeners() {
        ClearMouseListenersImpl(Event::Type::mouseEnter, this);
    }

    void Frame::ClearMouseExitListeners() {
        ClearMouseListenersImpl(Event::Type::mouseExit, this);
    }

    void Frame::ClearMouseWheelMoveListeners() {
        ClearMouseListenersImpl(Event::Type::mouseWheel, this);
    }

    void Frame::ClearMouseDragListeners() {
        ClearMouseListenersImpl(Event::Type::mouseDrag, this);
    }

    void Frame::ClearKeyTypeListeners() {
        ClearKeyListenersImpl(Event::Type::keyType, this);
    }

    void Frame::ClearKeyPressListeners() {
        ClearKeyListenersImpl(Event::Type::keyPress, this);
    }

    void Frame::ClearKeyReleaseListeners() {
        ClearKeyListenersImpl(Event::Type::keyRelease, this);
    }

    void Frame::ClearMouseListeners() {
        ClearKeyListenersImpl(Event::Type::mouse, this);
    }

    void Frame::ClearKeyListeners() {
        ClearKeyListenersImpl(Event::Type::key, this);
    }

    void Frame::ClearAddListeners() {
        ClearMouseListeners();
        ClearKeyListeners();
    }

    void Frame::NotifyKeyListeners(KeyEvent* keyEvent) {
        NotifyKeyListenersImpl(keyEvent);
    }

    void Frame::NotifyMouseListeners(MouseEvent* mouseEvent) {
        NotifyMouseListenersImpl(mouseEvent);
    }

    void Frame::AddKeyListenerImpl(Event::Type type, Frame* frame, KeyEventFunction func) {
        if (listeners == nullptr) {
            parent->AddKeyListenerImpl(type, frame, std::move(func));
            return;
        }
        listeners->AddKeyListenerToStore(type, frame, std::move(func));
    }

    void Frame::AddMouseListenerImpl(Event::Type type, Frame* frame, MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddMouseListenerImpl(type, frame, std::move(func));
            return;
        }
        listeners->AddMouseListenerToStore(type, frame, std::move(func));
    }

    void Frame::ClearKeyListenersImpl(Event::Type type, Frame* frame) {
        if (listeners == nullptr) {
            parent->ClearKeyListenersImpl(type, frame);
            return;
        }
        listeners->ClearKeyListenersInStore(type, frame);
    }

    void Frame::ClearMouseListenersImpl(Event::Type type, Frame* frame) {
        if (listeners == nullptr) {
            parent->ClearMouseListenersImpl(type, frame);
            return;
        }
        listeners->ClearMouseListenersInStore(type, frame);
    }

    void Frame::ClearAllKeyListenersImpl(Frame* frame) {
        if (listeners == nullptr) {
            parent->ClearAllKeyListenersImpl(frame);
            return;
        }
        listeners->ClearAllKeyListenersInStore(frame);
    }

    void Frame::ClearAllMouseListenersImpl(Frame* frame) {
        if (listeners == nullptr) {
            parent->ClearAllMouseListenersImpl(frame);
            return;
        }
        listeners->ClearAllMouseListenersInStore(frame);
    }

    void Frame::ClearAllListenersImpl(Frame* frame) {
        ClearAllKeyListenersImpl(frame);
        ClearAllMouseListenersImpl(frame);
    }

    void Frame::NotifyKeyListenersImpl(KeyEvent* keyEvent) {
        if (listeners == nullptr) {
            parent->NotifyKeyListenersImpl(keyEvent);
            return;
        }
        listeners->NotifyKeyListenersInStore(keyEvent);
    }

    void Frame::NotifyMouseListenersImpl(MouseEvent* mouseEvent) {
        if (listeners == nullptr) {
            parent->NotifyMouseListenersImpl(mouseEvent);
            return;
        }
        listeners->NotifyMouseListenersInStore(mouseEvent);
    }

    // Recursive packing childs
    void Frame::Pack() {
        this->PackImpl();
        for (auto child : childs) {
            child->Pack();
        }
    }


    // Implementation of packing
    void Frame::PackImpl() {
        //TODO 
    }

    void Frame::MergeListeners(std::unique_ptr<Listeners> listeners) {
        this->listeners->keyEventsMap.insert(listeners->keyEventsMap.begin(), listeners->keyEventsMap.end());
        this->listeners->mouseEventsMap.insert(listeners->mouseEventsMap.begin(), listeners->mouseEventsMap.end());
    }

    Frame::~Frame() {}

    void Frame::Listeners::AddKeyListenerToStore(Event::Type type, Frame* frame, KeyEventFunction func) {
        keyEventsMap[type][frame].push_back(func);
    }

    void Frame::Listeners::AddMouseListenerToStore(Event::Type type, Frame* frame, MouseEventFunction func) {
        mouseEventsMap[type][frame].push_back(func);
    }

    void Frame::Listeners::ClearKeyListenersInStore(Event::Type type, Frame* frame) {
        keyEventsMap[type][frame].clear();
    }

    void Frame::Listeners::ClearMouseListenersInStore(Event::Type type, Frame* frame) {
        mouseEventsMap[type][frame].clear();
    }

    void Frame::Listeners::ClearAllKeyListenersInStore(Frame* frame) {
        for (auto& ob : keyEventsMap) {
            keyEventsMap[ob.first][frame].clear();
        }
    }

    void Frame::Listeners::ClearAllMouseListenersInStore(Frame* frame) {
        for (auto& ob : keyEventsMap) {
            mouseEventsMap[ob.first][frame].clear();
        }
    }

    void Frame::Listeners::ClearAllListenersInStore(Frame* frame) {
        ClearAllKeyListenersInStore(frame);
        ClearAllMouseListenersInStore(frame);
    }

    void Frame::Listeners::NotifyKeyListenersInStore(KeyEvent* keyEvent) {
        for (auto& ob : keyEventsMap[Event::Type::key]) {
            Frame* sender = ob.first;
            for (auto& function : keyEventsMap[Event::Type::key][sender]) {
                function(sender, keyEvent);
            }
        }
        for (auto& ob : keyEventsMap[keyEvent->type]) {
            Frame* sender = ob.first;
            for (auto& function : keyEventsMap[keyEvent->type][sender]) {
                function(sender, keyEvent);
            }
        }
    }

    void Frame::Listeners::NotifyMouseListenersInStore(MouseEvent* mouseEvent) {

        auto contains = [](Frame *frame, MouseEvent* mouseEvent) {
            Rect rect(frame->GetXAbs(), frame->GetYAbs(), frame->width, frame->height);
            int x = mouseEvent->xAbs;
            int y = mouseEvent->yAbs;
            if (x >= rect.X && y >= rect.Y && x <= (rect.X + rect.Width) && y <= (rect.Y + rect.Height)) {
                return true;
            }
            return false;
        };

        if (mouseEvent->type == Event::Type::mouseMove) {
            MouseMove(*mouseEvent);
        }
        for (auto& ob : mouseEventsMap[Event::Type::mouse]) {
            Frame* sender = ob.first;
            for (auto& function : mouseEventsMap[Event::Type::mouse][sender]) {
                if (contains(sender, mouseEvent)) {
                    function(sender, mouseEvent);
                }
            }
        }
        for (auto& ob : mouseEventsMap[mouseEvent->type]) {
            Frame* sender = ob.first;
            for (auto& function : mouseEventsMap[mouseEvent->type][sender]) {
                if (contains(sender, mouseEvent) || mouseEvent->type == Event::Type::mouseExit) {
                    function(sender, mouseEvent);
                }
            }
        }
    }

}