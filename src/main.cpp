#include <stdint.h>

// TODO: sglg_Type_Bool is missing in screenshotter_generated.h. Investigate this...
typedef int Int;
typedef Int Bool;
typedef void Void;
typedef char Char;
typedef uintptr_t Uintptr;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

#define ASSERT(exp) { }
#if ALLOW_ASSERTS
    #undef ASSERT
    #define ASSERT(exp) { if(!(exp)) {*(uint64_t volatile *)0 = 0; } }
    #define MEMORY_ARENA_ALLOW_ASSERT
    #define STRING_ALLOW_ASSERT
#endif

#include <windows.h>

#define MEMORY_ARENA_IMPLEMENTATION
#define MEMORY_PUBLIC_DEC static
#if INTERNAL
    #define MEMORY_ARENA_WRITE_ERRORS
#endif
#include "../shared/memory_arena.h"

#define STRING_IMPLEMENTATION
#define STRING_PUBLIC_DEC static
#include "../shared/string.h"

#define STB_SPRINTF_IMPLEMENTATION
#include "../shared/stb_sprintf.h"

#include "main_generated.h"

enum Memory_Index : Int {
    Memory_Index_permanent,
    Memory_Index_temp,
};

#define internal static // TODO: Rename when mirror supports

#include "image.cpp"

#define ARRAY_COUNT(arr) (sizeof(arr) / (sizeof(*(arr))))
#define BYTES(v)     ((v)            * (8LL))
#define KILOBYTES(v) ((v)            * (1024LL))
#define MEGABYTES(v) ((KILOBYTES(v)) * (1024LL))
#define GIGABYTES(v) ((MEGABYTES(v)) * (1024LL))

// TODO: This won't work for minified windows. See https://www.codeproject.com/Articles/20651/Capturing-Minimized-Window-A-Kid-s-Trick
//       for how to handle that.

// TODO: Should open a new directory each time.
// TODO: Should save a new file each time.
// TODO: Have settings load from a config file.

struct Config {
    String target_window_name;
    Bool copy_to_clipboard;
    Bool include_title_bar;
    String target_output_directory;
    Int amount_to_sleep;
};

internal HWND
find_window_from_name(Memory *memory, String window_title) {
    HWND window = 0;

    Char *window_title_raw = (Char *)memory_push(memory, Memory_Index_temp, window_title.len + 1); // Nul-terminate
    string_copy(window_title_raw, window_title.e, window_title.len);
    if(!window_title_raw) {
        ASSERT(0); // TODO: Error handling
    } else {
        window = FindWindowA(TEXT(window_title_raw), NULL);
        if(!window) {
            ASSERT(0); // TODO: Error handling
        }

        memory_pop(memory, window_title_raw);
    }

    return(window);
}

// Done on a separate thread so when we have a UI and Window it can handle window-messages without interuption.
struct Thread_Parameters {
    Config *config;
    Memory *memory;
};
internal DWORD
main_thread(void *data) {
    Thread_Parameters *tp = (Thread_Parameters *)data;

    Config *config = tp->config;
    Memory *memory = tp->memory;

    U64 iteration_count = 0;
    while(true) {
        HWND window = find_window_from_name(memory, config->target_window_name);
        RECT rect = {};
        GetClientRect(window, &rect);
        Int width = rect.right - rect.left;
        Int height = rect.bottom - rect.top;
        HDC dc = GetDC(0);
        HDC capture_dc = CreateCompatibleDC(dc);
        HBITMAP bitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);

        HGDIOBJ gdiObj = SelectObject(capture_dc, bitmap);

        PrintWindow(window, capture_dc, (config->include_title_bar) ? 0 : PW_CLIENTONLY);

        // TODO: This sometimes captures the current window, not the target for some reason...
        //BitBlt(capture_dc, 0, 0, width, height, dc, 0, 0, SRCCOPY | CAPTUREBLT);
        //SelectObject(capture_dc, gdiObj);

        if(config->copy_to_clipboard) {
            OpenClipboard(0);
            EmptyClipboard();
            SetClipboardData(CF_BITMAP, bitmap);
            CloseClipboard();
        }

        BITMAPINFO bmp_infp = {};
        bmp_infp.bmiHeader.biSize = sizeof(bmp_infp.bmiHeader);

        BITMAPINFOHEADER bmp_header = {};
        bmp_header.biSize = sizeof(BITMAPINFOHEADER);
        bmp_header.biWidth = width;
        bmp_header.biHeight = height;
        bmp_header.biPlanes = 1;
        bmp_header.biBitCount = 32;

        U32 image_size = ((width * bmp_header.biBitCount + 31) / 32) * 4 * height; // TODO: Why 31 / 32?? Why not just width * height * 4?
        U8 *image_data = (U8 *)memory_push(memory, Memory_Index_permanent, image_size);
        GetDIBits(dc, bitmap, 0, height, image_data, (BITMAPINFO *)&bmp_header, DIB_RGB_COLORS);

        // TODO: As well as saving the file, we should create an output directory per-session.

        Int output_filename_size = config->target_output_directory.len + 256; // 256 is padding
        Char *output_filename = (Char *)memory_push(memory, Memory_Index_temp, output_filename_size);
        Int bytes_written = stbsp_snprintf(output_filename, output_filename_size, "%.*s/file_%I64d.bmp", // TODO: %d prints S32 not U64
                                           config->target_output_directory.len, config->target_output_directory.e,
                                           iteration_count);
        ASSERT(bytes_written < output_filename_size);

        Image image = {};
        image.width = width;
        image.height = height;
        image.pixels = (U32 * )image_data;
        write_image_to_disk(memory, &image, output_filename);

        memory_pop(memory, output_filename);

        Sleep(config->amount_to_sleep);
        ++iteration_count;
    }
}

int
main(int argc, char **argv) {
    // TODO: Have some output depending on input. Support --version, --help, etc...

    Uintptr permanent_size = MEGABYTES(128);
    Uintptr temp_size = MEGABYTES(128);

    Void *all_memory = VirtualAlloc(0, get_memory_base_size() + permanent_size + temp_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    Uintptr group_inputs[] = { permanent_size, temp_size };
    ASSERT(SGLG_ENUM_COUNT(Memory_Index) == ARRAY_COUNT(group_inputs));
    Memory memory = create_memory_base(all_memory, group_inputs, ARRAY_COUNT(group_inputs));

    // TODO: Would be good to read these from a directory
    Config config = {};
    config.target_window_name = "Notepad";
    config.include_title_bar = true;
    config.target_output_directory = "C:/tmp";
    config.amount_to_sleep = 5000;

    Thread_Parameters *p = (Thread_Parameters *)memory_push(&memory, Memory_Index_permanent, sizeof(Thread_Parameters));
    ASSERT(p);
    p->memory = &memory;
    p->config = &config;
    HANDLE thread_handle = CreateThread(0, 0, main_thread, p, 0, 0);

    while(true); // TODO: Hacky

    // TODO: Assert Memory_Index_temp is 0.
    return(0);
}

#include "main_generated.cpp"
