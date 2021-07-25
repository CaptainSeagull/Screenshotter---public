enum Type {
    Type_unknown,
    Type_char,
    Type_int,
    Type_unsigned,
    Type_signed,
    Type_short,
    Type_long,
    Type_float,
    Type_double,
    Type_wchar_t,
    Type_bool,
    Type_void,
    Type_uint8_t,
    Type_uint16_t,
    Type_uint32_t,
    Type_uint64_t,
    Type_int8_t,
    Type_int16_t,
    Type_int32_t,
    Type_int64_t,
    Type_uintptr_t,
    Type_intptr_t,
    Type_Memory_Arena_Error,
    Type_Memory_Group,
    Type_Memory,
    Type_Internal_Push_Info,
    Type_String,
    Type_String_To_Int_Result,
    Type_String_To_Float_Result,
    Type_Find_Index_Result,
    Type_stbsp__context,
    Type_Int,
    Type_File,
    Type_Key,
    Type_Platform_Callbacks,
    Type_Bitmap,
    Type_Settings,
    Type_Window_Info,
    Type_API,
    Type_Memory_Index,
    Type_Config,
    Type_Image,
    Type_Bitmap_Header,
    Type___m128i,
    Type___m128,
    Type_V2,
    Type_V3,
    Type_V4,
    Type_Lane_F32,
    Type_Lane_U32,
    Type_Lane_V2,
    Type_Lane_V3,
    Type_Lane_V4,
    Type_Lane_M2x2,
    Type_stbtt_pack_context,
    Type_stbtt_fontinfo,
    Type_stbrp_rect,
    Type_stbtt_kerningentry,
    Type_V2u,
    Type_BB,
    Type_Render_Entity,
    Type_Image_Letter,
    Type_Rect,
    Type_Image_Rect,
    Type_Word,
    Type_Line,
    Type_Render_Entity_For_Size,
    Type_Render_Image,
    Type_Internal,
    Type_Font,
    Type_Renderer,
    Type_Image_Letter_Result,
    Type_Entry,
    Type_DLL_Data,
};

// Utils
#define ENTITY_PATTERN(Type) PREPROC_CONCAT(UNION_OF_SUBCLASSES_INTERNAL_Memory_Arena_Error_count, Type)
#define PREPROC_CONCAT(a, b) a##b
#define ENUM_COUNT(name) PREPROC_CONCAT(internal_enum_, name)
static int sgl_generated_string_compare(char const *a, uint32_t a_len, char const *b, uint32_t b_len);
static uint64_t get_enum_count(Type type);
static uint64_t type_to_size(Type type);
static Type string_to_type(char const *s, uint64_t l);

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
typedef __m128i Lane_U32_Internal ;
typedef __m128 Lane_F32_Internal ;
typedef char stbtt__check_size32 [ sizeof ( int32_t ) == 4 ? 1 : - 1 ] ;
typedef char stbtt__check_size16 [ sizeof ( int16_t ) == 2 ? 1 : - 1 ] ;
typedef int stbtt__test_oversample_pow2 [ ( 8 & ( 8 - 1 ) ) == 0 ? 1 : - 1 ] ;

// Forward declared structs

struct Memory_Group;
struct Memory;
struct Internal_Push_Info;
struct String;
struct String_To_Int_Result;
struct String_To_Float_Result;
struct Find_Index_Result;
struct stbsp__context;
struct File;
enum Key : Int;

struct Platform_Callbacks;
struct Bitmap;
struct Settings;
struct Window_Info;
struct API;
enum Memory_Index : Int;

struct Config;
struct Image;
struct Bitmap_Header;
union V2;
union V3;
union V4;
struct Lane_F32;
struct Lane_U32;
union Lane_V2;
union Lane_V3;
union Lane_V4;
struct Lane_M2x2;
struct stbtt_pack_context;
struct stbtt_fontinfo;
struct stbrp_rect;
struct stbtt_pack_context;
struct stbtt_fontinfo;
struct stbtt_kerningentry;
struct V2u;
struct BB;
struct Render_Entity;
struct Image_Letter;
struct Rect;
struct Image_Rect;
struct Word;
struct Line;
struct Render_Entity_For_Size;
struct Render_Image;
struct Internal;
struct Font;
struct Renderer;
struct Image_Letter_Result;
struct Entry;
struct DLL_Data;

// Forward declaration of functions
uint64_t get_memory_base_size(void );
Memory create_memory_base(void * base_memory , uintptr_t * inputs , uintptr_t inputs_count );
Memory_Group* get_memory_group(Memory * memory , uintptr_t buffer_index );
void* memory_push_(Memory * memory , uintptr_t buffer_index , uintptr_t size , char * fname , int line , uintptr_t alignment  );
void memory_pop(Memory * memory , void * memory_buffer );
void memory_clear_entire_group(Memory * memory , uintptr_t buffer_index );
 static uintptr_t internal_get_alignment_offset(Memory * memory , void * memory_base , uintptr_t current_index , uintptr_t alignment );
uint64_t get_memory_base_size(void );
Memory create_memory_base(void * base_memory , uintptr_t * inputs , uintptr_t inputs_count );
 static void memory_arena_zero(void * dest , uintptr_t size );
Memory_Group* get_memory_group(Memory * memory , uintptr_t buffer_index );
void* memory_push_(Memory * memory , uintptr_t buffer_index , uintptr_t size , char * file , int line , uintptr_t alignment );
void memory_pop(Memory * memory , void * memory_buffer );
void memory_clear_entire_group(Memory * memory , uintptr_t buffer_index );
String create_string(char * str , int len  );
String create_string(char const * str , int len  );
String create_substring(String str , int start , int end  );
int string_compare(String a , String b );
int operator==(String a , String b );
int string_contains(String a , String b );
int string_contains(String str , char target );
Find_Index_Result find_index(String str , char target , int find_last  );
int string_length(char * str );
int string_length(char const * str );
String_To_Int_Result string_to_int(String s );
String_To_Float_Result string_to_float(String s );
int string_copy(char * dst , char * src );
int string_copy(char const * dst , char const * src );
int string_copy(char * dst , char const * src );
int string_copy(char * dst , char * src , int len );
char to_upper(char a );
char to_lower(char a );
String create_string(char * str , int len );
String create_string(char const * str , int len );
String create_substring(String str , int start , int end );
int string_compare(String a , String b );
int operator==(String a , String b );
int string_contains(String a , String b );
int string_contains(String str , char target );
Find_Index_Result find_index(String str , char target , int find_last );
int string_length(char * str );
int string_length(char const * str );
 static int internal_char_to_int(char c );
