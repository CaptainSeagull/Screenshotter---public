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

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_malloc(x,u) memory_push_size((Memory *)u, Memory_Index_permanent, x)
#define STBTT_free(x,u)    {}

#define STBTT_assert ASSERT
#include "../shared/stb_truetype.h"

#define SNPRINTF stbsp_snprintf
#include "main_generated.h"
#include "renderer.h"
#include "renderer.cpp"

struct Entry {
    U64 green_window_id;
    U64 yellow_window_id;
    Bool highlighted;

    Window_Info *info; // TODO: Storing this here may cause issues later on if we remove/add items.
};

struct DLL_Data {
    Renderer renderer;

    U64 background_id;
    U64 button_id;
    U64 directory_word_id;

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

internal U64
load_font(API *api, Renderer *renderer, String fname) {
    U64 id = 0;
    File file = api->cb.read_file(api->memory, Memory_Index_temp, fname, false);
    ASSERT_IF(file.size > 0) {
        id = push_font(api, renderer, file);
        ASSERT(id);
        memory_pop(api->memory, file.e);
    }

    return(id);
}

internal Void
setup(API *api, DLL_Data *data, Renderer *renderer) {
    Memory *memory = api->memory;

    create_renderer(renderer, memory);

    Rect *white_background = push_solid_rectangle(renderer, renderer->root,
                                                  0, 0, api->window_width, api->window_height,
                                                  RGBA(255, 255, 255, 255));

    data->background_id = white_background->id;

    U64 comic_id = load_font(api, renderer, "c:/windows/fonts/comic.ttf");
    U64 arial_id = load_font(api, renderer, "c:/windows/fonts/arial.ttf");

#if 0
    Int y = 40;
    push_word(renderer, white_background, comic_id,
              10, y, 40,
              "Screenshotter!");

    Image arrow = load_image(api, "arrow.bmp");
    U64 arrow_id = push_image(renderer, arrow);

    Rect *r = push_solid_rectangle(renderer, white_background,
                                   10, y, 100, 100,
                                   RGBA(255, 0, 0, 255));

    push_image_rect(renderer, r,
                    0, 0, 30, 40,
                    arrow_id);
#else
    push_word(renderer, white_background, comic_id,
              10, 0, 40,
              "Screenshotter!");

    push_line(renderer, white_background, 0, 50, api->window_width, 50, 3.0f); // TODO: These lines don't resize with the window

    Word *directory_word = 0;
    U64 target_output_directory_length = string_length(api->target_output_directory);

    if(target_output_directory_length > 0) {
        String strings[] = { "Output Directory: ", api->target_output_directory };

        directory_word = push_words(renderer, white_background,
                                    arial_id, 40, 60, 25,
                                    strings, ARRAY_COUNT(strings));
    } else {
        directory_word = push_word(renderer, white_background,
                                   arial_id, 40, 60, 25,
                                   "Please select an output directory");
    }

    ASSERT(directory_word);
    data->directory_word_id = directory_word->id;

    Rect *button = push_solid_rectangle(renderer, white_background,
                                        5, 58, 30, 30,
                                        RGBA(255, 255, 255, 255));
    button->outline_thickness = 3.0f;
    button->outer_colour = 0xFF000000;
    data->button_id = button->id;

    push_line(renderer, white_background, 0, 95, api->window_width, 95, 3.0f);

    // Running programs text
    {
        // TODO: Something goes wrong if you open Brave and have this tab open (making it the window title).
        //   https://devblogs.microsoft.com/cppblog/data-breakpoints-15-8-update/
        // Investigate! It looks like there's some non-ascii characters in here. Deal with at some point!

        Int height = 25;
        Int running_y = 110;
        for(Int wnd_i = 0; (wnd_i < api->window_count); ++wnd_i) {
            U64 title_length = string_length(api->windows[wnd_i].title);
            U64 class_name_length = string_length(api->windows[wnd_i].class_name);

            if(title_length > 0 && class_name_length > 0) {
                Rect *yellow_window = push_solid_rectangle(renderer, white_background,
                                                           0, running_y, 640, height + 10,
                                                           RGBA(255, 255, 0, 0));
                Rect *green_window = push_solid_rectangle(renderer, white_background,
                                                          0, running_y, 640, height + 10,
                                                          RGBA(0, 255, 0, 0));
                yellow_window->visible = false;
                green_window->visible = false;

                data->windows[data->list_count].yellow_window_id = yellow_window->id;
                data->windows[data->list_count].green_window_id = green_window->id;
                data->windows[data->list_count].info = &api->windows[wnd_i];

                ++data->list_count;

                // Useful for debugging
#if 1
                push_word(renderer, yellow_window,
                          arial_id, 10, 5, height,
                          api->windows[wnd_i].title);
#else
                push_word(renderer, yellow_window,
                          arial_id, 10, 5, height,
                          api->windows[wnd_i].class_name);
#endif

                running_y += (height + 10);
            }
        }
    }
#endif
}

internal Void
update(API *api, Renderer *renderer) {
    DLL_Data *data = (DLL_Data *)api->dll_data;
    Memory *memory = api->memory;

    Int mouse_x = (Int)(api->mouse_pos_x * (F32)api->window_width);
    Int mouse_y = (Int)(api->mouse_pos_y * (F32)api->window_height);

    // Stretch main window.
    Rect *white_window = find_render_entity(renderer, data->background_id, Rect); ASSERT(white_window);
    white_window->width = api->window_width;
    white_window->height = api->window_height;

    if(string_length(api->new_target_output_directory) > 0) {
        Word *directory_word = find_render_entity(renderer, data->directory_word_id, Word);
        ASSERT(directory_word);

        String strings[] = { "Output Directory: ", api->new_target_output_directory };
        update_words(renderer, directory_word, strings, ARRAY_COUNT(strings));
    }

    // Button
    Rect *button = find_render_entity(renderer, data->button_id, Rect); ASSERT(button);

    button->inner_colour = RGB(255, 255, 255);
    if(mouse_x > button->x && mouse_x < button->x + button->width) {
        if(mouse_y > button->y && mouse_y < button->y + button->height) {
            button->inner_colour = RGB(0, 0, 255);
            if(api->key[key_mouse_left]) {
                button->inner_colour = RGB(255, 0, 0);
                if(!api->previous_key[key_mouse_left]) {
                    api->launch_browse_for_directory = true;
                }
            }
        }
    }

    // Yellow highlighting
    for(U32 list_i = 0; (list_i < data->list_count); ++list_i) {
        data->windows[list_i].info->should_screenshot = false;

        Rect *yellow_window = find_render_entity(renderer, data->windows[list_i].yellow_window_id, Rect);
        Rect *green_window = find_render_entity(renderer, data->windows[list_i].green_window_id, Rect);

        yellow_window->width = api->window_width;
        green_window->width = api->window_width;

        data->windows[list_i].highlighted = false;
        yellow_window->visible = false;
        if(mouse_x > yellow_window->x && mouse_x < yellow_window->x + yellow_window->width) {
            if(mouse_y > yellow_window->y && mouse_y < yellow_window->y + yellow_window->height) {
                data->windows[list_i].highlighted = true;
                if(api->key[key_mouse_left] && !api->previous_key[key_mouse_left]) {
                    green_window->visible = !green_window->visible;
                }

                if(!green_window->visible) {
                    yellow_window->visible = true;
                }
            }
        }

        if(green_window->visible) {
            data->windows[list_i].info->should_screenshot = true;
        }
    }

    render(renderer, &api->screen_bitmap);
}

extern "C" Void
handle_input_and_render(API *api) {
    DLL_Data *data = (DLL_Data *)api->dll_data;
    Renderer *renderer = &data->renderer;

#if INTERNAL
    Memory_Group *temp_group = get_memory_group(api->memory, Memory_Index_temp);
    if(temp_group->used != 0) {
        Internal_Push_Info *push_info = (Internal_Push_Info *)temp_group->base;
        ASSERT(0);
    }
#endif

    if(api->init) {
        setup(api, data, renderer);
    } else {
        update(api, renderer);
    }
}

extern "C" { int _fltused = 0; }
void __stdcall
_DllMainCRTStartup(void) {
    // TODO: Windows only... I don't think this needs to do anything
}

#include "main_generated.cpp"
