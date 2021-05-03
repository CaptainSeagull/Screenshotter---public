
/*SGLG_ENTITY_PATTERN(Entity)*/ struct Rect {
    Int x, y;
    Int width, height;
    U32 output_colour;
};

struct Render_Entity {
    //SGLG_ENTITY_OUTPUT_INTERNAL_Render_Entity;

    int i;
};

struct Renderer {
    Rect rectangles[256];
    Int rectangle_count;
};