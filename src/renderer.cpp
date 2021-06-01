
internal_global U64 global_entity_id = 1; // Start at 1 so we know 0 is invalid.

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

internal V2
get_position(Render_Entity *render_entity) {
    // TODO: I don't really like this... maybe move the X, Y to the Render_Image struct?

    V2 res = {};
    switch(render_entity->type) {
        case sglg_Type_Rect: {
            Rect *rect = (Rect *)render_entity;
            res = v2(rect->x, rect->y);
        } break;

        case sglg_Type_Image_Rect: {
            Image_Rect *rect = (Image_Rect *)render_entity;
            res = v2(rect->x, rect->y);
        } break;

        case sglg_Type_Word: {
            Word *word = (Word *)render_entity;
            res = v2(word->x, word->y);
        } break;
    }

    return(res);
}

internal Render_Entity *
new_node(Memory *memory) {
    Render_Entity *render_entity = (Render_Entity *)memory_push(memory, Memory_Index_renderer, sizeof(Render_Entity));
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

internal Void
create_renderer(Renderer *renderer, Memory *memory) {
    renderer->memory = memory;
    renderer->root = (Render_Entity * )memory_push(renderer->memory, Memory_Index_renderer, sizeof(Render_Entity));
    ASSERT(renderer->root);

    add_child_to_node(memory, &renderer->root);
}

internal Rect
create_rectangle(Int x, Int y, Int width, Int height, U8 r, U8 g, U8 b, U8 a) {
    Rect res = {};
    res.x = x;
    res.y = y;
    res.width = width;
    res.height = height;
    res.output_colour = (a << 24 | r << 16 | g << 8 | b << 0);

    return(res);
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
    U64 id = global_entity_id++;
    ASSERT(renderer->image_count + 1 < ARRAY_COUNT(renderer->images));
    Render_Image *render_image = &renderer->images[renderer->image_count++];
    render_image->width = image.width;
    render_image->height = image.height;
    render_image->pixels = image.pixels;
    render_image->id = id;

    return(id);
}

internal Render_Entity *
push_solid_rectangle(Renderer *renderer, Render_Entity **parent,
                     Int start_x, Int start_y, Int width, Int height,
                     U8 r, U8 g, U8 b, U8 a) {
    Render_Entity *render_entity = add_child_to_node(renderer->memory, parent);
    ASSERT(render_entity);

    render_entity->type = sglg_Type_Rect;
    Rect *rectangle = (Rect *)render_entity;

    *rectangle = create_rectangle(start_x, start_y, width, height, r, g, b, a);
    render_entity->id = global_entity_id++;

    return(render_entity);
}

internal Void
push_font(Renderer *renderer, Image_Letter *font_images) {
    for(Int i = 0; (i < 128); ++i) {
        U64 image_id = push_image(renderer, font_images[i].img);
        Render_Image *image = find_image_from_id(renderer, image_id);
        ASSERT(image);

        image->off_x = font_images[i].off_x;
        image->off_y = font_images[i].off_y;
        renderer->letter_ids[i] = image_id;
    }
}

internal Render_Image *
find_font_image(Renderer *renderer, Char c) {
    Render_Image *image = find_image_from_id(renderer, renderer->letter_ids[c]);
    ASSERT(image);

    return(image);
}

// TODO: The start_x / start_y stuff doesn't seem to be working...
internal Render_Entity *
push_word(Renderer *renderer, Render_Entity **parent, String str, Image_Letter *font_images, Int start_x, Int start_y, Int height) {
    Render_Entity *render_entity = add_child_to_node(renderer->memory, parent);
    render_entity->type = sglg_Type_Word;
    ASSERT(render_entity);

    V2u padding = v2u(1, 1);

    Word *word = (Word *)render_entity;
    word->x = start_x;
    word->y = start_y;

    Int running_x = 0, running_y = 0;

    for(Int i = 0; (i < str.len); ++i) {
        if(str.e[i] == '\n') {
            running_x = 0;
            running_y -= (height + padding.y);
        } else {
            Char c = to_upper(str.e[i]); // TODO: Temp, while we're rendering all text at the same height.
            Render_Image *image = find_font_image(renderer, c);

            //Int width = height;
            Int width = floor((F32)image->width * ((F32)height / (F32)image->height)); // TODO: Is this correct?

            push_image_rect(renderer, &render_entity,
                            running_x, running_y, width, height,
                            0, 0, 0, 0,
                            renderer->letter_ids[c]);

            running_x += (width + padding.x);
        }
    }

    return(render_entity);
}

internal Render_Entity *
push_image_rect(Renderer *renderer, Render_Entity **parent,
                Int start_x, Int start_y, Int width, Int height,
                Int sprite_x, Int sprite_y, Int sprite_width, Int sprite_height,
                U64 image_id) {
    ASSERT(find_image_from_id(renderer, image_id));

    Render_Entity *render_entity = add_child_to_node(renderer->memory, parent);
    ASSERT(render_entity);

    render_entity->type = sglg_Type_Image_Rect;
    Image_Rect *rectangle = (Image_Rect *)render_entity;

    *rectangle = create_image_rectangle(start_x, start_y, width, height, sprite_x, sprite_y, sprite_width, sprite_height, image_id);
    render_entity->id = global_entity_id++;

    return(render_entity);
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

// TODO: Find entity_from_id would be useful.

internal F32
floor(F32 a) {
    F32 r = (F32)((S32)a);
    return(r);
}

// TODO: Have this return 0 if we're accessing outside the image.
#define image_at(base,y,width,x) image_at_((U32 *)base,y,width,x)
internal U32 *
image_at_(U32 *base, U32 y, U32 width, U32 x) {
    U32 accessor = ((y * width) + x);
    // TODO: ASSERT we're not reading off the end.
    U32 *r = &base[accessor];
    return(r);
}

internal Void
render_node(Render_Entity *render_entity, Renderer *renderer, Bitmap *screen_bitmap, V2 input_offset) {
    V2u offset = v2u(input_offset + get_position(render_entity));

    // TODO: Most of the renderers are reading the screen pixels for y,x. However it'd probably be faster to just read for the y then
    //       ++ iterate through to write the X. Wouldn't be able to ASSERT as nicely though...

    switch(render_entity->type) {
        case sglg_Type_Rect: {
            Rect *rect = (Rect *)render_entity;

            U32 width = rect->width;
            U32 height = rect->height;

            for(U32 y = 0; (y < height); ++y) {
                for(U32 x = 0; (x < width); ++x) {
                    U32 *screen_pixel = image_at(screen_bitmap->memory, y + offset.y, screen_bitmap->width, x + offset.x);

                    // TODO: Is the order actually swapped? Would alpha be index 0?
#if 0
                    F64 a = (F64)((U8 *)&rect->output_colour)[3] / 255.0;

                    U32 l = minu32(rect->output_colour, *screen_pixel);
                    U32 u = maxu32(rect->output_colour, *screen_pixel);
                    U32 d = a * (u - l);
                    U32 output_colour = l + d;
#else
                    U32 bitmap_pixel = rect->output_colour;
                    F64 a = (F64)((U8 *)&bitmap_pixel)[3] / 255.0;
                    U32 output_colour = 0xFFFFFFFF;
                    for(Int i = 0; (i < 3); ++i) {
                        U32 s = ((U8 *)screen_pixel)[i];
                        U32 b = ((U8 *)&bitmap_pixel)[i];

                        U32 l = minu32(b, s);
                        U32 u = maxu32(b, s);
                        U32 d = a * (u - l);
                        U32 o = l + d;
                        ((U8 *)&output_colour)[i] = o;
                    }
#endif

                    *screen_pixel = output_colour;
                }
            }
        } break;

        case sglg_Type_Image_Rect: {
            Image_Rect *img_rect = (Image_Rect *)render_entity;
            Render_Image *img = find_image_from_id(renderer, img_rect->image_id);
            ASSERT(img);

            F32 sprite_width_to_use  = img_rect->sprite_width;
            F32 sprite_height_to_use = img_rect->sprite_height;

            if(sprite_width_to_use  == 0) { sprite_width_to_use  = img->width;  }
            if(sprite_height_to_use == 0) { sprite_height_to_use = img->height; }

            // TODO: This doesn't work if the width / height aren't uniform... apparently?

            F32 pct_w = sprite_width_to_use  / (F32)img_rect->width;
            F32 pct_h = sprite_height_to_use / (F32)img_rect->height;

            for(U32 y = 0; (y < img_rect->height); ++y) {
                for(U32 x = 0; (x < img_rect->width); ++x) {
                    U32 img_x = floor((F32)x * pct_w);
                    U32 img_y = floor((F32)y * pct_h);

                    U32 *screen_pixel = image_at(screen_bitmap->memory, y + offset.y, screen_bitmap->width, x + offset.x);
                    U32 *bitmap_pixel = image_at(img->pixels, img_rect->sprite_y + img_y, img->width, img_rect->sprite_x + img_x);

                    // TODO: Use off_x / off_y in here as well.

#if 0
                    // Contrinuous alpha... doesn't work :-(
                    U8 alpha8 = ((U8 *)bitmap_pixel)[0];

                    F32 alphaf32 = alpha8 / 255.0f;

                    U32 output_colour = 0xFFFFFFFF;
                    U8 *at = (U8 *)&output_colour;
                    for(Int i = 0; (i < 4); ++i, ++at) {
                        U8 bitmap_pixel8 = ((U8 *)bitmap_pixel)[i];
                        U8 screen_pixel8 = ((U8 *)screen_pixel)[i];

                        U32 lower = minu32(bitmap_pixel8, screen_pixel8);
                        U32 upper = maxu32(bitmap_pixel8, screen_pixel8);

                        U32 delta = alphaf32 * (upper - lower);
                        U32 output_colour_tmp = lower + delta;
                        ASSERT(output_colour_tmp <= 0xFF);
                        U8 output_colour8 = (U8)output_colour_tmp;

                        *at = output_colour8;
                    }

                    if(alphaf32 == 0) { ASSERT(output_colour == *screen_pixel); }
                    if(alphaf32 == 1) { ASSERT(output_colour == *bitmap_pixel); }
#else
                    // Binary alpha
                    U8 alpha8 = ((U8 *)bitmap_pixel)[0]; // TODO: 0 or 3?
                    U32 output_colour = *bitmap_pixel;
                    if(alpha8 == 255) { output_colour = *screen_pixel; }
#endif

                    *screen_pixel = output_colour;
                }
            }
        } break;

            //default: { ASSERT(0); } // TODO: Why is this being hit?
    }
}

internal Void
render_node_and_siblings(Render_Entity *render_entity, Renderer *renderer, Bitmap *screen_bitmap, V2 offset) {
    // TODO: Sort entities based on depth first?

    // Render all siblings first
    Render_Entity *next = render_entity;
    while(next) {
        render_node(next, renderer, screen_bitmap, offset);
        next = next->next;
    }

    // Now render children
    next = render_entity;
    while(next) {
        if(next->child) {
            render_node_and_siblings(next->child, renderer, screen_bitmap, offset + get_position(next));
        }
        next = next->next;
    }
}

internal Void
render(Renderer *renderer, Bitmap *screen_bitmap) {
    render_node_and_siblings(renderer->root, renderer, screen_bitmap, v2(0, 0));

    // TODO: Needs to handle clipping for drawing bitmaps off the end of screen.
    // TODO: Handle Rotation
}
