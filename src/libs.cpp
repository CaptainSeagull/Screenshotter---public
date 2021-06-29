// Move stuff mirror doesn't currently support in here.

// TODO: Now mirror works with stb_truetype can I get rid of this separate file?

#include "common.h"
#include "image.h"

#define internal static

void *my_malloc(uint64_t size);
void my_free(void *d);
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_malloc(x,u) ((void)(u),my_malloc(x))
#define STBTT_free(x,u)   ((void)(u),my_free(x))
#define STBTT_assert(exp) { }
#if ALLOW_ASSERTS
    #undef STBTT_assert
    #define STBTT_assert(exp) do { if(!(exp)) {*(uint64_t volatile *)0 = 0; } } while(0)
#endif
#include "../shared/stb_truetype.h"

#include "libs_generated.h"

internal Image_Letter
make_letter(stbtt_fontinfo *font, Char ch) {
    Image_Letter res = {};

    Int w, h, off_x, off_y;
    U8 *mono_bmp = stbtt_GetCodepointBitmap(font, 0, stbtt_ScaleForPixelHeight(font, 32.0f), ch, &w, &h, &off_x, &off_y);
    if(mono_bmp) {
#if 1
        res.img.width = w;
        res.img.height = h;
        res.img.pixels = (U32 *)my_malloc(w * h * 4);
        res.off_x = off_x;
        res.off_y = off_y;
#else
        res.width = w;
        res.height = h;
        res.pixels = (U32 *)my_malloc(w * h * 4);
#endif
        Int pitch = (w * 4);

        U8 *src = mono_bmp;
        U8 *dst_row = (U8 * )res.img.pixels + (h - 1) * pitch;
        for(U32 y = 0; (y < h); ++y) {
            U32 *dst = (U32 *)dst_row;
            for(U32 x = 0; (x < w); ++x) {
                U8 alpha = 0xFF - *src++;
                *dst++ = ((alpha << 24) | (alpha << 16) | (alpha << 8) | (alpha << 0));
            }

            dst_row -= pitch;
        }

        stbtt_FreeBitmap(mono_bmp, 0);
    }

    return(res);
}

Image_Letter *
create_font_data(API *api) {
    Memory *memory = api->memory;

    File file = api->cb.read_file(memory, Memory_Index_permanent, "c:/windows/fonts/arial.ttf", false);

    Image_Letter *font_images = (Image_Letter *)memory_push(memory, Memory_Index_font_data, sizeof(Image_Letter) * 256);

    stbtt_fontinfo font;
    stbtt_InitFont(&font, file.e, stbtt_GetFontOffsetForIndex(file.e, 0));

    for(U32 c = 0; (c < 128); ++c) {
        font_images[c] = make_letter(&font, c);
    }

    return(font_images);
}

//#include "libs_generated.cpp"