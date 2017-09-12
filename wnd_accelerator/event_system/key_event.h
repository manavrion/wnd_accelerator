#pragma once
#include "../afx.h"

namespace wnd_accelerator {

    struct KeyEvent {
        enum class EventType {
            keyPressed,
            keyReleased,
            keyTyped
        };
		enum KeyCodes {
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
			delete = 0x2E,
			help = 0x2F,

			0 = 0x30,
			1 = 0x31,
			2 = 0x32,
			3 = 0x33,
			4 = 0x34,
			5 = 0x35,
			6 = 0x36,
			7 = 0x37,
			8 = 0x38,
			9 = 0x39,

			A = 0x41,
			B = 0x42,
			C = 0x43,
			D = 0x44,
			E = 0x45,
			F = 0x46,
			G = 0x47,
			H = 0x48,
			I = 0x49,
			J = 0x4A,
			K = 0x4B,
			L = 0x4C,
			M = 0x4D,
			N = 0x4E,
			O = 0x4F,
			P = 0x50,
			Q = 0x51,
			R = 0x52,
			S = 0x53,
			T = 0x54,
			U = 0x55,
			V = 0x56,
			W = 0x57,
			X = 0x58,
			Y = 0x59,
			Z = 0x5A,

			WINLEFT = 0x5B,
			WINRIGHT = 0x5C,
			APPS = 0x5D,

			NUMPAD0 = 0x60,
			NUMPAD1 = 0x61,
			NUMPAD2 = 0x62,
			NUMPAD3 = 0x63,
			NUMPAD4 = 0x64,
			NUMPAD5 = 0x65,
			NUMPAD6 = 0x66,
			NUMPAD7 = 0x67,
			NUMPAD8 = 0x68,
			NUMPAD9 = 0x69,

			MULTIPLY = 0x6A,
			ADD = 0x6B,
			SEPARATOR = 0x6C,
			SUBTRACT = 0x6D,
			DECIMAL = 0x6E,
			DIVIDE = 0x6F,

			F1 = 0x70,
			F2 = 0x71,
			F3 = 0x72,
			F4 = 0x73,
			F5 = 0x74,
			F6 = 0x75,
			F7 = 0x76,
			F8 = 0x77,
			F9 = 0x78,
			F10 = 0x79,
			F11 = 0x7A,
			F12 = 0x7B,
			F13 = 0x7C,
			F14 = 0x7D,
			F15 = 0x7E,
			F16 = 0x7F,
			F17 = 0x80,
			F18 = 0x81,
			F19 = 0x82,
			F20 = 0x83,
			F21 = 0x84,
			F22 = 0x85,
			F23 = 0x86,
			F24 = 0x87,

			NUMLOCK = 0x90,
			SCROLL = 0x91,

			LSHIFT = 0xA0,
			RSHIFT = 0xA1,
			LCONTROL = 0xA2,
			RCONTROL = 0xA3,
			LALT = 0xA4,
			RALT = 0xA5,

			PLUS = 0xBB, // '+'
			COMMA = 0xBC, // ','
			MINUS = 0xBD, // '-'
			PERIOD = 0xBE, // '.'

			EXPONENT = 0xDC, // '^'

			ATTN = 0xF6,
			CRSEL = 0xF7,
			EXSEL = 0xF8,
			EREOF = 0xF9,
			PLAY = 0xFA,
			ZOOM = 0xFB,
			NONAME = 0xFC,
			PA1 = 0xFD,
			OEMCLEAR = 0xFE,

			MAX = 0x100
		};

        int  keyCode;
        EventType type;
    };

}