String_To_Int_Result string_to_int(String s );
String_To_Float_Result string_to_float(String s );
int string_copy(char * dst , char * src );
int string_copy(char const * dst , char const * src );
int string_copy(char * dst , char const * src );
int string_copy(char const * dst , char * src );
int string_copy(char * dst , char * src , int len );
char to_lower(char a );
char to_upper(char a );
int stbsp_sprintf(char * buf , char const * fmt , ... );
int stbsp_snprintf(char * buf , int count , char const * fmt , ... );
void stbsp_set_separators(char comma , char period );
 static int32_t stbsp__real_to_str(char const * * start , uint32_t * len , char * out , int32_t * decimal_pos , double value , uint32_t frac_digits );
 static int32_t stbsp__real_to_parts(int64_t * bits , int32_t * expo , double value );
void stbsp_set_separators(char pcomma , char pperiod );
 static char* stbsp__clamp_callback(char * buf , void * user , int len );
int stbsp_snprintf(char * buf , int count , char const * fmt , ... );
 static int32_t stbsp__real_to_parts(int64_t * bits , int32_t * expo , double value );
 static U32 safe_truncate_size_64(U64 v );
 static Void zero(Void * m , U64 s );
 static Void copy(Void * dst , Void * src , U64 size );
 static Void set(Void * dst , U8 v , U64 size );
 static Void flip_image(Void * dst_pixels , Void * src_pixels , Int width , Int height );
 static Char* memory_push_string(Memory * mem , Memory_Index idx , String s , Int padding  );
 static Void write_image_to_disk(API * api , Memory * memory , Image * image , String file_name );
 static Image load_image(API * api , String file_name );
 static float lane_max(float a , float b );
 static float minf32(float a , float b );
 static float maxf32(float a , float b );
 static uint32_t maxu32(uint32_t a , uint32_t b );
 static uint32_t minu32(uint32_t a , uint32_t b );
 static float clamp(float a , float l , float u );
 static float clamp01(float a );
 static float lerp(float t , float a , float b );
 static float random_unilateral(uint32_t * entropy_series );
 static float random_bilateral(uint32_t * entropy_series );
 static uint32_t xorshift32(uint32_t * entropy_series );
 static V2 v2(V2 a );
 static V2 v2(float x , float y );
 static V2 v2(float a );
 static V2 operator*(V2 a , float b );
 static V2 operator*(float a , V2 b );
 static V2 operator*=(V2 a , float b );
 static V2 operator/(float a , V2 b );
 static V2 operator/(V2 a , float b );
 static V2 operator/=(V2 a , float b );
 static V2 operator+(V2 a , V2 b );
 static V2 operator+(V2 a , V2 b );
 static V2 operator+(V2 a , V2 b );
 static V2 operator+=(V2 a , V2 b );
 static V2 operator-(V2 a , V2 b );
 static V2 operator-(V2 a , V2 b );
 static V2 operator-(V2 a , V2 b );
 static V2 operator-(V2 a );
 static V2 operator-=(V2 a , V2 b );
 static V2 operator&(uint32_t a , V2 b );
 static V2 normalise_or_zero(V2 a );
 static float inner(V2 a , V2 b );
 static V2 hadamard(V2 a , V2 b );
 static float length_sq(V2 a );
 static float length(V2 a );
 static V2 normalise(V2 a );
 static V2 lerp(float t , V2 a , V2 b );
 static V3 v3(V3 a );
 static V3 v3(float x , float y , float z );
 static V3 v3(float a );
 static V3 operator*(V3 a , float b );
 static V3 operator*(float a , V3 b );
 static V3 operator*=(V3 a , float b );
 static V3 operator/(V3 a , float b );
 static V3 operator/=(V3 a , float b );
 static V3 operator+(V3 a , V3 b );
 static V3 operator+(V3 a , V3 b );
 static V3 operator+(V3 a , V3 b );
 static V3 operator+=(V3 a , V3 b );
 static V3 operator-(V3 a , V3 b );
 static V3 operator-(V3 a , V3 b );
 static V3 operator-(V3 a , V3 b );
 static V3 operator-(V3 a );
 static V3 operator-=(V3 a , V3 b );
 static V3 operator&(uint32_t a , V3 b );
 static float inner(V3 a , V3 b );
 static V3 hadamard(V3 a , V3 b );
 static V3 cross(V3 a , V3 b );
 static float length_sq(V3 a );
 static float length(V3 a );
 static V3 normalise(V3 a );
 static V3 normalise_or_zero(V3 a );
 static V4 v4(V4 a );
 static V4 v4(float x , float y , float z , float w );
 static V4 v4(float a );
 static V4 operator*(V4 a , float b );
 static V4 operator*(float a , V4 b );
 static V4 operator*=(V4 a , float b );
 static V4 operator/(float a , V4 b );
 static V4 operator/(V4 a , float b );
 static V4 operator/=(V4 a , float b );
 static V4 operator+(V4 a , V4 b );
 static V4 operator+(V4 a , V4 b );
 static V4 operator+(V4 a , V4 b );
 static V4 operator+=(V4 a , V4 b );
 static V4 operator-(V4 a , V4 b );
 static V4 operator-(V4 a , V4 b );
 static V4 operator-(V4 a , V4 b );
 static V4 operator-(V4 a );
 static V4 operator-=(V4 a , V4 b );
 static V4 operator&(uint32_t a , V4 b );
 static V4 normalise_or_zero(V4 a );
 static float inner(V4 a , V4 b );
 static V4 hadamard(V4 a , V4 b );
 static float length_sq(V4 a );
 static float length(V4 a );
 static V4 normalise(V4 a );
 static void conditional_assign(Lane_U32 mask , Lane_F32 * dst , Lane_F32 src );
 static Lane_F32 lane_f32(float a );
 static Lane_F32 lane_f32(float a , float b , float c , float d , float e , float f , float g , float h );
 static Lane_F32 lane_f32_from_u32(uint32_t a );
 static Lane_F32 lane_f32_from_u32(Lane_U32 a );
 static Lane_F32 lane_f32_zero(void );
 static Lane_F32 lane_f32_floor(Lane_F32 a );
 static float extract(Lane_F32 a , uint32_t lane );
 static Lane_F32 operator&(Lane_U32 a , Lane_F32 b );
 static Lane_F32 operator*(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator*(Lane_F32 a , float b );
 static Lane_F32 operator*(float a , Lane_F32 b );
 static Lane_F32 operator*=(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator/(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator/(Lane_F32 a , float b );
 static Lane_F32 operator/(float a , Lane_F32 b );
 static Lane_F32 operator/=(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator+(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator+(Lane_F32 a , float b );
 static Lane_F32 operator+(float a , Lane_F32 b );
 static Lane_F32 operator+=(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator++(Lane_F32 a );
 static Lane_F32 operator-(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator-(Lane_F32 a );
 static Lane_F32 operator-(Lane_F32 a , float b );
 static Lane_F32 operator-(float a , Lane_F32 b );
 static Lane_F32 operator-=(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator--(Lane_F32 a );
 static Lane_F32 square_root(Lane_F32 a );
 static float square_root(float a );
 static Lane_F32 rsquare_root(Lane_F32 a );
 static float rsquare_root(float a );
 static Lane_F32 maxf32(Lane_F32 a , Lane_F32 b );
 static Lane_F32 maxf32(float a , Lane_F32 b );
 static Lane_F32 maxf32(Lane_F32 a , float b );
 static Lane_F32 minf32(Lane_F32 a , Lane_F32 b );
 static Lane_F32 minf32(float a , Lane_F32 b );
 static Lane_F32 minf32(Lane_F32 a , float b );
 static Lane_F32 clamp(Lane_F32 a , Lane_F32 l , Lane_F32 u );
 static Lane_F32 clamp(Lane_F32 a , float l , float u );
 static Lane_F32 clamp01(Lane_F32 a );
 static Lane_F32 lerp(Lane_F32 t , Lane_F32 a , Lane_F32 b );
 static Lane_F32 lerp(float t , Lane_F32 a , Lane_F32 b );
 static float horizontal_add(Lane_F32 a );
 static Lane_F32 gather_f32_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static void conditional_assign(Lane_U32 mask , Lane_U32 * dst , Lane_U32 src );
 static Lane_U32 lane_u32(uint32_t a );
 static Lane_U32 lane_u32(uint32_t a , uint32_t b , uint32_t c , uint32_t d , uint32_t e , uint32_t f , uint32_t g , uint32_t h );
 static Lane_U32 lane_u32_from_f32(float a );
 static Lane_U32 lane_u32_from_f32(Lane_F32 a );
 static Lane_U32 and_not(Lane_U32 a , Lane_U32 b );
 static Lane_U32 not_zero(Lane_U32 a );
 static uint32_t extract(Lane_U32 a , uint32_t lane );
 static int lane_mask_is_zeroed(Lane_U32 a );
 static int lane_mask_is_full(Lane_U32 a );
 static uint64_t horizontal_add(Lane_U32 a );
 static Lane_U32 operator<<(Lane_U32 a , uint32_t s );
 static Lane_U32 operator>>(Lane_U32 a , uint32_t s );
 static Lane_U32 operator^(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator|(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator&(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator!(Lane_U32 a );
 static Lane_U32 operator*(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator*(Lane_U32 a , uint32_t b );
 static Lane_U32 operator*(uint32_t a , Lane_U32 b );
 static Lane_U32 operator*=(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator+(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator+(Lane_U32 a , uint32_t b );
 static Lane_U32 operator+(uint32_t a , Lane_U32 b );
 static Lane_U32 operator+=(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator-(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator-(Lane_U32 a );
 static Lane_U32 operator-(Lane_U32 a , uint32_t b );
 static Lane_U32 operator-(uint32_t a , Lane_U32 b );
 static Lane_U32 operator-=(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator==(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator!=(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator==(Lane_U32 a , uint32_t b );
 static Lane_U32 operator!=(Lane_U32 a , uint32_t b );
 static Lane_U32 gather_u32_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_V2 lane_v2(V2 a );
 static Lane_V2 lane_v2(Lane_F32 x , Lane_F32 y );
 static Lane_V2 lane_v2(float x , float y );
 static Lane_V2 lane_v2(Lane_F32 a );
 static Lane_V2 lane_v2(float a );
 static Lane_V2 lane_v2_zero(void );
 static Lane_V2 operator*(Lane_V2 a , Lane_F32 b );
 static Lane_V2 operator*(Lane_F32 a , Lane_V2 b );
 static Lane_V2 operator*=(Lane_V2 a , Lane_F32 b );
 static Lane_V2 operator*(Lane_V2 a , float b );
 static Lane_V2 operator*(float a , Lane_V2 b );
 static Lane_V2 operator*=(Lane_V2 a , float b );
 static Lane_V2 operator/(Lane_V2 a , Lane_F32 b );
 static Lane_V2 operator/=(Lane_V2 a , Lane_F32 b );
 static Lane_V2 operator/(Lane_V2 a , float b );
 static Lane_V2 operator/=(Lane_V2 a , float b );
 static Lane_V2 operator+(Lane_V2 a , Lane_V2 b );
 static Lane_V2 operator+(Lane_V2 a , V2 b );
 static Lane_V2 operator+(V2 a , Lane_V2 b );
 static Lane_V2 operator+=(Lane_V2 a , Lane_V2 b );
 static Lane_V2 operator-(Lane_V2 a , Lane_V2 b );
 static Lane_V2 operator-(Lane_V2 a , V2 b );
 static Lane_V2 operator-(V2 a , Lane_V2 b );
 static Lane_V2 operator-(Lane_V2 a );
 static Lane_V2 operator-=(Lane_V2 a , Lane_V2 b );
 static Lane_U32 operator==(Lane_V2 a , Lane_V2 b );
 static Lane_V2 operator&(Lane_U32 a , Lane_V2 b );
 static Lane_V2 normalise_or_zero(Lane_V2 a );
 static Lane_F32 inner(Lane_V2 a , Lane_V2 b );
 static Lane_V2 hadamard(Lane_V2 a , Lane_V2 b );
 static Lane_F32 length_sq(Lane_V2 a );
 static Lane_F32 length(Lane_V2 a );
 static Lane_V2 normalise(Lane_V2 a );
 static Lane_V2 lerp(Lane_F32 t , Lane_V2 a , Lane_V2 b );
 static Lane_V2 lerp(float t , Lane_V2 a , Lane_V2 b );
 static V2 extract(Lane_V2 a , uint32_t lane );
 static void conditional_assign(Lane_U32 mask , Lane_V2 * dst , Lane_V2 src );
 static V2 horizontal_add(Lane_V2 a );
 static Lane_V2 gather_v2_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_V3 lane_v3(V3 a );
 static Lane_V3 lane_v3(Lane_F32 x , Lane_F32 y , Lane_F32 z );
 static Lane_V3 lane_v3(float x , float y , float z );
 static Lane_V3 lane_v3(Lane_F32 a );
 static Lane_V3 lane_v3(float a );
 static Lane_V3 lane_v3_zero(void );
 static Lane_V3 operator*(Lane_V3 a , Lane_F32 b );
 static Lane_V3 operator*(Lane_F32 a , Lane_V3 b );
 static Lane_V3 operator*=(Lane_V3 a , Lane_F32 b );
 static Lane_V3 operator*(Lane_V3 a , float b );
 static Lane_V3 operator*(float a , Lane_V3 b );
 static Lane_V3 operator*=(Lane_V3 a , float b );
 static Lane_V3 operator/(Lane_V3 a , Lane_F32 b );
 static Lane_V3 operator/=(Lane_V3 a , Lane_F32 b );
 static Lane_V3 operator/(Lane_V3 a , float b );
 static Lane_V3 operator/=(Lane_V3 a , float b );
 static Lane_V3 operator+(Lane_V3 a , Lane_V3 b );
 static Lane_V3 operator+(Lane_V3 a , V3 b );
 static Lane_V3 operator+(V3 a , Lane_V3 b );
 static Lane_V3 operator+=(Lane_V3 a , Lane_V3 b );
 static Lane_V3 operator-(Lane_V3 a , Lane_V3 b );
 static Lane_V3 operator-(Lane_V3 a , V3 b );
 static Lane_V3 operator-(V3 a , Lane_V3 b );
 static Lane_V3 operator-(Lane_V3 a );
 static Lane_V3 operator-=(Lane_V3 a , Lane_V3 b );
 static Lane_U32 operator==(Lane_V3 a , Lane_V3 b );
 static Lane_V3 operator&(Lane_U32 a , Lane_V3 b );
 static Lane_F32 inner(Lane_V3 a , Lane_V3 b );
 static Lane_V3 hadamard(Lane_V3 a , Lane_V3 b );
 static Lane_V3 cross(Lane_V3 a , Lane_V3 b );
 static Lane_F32 length_sq(Lane_V3 a );
 static Lane_F32 length(Lane_V3 a );
 static Lane_V3 normalise(Lane_V3 a );
 static Lane_V3 normalise_or_zero(Lane_V3 a );
 static Lane_V3 lerp(Lane_F32 t , Lane_V3 a , Lane_V3 b );
 static Lane_V3 lerp(float t , Lane_V3 a , Lane_V3 b );
 static V3 extract(Lane_V3 a , uint32_t lane );
 static void conditional_assign(Lane_U32 mask , Lane_V3 * dst , Lane_V3 src );
 static V3 horizontal_add(Lane_V3 a );
 static Lane_V3 gather_v3_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_V4 lane_v4(V4 a );
 static Lane_V4 lane_v4(Lane_F32 x , Lane_F32 y , Lane_F32 z , Lane_F32 w );
 static Lane_V4 lane_v4(float x , float y , float z , float w );
 static Lane_V4 lane_v4(float a );
 static Lane_V4 lane_v4_zero(void );
 static Lane_V4 operator*(Lane_V4 a , Lane_F32 b );
 static Lane_V4 operator*(Lane_F32 a , Lane_V4 b );
 static Lane_V4 operator*=(Lane_V4 a , Lane_F32 b );
 static Lane_V4 operator*(Lane_V4 a , float b );
 static Lane_V4 operator*(float a , Lane_V4 b );
 static Lane_V4 operator*=(Lane_V4 a , float b );
 static Lane_V4 operator/(Lane_V4 a , Lane_F32 b );
 static Lane_V4 operator/=(Lane_V4 a , Lane_F32 b );
 static Lane_V4 operator/(Lane_V4 a , float b );
 static Lane_V4 operator/=(Lane_V4 a , float b );
 static Lane_V4 operator+(Lane_V4 a , Lane_V4 b );
 static Lane_V4 operator+(Lane_V4 a , V4 b );
 static Lane_V4 operator+(V4 a , Lane_V4 b );
 static Lane_V4 operator+=(Lane_V4 a , Lane_V4 b );
 static Lane_V4 operator-(Lane_V4 a , Lane_V4 b );
 static Lane_V4 operator-(Lane_V4 a , V4 b );
 static Lane_V4 operator-(V4 a , Lane_V4 b );
 static Lane_V4 operator-(Lane_V4 a );
 static Lane_V4 operator-=(Lane_V4 a , Lane_V4 b );
 static Lane_U32 operator==(Lane_V4 a , Lane_V4 b );
 static Lane_V4 operator&(Lane_U32 a , Lane_V4 b );
 static Lane_V4 normalise_or_zero(Lane_V4 a );
 static Lane_F32 inner(Lane_V4 a , Lane_V4 b );
 static Lane_V4 hadamard(Lane_V4 a , Lane_V4 b );
 static Lane_F32 length_sq(Lane_V4 a );
 static Lane_F32 length(Lane_V4 a );
 static Lane_V4 normalise(Lane_V4 a );
 static Lane_V4 lerp(Lane_F32 t , Lane_V4 a , Lane_V4 b );
 static Lane_V4 lerp(float t , Lane_V4 a , Lane_V4 b );
 static V4 extract(Lane_V4 a , uint32_t lane );
 static void conditional_assign(Lane_U32 mask , Lane_V4 * dst , Lane_V4 src );
 static V4 horizontal_add(Lane_V4 a );
 static Lane_V4 gather_v4_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_M2x2 lane_outer(V2 a , V2 b );
 static float maxf32(float a , float b );
 static float minf32(float a , float b );
 static uint32_t maxu32(uint32_t a , uint32_t b );
 static uint32_t minu32(uint32_t a , uint32_t b );
 static float clamp(float a , float l , float u );
 static float clamp01(float a );
 static float lerp(float t , float a , float b );
 static Lane_U32 xorshift32(Lane_U32 * entropy_series );
 static Lane_F32 random_unilateral(Lane_U32 * entropy_series );
 static Lane_F32 random_bilateral(Lane_U32 * entropy_series );
 static uint32_t xorshift32(uint32_t * entropy_series );
 static float random_unilateral(uint32_t * entropy_series );
 static float random_bilateral(uint32_t * entropy_series );
 static Lane_U32 operator*(Lane_U32 a , uint32_t b );
 static Lane_U32 operator*(uint32_t a , Lane_U32 b );
 static Lane_U32 operator*=(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator+(Lane_U32 a , uint32_t b );
 static Lane_U32 operator+(uint32_t a , Lane_U32 b );
 static Lane_U32 operator+=(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator-(Lane_U32 a , uint32_t b );
 static Lane_U32 operator-(uint32_t a , Lane_U32 b );
 static Lane_U32 operator-=(Lane_U32 a , Lane_U32 b );
 static uint32_t extract(Lane_U32 a , uint32_t lane );
 static uint64_t horizontal_add(Lane_U32 a );
 static Lane_U32 operator==(Lane_U32 a , uint32_t b );
 static Lane_U32 operator!=(Lane_U32 a , uint32_t b );
 static float extract(Lane_F32 a , uint32_t lane );
 static Lane_F32 clamp(Lane_F32 a , Lane_F32 l , Lane_F32 u );
 static Lane_F32 clamp(Lane_F32 a , float l , float u );
 static Lane_F32 lane_clamp01(Lane_F32 a );
 static Lane_F32 operator*(Lane_F32 a , float b );
 static Lane_F32 operator*(float a , Lane_F32 b );
 static Lane_F32 operator*=(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator/(Lane_F32 a , float b );
 static Lane_F32 operator/(float a , Lane_F32 b );
 static Lane_F32 operator/=(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator+(Lane_F32 a , float b );
 static Lane_F32 operator+(float a , Lane_F32 b );
 static Lane_F32 operator+=(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator-(Lane_F32 a );
 static Lane_F32 operator-(Lane_F32 a , float b );
 static Lane_F32 operator-(float a , Lane_F32 b );
 static Lane_F32 operator-=(Lane_F32 a , Lane_F32 b );
 static float horizontal_add(Lane_F32 a );
 static Lane_U32 operator>(Lane_F32 a , float b );
 static Lane_U32 operator>=(Lane_F32 a , float b );
 static Lane_U32 operator<(Lane_F32 a , float b );
 static Lane_U32 operator<=(Lane_F32 a , float b );
 static Lane_U32 operator==(Lane_F32 a , float b );
 static Lane_U32 operator!=(Lane_F32 a , float b );
 static Lane_F32 maxf32(Lane_F32 a , float b );
 static Lane_F32 maxf32(float a , Lane_F32 b );
 static Lane_F32 minf32(Lane_F32 a , float b );
 static Lane_F32 minf32(float a , Lane_F32 b );
 static Lane_F32 lerp(Lane_F32 t , Lane_F32 a , Lane_F32 b );
 static Lane_F32 lerp(float t , Lane_F32 a , Lane_F32 b );
 static Lane_V2 lane_v2(V2 a );
 static Lane_V2 lane_v2(Lane_F32 x , Lane_F32 y );
 static Lane_V2 lane_v2(float x , float y );
 static Lane_V2 lane_v2(Lane_F32 a );
 static Lane_V2 lane_v2(float a );
 static Lane_V2 normalise_or_zero(Lane_V2 a );
 static Lane_V2 lane_v2_zero(void );
 static Lane_V2 operator*(Lane_V2 a , Lane_F32 b );
 static Lane_V2 operator*(Lane_F32 a , Lane_V2 b );
 static Lane_V2 operator*=(Lane_V2 a , Lane_F32 b );
 static Lane_V2 operator*(Lane_V2 a , float b );
 static Lane_V2 operator*(float a , Lane_V2 b );
 static Lane_V2 operator*=(Lane_V2 a , float b );
 static Lane_V2 operator/(Lane_V2 a , Lane_F32 b );
 static Lane_V2 operator/=(Lane_V2 a , Lane_F32 b );
 static Lane_V2 operator/(Lane_V2 a , float b );
 static Lane_V2 operator/=(Lane_V2 a , float b );
 static Lane_V2 operator+(Lane_V2 a , Lane_V2 b );
 static Lane_V2 operator+(Lane_V2 a , V2 b );
 static Lane_V2 operator+(V2 a , Lane_V2 b );
 static Lane_V2 operator+=(Lane_V2 a , Lane_V2 b );
 static Lane_V2 operator-(Lane_V2 a , Lane_V2 b );
 static Lane_V2 operator-(Lane_V2 a , V2 b );
 static Lane_V2 operator-(V2 a , Lane_V2 b );
 static Lane_V2 operator-(Lane_V2 a );
 static Lane_V2 operator-=(Lane_V2 a , Lane_V2 b );
 static Lane_V2 operator&(Lane_U32 a , Lane_V2 b );
 static Lane_U32 operator==(Lane_V2 a , Lane_V2 b );
 static Lane_F32 inner(Lane_V2 a , Lane_V2 b );
 static Lane_V2 hadamard(Lane_V2 a , Lane_V2 b );
 static Lane_F32 length_sq(Lane_V2 a );
 static Lane_F32 length(Lane_V2 a );
 static Lane_V2 normalise(Lane_V2 a );
 static V2 extract(Lane_V2 a , uint32_t lane );
 static void conditional_assign(Lane_U32 mask , Lane_V2 * dst , Lane_V2 src );
 static V2 horizontal_add(Lane_V2 a );
 static Lane_V2 gather_v2_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_V2 lerp(Lane_F32 t , Lane_V2 a , Lane_V2 b );
 static Lane_V2 lerp(float t , Lane_V2 a , Lane_V2 b );
 static Lane_V3 lane_v3(V3 a );
 static Lane_V3 lane_v3(Lane_F32 x , Lane_F32 y , Lane_F32 z );
 static Lane_V3 lane_v3(float x , float y , float z );
 static Lane_V3 lane_v3(float a );
 static Lane_V3 lane_v3(Lane_F32 a );
 static Lane_V3 normalise_or_zero(Lane_V3 a );
 static Lane_V3 lane_v3_zero(void );
 static Lane_V3 operator*(Lane_V3 a , Lane_F32 b );
 static Lane_V3 operator*(Lane_F32 a , Lane_V3 b );
 static Lane_V3 operator*=(Lane_V3 a , Lane_F32 b );
 static Lane_V3 operator*(Lane_V3 a , float b );
 static Lane_V3 operator*(float a , Lane_V3 b );
 static Lane_V3 operator*=(Lane_V3 a , float b );
 static Lane_V3 operator/(Lane_V3 a , Lane_F32 b );
 static Lane_V3 operator/=(Lane_V3 a , Lane_F32 b );
 static Lane_V3 operator/(Lane_V3 a , float b );
 static Lane_V3 operator/=(Lane_V3 a , float b );
 static Lane_V3 operator+(Lane_V3 a , Lane_V3 b );
 static Lane_V3 operator+(Lane_V3 a , V3 b );
 static Lane_V3 operator+(V3 a , Lane_V3 b );
 static Lane_V3 operator+=(Lane_V3 a , Lane_V3 b );
 static Lane_V3 operator-(Lane_V3 a , Lane_V3 b );
 static Lane_V3 operator-(Lane_V3 a , V3 b );
 static Lane_V3 operator-(V3 a , Lane_V3 b );
 static Lane_V3 operator-(Lane_V3 a );
 static Lane_V3 operator-=(Lane_V3 a , Lane_V3 b );
 static Lane_V3 operator&(Lane_U32 a , Lane_V3 b );
 static Lane_U32 operator==(Lane_V3 a , Lane_V3 b );
 static Lane_F32 inner(Lane_V3 a , Lane_V3 b );
 static Lane_V3 hadamard(Lane_V3 a , Lane_V3 b );
 static Lane_V3 cross(Lane_V3 a , Lane_V3 b );
 static Lane_F32 length_sq(Lane_V3 a );
 static Lane_F32 length(Lane_V3 a );
 static Lane_V3 normalise(Lane_V3 a );
 static V3 extract(Lane_V3 a , uint32_t lane );
 static void conditional_assign(Lane_U32 mask , Lane_V3 * dst , Lane_V3 src );
 static V3 horizontal_add(Lane_V3 a );
 static Lane_V3 gather_v3_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_V3 lerp(Lane_F32 t , Lane_V3 a , Lane_V3 b );
 static Lane_V3 lerp(float t , Lane_V3 a , Lane_V3 b );
 static Lane_V4 lane_v4(V4 a );
 static Lane_V4 lane_v4(Lane_F32 x , Lane_F32 y , Lane_F32 z , Lane_F32 w );
 static Lane_V4 lane_v4(float x , float y , float z , float w );
 static Lane_V4 lane_v4(Lane_F32 a );
 static Lane_V4 lane_v4(float a );
 static Lane_V4 normalise_or_zero(Lane_V4 a );
 static Lane_V4 lane_v4_zero(void );
 static Lane_V4 operator*(Lane_V4 a , Lane_F32 b );
 static Lane_V4 operator*(Lane_F32 a , Lane_V4 b );
 static Lane_V4 operator*=(Lane_V4 a , Lane_F32 b );
 static Lane_V4 operator*(Lane_V4 a , float b );
 static Lane_V4 operator*(float a , Lane_V4 b );
 static Lane_V4 operator*=(Lane_V4 a , float b );
 static Lane_V4 operator/(Lane_V4 a , Lane_F32 b );
 static Lane_V4 operator/=(Lane_V4 a , Lane_F32 b );
 static Lane_V4 operator/(Lane_V4 a , float b );
 static Lane_V4 operator/=(Lane_V4 a , float b );
 static Lane_V4 operator+(Lane_V4 a , Lane_V4 b );
 static Lane_V4 operator+(Lane_V4 a , V4 b );
 static Lane_V4 operator+(V4 a , Lane_V4 b );
 static Lane_V4 operator+=(Lane_V4 a , Lane_V4 b );
 static Lane_V4 operator-(Lane_V4 a , Lane_V4 b );
 static Lane_V4 operator-(Lane_V4 a , V4 b );
 static Lane_V4 operator-(V4 a , Lane_V4 b );
 static Lane_V4 operator-(Lane_V4 a );
 static Lane_V4 operator-=(Lane_V4 a , Lane_V4 b );
 static Lane_V4 operator&(Lane_U32 a , Lane_V4 b );
 static Lane_U32 operator==(Lane_V4 a , Lane_V4 b );
 static Lane_F32 inner(Lane_V4 a , Lane_V4 b );
 static Lane_V4 hadamard(Lane_V4 a , Lane_V4 b );
 static Lane_F32 length_sq(Lane_V4 a );
 static Lane_F32 length(Lane_V4 a );
 static Lane_V4 normalise(Lane_V4 a );
 static V4 extract(Lane_V4 a , uint32_t lane );
 static void conditional_assign(Lane_U32 mask , Lane_V4 * dst , Lane_V4 src );
 static V4 horizontal_add(Lane_V4 a );
 static Lane_V4 gather_v4_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_V4 conditional_gather_v4_internal(Lane_U32 mask , void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_V4 lerp(Lane_F32 t , Lane_V4 a , Lane_V4 b );
 static Lane_V4 lerp(float t , Lane_V4 a , Lane_V4 b );
 static V2 v2(V2 a );
 static V2 v2(float x , float y );
 static V2 v2(float a );
 static V2 normalise_or_zero(V2 a );
 static V2 operator*(V2 a , float b );
 static V2 operator*(float a , V2 b );
 static V2 operator*=(V2 a , float b );
 static V2 operator/(float a , V2 b );
 static V2 operator/(V2 a , float b );
 static V2 operator/=(V2 a , float b );
 static V2 operator+(V2 a , V2 b );
 static V2 operator+=(V2 a , V2 b );
 static V2 operator-(V2 a , V2 b );
 static V2 operator-(V2 a );
 static V2 operator-=(V2 a , V2 b );
 static V2 operator&(uint32_t a , V2 b );
 static float inner(V2 a , V2 b );
 static V2 hadamard(V2 a , V2 b );
 static float length_sq(V2 a );
 static float length(V2 a );
 static V2 normalise(V2 a );
 static V2 lerp(float t , V2 a , V2 b );
 static V3 v3(V3 a );
 static V3 v3(float x , float y , float z );
 static V3 v3(float a );
 static V3 normalise_or_zero(V3 a );
 static V3 operator*(V3 a , float b );
 static V3 operator*(float a , V3 b );
 static V3 operator*=(V3 a , float b );
 static V3 operator/(float a , V3 b );
 static V3 operator/(V3 a , float b );
 static V3 operator/=(V3 a , float b );
 static V3 operator+(V3 a , V3 b );
 static V3 operator+=(V3 a , V3 b );
 static V3 operator-(V3 a , V3 b );
 static V3 operator-(V3 a );
 static V3 operator-=(V3 a , V3 b );
 static V3 operator&(uint32_t a , V3 b );
 static float inner(V3 a , V3 b );
 static V3 hadamard(V3 a , V3 b );
 static V3 cross(V3 a , V3 b );
 static float length_sq(V3 a );
 static float length(V3 a );
 static V3 normalise(V3 a );
 static V4 v4(V4 a );
 static V4 v4(float x , float y , float z , float w );
 static V4 v4(float a );
 static V4 normalise_or_zero(V4 a );
 static V4 operator*(V4 a , float b );
 static V4 operator*(float a , V4 b );
 static V4 operator*=(V4 a , float b );
 static V4 operator/(float a , V4 b );
 static V4 operator/(V4 a , float b );
 static V4 operator/=(V4 a , float b );
 static V4 operator+(V4 a , V4 b );
 static V4 operator+=(V4 a , V4 b );
 static V4 operator-(V4 a , V4 b );
 static V4 operator-(V4 a );
 static V4 operator-=(V4 a , V4 b );
 static V4 operator&(uint32_t a , V4 b );
 static float inner(V4 a , V4 b );
 static V4 hadamard(V4 a , V4 b );
 static float length_sq(V4 a );
 static float length(V4 a );
 static V4 normalise(V4 a );
float square_root(float a );
 static Lane_U32 lane_u32(uint32_t a );
 static Lane_U32 lane_u32(uint32_t a , uint32_t b , uint32_t c , uint32_t d , uint32_t e , uint32_t f , uint32_t g , uint32_t h );
 static Lane_U32 lane_u32_from_f32(float a );
 static Lane_U32 lane_u32_from_f32(Lane_F32 a );
 static Lane_U32 operator<<(Lane_U32 a , uint32_t s );
 static Lane_U32 operator>>(Lane_U32 a , uint32_t s );
 static Lane_U32 operator^(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator|(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator&(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator*(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator+(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator-(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator-(Lane_U32 a );
 static Lane_U32 operator==(Lane_U32 a , Lane_U32 b );
 static Lane_U32 operator!=(Lane_U32 a , Lane_U32 b );
 static Lane_U32 and_not(Lane_U32 a , Lane_U32 b );
 static Lane_U32 not_zero(Lane_U32 a );
 static void conditional_assign(Lane_U32 mask , Lane_U32 * dst , Lane_U32 src );
 static int lane_mask_is_zeroed(Lane_U32 a );
 static int lane_mask_is_full(Lane_U32 a );
 static Lane_U32 operator!(Lane_U32 a );
 static Lane_U32 gather_u32_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static Lane_F32 lane_f32(float a );
 static Lane_F32 lane_f32(float a , float b , float c , float d , float e , float f , float g , float h );
 static Lane_F32 lane_f32_from_u32(uint32_t a );
 static Lane_F32 lane_f32_from_u32(Lane_U32 a );
 static Lane_F32 lane_f32_zero(void );
 static Lane_F32 lane_f32_floor(Lane_F32 a );
 static Lane_F32 operator&(Lane_U32 a , Lane_F32 b );
 static Lane_F32 operator*(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator/(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator+(Lane_F32 a , Lane_F32 b );
 static Lane_F32 operator-(Lane_F32 a , Lane_F32 b );
 static Lane_U32 operator>(Lane_F32 a , Lane_F32 b );
 static Lane_U32 operator>=(Lane_F32 a , Lane_F32 b );
 static Lane_U32 operator<(Lane_F32 a , Lane_F32 b );
 static Lane_U32 operator<=(Lane_F32 a , Lane_F32 b );
 static Lane_U32 operator==(Lane_F32 a , Lane_F32 b );
 static Lane_U32 operator!=(Lane_F32 a , Lane_F32 b );
 static void conditional_assign(Lane_U32 mask , Lane_F32 * dst , Lane_F32 src );
 static Lane_F32 square_root(Lane_F32 a );
 static Lane_F32 rsquare_root(Lane_F32 a );
 static Lane_F32 maxf32(Lane_F32 a , Lane_F32 b );
 static Lane_F32 minf32(Lane_F32 a , Lane_F32 b );
 static Lane_F32 gather_f32_internal(void * ptr , uint64_t stride , Lane_U32 indices );
 static void stbtt_GetScaledFontVMetrics(const uint8_t * fontdata , int index , float size , float * ascent , float * descent , float * lineGap );
 static int stbtt_GetNumberOfFonts(const uint8_t * data );
 static int stbtt_GetFontOffsetForIndex(const uint8_t * data , int index );
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
 static void stbtt_FreeBitmap(uint8_t * bitmap , void * userdata );
 static uint8_t* stbtt_GetCodepointBitmap(const stbtt_fontinfo * info , float scale_x , float scale_y , int codepoint , int * width , int * height , int * xoff , int * yoff );
 static uint8_t* stbtt_GetCodepointBitmapSubpixel(const stbtt_fontinfo * info , float scale_x , float scale_y , float shift_x , float shift_y , int codepoint , int * width , int * height , int * xoff , int * yoff );
 static void stbtt_MakeCodepointBitmap(const stbtt_fontinfo * info , uint8_t * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , int codepoint );
 static void stbtt_MakeCodepointBitmapSubpixel(const stbtt_fontinfo * info , uint8_t * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , float shift_x , float shift_y , int codepoint );
 static void stbtt_MakeCodepointBitmapSubpixelPrefilter(const stbtt_fontinfo * info , uint8_t * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , float shift_x , float shift_y , int oversample_x , int oversample_y , float * sub_x , float * sub_y , int codepoint );
 static void stbtt_GetCodepointBitmapBox(const stbtt_fontinfo * font , int codepoint , float scale_x , float scale_y , int * ix0 , int * iy0 , int * ix1 , int * iy1 );
 static void stbtt_GetCodepointBitmapBoxSubpixel(const stbtt_fontinfo * font , int codepoint , float scale_x , float scale_y , float shift_x , float shift_y , int * ix0 , int * iy0 , int * ix1 , int * iy1 );
 static uint8_t* stbtt_GetGlyphBitmap(const stbtt_fontinfo * info , float scale_x , float scale_y , int glyph , int * width , int * height , int * xoff , int * yoff );
 static uint8_t* stbtt_GetGlyphBitmapSubpixel(const stbtt_fontinfo * info , float scale_x , float scale_y , float shift_x , float shift_y , int glyph , int * width , int * height , int * xoff , int * yoff );
 static void stbtt_MakeGlyphBitmap(const stbtt_fontinfo * info , uint8_t * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , int glyph );
 static void stbtt_MakeGlyphBitmapSubpixel(const stbtt_fontinfo * info , uint8_t * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , float shift_x , float shift_y , int glyph );
 static void stbtt_MakeGlyphBitmapSubpixelPrefilter(const stbtt_fontinfo * info , uint8_t * output , int out_w , int out_h , int out_stride , float scale_x , float scale_y , float shift_x , float shift_y , int oversample_x , int oversample_y , float * sub_x , float * sub_y , int glyph );
 static void stbtt_GetGlyphBitmapBox(const stbtt_fontinfo * font , int glyph , float scale_x , float scale_y , int * ix0 , int * iy0 , int * ix1 , int * iy1 );
 static void stbtt_GetGlyphBitmapBoxSubpixel(const stbtt_fontinfo * font , int glyph , float scale_x , float scale_y , float shift_x , float shift_y , int * ix0 , int * iy0 , int * ix1 , int * iy1 );
 static void stbtt_FreeSDF(uint8_t * bitmap , void * userdata );
 static uint8_t* stbtt_GetGlyphSDF(const stbtt_fontinfo * info , float scale , int glyph , int padding , uint8_t onedge_value , float pixel_dist_scale , int * width , int * height , int * xoff , int * yoff );
 static uint8_t* stbtt_GetCodepointSDF(const stbtt_fontinfo * info , float scale , int codepoint , int padding , uint8_t onedge_value , float pixel_dist_scale , int * width , int * height , int * xoff , int * yoff );
 static int stbtt_FindMatchingFont(const uint8_t * fontdata , const char * name , int flags );
 static int stbtt_CompareUTF8toUTF16_bigendian(const char * s1 , int len1 , const char * s2 , int len2 );
 static uint16_t ttUSHORT(uint8_t * p );
 static int16_t ttSHORT(uint8_t * p );
 static uint32_t ttULONG(uint8_t * p );
 static int32_t ttLONG(uint8_t * p );
 static int stbtt__isfont(uint8_t * font );
 static uint32_t stbtt__find_table(uint8_t * data , uint32_t fontstart , const char * tag );
 static int stbtt_GetFontOffsetForIndex_internal(uint8_t * font_collection , int index );
 static int stbtt_GetNumberOfFonts_internal(uint8_t * font_collection );
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
 static int32_t stbtt__GetCoverageIndex(uint8_t * coverageTable , int glyph );
 static int32_t stbtt__GetGlyphClass(uint8_t * classDefTable , int glyph );
 static V2u v2u(V2 v );
 static V2u v2u(U32 x , U32 y );
 static Render_Entity* new_node(Memory * memory );
 static Render_Entity* find_end_node(Render_Entity * node );
 static Void internal_add_new_node(Render_Entity * * parent , Render_Entity * child );
 static Render_Entity* add_child_to_node(Memory * memory , Render_Entity * * parent );
 static Void create_renderer(Renderer * renderer , Memory * memory );
 static Image_Rect create_image_rectangle(Int x , Int y , Int width , Int height , Int sprite_x , Int sprite_y , Int sprite_width , Int sprite_height , U64 image_id );
 static U64 push_image(Renderer * renderer , Image image );
 static Render_Image* push_image_internal(Renderer * renderer , Image image );
 static Rect* push_solid_rectangle(Renderer * renderer , Render_Entity * parent , Int x , Int y , Int width , Int height , U32 inner_colour );
 static Line* push_line(Renderer * renderer , Render_Entity * parent , Int x1 , Int y1 , Int x2 , Int y2 , F32 thickness );
 static U64 push_font(API * api , Renderer * renderer , File file );
 static Word* push_word(Renderer * renderer , Render_Entity * parent , U64 font_id , Int x , Int y , Int height , String string );
 static Word* push_words(Renderer * renderer , Render_Entity * parent , U64 font_id , Int x , Int y , Int height , String * strings , Int string_count );
 static Render_Image* find_font_image(Renderer * renderer , Font * font , Char c );
 static Font* find_font_from_id(Renderer * renderer , U64 id );
 static Bool is_ascii(Int c );
 static Int idx_to_ascii(Int i );
 static Int ascii_to_idx(Int c );
 static Void internal_set_words(Renderer * renderer , Word * word , String * strings , Int string_count );
 static Void update_word(Renderer * renderer , Word * word , String string );
 static Void update_words(Renderer * renderer , Word * word , String * strings , Int string_count );
 static Image_Rect* push_image_rect(Renderer * renderer , Render_Entity * parent , Int x , Int y , Int width , Int height , U64 image_id );
 static Render_Image* find_image_from_id(Renderer * renderer , U64 id );
 static Render_Entity* find_render_entity_internal(Render_Entity * render_entity , U64 id );
 static F32 floor(F32 a );
 static F32 ceil(F32 a );
 static F32 absolute(F32 a );
 static F32 power(F32 x , Int y );
 static F32 fast_power(F32 a , F32 b );
 static U32* image_at_(U32 * base , U32 width , U32 height , U32 x , U32 y );
 static Void render_node(Render_Entity * render_entity , Renderer * renderer , Bitmap * screen_bitmap , BB parent );
 static BB get_overlap(BB a , BB b );
 static Void render_node_and_siblings(Render_Entity * render_entity , Renderer * renderer , Bitmap * screen_bitmap , BB parent_bb );
 static Void render(Renderer * renderer , Bitmap * screen_bitmap );
extern "C" Void init_platform_settings(Settings * settings );
 static U64 load_font(API * api , Renderer * renderer , String fname );
 static Void setup(API * api , DLL_Data * data , Renderer * renderer );
 static Void update(API * api , Renderer * renderer );
extern "C" Void handle_input_and_render(API * api );
void  __stdcall _DllMainCRTStartup(void );
static char const *Memory_Arena_Error_to_string(Memory_Arena_Error e);
static int Memory_Arena_Error_count(Memory_Arena_Error e);
static char const *Key_to_string(Key e);
static Int Key_count(Key e);
static char const *Memory_Index_to_string(Memory_Index e);
static Int Memory_Index_count(Memory_Index e);

// Helpers
#define internal_enum_Memory_Arena_Error (6)
#define internal_enum_Key (58)
#define internal_enum_Memory_Index (3)
#define UNION_OF_SUBCLASSES_INTERNAL_Render_Entity union { Rect _Rect; Image_Rect _Image_Rect; Word _Word; Line _Line; }; 
