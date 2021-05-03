
SGLG_ENTITY_PATTERN(Render_Entity) struct Rect {
    Int x, y;
    Int width, height;
    U32 output_colour;
};

struct Render_Entity {
    SGLG_ENTITY_OUTPUT_INTERNAL_Render_Entity;
    sglg_Type type;

    Int depth; // TODO: Unused
    U64 id;
};

struct Renderer {
    Render_Entity render_entity[256];
    Int render_entity_count;
};