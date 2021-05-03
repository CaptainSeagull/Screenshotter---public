
internal_global U64 global_entity_id;

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

// TODO: Would be good to return the ID as well.
internal Rect *
push_solid_rectangle(Renderer *renderer, Int start_x, Int start_y, Int width, Int height, U8 r, U8 g, U8 b, U8 a) {
    Render_Entity *render_entity = &renderer->render_entity[renderer->render_entity_count];
    render_entity->type = sglg_Type_Rect;
    Rect *rectangle = (Rect *)render_entity;

    *rectangle = create_rectangle(start_x, start_y, width, height, r, g, b, a);
    render_entity->id = global_entity_id++;
    ++renderer->render_entity_count;

    return(rectangle);
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

            default: { ASSERT(0); }
        }

    }
}

