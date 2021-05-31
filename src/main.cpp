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
};

extern "C" Void
init_platform_settings(Settings *settings) {
    settings->dll_data_struct_size = sizeof(DLL_Data);
    settings->thread_count = 0;
    settings->window_width = 640;
    settings->window_height = 480;
}

Image *create_font_data(API *api);

internal API *global_api;
extern "C" Void
handle_input_and_render(API *api) {
    global_api = api;

    DLL_Data *data = (DLL_Data *)api->dll_data;

    Renderer *renderer = &data->renderer;

    if(api->init) {
        create_renderer(renderer, api->memory);

        Render_Entity *white_window = push_solid_rectangle(renderer, &renderer->root,
                                                           0, 0, 640, 480,
                                                           255, 255, 255, 255);

        /*push_solid_rectangle(renderer, &white_window,
                             0, 0, 256, 256,
                             255, 0, 0, 128);
        push_solid_rectangle(renderer, &white_window,
                             128, 128, 256, 256,
                             0, 0, 255, 128);*/

        Image image_arrow = load_image(api, "arrow2.bmp");
        U64 arrow_id = push_image(renderer, image_arrow);

        File file = api->cb.read_file(api->memory, Memory_Index_permanent, "c:/windows/fonts/courier_new.ttf", false);
        Image *font_images = create_font_data(api);

        //Render_Entity *black_window = push_solid_rectangle(renderer, &white_window,
        //                                                   0, 0, 512, 512,
        //                                                   255, 0, 0, 255);
        Render_Entity *yellow_window = push_solid_rectangle(renderer, &white_window,
                                                            0, 100, 640, 128,
                                                            255, 255, 0, 0);

        // TODO: The image rendering seems a little flakey, especially for indivual letters (even ignoring the alpha issues).
        //       Investigate it further.

        push_word(renderer, &yellow_window, "Jonathan\nLivingstone!", font_images, 0, 400, 64);

        Image img = load_image(api, "arrow3.bmp");
        U64 id_a = push_image(renderer, img);
        /*push_image_rect(renderer, &yellow_window,
                        300, 0, 128, 128,
                        0, 0, 64, 64,
                        id_a);*/

        /*push_image_rect(renderer, &yellow_window,
                        300, 0, 256, 256,
                        64, 64, 64, 64,
                        id_a);*/
        Int start_x = 100;
        /*push_image_rect(renderer, &yellow_window,
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
                        id_a);*/


#if 0
        U64 id_a = push_image(renderer, font_images['a']);
        U64 id_b = push_image(renderer, font_images['B']);
        U64 id_3 = push_image(renderer, font_images['3']);


        push_image_rect(renderer, &black_window,
                        0, 0, 128, 128,
                        0, 0, 0, 0,
                        id_a);
        push_image_rect(renderer, &black_window,
                        128, 0, 128, 128,
                        0, 0, 0, 0,
                        id_b);
        push_image_rect(renderer, &black_window,
                        256, 0, 128, 128,
                        0, 0, 0, 0,
                        id_3);
#endif
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
