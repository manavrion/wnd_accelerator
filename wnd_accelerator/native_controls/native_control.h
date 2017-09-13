#pragma once
#include "../afx.h"
#include "../frame_object.h"
#include <list>

namespace wnd_accelerator {

    class NativeControl : public Frame {
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

        virtual Frame* AddMouseClickListener(MouseEventFunction func) noexcept;
        virtual Frame* AddMouseMoveListener(MouseEventFunction func) noexcept;

        virtual Frame* AddLeftMouseButtonPressListener(MouseEventFunction func) noexcept;
        virtual Frame* AddMiddleMouseButtonPressListener(MouseEventFunction func) noexcept;
        virtual Frame* AddRightMouseButtonPressListener(MouseEventFunction func) noexcept;

        virtual Frame* AddLeftMouseButtonReleaseListener(MouseEventFunction func) noexcept;
        virtual Frame* AddMiddleMouseButtonReleaseListener(MouseEventFunction func) noexcept;
        virtual Frame* AddRightMouseButtonReleaseListener(MouseEventFunction func) noexcept;

        // TODO
        virtual Frame* AddMouseEnterListener(MouseEventFunction func) noexcept;
        virtual Frame* AddMouseExitListener(MouseEventFunction func) noexcept;
        virtual Frame* AddMouseWheelMoveListener(MouseEventFunction func) noexcept;
        virtual Frame* AddMouseDragListener(MouseEventFunction func) noexcept;

        virtual Frame* AddKeyTypeListener(KeyEventFunction func) noexcept;
        virtual Frame* AddKeyPressListener(KeyEventFunction func) noexcept;
        virtual Frame* AddKeyReleaseListener(KeyEventFunction func) noexcept;

    protected:
        virtual void Init(NativeControl* parent) = 0;
        virtual void PackImpl() = 0;

        struct Listeners {
            using KeyEventFunctionsList = std::list<std::pair<Frame*, KeyEventFunction>>;
            using MouseEventFunctionsList = std::list<std::pair<Frame*, MouseEventFunction>>;
            Listeners() = default;
            Listeners(const Listeners&) = default;
            Listeners(Listeners&&) = default;
            ~Listeners() = default;

            std::unordered_map<Event::Type, KeyEventFunctionsList> keyEventsMap;
            std::unordered_map<Event::Type, MouseEventFunctionsList> mouseEventsMap;
        };
        virtual void MergeListeners(std::unique_ptr<Listeners> listeners);

        // static
		friend LRESULT CALLBACK windowProcMapper(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

        virtual LRESULT WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        bool isInitialized;
        NativeControl* parent;
        std::list<NativeControl*> childs;
        std::unique_ptr<Listeners> listeners; // Need to keep event listeners before parent set

        // OS_WIN
        HWND hWindow = 0;

    public:
        virtual ~NativeControl();

    };

}