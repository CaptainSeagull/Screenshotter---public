
#include "common_includes.cpp"

#include "main_generated.h"

extern "C" {
    int _fltused = 0;
}

extern "C" Void handle_input_and_render(API *api) {
    // TODO: Just setting the window bitmap to white.
    set(api->bitmap_memory, 255, 1920 * 1080 * 4);
}

// TODO: Windows only...
void __stdcall _DllMainCRTStartup() {
    // TODO: Doesn't this need to do anything?
}

#include "main_generated.cpp"
