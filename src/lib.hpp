#ifndef LIB_H
#define LIB_H

#include <vector>
#include "renderer.hpp"

#define K_ESCAPE 0x1B
#define K_ENTER 0x0D
#define K_SHIFT 0x10
#define K_CONTROL 0x11
#define K_SPACE 0x20
#define K_END 0x23
#define K_HOME 0x24
#define K_LEFT 0x25
#define K_UP 0x26
#define K_RIGHT 0x27
#define K_DOWN 0x28
#define K_INSERT 0x2D
#define K_DELETE 0x2E

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
