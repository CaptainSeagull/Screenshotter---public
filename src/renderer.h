
struct Rect {
    Int x, y;
    Int width, height;
    U32 output_colour;
};

struct Renderer {
    Rect rectangles[256];
    Int rectangle_count;
};