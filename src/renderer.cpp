
internal V2u
v2u(V2 v) {
    V2u r = { (U32)v.x, (U32)v.y };
    return(r);
}

internal V2u
v2u(U32 x, U32 y) {
    V2u r = { x, y };
    return(r);
}

internal Render_Entity *
new_node(Memory *memory) {
    Render_Entity *render_entity = (Render_Entity *)memory_push_size(memory, Memory_Index_permanent, sizeof(Render_Entity_For_Size));
    ASSERT(render_entity);

    return(render_entity);
}

internal Render_Entity *
find_end_node(Render_Entity *node) {
    if(node) {
        while(node->next) {
            node = node->next;
        }
    }

    return(node);
}

internal Void
internal_add_new_node(Render_Entity **parent, Render_Entity *child) {
    if((*parent)->child) {
        Render_Entity *end_node = find_end_node((*parent)->child);
        end_node->next = child;
    } else {
        (*parent)->child = child;
    }
}

internal Render_Entity *
add_child_to_node(Memory *memory, Render_Entity **parent) {
    Render_Entity *node = new_node(memory);
    internal_add_new_node(parent, node);

    return(node);
}

internal Bool
create_renderer(Renderer *renderer, Memory *memory) {
    Bool r = false;

    renderer->_internal.entity_id_count = 1; // Start at 1 so 0 can be invalid.
    renderer->memory = memory;
    renderer->error = Render_Error_no_error;

    renderer->root = (Render_Entity *)memory_push_size(memory, Memory_Index_permanent, sizeof(Render_Entity_For_Size));

    renderer->image_count_max = 512;
    renderer->images = memory_push_type(renderer->memory, Memory_Index_permanent, Render_Image, renderer->image_count_max);

    renderer->font_count_max = 8;
    renderer->fonts = memory_push_type(renderer->memory, Memory_Index_permanent, Font, renderer->font_count_max);

    if(renderer->root && renderer->images && renderer->fonts) {
        renderer->root->visible = true;
        add_child_to_node(memory, &renderer->root);
        r = true;
    } else {
        renderer->error = Render_Error_allocation_failure;
        ASSERT(0);
    }

    return(r);
}

internal Image_Rect
create_image_rectangle(Int x, Int y, Int width, Int height, Int sprite_x, Int sprite_y, Int sprite_width, Int sprite_height, U64 image_id) {
    Image_Rect res = {};
    res.x = x;
    res.y = y;
    res.width = width;
    res.height = height;
    res.sprite_x = sprite_x;
    res.sprite_y = sprite_y;
    res.sprite_width = sprite_width;
    res.sprite_height = sprite_height;
    res.image_id = image_id;

    return(res);
}


internal U64
push_image(Renderer *renderer, Image image) {
    U64 id = 0;
    Render_Image *ri = push_image_internal(renderer, image);
    ASSERT_IF(ri) {
        id = ri->id;
    }

    return(id);
}

internal Render_Image *
push_image_internal(Renderer *renderer, Image image) {
    Render_Image *render_image = 0;

    ASSERT_IF(renderer->image_count + 1 < renderer->image_count_max) {
        render_image = &renderer->images[renderer->image_count++];
        render_image->width = image.width;
        render_image->height = image.height;
        render_image->pixels = image.pixels;
        render_image->id = renderer->_internal.entity_id_count++;
    }

    return(render_image);
}

internal Render_Entity *
create_render_entity(Renderer *renderer, Render_Entity **parent, Type type) {
    Render_Entity *render_entity = add_child_to_node(renderer->memory, parent);
    ASSERT_IF(render_entity) {
        render_entity->visible = true;
        render_entity->type = type;
        render_entity->id = renderer->_internal.entity_id_count++;
    }

    return(render_entity);
}

internal Rect *
push_solid_rectangle(Renderer *renderer, Render_Entity *parent,
                     Int x, Int y, Int width, Int height,
                     U32 inner_colour) {
    Rect *rect = (Rect *)create_render_entity(renderer, &parent, Type_Rect);
    ASSERT_IF(rect) {
        rect->x = x;
        rect->y = y;
        rect->width = width;
        rect->height = height;
        rect->inner_colour = inner_colour;
    }

    return(rect);
}

