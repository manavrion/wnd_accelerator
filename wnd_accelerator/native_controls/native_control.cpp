#include "native_control.h"

#include <unordered_map>

namespace wnd_accelerator {

    NativeControl::NativeControl() :
        isInitialized(false),
        parent(nullptr),
        listeners(new Listeners) {}

    void NativeControl::Pack() {
        this->PackImpl();
        for (auto child : childs) {
            child->Pack();
        };
    }

    void NativeControl::Build() {
        this->Init(parent);
        for (auto child : childs) {
            child->Build();
        }
    }

    NativeControl* NativeControl::Add(NativeControl* child) {
        child->parent = this;
        childs.push_back(child);
        this->MergeListeners(std::move(child->listeners));
        child->listeners.reset();
        return this;
    }

    std::list<NativeControl*>& NativeControl::GetChilds() noexcept {
        return childs;
    }

     NativeControl* NativeControl::GetParent() noexcept {
        return parent;
    }

    void NativeControl::ClearChilds() {
        while (!childs.empty()) {
            delete childs.front();
            childs.erase(childs.begin());
        }
    }

    bool NativeControl::IsInitialized() const noexcept {
        return isInitialized;
    }

    Frame* NativeControl::AddMouseClickListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddMouseClickListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseClick].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddMouseMoveListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddMouseMoveListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseMove].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddLeftMouseButtonPressListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddLeftMouseButtonPressListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::leftMouseButtonPress].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddMiddleMouseButtonPressListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddMiddleMouseButtonPressListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::middleMouseButtonPress].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddRightMouseButtonPressListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddRightMouseButtonPressListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::rightMouseButtonPress].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddLeftMouseButtonReleaseListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddLeftMouseButtonReleaseListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::leftMouseButtonRelease].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddMiddleMouseButtonReleaseListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddMiddleMouseButtonReleaseListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::middleMouseButtonRelease].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddRightMouseButtonReleaseListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddRightMouseButtonReleaseListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::rightMouseButtonRelease].push_back({this, std::move(func)});
        return this;
    }

    // TODO

    Frame* NativeControl::AddMouseEnterListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddMouseEnterListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseEnter].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddMouseExitListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddMouseExitListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseExit].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddMouseWheelMoveListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddMouseWheelMoveListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseMove].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddMouseDragListener(MouseEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddMouseDragListener(func);
            return this;
        }
        listeners->mouseEventsMap[Event::Type::mouseDrag].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddKeyTypeListener(KeyEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddKeyTypeListener(func);
            return this;
        }
        listeners->keyEventsMap[Event::Type::keyType].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddKeyPressListener(KeyEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddKeyPressListener(func);
            return this;
        }
        listeners->keyEventsMap[Event::Type::keyPress].push_back({this, std::move(func)});
        return this;
    }

    Frame* NativeControl::AddKeyReleaseListener(KeyEventFunction func) noexcept {
        if (listeners == nullptr) {
            parent->AddKeyReleaseListener(func);
            return this;
        }
        listeners->keyEventsMap[Event::Type::keyRelease].push_back({this, std::move(func)});
        return this;
    }

    void NativeControl::MergeListeners(std::unique_ptr<Listeners> listeners) {
        listeners->keyEventsMap.insert(listeners->keyEventsMap.begin(), listeners->keyEventsMap.end());
        listeners->mouseEventsMap.insert(listeners->mouseEventsMap.begin(), listeners->mouseEventsMap.end());
    }

    NativeControl::~NativeControl() {
    }

}