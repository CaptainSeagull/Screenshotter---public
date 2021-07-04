// Move stuff mirror doesn't currently support in here.

#define FLIP_IMAGE 1

internal Image_Letter
make_letter(Memory *memory, stbtt_fontinfo *font, Char ch) {
    Image_Letter res = {};

    Int w, h, off_x, off_y;
    U8 *mono_bmp = stbtt_GetCodepointBitmap(font, 0, stbtt_ScaleForPixelHeight(font, 64.0f), ch, &w, &h, &off_x, &off_y);
    if(mono_bmp) {
        res.img.width = w;
        res.img.height = h;
        res.img.pixels = (U32 *)memory_push(memory, Memory_Index_permanent, w * h * 4);
        ASSERT(res.img.pixels);

#if FLIP_IMAGE
        //res.off_x = off_x; // TODO: Do we care about this?
        res.off_y = -off_y - h;
#else
        res.off_x = off_x;
        res.off_y = off_y;
#endif

        Int pitch = (w * 4);

        U8 *src = mono_bmp;
#if FLIP_IMAGE
        U8 *dst_row = (U8 * )res.img.pixels + (h - 1) * pitch;
#else
        U8 *dst_row = (U8 * )res.img.pixels;
#endif
        for(U32 y = 0; (y < h); ++y) {
            U32 *dst = (U32 *)dst_row;
            for(U32 x = 0; (x < w); ++x) {
                U8 alpha = 0xFF - *src++;
                *dst++ = ((alpha << 24) | (alpha << 16) | (alpha << 8) | (alpha << 0));
            }

#if FLIP_IMAGE
            dst_row -= pitch;
#else
            dst_row += pitch;
#endif
        }

        stbtt_FreeBitmap(mono_bmp, 0);
    }

    return(res);
}

internal Image_Letter *
create_font_data(API *api) {
    Memory *memory = api->memory;

    File file = api->cb.read_file(memory, Memory_Index_permanent, "c:/windows/fonts/arial.ttf", false);

    Image_Letter *font_images = (Image_Letter *)memory_push(memory, Memory_Index_font_data, sizeof(Image_Letter) * 256);
    ASSERT(font_images);

    stbtt_fontinfo font;
    stbtt_InitFont(&font, file.e, stbtt_GetFontOffsetForIndex(file.e, 0));

    for(U32 c = 0; (c < 128); ++c) {
        font_images[c] = make_letter(memory, &font, c);
    }

    return(font_images);
}

