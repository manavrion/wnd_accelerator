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

    protected:
        bool isInitialized;
        NativeControl* parent;
        std::list<NativeControl*> childs;

        // OS_WIN
        HWND hwnd = 0;

    public:
        virtual ~NativeControl();

    };

}