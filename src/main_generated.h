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
    sglg_Type_Int,
    sglg_Type_Memory_Arena_Error,
    sglg_Type_Memory_Group,
    sglg_Type_Memory,
    sglg_Type_Internal_Push_Info,
    sglg_Type_String,
    sglg_Type_String_To_Int_Result,
    sglg_Type_String_To_Float_Result,
    sglg_Type_Memory_Index,
    sglg_Type_Config,
    sglg_Type_File,
    sglg_Type_Key,
    sglg_Type_Platform_Callbacks,
    sglg_Type_API,
    sglg_Type_Image,
    sglg_Type_Bitmap_Header,
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

// Forward declared structs

struct Memory_Group;
struct Memory;
struct Internal_Push_Info;
struct String;
struct String_To_Int_Result;
struct String_To_Float_Result;
enum Memory_Index : Int;

struct Config;
struct File;
enum Key : Int;

struct Platform_Callbacks;
struct API;
struct Image;
struct Bitmap_Header;

// Forward declaration of functions
 static uint64_t get_memory_base_size(void );
 static Memory create_memory_base(void * base_memory , uintptr_t * inputs , uintptr_t inputs_count );
 static Memory_Group* get_memory_group(Memory * memory , uintptr_t buffer_index );
 static void* memory_push(Memory * memory , uintptr_t buffer_index , uintptr_t size , uintptr_t alignment  );
 static void memory_pop(Memory * memory , void * memory_buffer );
 static void memory_clear_entire_group(Memory * memory , uintptr_t buffer_index );
 static uintptr_t internal_get_alignment_offset(Memory * memory , void * memory_base , uintptr_t current_index , uintptr_t alignment );
 static uint64_t get_memory_base_size(void );
 static Memory create_memory_base(void * base_memory , uintptr_t * inputs , uintptr_t inputs_count );
 static void memory_arena_zero(void * dest , uintptr_t size );
 static Memory_Group* get_memory_group(Memory * memory , uintptr_t buffer_index );
 static void* memory_push(Memory * memory , uintptr_t buffer_index , uintptr_t size , uintptr_t alignment );
 static void memory_pop(Memory * memory , void * memory_buffer );
 static void memory_clear_entire_group(Memory * memory , uintptr_t buffer_index );
 static String create_string(char * str , int len  );
 static String create_string(char const * str , int len  );
 static String create_substring(String str , int start , int end  );
 static int string_compare(String a , String b );
 static int operator==(String a , String b );
 static int string_contains(String a , String b );
 static int string_contains(String str , char target );
 static int find_index(String str , char target , int find_last  );
 static int string_length(char * str );
 static int string_length(char const * str );
 static int char_to_int(char c );
 static String_To_Int_Result string_to_int(String s );
 static String_To_Float_Result string_to_float(String s );
 static int string_copy(char * dst , char * src );
 static int string_copy(char const * dst , char const * src );
 static int string_copy(char * dst , char const * src );
 static int string_copy(char * dst , char * src , int len );
 static String create_string(char * str , int len );
 static String create_string(char const * str , int len );
 static String create_substring(String str , int start , int end );
 static int string_compare(String a , String b );
 static int operator==(String a , String b );
 static int string_contains(String a , String b );
 static int string_contains(String str , char target );
 static int find_index(String str , char target , int find_last );
 static int string_length(char * str );
 static int string_length(char const * str );
 static int char_to_int(char c );
 static String_To_Int_Result string_to_int(String s );
 static String_To_Float_Result string_to_float(String s );
 static int string_copy(char * dst , char * src );
 static int string_copy(char const * dst , char const * src );
 static int string_copy(char * dst , char const * src );
 static int string_copy(char const * dst , char * src );
 static int string_copy(char * dst , char * src , int len );
 static U32 safe_truncate_size_64(U64 v );
 static Void zero(Void * m , U64 s );
 static Void copy(Void * dst , Void * src , U64 size );
 static Void set(Void * dst , U8 v , U64 size );
 static F32 clamp01(F32 a );
 static Void write_image_to_disk(API * api , Memory * memory , Image * image , String file_name );
extern "C" Void handle_input_and_render(API * api );
static char const *sglg_Memory_Arena_Error_to_string(Memory_Arena_Error e);
static int sglg_Memory_Arena_Error_count(Memory_Arena_Error e);
static char const *sglg_Memory_Index_to_string(Memory_Index e);
static Int sglg_Memory_Index_count(Memory_Index e);
static char const *sglg_Key_to_string(Key e);
static Int sglg_Key_count(Key e);

// Helpers
#define sglg_internal_enum_Memory_Arena_Error (7)
#define sglg_internal_enum_Memory_Index (3)
#define sglg_internal_enum_Key (58)
