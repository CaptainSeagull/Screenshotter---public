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
    sglg_Type_Internal_Push_Info,
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
    sglg_Type_Config,
    sglg_Type_Image,
    sglg_Type_Image_Letter,
    sglg_Type_Bitmap_Header,
    sglg_Type_V2,
    sglg_Type_V3,
    sglg_Type_V4,
    sglg_Type_Lane_F32,
    sglg_Type_Lane_U32,
    sglg_Type_Lane_V2,
    sglg_Type_Lane_V3,
    sglg_Type_Lane_V4,
    sglg_Type_Lane_M2x2,
    sglg_Type_Win32_Work_Queue_Entry,
    sglg_Type_Win32_Work_Queue,
    sglg_Type_Void,
    sglg_Type_Win32_Loaded_Code,
    sglg_Type_Win32_Debug_Window,
    sglg_Type_Win32_API,
    sglg_Type_Win32_Screen_Capture_Thread_Parameters,
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
typedef uint32_t Lane_U32_Internal ;
typedef float Lane_F32_Internal ;
typedef Void Handle_Input_And_Render ( API * ) ;
typedef Void Init_Platform_Settings ( Settings * settings ) ;

// Forward declared structs

struct Memory_Group;
struct Memory;
struct Internal_Push_Info;
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

struct Config;
struct Image;
struct Image_Letter;
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
struct Win32_Work_Queue_Entry;
struct Win32_Work_Queue;
struct Win32_Loaded_Code;
struct Win32_Debug_Window;
struct Win32_API;
struct Win32_Screen_Capture_Thread_Parameters;

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
String create_string(char * str , int len );
String create_string(char const * str , int len );
String create_substring(String str , int start , int end );
int string_compare(String a , String b );
int operator==(String a , String b );
int string_contains(String a , String b );
int string_contains(String str , char target );
int find_index(String str , char target , int find_last );
int string_length(char * str );
int string_length(char const * str );
int char_to_int(char c );
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
 static Void write_image_to_disk(API * api , Memory * memory , Image * image , String file_name );
Image load_image(API * api , String file_name );
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
 static File win32_read_file(Memory * memory , U32 memory_index_to_use , String fname , Bool null_terminate );
 static Bool win32_write_file(Memory * memory , String fname , U8 * data , U64 size );
 static Int win32_get_processor_count(Void );
 static U64 win32_locked_add(U64 volatile * a , U64 b );
 static F32 win32_safe_div(F32 a , F32 b );
 static Bool win32_add_work_queue_entry(API * api , Void * data , Void * cb );
 static Bool win32_do_next_work_queue_entry(Win32_Work_Queue * queue );
 static Void win32_complete_all_work(API * api );
 static Win32_Loaded_Code win32_load_code(Char * source_fname , Char * temp_fname );
void  __stdcall WinMainCRTStartup();
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