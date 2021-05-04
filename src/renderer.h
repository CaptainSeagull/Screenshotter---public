
SGLG_ENTITY_PATTERN(Render_Entity) struct Rect {
    Int x, y;
    Int width, height;
    U32 output_colour;
};

SGLG_ENTITY_PATTERN(Render_Entity) struct Image_Rect {
    U64 image_id;
    Int x, y;
    Int width, height;
};

struct Render_Entity {
    SGLG_ENTITY_OUTPUT_INTERNAL_Render_Entity;
    sglg_Type type;

    U64 id;
};

struct Render_Image {
    Image img; // TODO: Named poorly...
    U64 id;
    // TODO: Maybe an enum for how to render?
};

struct Renderer {
    Render_Entity render_entity[256]; // TODO: Should be a binary tree.
    Int render_entity_count;

    Render_Image images[256];
    Int image_count;
};