internal Line *
push_line(Renderer *renderer, Render_Entity *parent,
          Int x1, Int y1, Int x2, Int y2,
          F32 thickness) {
    Line *line = (Line *)create_render_entity(renderer, &parent, Type_Line);
    ASSERT_IF(line) {
        line->x = x1;
        line->y = y1;
        line->x2 = x2;
        line->y2 = y2;

        line->width = MAX(ABS(line->y2 - line->y), ABS(line->y - line->y2));
        line->height = MAX(ABS(line->x2 - line->x), ABS(line->x - line->x2));

        line->thickness = thickness;
    }

    return(line);
}

struct Image_Letter_Result {
    Image_Letter image_letter;
    Bool success;
};
internal Image_Letter_Result
make_letter_image(Memory *memory, stbtt_fontinfo *font, Int ch) {
    Image_Letter_Result res = {};

    //ch = 0x061F; // For testing - https://codepoints.net/U+061F

    Int w, h, off_x, off_y;
    U8 *mono_bmp = stbtt_GetCodepointBitmap(font, 0, stbtt_ScaleForPixelHeight(font, 64.0f), ch, &w, &h, &off_x, &off_y);
    if(mono_bmp) {
        Image_Letter image_letter = {};
        image_letter.img.width = w;
        image_letter.img.height = h;
        image_letter.img.pixels = memory_push_type(memory, Memory_Index_permanent, U32, w * h);
        ASSERT_IF(image_letter.img.pixels) {

#define FLIP_IMAGE 0

#if FLIP_IMAGE
            //image_letter.off_x = off_x; // TODO: Do we care about this?
            image_letter.off_y = -off_y - h;
#else
            image_letter.off_x = off_x;
            image_letter.off_y = off_y;
#endif

            Int pitch = (w * 4);

            U8 *src = mono_bmp;
#if FLIP_IMAGE
            U8 *dst_row = (U8 * )image_letter.img.pixels + (h - 1) * pitch;
#else
            U8 *dst_row = (U8 * )image_letter.img.pixels;
#endif
            for(U32 y = 0; (y < h); ++y) {
                U32 *dst = (U32 *)dst_row;
                for(U32 x = 0; (x < w); ++x) {
                    U8 alpha = 0xFF - *src++;
                    *dst++ = ((alpha << 24) | (alpha << 16) | (alpha << 8) | (alpha << 0));
                }

#if FLIP_IMAGE
                dst_row -= pitch;
#else
                dst_row += pitch;
#endif
            }

            stbtt_FreeBitmap(mono_bmp, memory);

            res.image_letter = image_letter;
            res.success = true;
        }
    }

    return(res);
}

internal U64
push_font(API *api, Renderer *renderer, File file) {
    U64 font_id = 0;

    Memory *memory = api->memory;

    stbtt_fontinfo font_info = {};
    font_info.userdata = memory;
    Bool success = stbtt_InitFont(&font_info, file.e, stbtt_GetFontOffsetForIndex(file.e, 0));
    if(success) {
        ASSERT_IF(renderer->font_count + 1 < renderer->font_count_max) {
            Font *font = &renderer->fonts[renderer->font_count++];
            font->id = renderer->_internal.entity_id_count++;

            // TODO: This is dumb. Should do this (and store it in a hash) as we're actualy pushing letters.
            //       Or just store the letters as normal images with IDs?

            for(Int letter_i = 32; (letter_i <= 126); ++letter_i) { // ASCII is 32 - 126 (inclusive).
                Image_Letter_Result ilr = make_letter_image(memory, &font_info, letter_i);
                if(ilr.success) {
                    Image_Letter *image_letter = &ilr.image_letter;

                    Render_Image *image = push_image_internal(renderer, image_letter->img);
                    ASSERT_IF(image) {
                        image->off_x = image_letter->off_x;
                        image->off_y = image_letter->off_y;

                        font->letter_ids[ascii_to_idx(letter_i)] = image->id;

                        font->full_height = MAX(font->full_height, image->height);
                    }
                }
            }

            // Update the offset using the new height.
            for(Int letter_i = 33/*Skip space*/; (letter_i <= 126); ++letter_i) {
                Render_Image *image = find_font_image(renderer, font, letter_i);
                if(image) {
                    image->off_y += font->full_height;
                }
            }

            font_id = font->id;
        }
    }

    return(font_id);
}

