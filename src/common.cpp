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

template<typename T>
internal Void
zero(T *v) {
    zero((void *)v, sizeof(T));
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

internal Char *
memory_push_string(Memory *mem, Memory_Index idx, String str, Int padding = 0) {
    uint64_t str_length = string_length(str);
    Char *res = memory_push_type(mem, idx, Char, str_length + 1 + padding);
    ASSERT_IF(res) {
        copy(res, str.start, str_length);
    }

    return(res);
}

// TODO: "power" and "fast_power" aren't used and were just experimenting...
internal F32
power(F32 x, Int y) {
    F32 res = 1;
    if(y == 0) {
        res = 1;
    } else {
        F32 t = power(x, y / 2);
        if(y % 2 == 0) {
            res = t * t;
        } else {
            if(y > 0) {
                res = x * t * t;
            } else {
                res = (t * t) / x;
            }
        }
    }

    return(res);
}

internal F32
fast_power(F32 a, F32 b) {
    union {
        F32 d;
        int x[2];
    } u = { a };

    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}

#include "image.cpp"
