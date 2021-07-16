
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
    Render_Entity *render_entity = (Render_Entity *)memory_push(memory, Memory_Index_renderer, sizeof(Render_Entity_For_Size));
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
    ++renderer->_internal.entity_id_count; // Use 0 for invalid
    renderer->memory = memory;
    renderer->root = (Render_Entity * )memory_push(renderer->memory, Memory_Index_renderer, sizeof(Render_Entity));
    ASSERT(renderer->root);

    add_child_to_node(memory, &renderer->root);
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
    U64 id = renderer->_internal.entity_id_count++;
    ASSERT(renderer->image_count + 1 < ARRAY_COUNT(renderer->images));
    Render_Image *render_image = &renderer->images[renderer->image_count++];
    render_image->width = image.width;
    render_image->height = image.height;
    render_image->pixels = image.pixels;
    render_image->id = id;

    return(id);
}

internal Render_Entity *
create_render_entity(Renderer *renderer, Render_Entity **parent, sglg_Type type) {
    Render_Entity *render_entity = add_child_to_node(renderer->memory, parent);
    ASSERT(render_entity);

    render_entity->visible = true;
    render_entity->type = type;
    render_entity->id = renderer->_internal.entity_id_count++;

    return(render_entity);
}

#define push_solid_rectangle(renderer, parent, x, y, width, height, r, g, b, a) \
    push_solid_rectangle_(renderer, (Render_Entity **)parent, x, y, width, height, r, g, b, a)
internal Rect *
push_solid_rectangle_(Renderer *renderer, Render_Entity **parent,
                      Int x, Int y, Int width, Int height,
                      U8 r, U8 g, U8 b, U8 a) {
    Rect *rect = (Rect *)create_render_entity(renderer, parent, sglg_Type_Rect);

    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;
    rect->output_colour = (a << 24 | r << 16 | g << 8 | b << 0);

    return(rect);
}

