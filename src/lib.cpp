#include "lib.hpp"
#include <stdio.h>
#include <windows.h>

void TUI::init() {
    key_events.reserve(1);
    SetConsoleOutputCP(CP_UTF8);
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
    printf("\033[39m\033[49m\n");
    
}

void TUI::set_event_key(std::string name, int key, int modifier) {
    key_events.push_back(KeyEvent{name, key, modifier});
}

void TUI::actions() {
    check_events();
    renderer.draw_boxes();
}

bool TUI::is_event_hit(std::string name) {
    for (int i = 0; i < (int)hit_events.size(); i++) {
        if (hit_events[i] == name) return true;
    }
    return false;
}

void TUI::check_events() {
    hit_events.clear();
    for (int i = 0; i < (int)key_events.size(); i++) {
        const KeyEvent& event = key_events[i];
        if (!(GetKeyState(event.key) & 0x8000)) {
            return;
        }
    
        if (event.modifier == KeyModifierNone || is_modifier_pressed(event.modifier)) {
            hit_events.push_back(event.id);
        }
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