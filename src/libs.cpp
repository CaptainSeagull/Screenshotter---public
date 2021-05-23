// Move stuff mirror doesn't currently support in here.

#include "common.h"
#include "image.h"
#include <stdio.h>

#define internal static

void *my_malloc(uint64_t size);
void my_free(void *d);

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_malloc(x,u) ((void)(u),my_malloc(x))
#define STBTT_free(x,u)   ((void)(u),my_free(x))
#define STBTT_assert(exp) { }
#if ALLOW_ASSERTS
    #undef STBTT_assert
    #define STBTT_assert(exp) do { if(!(exp)) {*(uint64_t volatile *)0 = 0; } } while(0)
#endif
#include "../shared/stb_truetype.h"

internal Image
make_letter(U8 *file_data, U64 file_size, Char ch) {
    Image res = {};

    stbtt_fontinfo font;
    stbtt_InitFont(&font, file_data, stbtt_GetFontOffsetForIndex(file_data, 0));

    Int w, h, x_off, y_off;
    U8 *mono_bmp = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, 32.0f), ch, &w, &h, &x_off, &y_off);
    if(mono_bmp) {
        res.width = w;
        res.height = h;
        res.pixels = (U32 *)my_malloc(w * h * 4);

        Int pitch = (w * 4);

        U8 *src = mono_bmp;
        U8 *dst_row = (U8 * )res.pixels + (h - 1) * pitch;
        for(U32 y = 0; (y < h); ++y) {
            U32 *dst = (U32 *)dst_row;
            for(U32 x = 0; (x < w); ++x) {
                U8 alpha = *src++;
                *dst++ = ((alpha << 24) | (alpha << 16) | (alpha << 8) | (alpha << 0));
            }

            dst_row -= pitch;
        }

        stbtt_FreeBitmap(mono_bmp, 0);
    }

    return(res);
}

Image *
create_font_data(API *api) {
    Memory *memory = api->memory;

    File file = api->cb.read_file(memory, Memory_Index_permanent, "c:/windows/fonts/arial.ttf", false);

    Image *font_images = (Image *)memory_push(memory, Memory_Index_font_data, sizeof(Image) * 256);

    // TODO: This is _super_ slow. Maybe a better way than gathering each letter individually.
    for(U32 c = 0; (c < 128); ++c) {
        font_images[c] = make_letter((U8 *)file.e, file.size, c);
    }

    return(font_images);
}