internal Word *
push_word(Renderer *renderer, Render_Entity *parent, U64 font_id, Int x, Int y, Int height, String string) {
    Word *r = push_words(renderer, parent, font_id, x, y, height, &string, 1);
    ASSERT(r);
    return(r);
}

internal Word *
push_words(Renderer *renderer, Render_Entity *parent, U64 font_id, Int x, Int y, Int height, String *strings, Int string_count) {
    Word *word = (Word *)create_render_entity(renderer, &parent, Type_Word);
    ASSERT_IF(word) {
        word->x = x;
        word->y = y;
        word->height = height;
        word->font_id = font_id;

        internal_set_words(renderer, word, strings, string_count);
    }

    return(word);
}

internal Render_Image *
find_font_image(Renderer *renderer, Font *font, Int c) {
    Render_Image *image = 0;
    ASSERT_IF(is_ascii(c)) {
        image = find_image_from_id(renderer, font->letter_ids[ascii_to_idx(c)]);
        ASSERT(image);
    }

    return(image);
}

internal Font *
find_font_from_id(Renderer *renderer, U64 id) {
    Font *res = 0;
    for(Int i = 0; (i < renderer->font_count); ++i) {
        if(renderer->fonts[i].id == id) {
            res = &renderer->fonts[i];
            break; // for
        }
    }

    return(res);
}

internal Bool
is_ascii(Int c) {
    Bool r = (c >= 32 && c <= 126);
    return(r);
}

internal Int
idx_to_ascii(Int i) {
    Int c = i + 32;
    ASSERT(is_ascii(c));
    return(c);
}

internal Int
ascii_to_idx(Int c) {
    ASSERT(is_ascii(c));
    Int i = c - 32;
    return(i);
}

internal Void
internal_set_words(Renderer *renderer, Word *word, String *strings, Int string_count) {
    Font *font = find_font_from_id(renderer, word->font_id);
    ASSERT_IF(font) {
        Int running_x = 0;
        Int running_y = 0;

        for(Int string_i = 0; (string_i < string_count); ++string_i) {
            String *str = &strings[string_i];

            U64 str_length = string_length(*str);

            for(U64 letter_i = 0; (letter_i < str_length); ++letter_i) {
                Char c = *get_codepoint_at(*str, letter_i);

                // TODO: Ha
                if(c == '\n') {
                    running_x = 0;
                    running_y += word->height;
                    // TODO: Also increase the height of word?
                } else {
                    Int width_to_add = 0;
                    if(c == ' ' || !is_ascii(c)) {
                        width_to_add += word->height / 2; // TODO: Arbitrary
                    } else {
                        Render_Image *image = find_font_image(renderer, font, c);
                        ASSERT_IF(image) {
                            F32 char_pct_height_of_total = (F32)image->height / (F32)font->full_height;
                            ASSERT(char_pct_height_of_total >= 0 && char_pct_height_of_total <= 1);

                            Int height_to_use = (Int)(word->height * char_pct_height_of_total);
                            Int width_to_use = (Int)FLOOR((F32)image->width * ((F32)height_to_use / (F32)image->height)); // TODO: Is this correct?

                            push_image_rect(renderer, word,
                                            running_x, running_y, width_to_use, height_to_use,
                                            font->letter_ids[ascii_to_idx(c)]);

                            width_to_add += (width_to_use + image->off_x); // TODO: This should be a scaled off_x
                        }
                    }

                    running_x += width_to_add;
                    word->width += width_to_add * 2; // TODO: *2 because this doesn't seem to be correct...
                }
            }
        }
    }
}

internal Void
update_word(Renderer *renderer, Word *word, String string) {
    update_words(renderer, word, &string, 1);
}

internal Void
update_words(Renderer *renderer, Word *word, String *strings, Int string_count) {
    word->child = 0; // TODO: Should copy to a freelist
    internal_set_words(renderer, word, strings, string_count);
}

