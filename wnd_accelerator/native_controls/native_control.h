#pragma once
#include "../afx.h"
#include "../frame_object.h"
#include <list>

namespace wnd_accelerator {

    class NativeControl : public FrameObject {
    public:
        NativeControl();
        NativeControl(const NativeControl& abstructNativeControl) = delete;
        NativeControl(NativeControl&& abstructNativeControl) = delete;

        virtual void Pack() final;
        virtual void Build() final;

        NativeControl* Add(NativeControl* child);
        std::list<NativeControl*>& GetChilds() noexcept;
        NativeControl* GetParent() noexcept;
        void ClearChilds();       

        bool IsInitialized() const noexcept;

    protected:
        virtual void Init(NativeControl* parent) = 0;
        virtual void PackImpl() = 0;

		virtual void NotifyMouseClicked(const MouseEvent& mouseEvent);
		virtual void NotifyMousePressed(const MouseEvent& mouseEvent);
		virtual void NotifyMouseReleased(const MouseEvent& mouseEvent);
		virtual void NotifyMouseEntered(const MouseEvent& mouseEvent);
		virtual void NotifyMouseExited(const MouseEvent& mouseEvent);
		virtual void NotifyMouseWheelMoved(const MouseEvent& mouseEvent);
		virtual void NotifyMouseDragged(const MouseEvent& mouseEvent);
		virtual void NotifyMouseMoved(const MouseEvent& mouseEvent);

		virtual void NotifyKeyTyped(const KeyEvent& keyEvent);
		virtual void NotifyKeyPressed(const KeyEvent& keyEvent);
		virtual void NotifyKeyReleased(const KeyEvent& keyEvent);

		friend LRESULT CALLBACK windowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        bool isInitialized;
        NativeControl* parent;
        std::list<NativeControl*> childs;

        // OS_WIN
        HWND hWindow = 0;

    public:
        virtual ~NativeControl();

    };

}