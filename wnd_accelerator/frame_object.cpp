#include "frame_object.h"

namespace wnd_accelerator {

    Frame::Frame() :
        x(10), y(10),
        width(100), height(25) {}

    Frame* Frame::SetX(int x) noexcept {
        this->x = x;
        return this;
    }

    Frame* Frame::SetY(int y) noexcept {
        this->y = y;
        return this;
    }

    Frame* Frame::SetWidth(int width) noexcept {
        this->width = width;
        return this;
    }

    Frame* Frame::SetHeight(int height) noexcept {
        this->height = height;
        return this;
    }

    Frame* Frame::SetText(std::string text) noexcept {
        this->text = std::move(text);
        return this;
    }

    Frame* Frame::SetBackground(Color background) noexcept {
        this->background = std::move(background);
        return this;
    }

    Frame* Frame::SetPosition(int x, int y) noexcept {
        this->x = x;
        this->y = y;
        return this;
    }

    Frame* Frame::SetPosition(const Point& point) noexcept {
        return SetPosition(point.X, point.Y);
    }

    Frame* Frame::SetSize(int width, int height) noexcept {
        this->width = width;
        this->height = height;
        return this;
    }

    Frame* Frame::SetSize(const Size& size) noexcept {
        return SetSize(size.Width, size.Height);
    }

    Frame* Frame::SetRect(int x, int y, int width, int height) noexcept {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        return this;
    }

    Frame* Frame::SetRect(const Rect& rect) noexcept {
        return SetRect(rect.X, rect.Y, rect.Width, rect.Height);
    }

    Frame* Frame::SetProperty(int x, int y, int width, int height, std::string text, Color background) noexcept {
        SetRect(x, y, width, height);
        SetText(std::move(text));
        SetBackground(std::move(background));
        return this;
    }

    int Frame::GetX() const noexcept {
        return x;
    }

    int Frame::GetY() const noexcept {
        return y;
    }

    int Frame::GetWidth() const noexcept {
        return width;
    }

    int Frame::GetHeight() const noexcept {
        return height;
    }

    std::string Frame::GetText() const noexcept {
        return text;
    }

    Color Frame::GetBackground() const noexcept {
        return background;
    }

    Point Frame::GetPosition() const noexcept {
        return Point(x, y);
    }

    Size Frame::GetSize() const noexcept {
        return Size(width, height);
    }

    Rect Frame::GetRect() const noexcept {
        return Rect(x, y, width, height);
    }


    Frame::~Frame() {}

}