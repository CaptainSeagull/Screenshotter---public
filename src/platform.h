struct File {
    U8 *e;
    Uintptr size;
    String fname;
};

enum Key : Int {
    key_unknown = -1,

    // 0-9 are matched by index,

    key_ctrl = 11,
    key_shift,
    key_alt,
    key_space,
    key_escape,

    key_left,
    key_right,
    key_up,
    key_down,

    key_mouse_left,
    key_mouse_middle,
    key_mouse_right,

    left_stick_x,
    left_stick_y,

    right_stick_x,
    right_stick_y,

    dpad_right,
    dpad_up,
    dpad_down,
    dpad_left,

    start,
    back,

    left_shoulder,
    right_shoulder,
    left_thumb,
    right_thumb,

    controller_a,
    controller_b,
    controller_x,
    controller_y,

    key_A = 65, // 'A'
    key_B,
    key_C,
    key_D,
    key_E,
    key_F,
    key_G,
    key_H,
    key_I,
    key_J,
    key_K,
    key_L,
    key_M,
    key_N,
    key_O,
    key_P,
    key_Q,
    key_R,
    key_S,
    key_T,
    key_U,
    key_V,
    key_W,
    key_X,
    key_Y,
    key_Z,

    key_cnt = 128
};

struct Platform_Callbacks {
    File (*read_file)(Memory *memory, U32 memory_index_to_use, String fname, Bool null_terminate);
    Bool (*write_file)(Memory *memory, String fname, U8 *data, U64 size);

    U64 (*locked_add)(U64 volatile *a, U64 b);

    Bool (*add_work_queue_entry)(struct API *api, Void *e, Void (*cb)(Void *d));
    Void (*complete_all_work)(struct API *api);
};

struct Bitmap {
    Void *memory;
    Int width;
    Int height;
};

struct Settings {
    U64 dll_data_struct_size;
    Int thread_count;

    Int window_width;
    Int window_height;
};

struct Window_Info {
    String title;
    String class_name;
    Void *unique_id;
};

// TODO: Tidy API struct
struct API {
    F32 previous_key[256];
    F32 key[256];

    Memory *memory;
    Bool init;
    Bool running;
    F32 dt;
    F32 seconds_elapsed_for_last_frame;

    F32 previous_mouse_pos_x, previous_mouse_pos_y;
    F32 mouse_pos_x, mouse_pos_y;

    Int window_width, window_height; // Client size

    Bitmap screen_bitmap;
    Bool screen_image_size_change;

    U64 randomish_seed;

    Int max_work_queue_count;

    Platform_Callbacks cb;
    Void *platform_specific;

    Void *dll_data;

    // input_windows are all the potential windows passed into main.cpp.
    Int input_window_count;
    Window_Info input_windows[256];

    // output_windows are all the windows we should run the screenshotting on. Filled out inside main.cpp.
    Int output_window_count;
    Window_Info output_windows[256];

    Bool launch_browse_for_directory;

    Bool include_title_bar;
    Int amount_to_sleep;

    // TODO: Wrap the directory stuff in some functions and make these private

    // target_output_directory is what the user select. target_output_directory_full includes "Screenshotter_x" at the end.
    String target_output_directory;
    String target_output_directory_full;

    // When changing the directory just change this.
    String new_target_output_directory;
};

