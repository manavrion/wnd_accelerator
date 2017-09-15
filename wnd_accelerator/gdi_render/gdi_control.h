#pragma once
#include "../frame.h"

namespace wnd_accelerator {

    class GdiControl : public Frame {
    public:
        GdiControl();
        GdiControl(const GdiControl&) = delete;
        GdiControl(GdiControl&&) = delete;
        GdiControl& operator=(const GdiControl&) = delete;
        virtual ~GdiControl();

    protected:
        // Build real frame
        virtual void BuildImpl();

        // Apply resize and reposition
        virtual void UpdateImpl();

        // Some painting operations of this object
        virtual void Paint() final;

        // Next methoods called by Paint()
        virtual void PaintPre(Graphics* graphics) = 0;
        virtual void PaintChildBuffers(Graphics* graphics);
        virtual void PaintPost(Graphics* graphics) = 0;

        void CreateBuffer();
        void DeleteBuffer();
        void ResizeBuffer();

    protected:
        Bitmap* buffer;
        Graphics* graphics;
    };

}