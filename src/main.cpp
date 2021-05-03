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

    if(api->init) {
        push_solid_rectangle(&data->renderer, 100, 100, 100, 100, 255, 0,   0, 0);
        push_solid_rectangle(&data->renderer, 200, 100, 100, 100, 255, 0, 255, 0);
    }

    render(&data->renderer, &api->screen_bitmap);
}

extern "C" { int _fltused = 0; }
void __stdcall
_DllMainCRTStartup(Void) {
    // TODO: Windows only... I don't think this needs to do anything
}

#include "main_generated.cpp"
