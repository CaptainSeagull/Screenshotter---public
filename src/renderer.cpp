
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

struct V2 {
    F32 x, y;
};

internal V2
v2(F32 x, F32 y) {
    V2 r = { x, y };
    return(r);
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

#if 1
                // TODO: Does a dumb render not taking scaling into the actual size of the rectangle into account.
#if 0
                U32 width = img_rect->width;
                U32 height = img_rect->height;
#else
                U32 width = img->img.width;
                U32 height = img->img.height;
#endif

                U32 *image_pixels = img->img.pixels;
                for(Int y = 0; (y < height); ++y) {
                    U32 *out_position = (U32 *)bitmap->memory + ((y + img_rect->y) * bitmap->width) + img_rect->x;

                    U32 *pixels = image_pixels + (y * width);
                    for(Int x = 0; (x < width); ++x) {
                        *out_position++ = *pixels++;
                    }
                }
#else
                V2 top_left     = v2(img_rect->x,                  img_rect->y);
                V2 bottom_right = v2(img_rect->x + img->img.width, img_rect->y + + img->img.height);

                U32 *pixels = img->img.pixels;
                for(Int y = 0, _y = img_rect->y; (_y < img_rect->y + img->img.height); ++_y, ++y) {
                    U32 *out_position = (U32 *)bitmap->memory + (_y * bitmap->width) + img_rect->x;
                    for(Int x = 0; (x < img->img.width); ++x) {
                        F32 pct_x = clamp01(lerp(x, top_left.x, bottom_right.x));
                        F32 pct_y = clamp01(lerp(y, top_left.y, bottom_right.y));

                        F32 hit_x = floor((F32)img->img.width * pct_x);
                        F32 hit_y = floor((F32)img->img.height * pct_y);

                        U64 pixel_pointer_offset = (U64)(((hit_y * (F32)img->img.width) + hit_x));

                        U32 *pixel_pointer = img->img.pixels + pixel_pointer_offset;

                        *out_position++ = *pixel_pointer;
                    }
                }
#endif

            } break;

            default: { ASSERT(0); }
        }

    }
}

