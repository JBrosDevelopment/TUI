#pragma once
#include <cstdint>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
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

    // Check modifier keys using GetAsyncKeyState
    if (key == KEY_SHIFT) return (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    if (key == KEY_CTRL) return (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
    if (key == KEY_ALT) return (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;

    // Return and reset the key state (so you only get it once per press)
    bool pressed = keyStates[key];
    keyStates[key] = false;
    return pressed;
}

#else

// Simple implementation for non-Windows systems without external dependencies
inline bool GetKeyState(KeyCode key) {
    static struct termios oldt, newt;
    static bool initialized = false;

    if (!initialized) {
        // Save the terminal settings
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        initialized = true;
    }

    // Set non-blocking mode
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    char c = 0;
    if (read(STDIN_FILENO, &c, 1) > 0) {
        // Restore blocking mode
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        // Map basic keys
        if (c >= 'A' && c <= 'Z') return key == (KeyCode)(KEY_A + (c - 'A'));
        if (c >= 'a' && c <= 'z') return key == (KeyCode)(KEY_A + (c - 'a'));
        if (c == 27) return key == KEY_ESC;
        if (c == 13) return key == KEY_ENTER;
        if (c == ' ') return key == KEY_SPACE;
    }

    // Restore blocking mode
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    return false;
}

#endif
