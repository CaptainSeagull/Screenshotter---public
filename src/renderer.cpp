
internal_global U64 global_entity_id = 1; // Start at 1 so we know 0 is invalid.

internal V2u
v2u(V2 v) {
    V2u r = { (U32)v.x, (U32)v.y };
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
    renderer->images[renderer->image_count++] = { image.width, image.height, image.pixels, id };

    return(id);
}

internal Render_Entity *
push_solid_rectangle(Renderer *renderer, Render_Entity **parent, Int start_x, Int start_y, Int width, Int height, U8 r, U8 g, U8 b, U8 a) {
    Render_Entity *render_entity = add_child_to_node(renderer->memory, parent);
    ASSERT(render_entity);

    render_entity->type = sglg_Type_Rect;
    Rect *rectangle = (Rect *)render_entity;

    *rectangle = create_rectangle(start_x, start_y, width, height, r, g, b, a);
    render_entity->id = global_entity_id++;

    return(render_entity);
}

internal Render_Entity *
push_image_rect(Renderer *renderer, Render_Entity **parent,
                Int start_x, Int start_y, Int width, Int height,
                Int sprite_x, Int sprite_y, Int sprite_width, Int sprite_height,
                U64 image_id) {
    Render_Entity *render_entity = 0;
    if(!find_image_from_id(renderer, image_id)) {
        ASSERT(0);
    } else {
        render_entity = add_child_to_node(renderer->memory, parent);
        ASSERT(render_entity);

        render_entity->type = sglg_Type_Image_Rect;
        Image_Rect *rectangle = (Image_Rect *)render_entity;

        *rectangle = create_image_rectangle(start_x, start_y, width, height, sprite_x, sprite_y, sprite_width, sprite_height, image_id);
        render_entity->id = global_entity_id++;
    }

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
                    U32 *output = image_at(screen_bitmap->memory, y + offset.y, screen_bitmap->width, x + offset.x);

                    // TODO: Is the order actually swapped? Would alpha be index 0?
                    F64 a = (F64)((U8 *)&rect->output_colour)[3] / 255.0;

                    U32 l = minu32(rect->output_colour, *output);
                    U32 u = maxu32(rect->output_colour, *output);
                    U32 d = a * (u - l);

                    U32 output_colour = l + d;

                    *output = output_colour;
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

            // TODO: The clamp here may just be masking bugs.
            F32 pct_w = clamp01(sprite_width_to_use  / (F32)img_rect->width);
            F32 pct_h = clamp01(sprite_height_to_use / (F32)img_rect->height);

            ASSERT(pct_w >= 0 && pct_w <= 1);
            ASSERT(pct_h >= 0 && pct_h <= 1);

            for(U32 y = 0; (y < img_rect->width); ++y) {
                for(U32 x = 0; (x < img_rect->height); ++x) {
                    U32 img_x = floor((F32)x * pct_w);
                    U32 img_y = floor((F32)y * pct_h);

                    U32 *screen_pixel = image_at(screen_bitmap->memory, y + offset.y, screen_bitmap->width, x + offset.x);
                    U32 *bitmap_pixel = image_at(img->pixels, img_rect->sprite_y + img_y, img->width, img_rect->sprite_x + img_x);

                    // TODO: Is this alpha stuff correct?
                    F64 a = (F64)((U8 *)bitmap_pixel)[3] / 255.0;

                    U32 output_colour = 0;
                    for(Int i = 0; (i < 3); ++i) {
                        F64 c = (F64)((U8 *)bitmap_pixel)[i] / 255.0;

                        U32 l = minu32(*bitmap_pixel, *screen_pixel);
                        U32 u = maxu32(*bitmap_pixel, *screen_pixel);
                        U32 d = a * (u - l);
                        U32 o = l + d;
                        ((U8 *)&output_colour)[i] = o;
                    }

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