internal Image_Rect *
push_image_rect(Renderer *renderer, Render_Entity *parent,
                Int x, Int y, Int width, Int height,
                U64 image_id) {
    Image_Rect *image_rect = 0;
    ASSERT_IF(find_image_from_id(renderer, image_id)) { // Make sure the image ID is valid
        image_rect = (Image_Rect *)create_render_entity(renderer, &parent, Type_Image_Rect);
        ASSERT_IF(image_rect) {
            image_rect->x = x;
            image_rect->y = y;
            image_rect->width = width;
            image_rect->height = height;
            image_rect->image_id = image_id;
        }
    }

    return(image_rect);
}

internal Render_Image *
find_image_from_id(Renderer *renderer, U64 id) {
    Render_Image *img = 0;
    for(U64 img_i = 0; (img_i < renderer->image_count); ++img_i) {
        if(renderer->images[img_i].id == id) {
            img = &renderer->images[img_i];
            break; // for
        }
    }

    return(img);
}

internal Render_Entity *
find_render_entity_internal(Render_Entity *render_entity, U64 id) {
    Render_Entity *res = 0;

    Render_Entity *next = render_entity;
    while(next) {
        if(next->id == id) {
            res = next;
            break; // while
        }

        next = next->next;
    }

    if(!res) {
        next = render_entity;
        while(next) {
            if(next->child) {
                res = find_render_entity_internal(next->child, id);
                if(res) {
                    break; // while
                }
            }

            next = next->next;
        }
    }

    return(res);
}

#define find_render_entity(renderer, id, Type) (Type *)find_render_entity_(renderer, id, CONCAT(Type_, Type))
internal Render_Entity *
find_render_entity_(Renderer *renderer, U64 id, Type expected_type) {
    Render_Entity *r = find_render_entity_internal(renderer->root, id);
    ASSERT(r && r->type == expected_type);
    return(r);
}

#define image_at(base,w,h,x,y) image_at_((U32 *)base,w,h,x,y)
internal U32 *
image_at_(U32 *base, U32 width, U32 height, U32 x, U32 y) {
    U32 *res = 0;
    if(x <= width && y <= height) {
        res = &base[(y * width) + x];
    }

    return(res);
}

