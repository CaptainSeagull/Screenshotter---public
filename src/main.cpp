#define MEMORY_ARENA_IMPLEMENTATION
#if INTERNAL
    #define MEMORY_ARENA_WRITE_ERRORS
#endif
#define STRING_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION

#include "common.cpp"
#define LANE_PUBLIC_DEC static
#define LANE_WIDTH 1 // TODO: Mirror isn't handling this being different correctly.
#include "../shared/lane/lane.cpp"

#include "main_generated.h"
#include "renderer.h"
#include "renderer.cpp"

struct DLL_Data {
    Renderer renderer;
    U64 yellow_window_id;
};

extern "C" Void
init_platform_settings(Settings *settings) {
    settings->dll_data_struct_size = sizeof(DLL_Data);
    settings->thread_count = 0;
    settings->window_width = 640;
    settings->window_height = 480;
}

Image_Letter *create_font_data(API *api);

internal Void
setup(API *api, DLL_Data *data, Renderer *renderer) {

    create_renderer(renderer, api->memory);

    Render_Entity *white_window = push_solid_rectangle(renderer, &renderer->root,
                                                       0, 0, 640, 480,
                                                       255, 255, 255, 255);

    Image image_arrow = load_image(api, "arrow2.bmp");
    U64 arrow_id = push_image(renderer, image_arrow);

    Image_Letter *font_images = create_font_data(api);

    push_font(renderer, font_images);

    Render_Entity *yellow_window = push_solid_rectangle(renderer, &white_window,
                                                        0, 100, 640, 128,
                                                        255, 255, 0, 0);
    data->yellow_window_id = yellow_window->id;

    push_word(renderer, &yellow_window, "Jonathan\nLivingstone!", font_images, 50, 150, 64);

    Image img = load_image(api, "arrow3.bmp");
    U64 id_a = push_image(renderer, img);

    Int start_x = 100;
    push_image_rect(renderer, &yellow_window,
                    start_x, 0, 32, 32,
                    64, 64, 64, 64,
                    id_a);
    push_image_rect(renderer, &yellow_window,
                    start_x + 32, 0, 64, 64,
                    64, 64, 64, 64,
                    id_a);
    push_image_rect(renderer, &yellow_window,
                    start_x + 32 + 64, 0, 32, 64,
                    64, 64, 64, 64,
                    id_a);
    push_image_rect(renderer, &yellow_window,
                    start_x + 128, 0, 64, 32,
                    64, 64, 64, 64,
                    id_a);
}

internal API *global_api;
extern "C" Void
handle_input_and_render(API *api) {
    global_api = api;

    DLL_Data *data = (DLL_Data *)api->dll_data;

    Renderer *renderer = &data->renderer;

    Int mouse_x = (Int)(api->mouse_pos_x * (F32)api->window_width);
    Int mouse_y = (Int)((1.0f - api->mouse_pos_y) * (F32)api->window_height);

    if(api->init) {
        setup(api, data, renderer);
    } else {
        Render_Entity *yellow_window_render_entity = find_render_entity(renderer, data->yellow_window_id);
        ASSERT(yellow_window_render_entity);

        Rect *yellow_window = (Rect *)yellow_window_render_entity;

        if(mouse_x > yellow_window->x && mouse_x < yellow_window->x + yellow_window->width) {
            if(mouse_y > yellow_window->y && mouse_y < yellow_window->y + yellow_window->height) {
                yellow_window_render_entity->visible = true;
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

// Some stuff which library code can use.
void *my_malloc(uint64_t size) { return memory_push(global_api->memory, Memory_Index_malloc_nofree_size, size); }
void my_free(void *d) { /* Do nothing... */ }

#include "main_generated.cpp"
