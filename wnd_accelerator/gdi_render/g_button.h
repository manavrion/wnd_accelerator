#pragma once
#include "gdi_control.h"

namespace wnd_accelerator {

    class GButton : public GdiControl {
    public:
        GButton() {
            background = Color(50, 50, 50);
            AddMouseEnterListener([&]() {
                background = Color(80, 80, 80);
                Repaint();
            });
            AddMouseExitListener([&]() {
                background = Color(50, 50, 50);
                Repaint();
            });
            AddLeftMouseButtonPressListener([&]() {
                background = Color(100, 100, 100);
                Repaint();
            });
            AddLeftMouseButtonReleaseListener([&]() {
                background = Color(80, 80, 80);
                Repaint();
            });
        }
        virtual ~GButton() {}

    protected:
        virtual void PaintPre(Graphics graphics) {
            graphics.FillRectangle(&SolidBrush(background), Rect(0, 0, width, height));
            graphics.DrawString(text, &Font(L"Arial", 16), PointF(50, 13), &SolidBrush(Color(255, 255, 255)));
        }
        virtual void PaintPost(Graphics graphics) {}
    };

}