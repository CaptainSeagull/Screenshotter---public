
struct V2u {
    U32 x, y;
};

SGLG_ENTITY_PATTERN(Render_Entity) struct Rect {
    Int x, y;
    Int width, height;
    U32 output_colour;
};

// TODO: Make a sprite-sheet version.
SGLG_ENTITY_PATTERN(Render_Entity) struct Image_Rect {
    U64 image_id;
    Int x, y;
    Int width, height;

    Int sprite_x, sprite_y;
    Int sprite_width, sprite_height;
};

SGLG_ENTITY_PATTERN(Render_Entity) struct Word {
    Int x, y;
};

struct Render_Entity {
    SGLG_ENTITY_OUTPUT_INTERNAL_Render_Entity;
    sglg_Type type;
    U64 id;

    Render_Entity *next, *child;
    Bool visible;
};

struct Render_Image {
    Int width, height;
    U32 *pixels;

    Int off_x, off_y;

    U64 id;
    // TODO: Maybe an enum for how to render for scaling / tiling, etc...
};

struct Internal {
    U64 entity_id_count;
};

struct Renderer {
    Render_Entity *root;
    Memory *memory;

    Render_Image images[256];
    Int image_count;
    U64 letter_ids[128];

    Internal _internal;
};