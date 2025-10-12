#ifndef LIB_H
#define LIB_H

#include <vector>

#define ESCAPE 0x1B
#define ENTER 0x0D
#define SHIFT 0x10
#define CONTROL 0x11
#define SPACE 0x20
#define END 0x23
#define HOME 0x24
#define LEFT 0x25
#define UP 0x26
#define RIGHT 0x27
#define DOWN 0x28
#define INSERT 0x2D
#define DELETE 0x2E

#define EXIT_KEY_EVENT 0

enum KeyModifiers {
    KeyModifierNone = 0,
    KeyModifierShift = 1,
    KeyModifierControl = 2,
    KeyModifierAlt = 4,
};

typedef struct {
    int event_id;
    int key;
    int modifier;
} KeyEvent;

class TUI {
public:
    void init();
    void clear_screen();
    bool is_running();
    void set_event_key(int event_id, int virtual_key, int modifier);
    void actions();
    void exit();

private:
    void check_exit();
    bool is_modifier_pressed(int mod);
    bool running;
    std::vector<KeyEvent> key_events;
};


#endif // LIB_H
