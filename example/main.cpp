#include "../src/lib.hpp"

int main() {
    TUI tui;
    tui.init();
    tui.clear_screen();

    while (tui.is_running()) {
        tui.actions();
    }
    
    return 0;
}
