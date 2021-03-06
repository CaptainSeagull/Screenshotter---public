
#define RGBA(r,g,b,a) (U32)(a << 24 | r << 16 | g << 8 | b << 0)
#if defined(RGB)
    #undef RGB
#endif
#define RGB(r,g,b) RGBA(r,g,b,0xFF)

struct V2u {
    U32 x, y;
};

struct BB {
    Int x, y;
    Int width, height;
};

struct Render_Entity {
    Int x, y;
    Int width, height;

    Type type;
    U64 id;
    Bool visible;

    Render_Entity *next, *child;
};

struct Image_Letter {
    Image img;
    Int off_x, off_y;
};

struct Rect : public Render_Entity {
    F32 outline_thickness;
    U32 inner_colour;
    U32 outer_colour;
};

// TODO: Make a sprite-sheet version.
struct Image_Rect : public Render_Entity {
    U64 image_id;

    Int sprite_x, sprite_y;
    Int sprite_width, sprite_height;
};

struct Word : public Render_Entity {
    //String string; // TODO: Not used
    //Int height;
    U64 font_id;
};

struct Line : public Render_Entity {
    Int x2, y2;
    F32 thickness;
};

struct Render_Entity_For_Size {
    ENTITY_PATTERN(Render_Entity);
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

struct Font {
    U64 id;
    U64 letter_ids[96]; // ASCII is 32..126 (inclusive) - 95 characters
    Int full_height;
};

enum Render_Error : Int {
    Render_Error_no_error,
    Render_Error_allocation_failure,
};

struct Renderer {
    Render_Entity *root;
    Memory *memory;

    Render_Image *images;
    U32 image_count_max, image_count;

    Font *fonts;
    U32 font_count_max, font_count;

    Render_Error error;
    Internal _internal;
};
