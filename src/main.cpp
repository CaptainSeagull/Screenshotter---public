#define MEMORY_ARENA_IMPLEMENTATION
#if INTERNAL
    #define MEMORY_ARENA_WRITE_ERRORS
#endif
#define STRING_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION

#include "common.cpp"
#define LANE_PUBLIC_DEC static
#define LANE_WIDTH 4 // TODO: Mirror isn't handling this being different correctly.
#include "../shared/lane/lane.cpp"

internal API *global_api;
internal void *my_malloc(uint64_t size) { return memory_push(global_api->memory, Memory_Index_malloc_nofree_size, size); }
internal void my_free(void *d) { /* Do nothing... */ }
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_malloc(x,u) ((void)(u),my_malloc(x))
#define STBTT_free(x,u)   ((void)(u),my_free(x))
#define STBTT_assert(exp) { }
#if ALLOW_ASSERTS
    #undef STBTT_assert
    #define STBTT_assert ASSERT
#endif
#include "../shared/stb_truetype.h"

#include "main_generated.h"
#include "renderer.h"
#include "renderer.cpp"
#include "letter_stuff.cpp"

struct Entry {
    U64 green_window_id;
    U64 yellow_window_id;
    Bool highlighted;

    Window_Info info;
};

struct DLL_Data {
    Renderer renderer;

    U64 background_id;

    Entry windows[256];
    U32 list_count;
};

extern "C" Void
init_platform_settings(Settings *settings) {
    settings->dll_data_struct_size = sizeof(DLL_Data);
    settings->thread_count = 0;
    settings->window_width = 640;
    settings->window_height = 480;
}

internal Void
setup(API *api, DLL_Data *data, Renderer *renderer) {

    create_renderer(renderer, api->memory);

    Render_Entity *white_window = push_solid_rectangle(renderer, &renderer->root,
                                                       0, 0, api->window_width, api->window_height,
                                                       255, 255, 255, 255);
    data->background_id = white_window->id;

    Image_Letter *font_images = create_font_data(api);
    push_font(renderer, font_images);

    push_word(renderer, &white_window,
              "Screenshotter!",
              font_images, 10, 5, 30);

    // Running programs text
    {
        // TODO: Something goes wrong if you open Brave and have this tab open (making it the window title).
        //   https://devblogs.microsoft.com/cppblog/data-breakpoints-15-8-update/
        // Investigate!

        Int height = 20;
        Int running_y = 40;
        for(Int wnd_i = 0; (wnd_i < api->window_count); ++wnd_i) {
            if(api->windows[wnd_i].title.len > 0 && api->windows[wnd_i].class_name.len > 0) {
                Render_Entity *yellow_window = push_solid_rectangle(renderer, &white_window,
                                                                    0, running_y, 640, height + 10,
                                                                    255, 255, 0, 0);
                Render_Entity *green_window = push_solid_rectangle(renderer, &white_window,
                                                                   0, running_y, 640, height + 10,
                                                                   0, 255, 0, 0);
                yellow_window->visible = false;
                green_window->visible = false;

                data->windows[data->list_count].yellow_window_id = yellow_window->id;
                data->windows[data->list_count].green_window_id = green_window->id;
                data->windows[data->list_count].info = api->windows[wnd_i];

                ++data->list_count;

                // Useful for debugging
#if 1
                push_word(renderer, &yellow_window,
                          api->windows[wnd_i].title,
                          font_images, 10, 5, height);
#else
                push_word(renderer, &yellow_window,
                          api->windows[wnd_i].class_name,
                          font_images, 10, 5, height);
#endif

                running_y += (height + 10);
            }
        }
    }

#if 0
#if 0
    Void *tmp = memory_push(api->memory, Memory_Index_temp, 128 * 128 * 4);
    memory_pop(api->memory, tmp);

    Image image_arrow = load_image(api, "arrow2.bmp");
    Image_Letter *font_images = create_font_data(api);
    push_font(renderer, font_images);
    push_word(renderer, &white_window, "A.a,g", font_images, 100, 100, 40);
#else
    Image image_arrow = load_image(api, "arrow2.bmp");
    U64 arrow_id = push_image(renderer, image_arrow);
    push_image_rect(renderer, &white_window, 0, 0, 32, 32, 64, 64, 64, 64, arrow_id);


    Image_Letter *font_images = create_font_data(api);

    push_font(renderer, font_images);

    Render_Entity *yellow_window = push_solid_rectangle(renderer, &white_window,
                                                        0, 100, 640, 128,
                                                        255, 255, 0, 0);
    data->yellow_window_ids = yellow_window->id;

    Int height = 30;
    Int running_y = 10;
    for(Int wnd_i = 0; (wnd_i < api->top_level_window_titles_count); ++wnd_i) {
        if(api->top_level_window_titles[wnd_i].len > 0) {
            push_word(renderer, &white_window,
                      api->top_level_window_titles[wnd_i],
                      font_images, 0, running_y, height);
            running_y += (height + 10);
        }
    }

    Image test_img = load_image(api, "test.bmp");
    U64 test_id = push_image(renderer, test_img);
    push_image_rect(renderer, &yellow_window,
                    0, 0, 128, 128,
                    0, 0, 0, 0,
                    test_id);

    Int start_x = 100;
    push_image_rect(renderer, &yellow_window,
                    start_x, 0, 32, 32,
                    64, 64, 64, 64,
                    arrow_id);
    push_image_rect(renderer, &yellow_window,
                    start_x + 32, 0, 64, 64,
                    64, 64, 64, 64,
                    arrow_id);
    push_image_rect(renderer, &yellow_window,
                    start_x + 32 + 64, 0, 32, 64,
                    64, 64, 64, 64,
                    arrow_id);
    push_image_rect(renderer, &yellow_window,
                    start_x + 128, 0, 64, 32,
                    64, 64, 64, 64,
                    arrow_id);
#endif
#endif
}