internal Void
render_node(Render_Entity *render_entity, Renderer *renderer, Bitmap *screen_bitmap, BB parent) {
    V2u offset = v2u(parent.x + render_entity->x,
                     parent.y + render_entity->y);

    // TODO: Most of the renderers are reading the screen pixels for y,x. However it'd probably be faster to just read for the y then
    //       ++ iterate through to write the X. Wouldn't be able to ASSERT as nicely though...
    if(render_entity->visible) {

        switch(render_entity->type) {
            case Type_Rect: {
                Rect *rect = (Rect *)render_entity;

                U32 width = rect->width;
                U32 height = rect->height;

                F32 line_thickness = rect->outline_thickness;

                for(Int iter_y = 0; (iter_y < height); ++iter_y) {
                    for(Int iter_x = 0; (iter_x < width); ++iter_x) {

                        if(iter_x + offset.x < parent.width && iter_y + offset.y < parent.height) {

                            U32 *screen_pixel = image_at(screen_bitmap->memory,
                                                         screen_bitmap->width,
                                                         screen_bitmap->height,
                                                         iter_x + offset.x,
                                                         iter_y + offset.y);

                            if(screen_pixel) {

                                // TODO: Is the order actually swapped? Would alpha be index 0?
#if 0
                                F64 a = (F64)((U8 *)&rect->inner_colour)[3] / 255.0;

                                U32 l = MIN(rect->inner_colour, *screen_pixel);
                                U32 u = MAX(rect->inner_colour, *screen_pixel);
                                U32 d = a * (u - l);
                                U32 inner_colour = l + d;
#else

                                Bool on_outline = false;
                                if(iter_y < line_thickness || iter_x < line_thickness) {
                                    on_outline = true;
                                } else if(iter_y > height - line_thickness || iter_x > width - line_thickness) {
                                    on_outline = true;
                                }

                                U32 bitmap_pixel = (on_outline) ? rect->outer_colour : rect->inner_colour;
#if 1
                                U32 colour = bitmap_pixel;
#else
                                F64 a = (F64)((U8 *)&bitmap_pixel)[3] / 255.0;
                                U32 colour = 0xFFFFFFFF;
                                for(Int i = 0; (i < 3); ++i) {
                                    U32 s = ((U8 *)screen_pixel)[i];
                                    U32 b = ((U8 *)&bitmap_pixel)[i];

                                    U32 l = MIN(b, s);
                                    U32 u = MAX(b, s);
                                    U32 d = a * (u - l);
                                    U32 o = l + d;
                                    ((U8 *)&colour)[i] = o;
                                }
#endif
#endif

                                *screen_pixel = colour;
                            }
                        }
                    }
                }
            } break;

            case Type_Line: {
                Line *line = (Line *)render_entity;

                F32 rise = (F32)MAX(ABS(line->y2 - line->y), ABS(line->y - line->y2));
                F32 run = (F32)MAX(ABS(line->x2 - line->x), ABS(line->x - line->x2));

                line->width = (Int)rise; // Not used for anything - just "nice to have" I guess
                line->height = (Int)run;

                F32 m = (run != 0) ? rise / run : 0;
                F32 y_intercept = line->y - (m * line->x);
                F32 x_intercept = line->x - (m * line->y);

                F32 thickness = line->thickness;
                Int thickness_x2 = (Int)(line->thickness * 2.0f);
                Int rise_test = (Int)(rise + thickness_x2);
                Int run_test = (Int)(run + thickness_x2);

                U32 colour = RGBA(0, 0, 0, 0xFF); // TODO: Make colour configruable

                for(Int iter_y = -thickness_x2; (iter_y < rise_test); ++iter_y) {
                    for(Int iter_x = -thickness_x2; (iter_x < run_test); ++iter_x) {

                        if(iter_x + offset.x < parent.width && iter_y + offset.y < parent.height) {
                            U32 *screen_pixel = image_at(screen_bitmap->memory,
                                                         screen_bitmap->width,
                                                         screen_bitmap->height,
                                                         iter_x + offset.x,
                                                         iter_y + offset.y);

                            if(screen_pixel) {
                                F32 x = (F32)(iter_x + offset.x);
                                F32 y = (F32)(iter_y + offset.y);
                                if(run != 0) {
                                    F32 t = ((m * x) + y_intercept);
                                    if(ABS(y - t) < thickness) {
                                        *screen_pixel = colour;
                                    }
                                } else {
                                    if(ABS(x - x_intercept) < thickness) {
                                        *screen_pixel = colour;
                                    }
                                }
                            }
                        }
                    }
                }

            } break;

            case Type_Image_Rect: {
                Image_Rect *img_rect = (Image_Rect *)render_entity;
                Render_Image *img = find_image_from_id(renderer, img_rect->image_id);
                ASSERT(img);

                F32 sprite_width_to_use  = (F32)img_rect->sprite_width;
                F32 sprite_height_to_use = (F32)img_rect->sprite_height;

                if(sprite_width_to_use  == 0) { sprite_width_to_use  = (F32)img->width;  }
                if(sprite_height_to_use == 0) { sprite_height_to_use = (F32)img->height; }

                // TODO: This doesn't work if the width / height aren't uniform... apparently?

                F32 pct_w = sprite_width_to_use  / (F32)img_rect->width;
                F32 pct_h = sprite_height_to_use / (F32)img_rect->height;

                F32 off_y_scaled = (F32)img->off_y * ((F32)img_rect->height / (F32)img->height);

                for(U32 iter_y = 0; (iter_y < img_rect->height); ++iter_y) {
                    for(U32 iter_x = 0; (iter_x < img_rect->width); ++iter_x) {

                        if(iter_x + offset.x < parent.width) {
                            // TODO: There's an issue with how I'm calculating the Word type's height, so it ends up filtering this
                            //       out completely. Look into this!
                            /*if(iter_y + offset.y < parent.height)*/ {
                                U32 img_x = (U32)FLOOR((F32)iter_x * pct_w);
                                U32 img_y = (U32)FLOOR((F32)iter_y * pct_h);

                                U32 *screen_pixel = image_at(screen_bitmap->memory,
                                                             screen_bitmap->width,
                                                             screen_bitmap->height,
                                                             iter_x + offset.x,
                                                             iter_y + offset.y + (U32)(off_y_scaled));
                                U32 *bitmap_pixel = image_at(img->pixels,
                                                             img->width,
                                                             img->height,
                                                             img_rect->sprite_x + img_x,
                                                             img_rect->sprite_y + img_y);

                                // TODO: Will bitmap_pixel ever be NULL?
                                ASSERT(bitmap_pixel);
                                if(screen_pixel && bitmap_pixel) {

                                    // TODO: Use off_x / off_y in here as well.

#if 0
                                    // Contrinuous alpha... doesn't work :-(
                                    U8 alpha8 = ((U8 *)bitmap_pixel)[0];

                                    F32 alphaf32 = alpha8 / 255.0f;

                                    U32 inner_colour = 0xFFFFFFFF;
                                    U8 *at = (U8 *)&inner_colour;
                                    for(Int i = 0; (i < 4); ++i, ++at) {
                                        U8 bitmap_pixel8 = ((U8 *)bitmap_pixel)[i];
                                        U8 screen_pixel8 = ((U8 *)screen_pixel)[i];

                                        U32 lower = MIN(bitmap_pixel8, screen_pixel8);
                                        U32 upper = MAX(bitmap_pixel8, screen_pixel8);

                                        U32 delta = alphaf32 * (upper - lower);
                                        U32 output_colour_tmp = lower + delta;
                                        ASSERT(output_colour_tmp <= 0xFF);
                                        U8 output_colour8 = (U8)output_colour_tmp;

                                        *at = output_colour8;
                                    }

                                    if(alphaf32 == 0) { ASSERT(inner_colour == *screen_pixel); }
                                    if(alphaf32 == 1) { ASSERT(inner_colour == *bitmap_pixel); }
#else
                                    // Binary alpha
                                    U8 alpha8 = ((U8 *)bitmap_pixel)[0]; // TODO: 0 or 3?
                                    U32 inner_colour = *bitmap_pixel;
                                    if(alpha8 == 255) { inner_colour = *screen_pixel; }
#endif

                                    *screen_pixel = inner_colour;
                                }
                            }
                        }
                    }
                }
            } break;

                //default: { ASSERT(0); } // TODO: Why is this being hit?
        }
    }
}

