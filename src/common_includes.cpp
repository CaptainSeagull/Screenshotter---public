
// TODO: sglg_Type_Bool is missing in screenshotter_generated.h. Investigate this...
#include <stdint.h>

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

typedef float F32;
typedef double F64;

#define ASSERT(exp) { }
#if ALLOW_ASSERTS
    #undef ASSERT
    #define ASSERT(exp) do { if(!(exp)) {*(uint64_t volatile *)0 = 0; } } while(0)
    #define MEMORY_ARENA_ALLOW_ASSERT
    #define STRING_ALLOW_ASSERT
#endif

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

#define internal_global static
#define internal static

// TODO: These aren't shared between the UI and screenshooting threads. May be useful to have some way to pass memory back-and-forth.
enum Memory_Index : Int {
    Memory_Index_permanent,
    Memory_Index_temp,
    Memory_Index_internal_temp,
    Memory_Index_bitmap,
    Memory_Index_renderer,
    Memory_Index_malloc_nofree_size,
};

#define ARRAY_COUNT(arr) (sizeof(arr) / (sizeof(*(arr))))
#define BYTES(v)     ((v)            * (8LL))
#define KILOBYTES(v) ((v)            * (1024LL))
#define MEGABYTES(v) ((KILOBYTES(v)) * (1024LL))
#define GIGABYTES(v) ((MEGABYTES(v)) * (1024LL))

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
