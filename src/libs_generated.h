enum sglg_Type {
    sglg_Type_unknown,
    sglg_Type_char,
    sglg_Type_int,
    sglg_Type_unsigned,
    sglg_Type_signed,
    sglg_Type_short,
    sglg_Type_long,
    sglg_Type_float,
    sglg_Type_double,
    sglg_Type_wchar_t,
    sglg_Type_bool,
    sglg_Type_void,
    sglg_Type_uint8_t,
    sglg_Type_uint16_t,
    sglg_Type_uint32_t,
    sglg_Type_uint64_t,
    sglg_Type_int8_t,
    sglg_Type_int16_t,
    sglg_Type_int32_t,
    sglg_Type_int64_t,
    sglg_Type_uintptr_t,
    sglg_Type_intptr_t,
    sglg_Type_Memory_Arena_Error,
    sglg_Type_Memory_Group,
    sglg_Type_Memory,
    sglg_Type_String,
    sglg_Type_String_To_Int_Result,
    sglg_Type_String_To_Float_Result,
    sglg_Type_stbsp__context,
    sglg_Type_Int,
    sglg_Type_File,
    sglg_Type_Key,
    sglg_Type_Platform_Callbacks,
    sglg_Type_Bitmap,
    sglg_Type_Settings,
    sglg_Type_API,
    sglg_Type_Memory_Index,
    sglg_Type_Image,
    sglg_Type_Image_Letter,
    sglg_Type_stbtt_pack_context,
    sglg_Type_stbtt_fontinfo,
    sglg_Type_stbrp_rect,
    sglg_Type_stbtt_kerningentry,
};

// Utils
#define SGLG_ENTITY_PATTERN(name)
#define SGLG_PREPROC_CONCAT(a, b) a##b
#define SGLG_ENUM_COUNT(name) SGLG_PREPROC_CONCAT(sglg_internal_enum_, name)
static int sgl_generated_string_compare(char const *a, uint32_t a_len, char const *b, uint32_t b_len);
static uint64_t sglg_get_enum_count(sglg_Type type);
static uint64_t sglg_type_to_size(sglg_Type type);
static sglg_Type sglg_string_to_type(char const *s, uint64_t l);

// Forward declared typedefs
typedef char * STBSP_SPRINTFCB ( char * buf , void * user , int len ) ;
typedef int Int ;
typedef Int Bool ;
typedef void Void ;
typedef char Char ;
typedef uintptr_t Uintptr ;
typedef uint8_t U8 ;
typedef uint16_t U16 ;
typedef uint32_t U32 ;
typedef uint64_t U64 ;
typedef int8_t S8 ;
typedef int16_t S16 ;
typedef int32_t S32 ;
typedef int64_t S64 ;
typedef float F32 ;
typedef double F64 ;
typedef unsigned char stbtt_uint8 ;
typedef signed char stbtt_int8 ;
typedef unsigned short stbtt_uint16 ;
typedef signed short stbtt_int16 ;
typedef unsigned int stbtt_uint32 ;
typedef signed int stbtt_int32 ;
typedef char stbtt__check_size32 [ sizeof ( stbtt_int32 ) == 4 ? 1 : - 1 ] ;
typedef char stbtt__check_size16 [ sizeof ( stbtt_int16 ) == 2 ? 1 : - 1 ] ;
typedef int stbtt__test_oversample_pow2 [ ( 8 & ( 8 - 1 ) ) == 0 ? 1 : - 1 ] ;

// Forward declared structs

struct Memory_Group;
struct Memory;
struct String;
struct String_To_Int_Result;
struct String_To_Float_Result;
struct stbsp__context;
struct File;
enum Key : Int;

struct Platform_Callbacks;
struct Bitmap;
struct Settings;
struct API;
enum Memory_Index : Int;

struct Image;
struct Image_Letter;
struct stbtt_pack_context;
struct stbtt_fontinfo;
struct stbrp_rect;
struct stbtt_pack_context;
struct stbtt_fontinfo;
struct stbtt_kerningentry;

// Forward declaration of functions
uint64_t get_memory_base_size(void );
Memory create_memory_base(void * base_memory , uintptr_t * inputs , uintptr_t inputs_count );
Memory_Group* get_memory_group(Memory * memory , uintptr_t buffer_index );
void* memory_push_(Memory * memory , uintptr_t buffer_index , uintptr_t size , char * fname , int line , uintptr_t alignment  );
void memory_pop(Memory * memory , void * memory_buffer );
void memory_clear_entire_group(Memory * memory , uintptr_t buffer_index );
String create_string(char * str , int len  );
String create_string(char const * str , int len  );
String create_substring(String str , int start , int end  );
int string_compare(String a , String b );
int operator==(String a , String b );
int string_contains(String a , String b );
int string_contains(String str , char target );
int find_index(String str , char target , int find_last  );
int string_length(char * str );
int string_length(char const * str );
int char_to_int(char c );
String_To_Int_Result string_to_int(String s );
String_To_Float_Result string_to_float(String s );
int string_copy(char * dst , char * src );
int string_copy(char const * dst , char const * src );
int string_copy(char * dst , char const * src );
int string_copy(char * dst , char * src , int len );
char to_upper(char a );
char to_lower(char a );
int stbsp_sprintf(char * buf , char const * fmt , ... );
int stbsp_snprintf(char * buf , int count , char const * fmt , ... );
void stbsp_set_separators(char comma , char period );
void stbsp_set_separators(char pcomma , char pperiod );
 static char* stbsp__clamp_callback(char * buf , void * user , int len );
