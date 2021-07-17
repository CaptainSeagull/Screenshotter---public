
#define RGBA(r,g,b,a) (U32)(a << 24 | r << 16 | g << 8 | b << 0)

struct V2u {
    U32 x, y;
};

struct Render_Entity {
    Int x, y;
    sglg_Type type;
    U64 id;
    Bool visible;
    Render_Entity *next, *child;
};

struct Image_Letter {
    Image img;
    Int off_x, off_y;
};

// TODO: Instead of prefixing with SGLG_ENTITY_PATTERN, can I generate this just based on inheritance?

SGLG_ENTITY_PATTERN(Render_Entity) struct Rect : public Render_Entity {
    Int width, height;
    F32 outline_thickness;
    U32 inner_colour;
    U32 outer_colour;
};

// TODO: Make a sprite-sheet version.
SGLG_ENTITY_PATTERN(Render_Entity) struct Image_Rect : public Render_Entity {
    Int width, height;

    U64 image_id;

    Int sprite_x, sprite_y;
    Int sprite_width, sprite_height;
};

SGLG_ENTITY_PATTERN(Render_Entity) struct Word : public Render_Entity {
    String string; // TODO: Not used
    Int height;
    U64 font_id;
};

SGLG_ENTITY_PATTERN(Render_Entity) struct Line : public Render_Entity {
    Int x2, y2;
    F32 thickness;
};

struct Render_Entity_For_Size {
    SGLG_ENTITY_OUTPUT_INTERNAL_Render_Entity;
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
    Image_Letter *font_images;

    Internal _internal;
};
