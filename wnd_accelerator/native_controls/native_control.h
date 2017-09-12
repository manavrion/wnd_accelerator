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

    protected:
        bool isInitialized;
        NativeControl* parent;
        std::list<NativeControl*> childs;

        virtual void Init(NativeControl* parent) = 0;
        virtual void PackImpl() = 0;

    public:

        std::list<NativeControl*>& GetChilds();
        NativeControl* Add(NativeControl* child);
        NativeControl* GetParent();
        void ClearChilds();

        virtual void Pack();
        void Build();

        virtual bool IsInitialized() const = 0;
        virtual void Repaint() = 0;

    public:
        virtual ~NativeControl() { }

    };

}