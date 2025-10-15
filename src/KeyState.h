#pragma once
#include <cstdint>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
    #include <unistd.h>
#endif

enum KeyCode {
    KEY_UNKNOWN = 0,
    KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
    KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
    KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
    KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
    KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN,
    KEY_SHIFT, KEY_CTRL, KEY_ALT,
    KEY_SPACE, KEY_ENTER, KEY_ESC
};

#ifdef _WIN32

// Windows Implementation using <conio.h>
inline bool GetKeyState(KeyCode key) {
    static bool keyStates[256] = { false }; // keeps last pressed state

    // If a key was pressed, update its state
    if (_kbhit()) {
        int c = _getch();

        // handle escape codes for arrows
        if (c == 0 || c == 224) {
            int special = _getch();
            switch (special) {
                case 72: keyStates[KEY_UP] = true; break;    // up arrow
                case 80: keyStates[KEY_DOWN] = true; break;  // down arrow
                case 75: keyStates[KEY_LEFT] = true; break;  // left arrow
                case 77: keyStates[KEY_RIGHT] = true; break; // right arrow
            }
            return false;
        }

        // Normal keys
        if (c >= 'A' && c <= 'Z') keyStates[c - 'A' + KEY_A] = true;
        else if (c >= 'a' && c <= 'z') keyStates[c - 'a' + KEY_A] = true;
        else if (c == 27) keyStates[KEY_ESC] = true;
        else if (c == 13) keyStates[KEY_ENTER] = true;
        else if (c == ' ') keyStates[KEY_SPACE] = true;
    }

    // Return and reset the key state (so you only get it once per press)
    bool pressed = keyStates[key];
    keyStates[key] = false;
    return pressed;
}

#else
// Linux (X11) implementation
inline bool GetKeyState(KeyCode key) {
    static Display* display = XOpenDisplay(nullptr);
    if (!display) return false;

    char keys[32];
    XQueryKeymap(display, keys);

    KeySym ks = 0;
    switch (key) {
        case KEY_A: ks = XK_a; break;
        case KEY_B: ks = XK_b; break;
        case KEY_C: ks = XK_c; break;
        case KEY_D: ks = XK_d; break;
        case KEY_E: ks = XK_e; break;
        case KEY_F: ks = XK_f; break;
        case KEY_G: ks = XK_g; break;
        case KEY_H: ks = XK_h; break;
        case KEY_I: ks = XK_i; break;
        case KEY_J: ks = XK_j; break;
        case KEY_K: ks = XK_k; break;
        case KEY_L: ks = XK_l; break;
        case KEY_M: ks = XK_m; break;
        case KEY_N: ks = XK_n; break;
        case KEY_O: ks = XK_o; break;
        case KEY_P: ks = XK_p; break;
        case KEY_Q: ks = XK_q; break;
        case KEY_R: ks = XK_r; break;
        case KEY_S: ks = XK_s; break;
        case KEY_T: ks = XK_t; break;
        case KEY_U: ks = XK_u; break;
        case KEY_V: ks = XK_v; break;
        case KEY_W: ks = XK_w; break;
        case KEY_X: ks = XK_x; break;
        case KEY_Y: ks = XK_y; break;
        case KEY_Z: ks = XK_z; break;
        case KEY_LEFT:   ks = XK_Left; break;
        case KEY_RIGHT:  ks = XK_Right; break;
        case KEY_UP:     ks = XK_Up; break;
        case KEY_DOWN:   ks = XK_Down; break;
        case KEY_SHIFT:  ks = XK_Shift_L; break;
        case KEY_CTRL:   ks = XK_Control_L; break;
        case KEY_ALT:    ks = XK_Alt_L; break;
        case KEY_SPACE:  ks = XK_space; break;
        case KEY_ENTER:  ks = XK_Return; break;
        case KEY_ESC:    ks = XK_Escape; break;
        default: return false;
    }

    KeyCode kc = XKeysymToKeycode(display, ks);
    return (keys[kc >> 3] & (1 << (kc & 7))) != 0;
}
#endif
