#pragma once
#include "../afx.h"
#include "event.h"

namespace wnd_accelerator {

    struct KeyEvent : public Event {
		enum class KeyCodes {
			leftMouseButton = 0x01, // Left mouse button
			rightMouseButton = 0x02, // Right mouse button
			cancel = 0x03, // Control-break processing
			middleMouseButton = 0x04, // Middle mouse button (three-button mouse)
			xMouseButton1 = 0x05, // X1 mouse button
			xMouseButtom2 = 0x06, // X2 mouse button
			backspace = 0x08, // BACKSPACE key
			tab = 0x09, // TAB key
			clear = 0x0C, // CLEAR key
			enter = 0x0D, // ENTER key
			shift = 0x10, // SHIFT key
			ctrl = 0x11, // CTRL key
			alt = 0x12, // ALT key
			pause = 0x13, // PAUSE key
			capsLock = 0x14, // CAPS LOCK key

			imeKanaMode = 0x15, // IME Kana mode
			imeHanguelMode = 0x15, // IME Hanguel mode
			imeHangulMode = 0x15, // IME Hangul mode
			imeJunjaMode = 0x17, // IME Junja mode
			imeFinalMode = 0x18, // IME final mode
			imeHanjaMode = 0x19, // IME Hanja mode
			imeKanjiMode = 0x19, // IME Kanji mode

			escape = 0x1B,
			space = 0x20,
			pageUp = 0x21,
			pageDown = 0x22,
			end = 0x23,
			homeE = 0x24,
			leftArrow = 0x25, // left arrow key
			upArrow = 0x26, // up arrow key
			rightArrow = 0x27, // right arrow key
			downArrow = 0x28, // down arrow key
			select = 0x29,
			execute = 0x2B, // execute key
			snapshot = 0x2C,
			insert = 0x2D,
			del = 0x2E,
			help = 0x2F,

			num0 = 0x30,
			num1 = 0x31,
			num2 = 0x32,
			num3 = 0x33,
			num4 = 0x34,
			num5 = 0x35,
			num6 = 0x36,
			num7 = 0x37,
			num8 = 0x38,
			num9 = 0x39,

			alphaA = 0x41,
			alphaB = 0x42,
			alphaC = 0x43,
			alphaD = 0x44,
			alphaE = 0x45,
			alphaF = 0x46,
			alphaG = 0x47,
			alphaH = 0x48,
			alphaI = 0x49,
			alphaJ = 0x4A,
			alphaK = 0x4B,
			alphaL = 0x4C,
			alphaM = 0x4D,
			alphaN = 0x4E,
			alphaO = 0x4F,
			alphaP = 0x50,
			alphaQ = 0x51,
			alphaR = 0x52,
			alphaS = 0x53,
			alphaT = 0x54,
			alphaU = 0x55,
			alphaV = 0x56,
			alphaW = 0x57,
			alphaX = 0x58,
			alphaY = 0x59,
			alphaZ = 0x5A,

			winLeft = 0x5B,
			winRight = 0x5C,
			apps = 0x5D,

			numpad0 = 0x60,
			numpad1 = 0x61,
			numpad2 = 0x62,
			numpad3 = 0x63,
			numpad4 = 0x64,
			numpad5 = 0x65,
			numpad6 = 0x66,
			numpad7 = 0x67,
			numpad8 = 0x68,
			numpad9 = 0x69,

			multiply = 0x6A,
			add = 0x6B,
			separator = 0x6C,
			subtract = 0x6D,
			decimal = 0x6E,
			divide = 0x6F,

			f1 = 0x70,
			f2 = 0x71,
			f3 = 0x72,
			f4 = 0x73,
			f5 = 0x74,
			f6 = 0x75,
			f7 = 0x76,
			f8 = 0x77,
			f9 = 0x78,
			f10 = 0x79,
			f11 = 0x7A,
			f12 = 0x7B,
			f13 = 0x7C,
			f14 = 0x7D,
			f15 = 0x7E,
			f16 = 0x7F,
			f17 = 0x80,
			f18 = 0x81,
			f19 = 0x82,
			f20 = 0x83,
			f21 = 0x84,
			f22 = 0x85,
			f23 = 0x86,
			f24 = 0x87,

			numlock = 0x90,
			scroll = 0x91,

			lShift = 0xA0,
			rShift = 0xA1,
			lControl = 0xA2,
			rControl = 0xA3,
			lAlt = 0xA4,
			rAlt = 0xA5,

			plus = 0xBB, // '+'
			comma = 0xBC, // ','
			minus = 0xBD, // '-'
			period = 0xBE, // '.'

			exponent = 0xDC, // '^'

			attn = 0xF6,
			crsel = 0xF7,
			exsel = 0xF8,
			ereof = 0xF9,
			play = 0xFA,
			zoom = 0xFB,
			noname = 0xFC,
			pa1 = 0xFD,
			oemclear = 0xFE,

			max = 0x100
		};

        KeyCodes keyCode;
        wchar_t key;
    };

}