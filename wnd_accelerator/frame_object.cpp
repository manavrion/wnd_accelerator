#include "frame_object.h"

namespace wnd_accelerator {

    FrameObject::FrameObject() :
        x(10), y(10),
        width(100), height(25), 
        frameObjectKeyListener(this),
        frameObjectMouseListener(this) {}

    FrameObject* FrameObject::SetX(int x) noexcept {
        this->x = x;
        return this;
    }

    FrameObject* FrameObject::SetY(int y) noexcept {
        this->y = y;
        return this;
    }

    FrameObject* FrameObject::SetWidth(int width) noexcept {
        this->width = width;
        return this;
    }

    FrameObject* FrameObject::SetHeight(int height) noexcept {
        this->height = height;
        return this;
    }

    FrameObject* FrameObject::SetText(std::string text) noexcept {
        this->text = std::move(text);
        return this;
    }

    FrameObject* FrameObject::SetBackground(Color background) noexcept {
        this->background = std::move(background);
        return this;
    }

    FrameObject* FrameObject::SetPosition(int x, int y) noexcept {
        this->x = x;
        this->y = y;
        return this;
    }

    FrameObject* FrameObject::SetPosition(const Point& point) noexcept {
        return SetPosition(point.X, point.Y);
    }

    FrameObject* FrameObject::SetSize(int width, int height) noexcept {
        this->width = width;
        this->height = height;
        return this;
    }

    FrameObject* FrameObject::SetSize(const Size& size) noexcept {
        return SetSize(size.Width, size.Height);
    }

    FrameObject* FrameObject::SetRect(int x, int y, int width, int height) noexcept {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        return this;
    }

    FrameObject* FrameObject::SetRect(const Rect& rect) noexcept {
        return SetRect(rect.X, rect.Y, rect.Width, rect.Height);
    }

    FrameObject* FrameObject::SetProperty(int x, int y, int width, int height, std::string text, Color background) noexcept {
        SetRect(x, y, width, height);
        SetText(std::move(text));
        SetBackground(std::move(background));
        return this;
    }

    int FrameObject::GetX() const noexcept {
        return x;
    }

    int FrameObject::GetY() const noexcept {
        return y;
    }

    int FrameObject::GetWidth() const noexcept {
        return width;
    }

    int FrameObject::GetHeight() const noexcept {
        return height;
    }

    std::string FrameObject::GetText() const noexcept {
        return text;
    }

    Color FrameObject::GetBackground() const noexcept {
        return background;
    }

    Point FrameObject::GetPosition() const noexcept {
        return Point(x, y);
    }

    Size FrameObject::GetSize() const noexcept {
        return Size(width, height);
    }

    Rect FrameObject::GetRect() const noexcept {
        return Rect(x, y, width, height);
    }

    FrameObject* FrameObject::AddMouseListener(const MouseListener& mouseListener) noexcept {
        mouseListeners.push_back(mouseListener);
        return this;
    }

    FrameObject* FrameObject::AddKeyListener(const KeyListener& keyListener) noexcept {
        keyListeners.push_back(keyListener);
        return this;
    }

    FrameObject* FrameObject::AddKeyTypedListener(KeyPressedFunction func) noexcept {
        frameObjectKeyListener.keyTypedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddKeyPressedListener(KeyPressedFunction func) noexcept {
        frameObjectKeyListener.keyPressedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddKeyReleasedListener(KeyPressedFunction func) noexcept {
        frameObjectKeyListener.keyReleasedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddMouseClickedListener(MouseFunction func) noexcept {
        frameObjectMouseListener.mouseClickedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddMousePressedListener(MouseFunction func) noexcept {
        frameObjectMouseListener.mousePressedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddMouseReleasedListener(MouseFunction func) noexcept {
        frameObjectMouseListener.mouseReleasedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddMouseEnteredListener(MouseFunction func) noexcept {
        frameObjectMouseListener.mouseEnteredFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddMouseExitedListener(MouseFunction func) noexcept {
        frameObjectMouseListener.mouseExitedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddMouseWheelMovedListener(MouseFunction func) noexcept {
        frameObjectMouseListener.mouseWheelMovedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddMouseDraggedListener(MouseFunction func) noexcept {
        frameObjectMouseListener.mouseDraggedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject* FrameObject::AddMouseMovedListener(MouseFunction func) noexcept {
        frameObjectMouseListener.mouseMovedFunctions.push_back(std::move(func));
        return this;
    }

    FrameObject::~FrameObject() {}

    FrameObject::FrameObjectKeyListener::FrameObjectKeyListener(FrameObject* owner) : owner(owner) {}

    void FrameObject::FrameObjectKeyListener::KeyTyped(const KeyEvent& keyEvent) {
        for (auto& func : keyTypedFunctions) {
            func(owner, keyEvent);
        }
    }

    void FrameObject::FrameObjectKeyListener::KeyPressed(const KeyEvent& keyEvent) {
        for (auto& func : keyPressedFunctions) {
            func(owner, keyEvent);
        }
    }

    void FrameObject::FrameObjectKeyListener::KeyReleased(const KeyEvent& keyEvent) {
        for (auto& func : keyReleasedFunctions) {
            func(owner, keyEvent);
        }
    }

    FrameObject::FrameObjectMouseListener::FrameObjectMouseListener(FrameObject* owner) : owner(owner) {}

    void FrameObject::FrameObjectMouseListener::MouseClicked(const MouseEvent& mouseEvent) {
        for (auto& func : mouseClickedFunctions) {
            func(owner, mouseEvent);
        }
    }

    void FrameObject::FrameObjectMouseListener::MousePressed(const MouseEvent& mouseEvent) {
        for (auto& func : mousePressedFunctions) {
            func(owner, mouseEvent);
        }
    }

    void FrameObject::FrameObjectMouseListener::MouseReleased(const MouseEvent& mouseEvent) {
        for (auto& func : mouseReleasedFunctions) {
            func(owner, mouseEvent);
        }
    }

    void FrameObject::FrameObjectMouseListener::MouseEntered(const MouseEvent& mouseEvent) {
        for (auto& func : mouseEnteredFunctions) {
            func(owner, mouseEvent);
        }
    }

    void FrameObject::FrameObjectMouseListener::MouseExited(const MouseEvent& mouseEvent) {
        for (auto& func : mouseExitedFunctions) {
            func(owner, mouseEvent);
        }
    }

    void FrameObject::FrameObjectMouseListener::MouseWheelMoved(const MouseEvent& mouseEvent) {
        for (auto& func : mouseWheelMovedFunctions) {
            func(owner, mouseEvent);
        }
    }

    void FrameObject::FrameObjectMouseListener::MouseDragged(const MouseEvent& mouseEvent) {
        for (auto& func : mouseDraggedFunctions) {
            func(owner, mouseEvent);
        }
    }

    void FrameObject::FrameObjectMouseListener::MouseMoved(const MouseEvent& mouseEvent) {
        for (auto& func : mouseMovedFunctions) {
            func(owner, mouseEvent);
        }
    }

}