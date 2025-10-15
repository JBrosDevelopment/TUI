#include "../src/lib.hpp"

int main() {
    TUI tui;
    tui.init();
    tui.clear_screen();

    GraphicsBox box("Test", 8, 5, 22, 8, BorderType::BorderTypeSingle, C_RGB(100, 200, 255), C_RGB(255, 200, 100));
    tui.renderer.add_box(box);

    GraphicsObjectLine* line = box.add_line(&tui.renderer, 1, 1, 5, 5, 1, C_RGB(255, 0, 0));

    int x, y, w, h;
    box.get_position_size(&x, &y, &w, &h);

    tui.set_event_key("exit", KEY_ESC, KeyModifierNone);
    tui.set_event_key("move-left", KEY_LEFT, KeyModifierNone);
    tui.set_event_key("move-right", KEY_RIGHT, KeyModifierNone);
    tui.set_event_key("move-up", KEY_UP, KeyModifierNone);
    tui.set_event_key("move-down", KEY_DOWN, KeyModifierNone);
    tui.set_event_key("size-left", KEY_LEFT, KeyModifierControl);
    tui.set_event_key("size-right", KEY_RIGHT, KeyModifierControl);
    tui.set_event_key("size-up", KEY_UP, KeyModifierControl);
    tui.set_event_key("size-down", KEY_DOWN, KeyModifierControl);
    
    int position_x, position_y;
    tui.set_event_key("position-left", KEY_LEFT, KeyModifierShift);
    tui.set_event_key("position-right", KEY_RIGHT, KeyModifierShift);
    tui.set_event_key("position-up", KEY_UP, KeyModifierShift);
    tui.set_event_key("position-down", KEY_DOWN, KeyModifierShift);

    while (tui.is_running()) {
        tui.actions();
        if (tui.is_event_hit("exit")) tui.exit();

        for (auto event : tui.hit_events) {
            if (event == "move-left") x--;
            if (event == "move-right") x++;
            if (event == "move-up") y--;
            if (event == "move-down") y++;
            if (event == "size-left") w--;
            if (event == "size-right") w++;
            if (event == "size-up") h--;
            if (event == "size-down") h++;
            if (event == "position-left") position_x--;
            if (event == "position-right") position_x++;
            if (event == "position-up") position_y--;
            if (event == "position-down") position_y++;
        }

        box.move(&tui.renderer, x, y);
        box.resize(&tui.renderer, w, h);
    }
    
    return 0;
}