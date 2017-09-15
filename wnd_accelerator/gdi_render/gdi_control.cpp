#include "gdi_control.h"

namespace wnd_accelerator {

    GdiControl::GdiControl() : buffer(), graphics() {}

    GdiControl::~GdiControl() {
        DeleteBuffer();
    }

    // Build real frame
    void GdiControl::BuildImpl() {
        CreateBuffer();
    }

    // Apply resize and reposition
    void GdiControl::UpdateImpl() {
        ResizeBuffer();
    }

    // Some painting operations of this object
    void GdiControl::Paint() {
        PaintPre(graphics);
        PaintChildBuffers(graphics);
        PaintPost(graphics);
    }

    void GdiControl::PaintChildBuffers(Graphics* graphics) {
        for (auto child : childs) {
            graphics->DrawImage(((GdiControl*)child)->buffer, child->GetRect());
        }
    }

    void GdiControl::CreateBuffer() {
        if (buffer || graphics) {
            DeleteBuffer();
        }        
        buffer = new Gdiplus::Bitmap(width, height);
        graphics = new Gdiplus::Graphics(buffer);
    }

    void GdiControl::DeleteBuffer() {
        delete graphics;
        delete buffer;
    }

    void GdiControl::ResizeBuffer() {
        if (!(buffer->GetWidth() == width && buffer->GetHeight() == height)) {
            CreateBuffer();
        }
    }

}