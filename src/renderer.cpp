
internal_global U64 global_entity_id = 1; // Start at 1 so we know 0 is invalid.

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

internal U64
push_solid_rectangle(Renderer *renderer, Render_Entity **parent, Int start_x, Int start_y, Int width, Int height, U8 r, U8 g, U8 b, U8 a) {
    Render_Entity *render_entity = add_child_to_node(renderer->memory, parent);
    ASSERT(render_entity);

    render_entity->type = sglg_Type_Rect;
    Rect *rectangle = (Rect *)render_entity;

    *rectangle = create_rectangle(start_x, start_y, width, height, r, g, b, a);
    render_entity->id = global_entity_id++;

    return(render_entity->id);
}

internal U64
push_image_rect(Renderer *renderer, Render_Entity **parent, Int start_x, Int start_y, Int width, Int height, U64 image_id) {
    U64 entity_id = 0;
    if(!find_image_from_id(renderer, image_id)) {
        ASSERT(0);
    } else {
        Render_Entity *render_entity = add_child_to_node(renderer->memory, parent);
        ASSERT(render_entity);

        render_entity->type = sglg_Type_Image_Rect;
        Image_Rect *rectangle = (Image_Rect *)render_entity;

        *rectangle = create_image_rectangle(start_x, start_y, width, height, image_id);
        render_entity->id = global_entity_id++;

        entity_id = render_entity->id;
    }

    return(entity_id);
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
render(Renderer *renderer, Bitmap *screen_bitmap) {

    // TODO: Sort entities based on depth first?

    // TODO: This also needs to handle clipping for drawing bitmaps off the end of screen.
    // TODO: Rotation would be good to handle too.
    // TODO: Entities position should be based on parents. So moving a parents position should move all their children.

    Render_Entity *render_entity = renderer->root->child; // TODO: Hardcoded single-level
    while(render_entity) {
        switch(render_entity->type) {
            case sglg_Type_Rect: {
                Rect *rect = (Rect *)render_entity;

                U32 width = rect->width;
                U32 height = rect->height;

                for(U32 y = 0; (y < height); ++y) {
                    U32 *output = (U32 *)screen_bitmap->memory + ((y + rect->y) * screen_bitmap->width) + rect->x;

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

                F32 pct_width = (F32)img->width / (F32)img_rect->width;
                F32 pct_height = (F32)img->height / (F32)img_rect->height;

                for(U32 y = 0; (y < height); ++y) {
                    U32 *output = (U32 *)screen_bitmap->memory + ((y + img_rect->y) * screen_bitmap->width) + img_rect->x;

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

        render_entity = render_entity->next;
    }
}
