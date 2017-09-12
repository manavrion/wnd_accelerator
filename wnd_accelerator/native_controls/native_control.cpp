#include "native_control.h"

namespace wnd_accelerator {

    NativeControl::NativeControl() :
        isInitialized(false),
        parent(nullptr) {}

    std::list<NativeControl*>& NativeControl::GetChilds() {
        return childs;
    }

    NativeControl* NativeControl::Add(NativeControl* child) {
        child->parent = this;
        childs.push_back(child);
        return this;
    }

     NativeControl* NativeControl::GetParent() {
        return parent;
    }

    void NativeControl::ClearChilds() {
        while (!childs.empty()) {
            delete childs.front();
            childs.erase(childs.begin());
        }
    }

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

}