#include "window.h"

namespace wnd_accelerator {

    Window::Window() {}

    // You must use Update() to apply the size and position changes
    void Window::Update() {
        UpdateImpl();
        Repaint();
    }


    void Window::CreateBuffer() {
        if (buffer || graphics) {
            DeleteBuffer();
        }
        buffer = new Gdiplus::Bitmap(width+10, height+10);
        graphics = new Gdiplus::Graphics(buffer);
    }

    void Window::DeleteBuffer() {
        delete graphics;
        delete buffer;
    }

    void Window::ResizeBuffer() {
        /*if (!(buffer->GetWidth() == width && buffer->GetHeight() == height)) {
        CreateBuffer();
        }*/
    }

    Window::~Window() {
        DeleteBuffer();
    }

}
