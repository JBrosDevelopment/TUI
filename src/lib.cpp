#include "lib.hpp"
#include <stdio.h>
#include <windows.h>

void TUI::init() {
    key_events.reserve(1);
    set_event_key(EXIT_KEY_EVENT, VK_ESCAPE, KeyModifiers::KeyModifierShift);
    running = true;
}
void TUI::clear_screen() {
    printf("\033[2J");
}

bool TUI::is_running() {
    return running;
}

void TUI::exit() {
    running = false;
}

void TUI::set_event_key(int event_id, int virtual_key, int modifier) {
    key_events.push_back(KeyEvent{event_id, virtual_key, modifier});
}

void TUI::actions() {
    check_exit();
}

void TUI::check_exit() {
    const KeyEvent& exit_event = key_events[EXIT_KEY_EVENT];

    if (!(GetKeyState(exit_event.key) & 0x8000)) {
        return;
    }

    if (exit_event.modifier == KeyModifierNone || is_modifier_pressed(exit_event.modifier)) {
        exit();
    }
}

bool TUI::is_modifier_pressed(int mod) {
    bool shift_down = GetKeyState(VK_SHIFT) & 0x8000;
    bool control_down = GetKeyState(VK_CONTROL) & 0x8000;
    bool alt_down = GetKeyState(VK_MENU) & 0x8000;

    if ((mod & KeyModifierShift) && !shift_down) return false;
    if ((mod & KeyModifierControl) && !control_down) return false;
    if ((mod & KeyModifierAlt) && !alt_down) return false;

    return true;
}