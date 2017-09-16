#include "window.h"

namespace wnd_accelerator {

    Window::Window() {}

    // You must use Update() to apply the size and position changes
    void Window::Update() {
        UpdateImpl();
        Repaint();
    }

    Window::~Window() {}

}
