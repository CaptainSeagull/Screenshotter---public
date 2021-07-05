#include "common.h"

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

struct Config {
    String target_window_name;
    Bool copy_to_clipboard;
    Bool include_title_bar;
    String target_output_directory;
    Int amount_to_sleep;
};

internal Void
flip_image(Void *dst_pixels, Void *src_pixels, Int width, Int height) {
    Int pitch = width * 4;
    U8 *dst_row = (U8 * )dst_pixels + (height - 1) * pitch;
    U8 *src_row = (U8 * )src_pixels;

    for(U32 y = 0; (y < height); ++y) {
        U32 *dst = (U32 *)dst_row;
        U32 *src = (U32 *)src_row;
        for(U32 x = 0; (x < width); ++x) {
            *dst++ = *src++;
        }

        dst_row -= pitch;
        src_row += pitch;
    }
}

#include "image.cpp"
