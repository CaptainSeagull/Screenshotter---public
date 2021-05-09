
internal_global U64 global_entity_id = 1; // Start at 1 so we know 0 is invalid.

internal V2
v2(F32 x, F32 y) {
    V2 r = { x, y };
    return(r);
}

internal V2
operator+(V2 a, V2 b) {
    V2 r = { a.x + b.x, a.y + b.y };
    return(r);
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
create_image_rectangle(Int x, Int y, Int width, Int height, U64 image_id) {
    Image_Rect res = {};
    res.x = x;
    res.y = y;
    res.width = width;
    res.height = height;
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
push_image_rect(Renderer *renderer, Render_Entity **parent, Int start_x, Int start_y, Int width, Int height, U64 image_id) {
    Render_Entity *render_entity = 0;
    if(!find_image_from_id(renderer, image_id)) {
        ASSERT(0);
    } else {
        render_entity = add_child_to_node(renderer->memory, parent);
        ASSERT(render_entity);

        render_entity->type = sglg_Type_Image_Rect;
        Image_Rect *rectangle = (Image_Rect *)render_entity;

        *rectangle = create_image_rectangle(start_x, start_y, width, height, image_id);
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

internal F32
lerp(F32 t, F32 a, F32 b) {
    F32 r = (1.0f - t) * a + t * b;
    return(r);
}

internal F32
floor(F32 a) {
    F32 r = (F32)((S32)a);
    return(r);
}

internal Void
render_node(Render_Entity *render_entity, Renderer *renderer, Bitmap *screen_bitmap, V2 offset) {
    switch(render_entity->type) {
        case sglg_Type_Rect: {
            Rect *rect = (Rect *)render_entity;

            U32 width = rect->width;
            U32 height = rect->height;

            U32 offset_x = (U32)offset.x;
            U32 offset_y = (U32)offset.y;

            for(U32 y = 0; (y < height); ++y) {
                U32 *output = (U32 *)screen_bitmap->memory + ((y + (rect->y + offset_y)) * screen_bitmap->width) + (rect->x + offset_x);

                for(U32 x = 0; (x < width); ++x) {
                    *output++ = rect->output_colour;
                }
            }
        } break;

        case sglg_Type_Image_Rect: {
            Image_Rect *img_rect = (Image_Rect *)render_entity;
            Render_Image *img = find_image_from_id(renderer, img_rect->image_id);
            ASSERT(img);

            // TODO: Why / 2??
            U32 width = img_rect->width / 2;
            U32 height = img_rect->height / 2;

            U32 offset_x = (U32)offset.x;
            U32 offset_y = (U32)offset.y;

            F32 pct_width = (F32)img->width / (F32)img_rect->width;
            F32 pct_height = (F32)img->height / (F32)img_rect->height;

            for(U32 y = 0; (y < height); ++y) {
                U32 *output = (U32 *)screen_bitmap->memory + ((y + (offset_y + img_rect->y)) * screen_bitmap->width) + (img_rect->x + offset_x);

                for(U32 x = 0; (x < width); ++x) {
                    U32 img_x = floor((F32)x * pct_width);
                    U32 img_y = floor((F32)y * pct_height);

                    U32 *bitmap_pixel = (img->pixels + (img_y * img->width)) + img_x;
                    *output++ = *bitmap_pixel;
                }
            }
        } break;

            //default: { ASSERT(0); } // TODO: Why is this being hit?
    }
}

internal V2
get_position(Render_Entity *render_entity) {
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

internal Void
render_node_and_siblings(Render_Entity *render_entity, Renderer *renderer, Bitmap *screen_bitmap, V2 offset) {
    // Render all siblings first
    Render_Entity *next = render_entity;
    while(next) {
        render_node(next, renderer, screen_bitmap, offset);
        next = next->next;
    }

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

    //for(Render_Entity *render_entity = renderer->root; (render_entity); render_entity = render_entity->next) {
    //    render_node_and_siblings(render_entity);
    //}

    // TODO: Sort entities based on depth first?

    // TODO: This also needs to handle clipping for drawing bitmaps off the end of screen.
    // TODO: Rotation would be good to handle too.
    // TODO: Entities position should be based on parents. So moving a parents position should move all their children.

}
