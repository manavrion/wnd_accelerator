#pragma once
#include "afx.h"

namespace wnd_accelerator {

    struct IRect {
        virtual int GetX() const = 0;
        virtual int GetY() const = 0;
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
    };

}