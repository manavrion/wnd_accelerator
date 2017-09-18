#include "gdi_control.h"
#include "graphics.h"

namespace wnd_accelerator {

    GdiControl::GdiControl() {}

    GdiControl::~GdiControl() {}

    // Build real frame
    void GdiControl::BuildImpl() {}

    // Apply resize and reposition
    void GdiControl::UpdateImpl() {}

    // Some painting operations of this object
    void GdiControl::Paint(Graphics graphics) {
        paint = false;
        PaintPre(graphics);
        PaintChildBuffers(graphics);
        PaintPost(graphics);
    }

    void GdiControl::PaintChildBuffers(Graphics graphics) {
        for (auto child : childs) {
            if (((GdiControl*)child)->paint) {
                child->Paint(Graphics(graphics, child));
            }
        }
    }

}