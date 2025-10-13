#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>

#define C_FILL u8"\u2588"
#define C_EMPTY u8"\u2591"
#define C_L u8"\u258C"
#define C_R u8"\u2590"
#define C_T u8"\u2580"
#define C_B u8"\u2584"
#define C_LT u8"\u2598"
#define C_RT u8"\u259D"
#define C_LB u8"\u2596"
#define C_RB u8"\u2597"
#define C_LB_RT u8"\u259E"
#define C_LT_RB u8"\u259A"
#define C_LT_RT_RB u8"\u259C"
#define C_LB_LT_RT u8"\u259B"
#define C_RB_LB_LT u8"\u2599"
#define C_RT_RB_LB u8"\u259F"

#define C_Box_H_Line u8"\u2500"
#define C_Box_V_Line u8"\u2502"
#define C_Box_TL_Corner u8"\u250C"
#define C_Box_TR_Corner u8"\u2510"
#define C_Box_BL_Corner u8"\u2514"
#define C_Box_BR_Corner u8"\u2518"
#define C_Box_L_Juntion u8"\u251C"
#define C_Box_R_Juntion u8"\u2524"
#define C_Box_T_Juntion u8"\u252C"
#define C_Box_B_Juntion u8"\u2534"
#define C_Box_Intersection u8"\u253C"

#define C_DoubleBox_H_Line u8"\u2550"
#define C_DoubleBox_V_Line u8"\u2551"
#define C_DoubleBox_TL_Corner u8"\u2554"
#define C_DoubleBox_TR_Corner u8"\u2557"
#define C_DoubleBox_BL_Corner u8"\u255A"
#define C_DoubleBox_BR_Corner u8"\u255D"
#define C_DoubleBox_L_Juntion u8"\u2560"
#define C_DoubleBox_R_Juntion u8"\u2563"
#define C_DoubleBox_T_Juntion u8"\u2566"
#define C_DoubleBox_B_Juntion u8"\u2569"
#define C_DoubleBox_Intersection u8"\u256C"

enum BorderType {
    BorderTypeNone = 0,
    BorderTypeSingle = 1,
    BorderTypeDouble = 2
};

typedef struct {
    unsigned char r, g, b;
} Color;

constexpr Color C_RGB(unsigned char r, unsigned char g, unsigned char b) {
    return Color{r, g, b};
}

constexpr Color RED   = C_RGB(255, 0, 0);
constexpr Color GREEN = C_RGB(0, 255, 0);
constexpr Color BLUE  = C_RGB(0, 0, 255);
constexpr Color WHITE = C_RGB(255, 255, 255);
constexpr Color BLACK = C_RGB(0, 0, 0);

struct GraphicsObjectLine {
    int x1, y1, x2, y2;
    int width;
    Color color;
};

struct GraphicsObjectCurve {
    std::vector<std::pair<int, int>> points;
    int width;
    Color color;
};

struct GraphicsObjectPolygon {
    int x, y, w, h;
    int sides;
    Color color;
};

struct GraphicsObjectText {
    int x, y;
    std::string text;
    Color color;
};

struct GraphicsObjectMap {
    int x, y, w, h;
    Color color;
    std::vector<std::vector<bool>> map;
};

class Renderer;

class GraphicsBox {
public:
    GraphicsBox(std::string title, int x, int y, int w, int h, BorderType border_type, Color border_color, Color window_color);
    void move(Renderer* renderer, int x, int y);
    void resize(Renderer* renderer, int w, int h);
    void set_border_type(Renderer* renderer, BorderType border_type);
    void set_border_color(Renderer* renderer, Color border_color);
    void set_window_color(Renderer* renderer, Color window_color);
    void set_title(Renderer* renderer, std::string title);
    void get_position_size(int* x, int* y, int* w, int* h);
    BorderType get_border_type();
    Color get_border_color();
    Color get_window_color();
    std::string get_title();
    void add_line(Renderer* renderer, int x1, int y1, int x2, int y2, int width, Color color);
    void add_curve(Renderer* renderer, std::vector<std::pair<int, int>> points, int width, Color color);
    void add_polygon(Renderer* renderer, int x, int y, int w, int h, int sides, Color color);
    void add_text(Renderer* renderer, int x, int y, std::string text, Color color);
    void add_map(Renderer* renderer, int x, int y, int w, int h, Color color, std::vector<std::vector<bool>> map);
private:
    int x, y, w, h;
    BorderType border_type;
    Color border_color;
    Color window_color;
    std::string title;
public:
    std::vector<GraphicsObjectLine> graphics_lines;
    std::vector<GraphicsObjectCurve> graphics_curves;
    std::vector<GraphicsObjectPolygon> graphics_polygons;
    std::vector<GraphicsObjectText> graphics_texts;
    std::vector<GraphicsObjectMap> graphics_maps;
};

class Renderer {
public:
    void add_box(GraphicsBox box); 
    void adjusted_box(GraphicsBox* box);
    void graphics_updated_box(GraphicsBox* box);
    void draw_box(GraphicsBox* box);
    void draw_boxes();
    void reset_graphics();
    void draw_line(int offset_x, int offset_y, int x1, int y1, int x2, int y2, int width, Color color);
    void draw_curve(int offset_x, int offset_y, std::vector<std::pair<int, int>> points, int width, Color color);
    void draw_polygon(int offset_x, int offset_y, int x, int y, int w, int h, int sides, Color color);
    void draw_text(int offset_x, int offset_y, int x, int y, std::string text, Color color);
    void draw_map(int offset_x, int offset_y, int x, int y, int w, int h, Color color, std::vector<std::vector<bool>> map);
private:
    int x_cursor, y_cursor;
    Color fg_color, bg_color;
    void move_cursor(int x, int y);
    void set_fg_color(Color fg_color);
    void set_bg_color(Color bg_color);
    void draw_pixel(char character, int x, int y, Color color);
    void draw_pixel(const char* character, int x, int y, Color color);
    void draw_border(GraphicsBox* box);
    void draw_window(GraphicsBox* box);
    std::vector<GraphicsBox> boxes;
    std::vector<GraphicsBox*> adjusted_boxes;
    std::vector<GraphicsBox*> graphics_changed_boxes;
};

#endif // RENDERER_H