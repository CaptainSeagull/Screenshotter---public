#include "common.h"

// TODO: None of these are shared between the UI and "screenshooting" threads. May be useful to have some way to pass memory back-and-forth.
enum Memory_Index : Int {
    Memory_Index_permanent,
    Memory_Index_temp,
    Memory_Index_internal_temp,
    Memory_Index_bitmap,
    Memory_Index_renderer,
    Memory_Index_malloc_nofree_size,
};

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

internal U32
safe_truncate_size_64(U64 v) {
    ASSERT(v <= 0xFFFFFFFF);
    U32 res = (U32)v;

    return(res);
}

internal Void
zero(Void *m, U64 s) {
    U8 *m8 = (U8 *)m;
    while(s--) {
        *m8++ = 0;
    }
}

internal Void
copy(Void *dst, Void *src, U64 size) {
    U8 *dst8 = (U8 *)dst;
    U8 *src8 = (U8 *)src;
    while(size--) {
        *dst8++ = *src8++;
    }
}

internal Void
set(Void *dst, U8 v, U64 size) {
    U8 *dst8 = (U8 *)dst;
    while(size--) {
        *dst8++ = v;
    }
}

internal F32
clamp01(F32 a) {
    F32 r = a;
    if     (r < 0) { r = 0; }
    else if(r > 1) { r = 1; }

    return(r);
}

struct Config {
    String target_window_name;
    Bool copy_to_clipboard;
    Bool include_title_bar;
    String target_output_directory;
    Int amount_to_sleep;
};

#include "platform.h"
#include "image.cpp"
