
#include "common_includes.cpp"

#include "main_generated.h"

// TODO: Mirror isn't forward declaring the linkage for this correctly
extern "C" Void handle_input_and_render(API *api) {
    // TODO: Just setting the window bitmap to white.
    set(api->bitmap_memory, 255, 1920 * 1080 * 4);
}

#include "main_generated.cpp"
