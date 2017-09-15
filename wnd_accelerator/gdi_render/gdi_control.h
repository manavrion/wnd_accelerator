#pragma once
#include "../frame.h"

namespace wnd_accelerator {

    class GdiControl : public Frame {
    public:
        GdiControl();
        GdiControl(const GdiControl&) = delete;
        GdiControl(GdiControl&&) = delete;

        // Build real frame
        virtual void BuildImpl();

        // Apply resize and reposition
        virtual void UpdateImpl();

        // Some painting operations of this object
        virtual void Paint();




        virtual ~GdiControl() {}

    private:

    };

}