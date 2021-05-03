#include "common_includes.cpp"
#include "main_generated.h"
#include "renderer.cpp"

extern "C" Void
handle_input_and_render(API *api) {
    push_solid_rectangle(api->renderer, 100, 100, 100, 100, 255, 0,   0, 0);
    push_solid_rectangle(api->renderer, 200, 100, 100, 100, 255, 0, 255, 0);

    render(api->renderer, &api->screen_bitmap);
}

extern "C" { int _fltused = 0; }
void __stdcall
_DllMainCRTStartup(Void) {
    // TODO: Windows only... I don't think this needs to do anything
}

#include "main_generated.cpp"
