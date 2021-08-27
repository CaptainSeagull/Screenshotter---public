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

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#define STBTT_malloc(x,u) memory_push_size((Memory *)u, Memory_Index_permanent, x)
#define STBTT_free(x,u)   {}
#define STBTT_ifloor FLOOR
#define STBTT_iceil CEIL
//#define STBTT_sqrt square_root
// #define STBTT_pow // No pow implementation :-(

#define STBTT_assert ASSERT
#include "../shared/stb_truetype.h"

#define SNPRINTF stbsp_snprintf
#include "main_generated.h"
#include "renderer.h"
#include "renderer.cpp"

struct Entry {
    Bool show;
    U64 green_window_id;
    U64 yellow_window_id;
    U64 word_id;
    Bool highlighted;

    String original_title;
    String title;
    Bool title_changed;

    String class_name;
    Void *unique_id;
    Bool should_screenshot;
};

struct DLL_Data {
    Renderer renderer;

    U64 background_id;
    U64 button_id;
    U64 directory_word_id;

    Entry entry[256];
    U32 entry_count;

    U64 comic_id;
    U64 arial_id;

    U64 separator1_id;
    U64 separator2_id;
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

internal Entry *
find_entry(Entry *entries, U64 entry_count, Void *id) {
    Entry *r = 0;
    for(U64 entry_i = 0; (entry_i < entry_count); ++entry_i) {
        Entry *entry = &entries[entry_i];

        if(entry->unique_id == id) {
            r = entry;
            break; // for entry_i
        }
    }

    return(r);
}

internal Void
setup_to_render(API *api, DLL_Data *data, Renderer *renderer) {
    Memory *memory = api->memory;

    Rect *white_background = 0;
    if(api->init) {
        create_renderer(renderer, memory);

        white_background = push_solid_rectangle(renderer, renderer->root,
                                                0, 0, api->window_width, api->window_height,
                                                RGBA(255, 255, 255, 255));

        data->background_id = white_background->id;

        data->comic_id = load_font(api, renderer, "C:/Windows/fonts/comic.ttf");
        data->arial_id = load_font(api, renderer, "C:/Windows/fonts/arial.ttf");


        push_word(renderer, white_background, data->comic_id,
                  10, 0, 40,
                  "Screenshotter!");

        Line *separator1 = push_line(renderer, white_background, 0, 50, api->window_width, 50, 3.0f); // TODO: These lines don't resize with the window
        data->separator1_id = separator1->id;

        Word *directory_word = 0;
        U64 target_output_directory_length = string_length(api->target_output_directory);

        if(target_output_directory_length > 0) {
            String strings[] = { "Output Directory: ", api->target_output_directory };

            directory_word = push_words(renderer, white_background,
                                        data->arial_id, 40, 60, 25,
                                        strings, ARRAY_COUNT(strings));
        } else {
            directory_word = push_word(renderer, white_background,
                                       data->arial_id, 40, 60, 25,
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

        Line *separator2 = push_line(renderer, white_background, 0, 95, api->window_width, 95, 3.0f);
        data->separator2_id = separator2->id;
    } else {
        white_background = find_render_entity(renderer, data->background_id, Rect);
    }

    ASSERT(white_background);

    // Running programs text
    // TODO: Something goes wrong if you open Brave and have this tab open (making it the window title).
    //   https://devblogs.microsoft.com/cppblog/data-breakpoints-15-8-update/
    // Investigate! It looks like there's some non-ascii characters in here. Deal with at some point!

    // Hide all windows initially
    for(Int list_i = 0; (list_i < data->entry_count); ++list_i) {
        Entry *entry = &data->entry[list_i];
        entry->show = false;
        entry->title_changed = false;

        Rect *yellow_window = find_render_entity(renderer, entry->yellow_window_id, Rect); ASSERT(yellow_window);
        Rect *green_window  = find_render_entity(renderer, entry->green_window_id,  Rect); ASSERT(green_window);
        Word *word = find_render_entity(renderer, entry->word_id, Word); ASSERT(word);
        yellow_window->visible = false;
        green_window->visible = false;
        word->visible = false;
    }


    U64 temp_entry_buffer_it = 0;
    Entry *temp_entry_buffer = memory_push_type(memory, Memory_Index_temp, Entry, api->input_window_count);
    ASSERT(temp_entry_buffer);

    // If any windows in input_windows match the list, then add them where they currently are. Just tp preserve their position in the list.
    // We add the items here to a temporary buffer.
    for(Int list_i = 0; (list_i < data->entry_count); ++list_i) {
        Entry *entry = &data->entry[list_i];
        for(Int wnd_i = 0; (wnd_i < api->input_window_count); ++wnd_i) {
            Window_Info *wi = &api->input_windows[wnd_i];
            if((!is_empty(wi->title)) && (!is_empty(wi->class_name))) {

                if(wi->unique_id == entry->unique_id) {
                    if(wi->title != entry->title) {
                        entry->title_changed = true;
                        entry->title = wi->title;
                    }

                    temp_entry_buffer[temp_entry_buffer_it++] = *entry;

                    break; // for wnd_i
                }

            }
        }
    }

    Int height = 25;
    Int running_y = 110;
    Int y_to_increment = height + 10;

    // Now go through the temporary buffer and add the items in there to the actual list.
    for(U64 entry_i = 0; (entry_i < temp_entry_buffer_it); ++entry_i) {
        data->entry[entry_i] = temp_entry_buffer[entry_i];
        Entry *entry = &data->entry[entry_i];

        entry->show = true;

        Rect *yellow_window = find_render_entity(renderer, entry->yellow_window_id, Rect); ASSERT(yellow_window);
        Rect *green_window  = find_render_entity(renderer, entry->green_window_id,  Rect); ASSERT(green_window);

        Word *word = find_render_entity(renderer, entry->word_id, Word); ASSERT(word);
        ASSERT(word);

        word->y = running_y;
        if(entry->title_changed) {
            update_word(renderer, word, entry->title);
        }

        yellow_window->y = running_y;
        green_window->y = running_y;

        if(entry->should_screenshot) {
            green_window->visible = true;
        }

        running_y += y_to_increment;
    }

    memory_pop(memory, temp_entry_buffer);

    // Now iterate through to find new items. Done alst so they'll be added to the end.
    for(Int wnd_i = 0; (wnd_i < api->input_window_count); ++wnd_i) {
        Window_Info *input_window = &api->input_windows[wnd_i];

        if((!is_empty(input_window->title)) && (!is_empty(input_window->class_name))) {
            Entry *entry = find_entry(data->entry, data->entry_count, input_window->unique_id);

            if(!entry) {
                // Try to fill gaps initially before pushing on end.
                for(Int list_i = 0; (list_i < data->entry_count); ++list_i) {
                    if(!data->entry[list_i].show) {
                        entry = &data->entry[list_i];
                        zero(entry);
                        break; // list_i
                    }
                }

                // If we couldn't put it in a "gap", just shove on end.
                if((!entry) && (data->entry_count + 1 < ARRAY_COUNT(data->entry))) {
                    entry = &data->entry[data->entry_count++];
                }

                if(entry) {
                    Rect *yellow_window = push_solid_rectangle(renderer, white_background,
                                                               0, running_y, 640, height + 10,
                                                               RGBA(255, 255, 0, 0));
                    Rect *green_window = push_solid_rectangle(renderer, white_background,
                                                              0, running_y, 640, height + 10,
                                                              RGBA(0, 255, 0, 0));
                    Word *word = push_word(renderer, white_background,
                                           data->arial_id, 10, running_y, height,
                                           input_window->title);

                    yellow_window->visible = false;
                    green_window->visible = false;

                    entry->show = true;
                    entry->green_window_id = green_window->id;
                    entry->yellow_window_id = yellow_window->id;
                    entry->title = input_window->title;
                    entry->original_title = entry->title;
                    entry->class_name = input_window->class_name;
                    entry->unique_id = input_window->unique_id;
                    entry->highlighted = false;
                    entry->should_screenshot = false;
                    entry->word_id = word->id;

                    running_y += y_to_increment;
                }
            }
        }
    }
}

internal Void
update_and_render(API *api, Renderer *renderer) {
    DLL_Data *data = (DLL_Data *)api->dll_data;

    Int mouse_x = (Int)(api->mouse_pos_x * (F32)api->window_width);
    Int mouse_y = (Int)(api->mouse_pos_y * (F32)api->window_height);

    // Stretch main window.
    Rect *white_window = find_render_entity(renderer, data->background_id, Rect); ASSERT(white_window);
    white_window->width = api->window_width;
    white_window->height = api->window_height;

    Line *separator1 = find_render_entity(renderer, data->separator1_id, Line); ASSERT(separator1);
    Line *separator2 = find_render_entity(renderer, data->separator2_id, Line); ASSERT(separator2);

    separator1->x2 = api->window_width;
    separator2->x2 = api->window_width;

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
    for(U32 list_i = 0; (list_i < data->entry_count); ++list_i) {
        Entry *window = &data->entry[list_i];
        window->should_screenshot = false;

        Rect *yellow_window = find_render_entity(renderer, window->yellow_window_id, Rect); ASSERT(yellow_window);
        Rect *green_window  = find_render_entity(renderer, window->green_window_id,  Rect); ASSERT(green_window);
        Word *word = find_render_entity(renderer, window->word_id, Word); ASSERT(word);
        if(!window->show) {
            yellow_window->visible = false;
            green_window->visible = false;
            word->visible = false;
        } else {
            word->visible = true;

            yellow_window->width = api->window_width;
            green_window->width = api->window_width;

            window->highlighted = false;
            yellow_window->visible = false;
            if(mouse_x > yellow_window->x && mouse_x < yellow_window->x + yellow_window->width) {
                if(mouse_y > yellow_window->y && mouse_y < yellow_window->y + yellow_window->height) {
                    window->highlighted = true;
                    if(api->key[key_mouse_left] && !api->previous_key[key_mouse_left]) {
                        green_window->visible = !green_window->visible;
                    }

                    if(!green_window->visible) {
                        yellow_window->visible = true;
                    }
                }
            }

            if(green_window->visible) {
                window->should_screenshot = true;
            }
        }
    }

    // Save the list of windows to screenshot and pass back to OS layer.
    api->output_window_count = 0;
    for(Int wnd_i = 0; (wnd_i < data->entry_count); ++wnd_i) {
        Entry *entry = &data->entry[wnd_i];
        if(entry->should_screenshot) {
            api->output_windows[api->output_window_count].title = entry->original_title;
            api->output_windows[api->output_window_count].class_name = entry->class_name;
            api->output_windows[api->output_window_count].unique_id = entry->unique_id;
            ++api->output_window_count;
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
    ASSERT(renderer->error == Render_Error_no_error);

#endif

    setup_to_render(api, data, renderer);
    update_and_render(api, renderer);
}

extern "C" { int _fltused = 0; }
void __stdcall
_DllMainCRTStartup(void) {
    // TODO: list only... I don't think this needs to do anything
}

#include "main_generated.cpp"