internal BB
get_overlap(BB a, BB b) {
    Int x = MAX(a.x, b.x);
    Int y = MAX(a.y, b.y);
    Int w = MIN(a.width, b.width);
    Int h = MIN(a.height, b.height);

    BB r = { x, y, w, h };
    return(r);
}

internal Void
render_node_and_siblings(Render_Entity *render_entity, Renderer *renderer, Bitmap *screen_bitmap, BB parent_bb) {
    // TODO: Sort entities based on depth first?

    // Render all siblings first
    Render_Entity *next = render_entity;
    while(next) {
        render_node(next, renderer, screen_bitmap, parent_bb);
        next = next->next;
    }

    // Now render children
    next = render_entity;
    while(next) {
        // TODO: Hack to work around the fact we end up with empty nodes... should really just fix that tbh...
        if((next->type == Type_unknown || next->visible) && next->child) {

            BB cur = { next->x, next->y,
                       (next->width) ? next->width : 0xFFFF,
                       (next->height) ? next->height : 0xFFFF
                     };

            BB r = get_overlap(parent_bb, cur);

            render_node_and_siblings(next->child, renderer, screen_bitmap, r);
        }
        next = next->next;
    }
}

internal Void
render(Renderer *renderer, Bitmap *screen_bitmap) {
    BB rectangle = {
        0, 0,
        0xFFFF, 0xFFFF,
    };

    render_node_and_siblings(renderer->root, renderer, screen_bitmap, rectangle);

    // TODO: Needs to handle clipping for drawing bitmaps off the end of screen.
    // TODO: Handle Rotation
}
