#include "native_control.h"

#include <unordered_map>

namespace wnd_accelerator {

    NativeControl::NativeControl() :
        isInitialized(false),
        parent(nullptr) {}

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

    NativeControl::~NativeControl() {
    }

}