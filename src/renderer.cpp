
internal_global U64 global_entity_id = 1; // Start at 1 so we know 0 is invalid.

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
    renderer->images[renderer->image_count++] = { image, id };

    return(id);
}

internal U64
push_solid_rectangle(Renderer *renderer, Int start_x, Int start_y, Int width, Int height, U8 r, U8 g, U8 b, U8 a) {
    Render_Entity *render_entity = &renderer->render_entity[renderer->render_entity_count];
    render_entity->type = sglg_Type_Rect;
    Rect *rectangle = (Rect *)render_entity;

    *rectangle = create_rectangle(start_x, start_y, width, height, r, g, b, a);
    render_entity->id = global_entity_id++;
    ++renderer->render_entity_count;

    return(render_entity->id);
}

internal U64
push_image_rect(Renderer *renderer, Int start_x, Int start_y, Int width, Int height, U64 image_id) {
    U64 entity_id = 0;
    if(!find_image_from_id(renderer, image_id)) {
        ASSERT(0);
    } else {
        Render_Entity *render_entity = &renderer->render_entity[renderer->render_entity_count];
        render_entity->type = sglg_Type_Image_Rect;
        Image_Rect *rectangle = (Image_Rect *)render_entity;

        *rectangle = create_image_rectangle(start_x, start_y, width, height, image_id);
        render_entity->id = global_entity_id++;
        ++renderer->render_entity_count;

        entity_id = render_entity->id;
    }

    return(entity_id);
}

internal Render_Image *
find_image_from_id(Renderer *renderer, U64 id) {
    Render_Image *img = 0;
    for(Int img_i = 0; (img_i < renderer->image_count); ++img_i) {
        if(renderer->images[img_i].id == id) {
            img = &renderer->images[img_i];
            break; // for
        }
    }

    return(img);
}

internal Void
render(Renderer *renderer, Bitmap *bitmap) {

    // TODO: Sort entities based on depth first.

    for(Int entity_i = 0; (entity_i < renderer->render_entity_count); ++entity_i) {
        Render_Entity *render_entity = &renderer->render_entity[entity_i];

        switch(render_entity->type) {
            case sglg_Type_Rect: {
                Rect *rectangle = (Rect *)render_entity;

                for(Int y = rectangle->y; (y < rectangle->y + rectangle->height); ++y) {
                    U32 *out = (U32 *)bitmap->memory + (y * bitmap->width) + rectangle->x;
                    for(Int x = rectangle->x; (x < rectangle->x + rectangle->width); ++x) {
                        *out++ = rectangle->output_colour;
                    }
                }
            } break;

            case sglg_Type_Image_Rect: {
                Image_Rect *img_rect = (Image_Rect *)render_entity;
                Render_Image *img = find_image_from_id(renderer, img_rect->image_id);
                ASSERT(img);

                // TODO: Does a dumb render not taking scaling into the actual size of the rectangle into account.
                U32 *pixels = img->img.pixels;
                for(Int y = img_rect->y; (y < img_rect->y + img->img.height); ++y) {
                    U32 *out_position = (U32 *)bitmap->memory + (y * bitmap->width) + img_rect->x;
                    for(Int x = img_rect->x; (x < img_rect->x + img->img.width); ++x) {
                        *out_position++ = *pixels++;
                    }
                }


            } break;

            default: { ASSERT(0); }
        }

    }
}

