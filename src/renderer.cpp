#include "renderer.hpp"

GraphicsBox::GraphicsBox(std::string title, int x, int y, int w, int h, BorderType border_type, Color border_color, Color window_color) {
    this->title = title;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->border_type = border_type;
    this->border_color = border_color;
    this->window_color = window_color;
    this->graphics_lines = std::vector<GraphicsObjectLine>();
    this->graphics_curves = std::vector<GraphicsObjectCurve>();
    this->graphics_polygons = std::vector<GraphicsObjectPolygon>();
    this->graphics_texts = std::vector<GraphicsObjectText>();
    this->graphics_maps = std::vector<GraphicsObjectMap>();
}
void GraphicsBox::move(Renderer* renderer, int x, int y) {
    if (x == this->x && y == this->y) return;
    this->x = x;
    this->y = y;
    printf("%d,%d", y, x);
    exit(0);
    renderer->adjusted_box(this);
}
void GraphicsBox::resize(Renderer* renderer, int w, int h) {
    if (w == this->w && h == this->h) return;
    this->w = w;
    this->h = h;
    renderer->adjusted_box(this);
}
void GraphicsBox::set_border_type(Renderer* renderer, BorderType border_type) {
    if (border_type == this->border_type) return;
    this->border_type = border_type;
    renderer->adjusted_box(this);
}
void GraphicsBox::set_border_color(Renderer* renderer, Color border_color) {
    if (border_color.b == this->border_color.b && border_color.g == this->border_color.g && border_color.r == this->border_color.r) return;
    this->border_color = border_color;
    renderer->adjusted_box(this);
}
void GraphicsBox::set_window_color(Renderer* renderer, Color window_color) {
    if (border_color.b == this->border_color.b && border_color.g == this->border_color.g && border_color.r == this->border_color.r) return;
    this->window_color = window_color;
    renderer->adjusted_box(this);
}
void GraphicsBox::set_title(Renderer* renderer, std::string title) {
    if (title == this->title) return;
    this->title = title;
    renderer->adjusted_box(this);
}
void GraphicsBox::get_position_size(int* x, int* y, int* w, int* h) {
    *x = this->x;
    *y = this->y;
    *w = this->w;
    *h = this->h;
}
BorderType GraphicsBox::get_border_type() {
    return this->border_type;
}
Color GraphicsBox::get_border_color() {
    return this->border_color;
}
Color GraphicsBox::get_window_color() {
    return this->window_color;
}
std::string GraphicsBox::get_title() {
    return this->title;
}
GraphicsObjectLine* GraphicsBox::add_line(Renderer* renderer, int x1, int y1, int x2, int y2, int width, Color color) {
    GraphicsObjectLine line;
    line.x1 = x1;
    line.y1 = y1;
    line.x2 = x2;
    line.y2 = y2;
    line.width = width;
    line.color = color;
    graphics_lines.push_back(line);
    renderer->graphics_updated_box(this);
    return &graphics_lines[graphics_lines.size() - 1];
}
GraphicsObjectCurve* GraphicsBox::add_curve(Renderer* renderer, std::vector<std::pair<int, int>> points, int width, Color color) {
    GraphicsObjectCurve curve;
    curve.points = points;
    curve.width = width;
    curve.color = color;
    graphics_curves.push_back(curve);
    renderer->graphics_updated_box(this);
    return &graphics_curves[graphics_curves.size() - 1];
}
GraphicsObjectPolygon* GraphicsBox::add_polygon(Renderer* renderer, int x, int y, int w, int h, int sides, Color color) {
    GraphicsObjectPolygon polygon;
    polygon.x = x;
    polygon.y = y;
    polygon.w = w;
    polygon.h = h;
    polygon.sides = sides;
    polygon.color = color;
    graphics_polygons.push_back(polygon);
    renderer->graphics_updated_box(this);
    return &graphics_polygons[graphics_polygons.size() - 1];
}
GraphicsObjectText* GraphicsBox::add_text(Renderer* renderer, int x, int y, std::string text, Color color) {
    GraphicsObjectText text_object;
    text_object.x = x;
    text_object.y = y;
    text_object.text = text;
    text_object.color = color;
    graphics_texts.push_back(text_object);
    renderer->graphics_updated_box(this);
    return &graphics_texts[graphics_texts.size() - 1];
}
GraphicsObjectMap* GraphicsBox::add_map(Renderer* renderer, int x, int y, int w, int h, Color color, std::vector<std::vector<bool>> map) {
    GraphicsObjectMap map_object;
    map_object.x = x;
    map_object.y = y;
    map_object.w = w;
    map_object.h = h;
    map_object.color = color;
    map_object.map = map;
    graphics_maps.push_back(map_object);
    renderer->graphics_updated_box(this);
    return &graphics_maps[graphics_maps.size() - 1];
}

