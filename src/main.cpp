
#include "common.cpp"

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

Image make_letter_image(U8 *file_data, U64 file_size);

internal API *global_api;
extern "C" Void
handle_input_and_render(API *api) {
    global_api = api;

    DLL_Data *data = (DLL_Data *)api->dll_data;

    Renderer *renderer = &data->renderer;

    if(api->init) {
        create_renderer(renderer, api->memory);

        push_solid_rectangle(renderer, &renderer->root,
                             0, 0, 640, 480,
                             255, 255, 255, 0);

        /*push_solid_rectangle(renderer, &renderer->root,
                             100, 100, 100, 100,
                             255, 0, 0, 0);
        Render_Entity *purple_window = push_solid_rectangle(renderer, &renderer->root,
                                                            200, 100, 350, 300,
                                                            255, 0, 255, 0);
        Render_Entity *blue_window = push_solid_rectangle(renderer, &purple_window,
                                                          50, 50, 256, 128,
                                                          0, 0, 255, 0);

        Image image_arrow = load_image(api, "arrow2.bmp");
        U64 arrow_id = push_image(renderer, image_arrow);*/

        File file = api->cb.read_file(api->memory, Memory_Index_permanent, "c:/windows/fonts/arial.ttf", false);
        Image image_j = make_letter_image((U8 *)file.e, file.size);
        U64 j_id = push_image(renderer, image_j);

        /*push_image_rect(renderer, &blue_window,
                        0, 0, 64, 64,
                        0, 0, 64, 64,
                        arrow_id);
        push_image_rect(renderer, &blue_window,
                        64, 0, 64, 64,
                        64, 0, 64, 64,
                        arrow_id);
        push_image_rect(renderer, &blue_window,
                        128, 0, 64, 64,
                        0, 64, 64, 64,
                        arrow_id);
        push_image_rect(renderer, &blue_window,
                        192, 0, 64, 64,
                        64, 64, 64, 64,
                        arrow_id);*/
        Render_Entity *black_window = push_solid_rectangle(renderer, &renderer->root,
                                                           0, 0, 512, 512,
                                                           0, 0, 0, 255);

        push_image_rect(renderer, &black_window,
                        128, 128, 256, 256,
                        0, 0, 0, 0,
                        j_id);
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