#define push_line(renderer, parent, x1, y1, x2, y2, thickness) push_line_(renderer, (Render_Entity **)parent, x1, y1, x2, y2, thickness)
internal Line *
push_line_(Renderer *renderer, Render_Entity **parent,
           Int x1, Int y1, Int x2, Int y2,
           F32 thickness) {
    Line *line = (Line *)create_render_entity(renderer, parent, sglg_Type_Line);

    line->x = x1;
    line->y = y1;
    line->x2 = x2;
    line->y2 = y2;
    line->thickness = thickness;

    return(line);
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

#define push_word(renderer, parent, font_images, start_x, start_y, height, string) \
    push_word_(renderer, (Render_Entity **)parent, font_images, start_x, start_y, height, string)

internal Word *
push_word_(Renderer *renderer, Render_Entity **parent, Image_Letter *font_images, Int start_x, Int start_y, Int height, String string) {
    Word *r = push_words_(renderer, parent, font_images, start_x, start_y, height, &string, 1);
    return(r);
}

#define push_words(renderer, parent, font_images, start_x, start_y, height, strings, string_count) \
    push_words_(renderer, (Render_Entity **)parent, font_images, start_x, start_y, height, strings, string_count)

internal Word *
push_words_(Renderer *renderer, Render_Entity **parent, Image_Letter *font_images, Int start_x, Int start_y, Int height, String *strings, Int str_count) {
    Word *word = (Word *)create_render_entity(renderer, parent, sglg_Type_Word);
    ASSERT(word);

    //word->string = str;

    V2u padding = v2u(0, 0);

    word->x = start_x;
    word->y = start_y;

    Int running_x = 0, running_y = height;

    Render_Image *a_image = find_font_image(renderer, 'A');
    F32 full_height = a_image->height;


    for(Int str_i = 0; (str_i < str_count); ++str_i) {
        String *str = &strings[str_i];

        for(Int letter_i = 0; (letter_i < str->len); ++letter_i) {
            if(str->e[letter_i] == '\n') {
                running_x = 0;
                running_y -= (height + padding.y);
            } else {
                Char c = str->e[letter_i];

                if(c == ' ') {
                    running_x += height;
                } else {
                    Render_Image *image = find_font_image(renderer, c);

                    F32 char_pct_height_of_total = (F32)image->height / full_height;

                    Int height_to_use = (height * char_pct_height_of_total);
                    Int width_to_use = floor((F32)image->width * ((F32)height_to_use / (F32)image->height)); // TODO: Is this correct?

                    push_image_rect(renderer, (Render_Entity **)&word,
                                    running_x, running_y, width_to_use, height_to_use,
                                    0, 0, 0, 0,
                                    renderer->letter_ids[c]);

                    running_x += (width_to_use + padding.x + image->off_x); // TODO: This should be a scaled off_x
                }
            }
        }
    }

    return(word);
}

internal Image_Rect *
push_image_rect(Renderer *renderer, Render_Entity **parent,
                Int start_x, Int start_y, Int width, Int height,
                Int sprite_x, Int sprite_y, Int sprite_width, Int sprite_height,
                U64 image_id) {
    ASSERT(find_image_from_id(renderer, image_id));

    Image_Rect *image_rect = (Image_Rect *)create_render_entity(renderer, parent, sglg_Type_Image_Rect);
    ASSERT(image_rect);

    image_rect->x = start_x;
    image_rect->y = start_y;
    image_rect->width = width;
    image_rect->height = height;
    image_rect->sprite_x = sprite_x;
    image_rect->sprite_y = sprite_y;
    image_rect->sprite_width = sprite_width;
    image_rect->sprite_height = sprite_height;
    image_rect->image_id = image_id;

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

#define find_render_entity(Renderer, id, Type) (Type *)find_render_entity_(renderer, id, CONCAT(sglg_Type_, Type))
internal Render_Entity *
find_render_entity_(Renderer *renderer, U64 id, sglg_Type expected_type) {
    Render_Entity *r = find_render_entity_internal(renderer->root, id);
    ASSERT(r && r->type == expected_type);
    return(r);
}

// TODO: Find entity_from_id would be useful.

internal F32
floor(F32 a) {
    F32 r = (F32)((S32)a);
    return(r);
}

internal F32
absolute(F32 a) {
    F32 r = (a > 0) ? a : -a;
    return(r);
}

#define image_at(base,w,h,x,y) image_at_((U32 *)base,w,h,x,y)
internal U32 *
image_at_(U32 *base, U32 width, U32 height, U32 x, U32 y) {
    U32 *res = 0;
    if(x <= width && y <= height) {
        U32 accessor = ((y * width) + x);
        res = &base[accessor];
    }

    return(res);
}

internal Void
render_node(Render_Entity *render_entity, Renderer *renderer, Bitmap *screen_bitmap, V2 input_offset) {
    V2u offset = v2u(input_offset.x + render_entity->x,
                     input_offset.y + render_entity->y);

    // TODO: Most of the renderers are reading the screen pixels for y,x. However it'd probably be faster to just read for the y then
    //       ++ iterate through to write the X. Wouldn't be able to ASSERT as nicely though...
    if(render_entity->visible) {

        switch(render_entity->type) {
            case sglg_Type_Rect: {
                Rect *rect = (Rect *)render_entity;

                U32 width = rect->width;
                U32 height = rect->height;

                for(U32 iter_y = 0; (iter_y < height); ++iter_y) {
                    for(U32 iter_x = 0; (iter_x < width); ++iter_x) {
                        U32 *screen_pixel = image_at(screen_bitmap->memory,
                                                     screen_bitmap->width,
                                                     screen_bitmap->height,
                                                     iter_x + offset.x,
                                                     iter_y + offset.y);

                        if(screen_pixel) {

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
                }
            } break;

            case sglg_Type_Line: {
                Line *line = (Line *)render_entity;

                F32 rise = maxf32(absolute(line->y2 - line->y), absolute(line->y - line->y2));
                F32 run = maxf32(absolute(line->x2 - line->x), absolute(line->x - line->x2));

                F32 m = (run != 0) ? rise / run : 0;
                F32 y_intercept = line->y - (m * line->x);
                F32 x_intercept = line->x - (m * line->y);

                F32 thickness = line->thickness;
                F32 thickness_x2 = (line->thickness * 2.0f);
                F32 rise_test = (rise + thickness_x2);
                F32 run_test = (run + thickness_x2);

                for(Int iter_y = -thickness_x2; (iter_y < rise_test); ++iter_y) {
                    for(Int iter_x = -thickness_x2; (iter_x < run_test); ++iter_x) {
                        U32 *screen_pixel = image_at(screen_bitmap->memory,
                                                     screen_bitmap->width,
                                                     screen_bitmap->height,
                                                     iter_x + offset.x,
                                                     iter_y + offset.y);

                        if(screen_pixel) {
                            F32 x = iter_x + offset.x;
                            F32 y = iter_y + offset.y;
                            if(run != 0) {
                                F32 t = ((m * x) + y_intercept);
                                if(absolute(y - t) < thickness) {
                                    *screen_pixel = 0;
                                }
                            } else {
                                if(absolute(x - x_intercept) < thickness) {
                                    *screen_pixel = 0;
                                }
                            }

                        }
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

                F32 off_y_scaled = (F32)img->off_y * ((F32)img_rect->height / (F32)img->height);

                for(U32 iter_y = 0; (iter_y < img_rect->height); ++iter_y) {
                    for(U32 iter_x = 0; (iter_x < img_rect->width); ++iter_x) {
                        U32 img_x = floor((F32)iter_x * pct_w);
                        U32 img_y = floor((F32)iter_y * pct_h);

                        U32 *screen_pixel = image_at(screen_bitmap->memory,
                                                     screen_bitmap->width,
                                                     screen_bitmap->height,
                                                     iter_x + offset.x,
                                                     iter_y + offset.y + (off_y_scaled));
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
                }
            } break;

                //default: { ASSERT(0); } // TODO: Why is this being hit?
        }
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
            render_node_and_siblings(next->child, renderer, screen_bitmap, offset + v2(next->x, next->y));
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
