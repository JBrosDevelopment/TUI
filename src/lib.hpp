#ifndef LIB_H
#define LIB_H

#include <vector>
#include "renderer.hpp"
#include "KeyState.h"

enum KeyModifiers {
    KeyModifierNone = 0,
    KeyModifierShift = 1,
    KeyModifierControl = 2,
    KeyModifierAlt = 4,
};

typedef struct {
    std::string id;
    int key;
    int modifier;
} KeyEvent;

class TUI {
public:
    void init();
    void clear_screen();
    bool is_running();
    void set_event_key(std::string name, int virtual_key, int modifier);
    void actions();
    void exit();
    bool is_event_hit(std::string id);
    Renderer renderer;
    std::vector<std::string> hit_events;
    
private:
    void check_events();
    bool is_modifier_pressed(int mod);
    bool running;
    std::vector<KeyEvent> key_events;
};


#endif // LIB_H