int stbsp_snprintf(char * buf , int count , char const * fmt , ... );
void* my_malloc(uint64_t size );
void my_free(void * d );
 static void stbtt_GetScaledFontVMetrics(const stbtt_uint8 * fontdata , int index , float size , float * ascent , float * descent , float * lineGap );
 static int stbtt_GetNumberOfFonts(const stbtt_uint8 * data );
 static int stbtt_GetFontOffsetForIndex(const stbtt_uint8 * data , int index );
 static int stbtt_FindGlyphIndex(const stbtt_fontinfo * info , int unicode_codepoint );
 static float stbtt_ScaleForPixelHeight(const stbtt_fontinfo * info , float pixels );
 static float stbtt_ScaleForMappingEmToPixels(const stbtt_fontinfo * info , float pixels );
 static void stbtt_GetFontVMetrics(const stbtt_fontinfo * info , int * ascent , int * descent , int * lineGap );
 static int stbtt_GetFontVMetricsOS2(const stbtt_fontinfo * info , int * typoAscent , int * typoDescent , int * typoLineGap );
 static void stbtt_GetFontBoundingBox(const stbtt_fontinfo * info , int * x0 , int * y0 , int * x1 , int * y1 );
 static void stbtt_GetCodepointHMetrics(const stbtt_fontinfo * info , int codepoint , int * advanceWidth , int * leftSideBearing );
 static int stbtt_GetCodepointKernAdvance(const stbtt_fontinfo * info , int ch1 , int ch2 );
 static int stbtt_GetCodepointBox(const stbtt_fontinfo * info , int codepoint , int * x0 , int * y0 , int * x1 , int * y1 );
 static void stbtt_GetGlyphHMetrics(const stbtt_fontinfo * info , int glyph_index , int * advanceWidth , int * leftSideBearing );
 static int stbtt_GetGlyphKernAdvance(const stbtt_fontinfo * info , int glyph1 , int glyph2 );
 static int stbtt_GetGlyphBox(const stbtt_fontinfo * info , int glyph_index , int * x0 , int * y0 , int * x1 , int * y1 );
 static int stbtt_GetKerningTableLength(const stbtt_fontinfo * info );
 static int stbtt_IsGlyphEmpty(const stbtt_fontinfo * info , int glyph_index );
 static int stbtt_GetCodepointSVG(const stbtt_fontinfo * info , int unicode_codepoint , const char * * svg );
 static int stbtt_GetGlyphSVG(const stbtt_fontinfo * info , int gl , const char * * svg );
 static void stbtt_FreeBitmap(stbtt_uint8 * bitmap , void * userdata );
 static stbtt_uint8* stbtt_GetCodepointBitmap(const stbtt_fontinfo * info , float scale_x , float scale_y , int codepoint , int * width , int * height , int * xoff , int * yoff );
 static stbtt_uint8* stbtt_GetCodepointBitmapSubpixel(const stbtt_fontinfo * info , float scale_x , float scale_y , float shift_x , float shift_y , int codepoint , int * width , int * height , int * xoff , int * yoff );
 static void stbtt_MakeCodepointBitmap(const stbtt_fontinfo * info , stbtt_uint8 * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , int codepoint );
 static void stbtt_MakeCodepointBitmapSubpixel(const stbtt_fontinfo * info , stbtt_uint8 * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , float shift_x , float shift_y , int codepoint );
 static void stbtt_MakeCodepointBitmapSubpixelPrefilter(const stbtt_fontinfo * info , stbtt_uint8 * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , float shift_x , float shift_y , int oversample_x , int oversample_y , float * sub_x , float * sub_y , int codepoint );
 static void stbtt_GetCodepointBitmapBox(const stbtt_fontinfo * font , int codepoint , float scale_x , float scale_y , int * ix0 , int * iy0 , int * ix1 , int * iy1 );
 static void stbtt_GetCodepointBitmapBoxSubpixel(const stbtt_fontinfo * font , int codepoint , float scale_x , float scale_y , float shift_x , float shift_y , int * ix0 , int * iy0 , int * ix1 , int * iy1 );
 static stbtt_uint8* stbtt_GetGlyphBitmap(const stbtt_fontinfo * info , float scale_x , float scale_y , int glyph , int * width , int * height , int * xoff , int * yoff );
 static stbtt_uint8* stbtt_GetGlyphBitmapSubpixel(const stbtt_fontinfo * info , float scale_x , float scale_y , float shift_x , float shift_y , int glyph , int * width , int * height , int * xoff , int * yoff );
 static void stbtt_MakeGlyphBitmap(const stbtt_fontinfo * info , stbtt_uint8 * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , int glyph );
 static void stbtt_MakeGlyphBitmapSubpixel(const stbtt_fontinfo * info , stbtt_uint8 * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , float shift_x , float shift_y , int glyph );
 static void stbtt_MakeGlyphBitmapSubpixelPrefilter(const stbtt_fontinfo * info , stbtt_uint8 * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , float shift_x , float shift_y , int oversample_x , int oversample_y , float * sub_x , float * sub_y , int glyph );
 static void stbtt_GetGlyphBitmapBox(const stbtt_fontinfo * font , int glyph , float scale_x , float scale_y , int * ix0 , int * iy0 , int * ix1 , int * iy1 );
 static void stbtt_GetGlyphBitmapBoxSubpixel(const stbtt_fontinfo * font , int glyph , float scale_x , float scale_y , float shift_x , float shift_y , int * ix0 , int * iy0 , int * ix1 , int * iy1 );
 static void stbtt_FreeSDF(stbtt_uint8 * bitmap , void * userdata );
 static stbtt_uint8* stbtt_GetGlyphSDF(const stbtt_fontinfo * info , float scale , int glyph , int padding , stbtt_uint8 onedge_value , float pixel_dist_scale , int * width , int * height , int * xoff , int * yoff );
 static stbtt_uint8* stbtt_GetCodepointSDF(const stbtt_fontinfo * info , float scale , int codepoint , int padding , stbtt_uint8 onedge_value , float pixel_dist_scale , int * width , int * height , int * xoff , int * yoff );
 static int stbtt_FindMatchingFont(const stbtt_uint8 * fontdata , const char * name , int flags );
 static int stbtt_CompareUTF8toUTF16_bigendian(const char * s1 , int len1 , const char * s2 , int len2 );
 static stbtt_uint16 ttUSHORT(stbtt_uint8 * p );
 static stbtt_int16 ttSHORT(stbtt_uint8 * p );
 static stbtt_uint32 ttULONG(stbtt_uint8 * p );
 static stbtt_int32 ttLONG(stbtt_uint8 * p );
 static int stbtt__isfont(stbtt_uint8 * font );
 static stbtt_uint32 stbtt__find_table(stbtt_uint8 * data , stbtt_uint32 fontstart , const char * tag );
 static int stbtt_GetFontOffsetForIndex_internal(stbtt_uint8 * font_collection , int index );
 static int stbtt_GetNumberOfFonts_internal(stbtt_uint8 * font_collection );
 static int stbtt_FindGlyphIndex(const stbtt_fontinfo * info , int unicode_codepoint );
 static int stbtt__GetGlyfOffset(const stbtt_fontinfo * info , int glyph_index );
 static int stbtt__GetGlyphInfoT2(const stbtt_fontinfo * info , int glyph_index , int * x0 , int * y0 , int * x1 , int * y1 );
 static int stbtt_GetGlyphBox(const stbtt_fontinfo * info , int glyph_index , int * x0 , int * y0 , int * x1 , int * y1 );
 static int stbtt_GetCodepointBox(const stbtt_fontinfo * info , int codepoint , int * x0 , int * y0 , int * x1 , int * y1 );
 static int stbtt_IsGlyphEmpty(const stbtt_fontinfo * info , int glyph_index );
 static int stbtt__GetGlyphInfoT2(const stbtt_fontinfo * info , int glyph_index , int * x0 , int * y0 , int * x1 , int * y1 );
 static void stbtt_GetGlyphHMetrics(const stbtt_fontinfo * info , int glyph_index , int * advanceWidth , int * leftSideBearing );
 static int stbtt_GetKerningTableLength(const stbtt_fontinfo * info );
 static int stbtt__GetGlyphKernInfoAdvance(const stbtt_fontinfo * info , int glyph1 , int glyph2 );
 static stbtt_int32 stbtt__GetCoverageIndex(stbtt_uint8 * coverageTable , int glyph );
 static stbtt_int32 stbtt__GetGlyphClass(stbtt_uint8 * classDefTable , int glyph );
Image_Letter* create_font_data(API * api );
static char const *sglg_Memory_Arena_Error_to_string(Memory_Arena_Error e);
static int sglg_Memory_Arena_Error_count(Memory_Arena_Error e);
static char const *sglg_Key_to_string(Key e);
static Int sglg_Key_count(Key e);
static char const *sglg_Memory_Index_to_string(Memory_Index e);
static Int sglg_Memory_Index_count(Memory_Index e);

// Helpers
#define sglg_internal_enum_Memory_Arena_Error (7)
#define sglg_internal_enum_Key (58)
#define sglg_internal_enum_Memory_Index (7)