void Renderer::adjusted_box(GraphicsBox* box) {
    adjusted_boxes.push_back(box);
}
void Renderer::graphics_updated_box(GraphicsBox* box) {
    graphics_changed_boxes.push_back(box);
}
void Renderer::add_box(GraphicsBox box) {
    boxes.push_back(box);
    adjusted_boxes.push_back(&boxes.back());
}
void Renderer::draw_boxes() {
    if (adjusted_boxes.size() == 0) return;
    
    for (auto box : adjusted_boxes) {
        draw_box(box);
    }

    for (auto box : graphics_changed_boxes) {
        draw_window(box);
    }

    adjusted_boxes.clear();
    move_cursor(0, 0);
}
void Renderer::draw_box(GraphicsBox* box) {
    draw_border(box);
    draw_window(box);
}
void Renderer::draw_border(GraphicsBox* box) {
    if (box->get_border_type() == BorderType::BorderTypeNone) return;
    
    int x, y, w, h;
    box->get_position_size(&x, &y, &w, &h);

    std::string title = box->get_title();
    Color border_color = box->get_border_color();

    const char* TL_Corner;
    const char* TR_Corner;
    const char* BL_Corner;
    const char* BR_Corner;
    const char* H_Line;
    const char* V_Line;

    if (box->get_border_type() == BorderType::BorderTypeSingle) {
        TL_Corner = C_Box_TL_Corner;
        TR_Corner = C_Box_TR_Corner;
        BL_Corner = C_Box_BL_Corner;
        BR_Corner = C_Box_BR_Corner;
        H_Line = C_Box_H_Line;
        V_Line = C_Box_V_Line;
    } else if (box->get_border_type() == BorderType::BorderTypeDouble) {
        TL_Corner = C_DoubleBox_TL_Corner;
        TR_Corner = C_DoubleBox_TR_Corner;
        BL_Corner = C_DoubleBox_BL_Corner;
        BR_Corner = C_DoubleBox_BR_Corner;
        H_Line = C_DoubleBox_H_Line;
        V_Line = C_DoubleBox_V_Line;
    }

    // title and first part of bottom line
    for (int i = x + 1; i < x + w; i++) {
        draw_pixel(H_Line, i, y + h, border_color);
        if (i == x + 1) {
            set_fg_color(WHITE);
            move_cursor(i, y);
            printf("%s", title.c_str());
        } else if (i < x + 1 + (int)title.size()) {
            continue;
        } else {
            draw_pixel(H_Line, i, y, border_color);
        }
    }
    
    // left and right vertical lines
    for (int i = y + 1; i < y + h; i++) {
        draw_pixel(V_Line, x, i, border_color);
        draw_pixel(V_Line, x + w, i, border_color);
    }

    // corners
    draw_pixel(TL_Corner, x, y, border_color);
    draw_pixel(TR_Corner, x + w, y, border_color);
    draw_pixel(BL_Corner, x, y + h, border_color);
    draw_pixel(BR_Corner, x + w, y + h, border_color);

    // draw missing pixels
    draw_pixel(H_Line, x + 1, y + h, border_color);
    draw_pixel(H_Line, x + 2, y + h, border_color);
}
void Renderer::draw_window(GraphicsBox* box) {
    int x, y, w, h;
    box->get_position_size(&x, &y, &w, &h);
    Color window_color = box->get_window_color();
    
    int border = box->get_border_type() == BorderTypeNone ? 0 : 1; // if no border, don't add padding inside of window, otherwise add padding for border
    for (int i = y + border; i < y + h; i++) {
        for (int j = x + border; j < x + w; j++) {
            move_cursor(j, i);
            set_bg_color(window_color);
            printf(" ");
        }
    }

    for (auto line : box->graphics_lines) {
        draw_line(box, line.x1, line.y1, line.x2, line.y2, line.width, line.color);
    }
    for (auto curve : box->graphics_curves) {
        draw_curve(box, curve.points, curve.width, curve.color);
    }
    for (auto polygon : box->graphics_polygons) {
        draw_polygon(box, polygon.x, polygon.y, polygon.w, polygon.h, polygon.sides, polygon.color);
    }
    for (auto text : box->graphics_texts) {
        draw_text(box, text.x, text.y, text.text, text.color);
    }
    for (auto map : box->graphics_maps) {
        draw_map(box, map.x, map.y, map.w, map.h, map.color, map.map);
    }
}
void Renderer::draw_line(GraphicsBox* box, int x1, int y1, int x2, int y2, int width, Color color) {
    
}
void Renderer::draw_curve(GraphicsBox* box, std::vector<std::pair<int, int>> points, int width, Color color) {
    
}
void Renderer::draw_polygon(GraphicsBox* box, int x, int y, int w, int h, int sides, Color color) {
    
}
void Renderer::draw_text(GraphicsBox* box, int x, int y, std::string text, Color color) {
    
}
void Renderer::draw_map(GraphicsBox* box, int x, int y, int w, int h, Color color, std::vector<std::vector<bool>> map) {
    
}
void Renderer::draw_pixel(char character, int x, int y, Color color) {
    move_cursor(x, y);
    set_fg_color(color);
    printf("%c", character);
}
void Renderer::draw_pixel(const char* character, int x, int y, Color color) {
    move_cursor(x, y);
    set_fg_color(color);
    printf(character);
}
void Renderer::move_cursor(int x, int y) {
    if (this->x_cursor == x && this->y_cursor == y) return;
    this->x_cursor = x;
    this->y_cursor = y;
    printf("\x1b[%d;%dH", y, x);
}
void Renderer::set_fg_color(Color fg_color) {
    if (this->fg_color.r == fg_color.r && this->fg_color.g == fg_color.g && this->fg_color.b == fg_color.b) return;
    this->fg_color = fg_color;
    printf("\x1b[38;2;%d;%d;%dm", fg_color.r, fg_color.g, fg_color.b);
}
void Renderer::set_bg_color(Color bg_color) {
    if (this->bg_color.r == bg_color.r && this->bg_color.g == bg_color.g && this->bg_color.b == bg_color.b) return;
    this->bg_color = bg_color;
    printf("\x1b[48;2;%d;%d;%dm", bg_color.r, bg_color.g, bg_color.b);
}
void Renderer::reset_graphics() {
    move_cursor(0, 0);
    set_fg_color(WHITE);
    set_bg_color(BLACK);
}