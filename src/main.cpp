#include "common_includes.cpp"
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

extern "C" Void
handle_input_and_render(API *api) {
    DLL_Data *data = (DLL_Data *)api->dll_data;

    Memory *memory = api->memory;

    if(api->init) {
        create_renderer(memory, &data->renderer);

        push_solid_rectangle(memory, &data->renderer.root, 0, 0, 640, 480, 255, 255, 255, 0);

        push_solid_rectangle(memory, &data->renderer.root, 100, 100, 100, 100, 255, 0,   0, 0);
        push_solid_rectangle(memory, &data->renderer.root, 200, 100, 100, 100, 255, 0, 255, 0);

        Image image_arrow = load_image(api, "arrow.bmp");
        U64 arrow_id = push_image(&data->renderer, image_arrow);

        push_image_rect(&data->renderer, memory, &data->renderer.root, 100, 100, 128, 128, arrow_id);
        push_image_rect(&data->renderer, memory, &data->renderer.root, 200, 200,  64,  64, arrow_id);
        push_image_rect(&data->renderer, memory, &data->renderer.root, 300, 300,  32,  32, arrow_id);
    }

    render(&data->renderer, &api->screen_bitmap);
}

extern "C" { int _fltused = 0; }
void __stdcall
_DllMainCRTStartup(void) {
    // TODO: Windows only... I don't think this needs to do anything
}

#include "main_generated.cpp"