extern "C" Void
handle_input_and_render(API *api) {
    global_api = api;

    DLL_Data *data = (DLL_Data *)api->dll_data;
    Config *config = api->config;
    config->target_window_count = 0;

    Renderer *renderer = &data->renderer;

    Memory_Group *temp_group = get_memory_group(api->memory, Memory_Index_temp);
    ASSERT(temp_group->used == 0);

    Int mouse_x = (Int)(api->mouse_pos_x * (F32)api->window_width);
    Int mouse_y = (Int)(api->mouse_pos_y * (F32)api->window_height);

    if(api->init) {
        setup(api, data, renderer);
    } else {

        // Stretch main window.
        Render_Entity *white_window = find_render_entity(renderer, data->background_id); ASSERT(white_window);
        white_window->_Rect.width = api->window_width;
        white_window->_Rect.height = api->window_height;

        // Yellow highlighting
        for(U32 list_i = 0; (list_i < data->list_count); ++list_i) {

            // TODO: The API of having to get the root and actual entity separately is crappy...

            Render_Entity *yellow_window_render_entity = find_render_entity(renderer, data->windows[list_i].yellow_window_id); ASSERT(yellow_window_render_entity);
            Rect *yellow_window = (Rect *)yellow_window_render_entity;

            Render_Entity *green_window_render_entity = find_render_entity(renderer, data->windows[list_i].green_window_id); ASSERT(green_window_render_entity);
            Rect *green_window = (Rect *)green_window_render_entity;

            yellow_window->width = api->window_width;
            green_window->width = api->window_width;

            data->windows[list_i].highlighted = false;
            yellow_window_render_entity->visible = false;
            if(mouse_x > yellow_window->x && mouse_x < yellow_window->x + yellow_window->width) {
                if(mouse_y > yellow_window->y && mouse_y < yellow_window->y + yellow_window->height) {
                    data->windows[list_i].highlighted = true;
                    if(api->key[key_mouse_left] && !api->previous_key[key_mouse_left]) {
                        green_window_render_entity->visible = !green_window_render_entity->visible;
                    }

                    if(!green_window_render_entity->visible) {
                        yellow_window_render_entity->visible = true;
                    }
                }
            }

            if(green_window_render_entity->visible) {
                config->windows[config->target_window_count++] = data->windows[list_i].info;
            }
        }
    }

    render(renderer, &api->screen_bitmap);
}


extern "C" { int _fltused = 0; }
void __stdcall
_DllMainCRTStartup(void) {
    // TODO: Windows only... I don't think this needs to do anything
}

#include "main_generated.cpp"
