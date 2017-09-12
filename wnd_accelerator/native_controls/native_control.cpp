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

	void NativeControl::NotifyMouseClicked(const MouseEvent& mouseEvent) {
		for (auto& mouseListener : mouseListeners) {
			mouseListener.MousePressed(mouseEvent);
		}
		for (auto& child : childs) {
			child->NotifyMousePressed(mouseEvent);
		}
	}

	void NativeControl::NotifyMousePressed(const MouseEvent& mouseEvent) {
		for (auto& mouseListener : mouseListeners) {
			mouseListener.MouseClicked(mouseEvent);
		}
		for (auto& child : childs) {
			child->NotifyMouseClicked(mouseEvent);
		}
	}

	void NativeControl::NotifyMouseReleased(const MouseEvent& mouseEvent) {
		for (auto& mouseListener : mouseListeners) {
			mouseListener.MouseReleased(mouseEvent);
		}
		for (auto& child : childs) {
			child->NotifyMouseReleased(mouseEvent);
		}
	}

	void NativeControl::NotifyMouseEntered(const MouseEvent& mouseEvent) {
		for (auto& mouseListener : mouseListeners) {
			mouseListener.MouseEntered(mouseEvent);
		}
		for (auto& child : childs) {
			child->NotifyMouseEntered(mouseEvent);
		}
	}

	void NativeControl::NotifyMouseExited(const MouseEvent& mouseEvent) {
		for (auto& mouseListener : mouseListeners) {
			mouseListener.MouseExited(mouseEvent);
		}
		for (auto& child : childs) {
			child->NotifyMouseExited(mouseEvent);
		}
	}

	void NativeControl::NotifyMouseWheelMoved(const MouseEvent& mouseEvent) {
		for (auto& mouseListener : mouseListeners) {
			mouseListener.MouseWheelMoved(mouseEvent);
		}
		for (auto& child : childs) {
			child->NotifyMouseWheelMoved(mouseEvent);
		}
	}

	void NativeControl::NotifyMouseDragged(const MouseEvent& mouseEvent) {
		for (auto& mouseListener : mouseListeners) {
			mouseListener.MouseDragged(mouseEvent);
		}
		for (auto& child : childs) {
			child->NotifyMouseDragged(mouseEvent);
		}
	}

	void NativeControl::NotifyMouseMoved(const MouseEvent& mouseEvent) {
		for (auto& mouseListener : mouseListeners) {
			mouseListener.MouseMoved(mouseEvent);
		}
		for (auto& child : childs) {
			child->NotifyMouseMoved(mouseEvent);
		}
	}

	void NativeControl::NotifyKeyTyped(const KeyEvent& keyEvent) {
		for (auto& keyListener : keyListeners) {
			keyListener.KeyTyped(keyEvent);
		}
		for (auto& child : childs) {
			child->NotifyKeyTyped(keyEvent);
		}
	}

	void NativeControl::NotifyKeyPressed(const KeyEvent& keyEvent) {
		for (auto& keyListener : keyListeners) {
			keyListener.KeyPressed(keyEvent);
		}
		for (auto& child : childs) {
			child->NotifyKeyPressed(keyEvent);
		}
	}

	void NativeControl::NotifyKeyReleased(const KeyEvent& keyEvent) {
		for (auto& keyListener : keyListeners) {
			keyListener.KeyReleased(keyEvent);
		}
		for (auto& child : childs) {
			child->NotifyKeyReleased(keyEvent);
		}
	}

    NativeControl::~NativeControl() {
    }

}