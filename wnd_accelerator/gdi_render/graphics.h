#pragma once
#include "../afx.h"
#include "../frame.h"

#include <utility>
#include <string>

namespace wnd_accelerator {

    class Graphics final {
    public:
        Graphics(const Graphics &graphics)
            : ptr(graphics.ptr),
            dx(graphics.dx),
            dy(graphics.dy) {}
        Graphics(Gdiplus::Graphics* ptr, int dx, int dy)
            : ptr(ptr), dx(dx), dy(dy) {}
        Graphics(const Graphics &graphics, Frame* frame)
            : ptr(graphics.ptr), 
            dx(graphics.dx + frame->GetX()), 
            dy(graphics.dy + frame->GetY()) {}
        ~Graphics() {}


        void FillRectangle(Brush* brush, Rect rect) {
            rect.X += dx;
            rect.Y += dy;
            ptr->FillRectangle(brush, rect);
        }

        void DrawString(std::wstring text, Font* font, PointF point, Brush* brush) {
            point.X += dx;
            point.Y += dy;

            ptr->DrawString(text.c_str(), -1, font, PointF(50, 13), brush);
        }

        void DrawString(std::string text, Font* font, PointF point, Brush* brush) {
            point.X += dx;
            point.Y += dy;

            ptr->DrawString(std::wstring(text.begin(), text.end()).c_str(), -1, font, point, brush);
        }

        void DrawImage(Image *image, int x, int y, int width, int height) {
            x += dx;
            y += dy;
            ptr->DrawImage(image, x, y, width, height);
        }

        void Clear(Color color) {
            ptr->Clear(color);
        }

    private:
        Gdiplus::Graphics* ptr;
        int dx;
        int dy;
    };

}