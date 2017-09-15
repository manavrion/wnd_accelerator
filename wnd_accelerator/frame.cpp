#include "frame.h"

namespace wnd_accelerator {

    Frame::Frame() :
        x(10), y(10),
        width(100), height(25),
        staticWidth(false),
        staticHeight(false),
        build(false),
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
        RepaintImpl();
        parent->RepaintBackground();
    }


    // You should use RepaintBackground() instead of Repaint()
    // if the childs does not need to Repaint()
    void Frame::RepaintBackground() {
        Paint();
        parent->RepaintBackground();
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
        if (listeners == nullptr) {
            parent->AddMouseClickListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseClick].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddMouseMoveListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddMouseMoveListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseMove].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddLeftMouseButtonPressListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddLeftMouseButtonPressListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::leftMouseButtonPress].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddMiddleMouseButtonPressListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddMiddleMouseButtonPressListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::middleMouseButtonPress].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddRightMouseButtonPressListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddRightMouseButtonPressListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::rightMouseButtonPress].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddLeftMouseButtonReleaseListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddLeftMouseButtonReleaseListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::leftMouseButtonRelease].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddMiddleMouseButtonReleaseListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddMiddleMouseButtonReleaseListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::middleMouseButtonRelease].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddRightMouseButtonReleaseListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddRightMouseButtonReleaseListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::rightMouseButtonRelease].push_back({ this, std::move(func) });
        return this;
    }

    // TODO

    Frame* Frame::AddMouseEnterListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddMouseEnterListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseEnter].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddMouseExitListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddMouseExitListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseExit].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddMouseWheelMoveListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddMouseWheelMoveListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseMove].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddMouseDragListener(MouseEventFunction func) {
        if (listeners == nullptr) {
            parent->AddMouseDragListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseDrag].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddKeyTypeListener(KeyEventFunction func) {
        if (listeners == nullptr) {
            parent->AddKeyTypeListener(func);
            return this;
        }
        listeners->keyEventsMap[Event::Type::keyType].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddKeyPressListener(KeyEventFunction func) {
        if (listeners == nullptr) {
            parent->AddKeyPressListener(func);
            return this;
        }
        listeners->keyEventsMap[Event::Type::keyPress].push_back({ this, std::move(func) });
        return this;
    }

    Frame* Frame::AddKeyReleaseListener(KeyEventFunction func) {
        if (listeners == nullptr) {
            parent->AddKeyReleaseListener(func);
            return this;
        }
        listeners->keyEventsMap[Event::Type::keyRelease].push_back({ this, std::move(func) });
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

    void Frame::RepaintImpl() {
        for (auto child : childs) {
            child->RepaintImpl();
        }
        Paint();
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
        listeners->keyEventsMap.insert(listeners->keyEventsMap.begin(), listeners->keyEventsMap.end());
        listeners->mouseEventsMap.insert(listeners->mouseEventsMap.begin(), listeners->mouseEventsMap.end());
    }

    Frame::~Frame() {}

}