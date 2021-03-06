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
    Type_Image,
    Type_V2,
    Type_V3,
    Type_V4,
    Type_Lane_F32,
    Type_Lane_U32,
    Type_Lane_V2,
    Type_Lane_V3,
    Type_Lane_V4,
    Type_Lane_M2x2,
    Type_Win32_Work_Queue_Entry,
    Type_Win32_Work_Queue,
    Type_Void,
    Type_Win32_Loaded_Code,
    Type_Win32_Debug_Window,
    Type_Win32_API,
    Type_BOOL,
    Type_LRESULT,
    Type_ATOM,
    Type_HWND,
    Type_HDC,
    Type_HBITMAP,
    Type_HGDIOBJ,
    Type_HRESULT,
    Type_PIDLIST_ABSOLUTE,
    Type_HGLRC,
    Type_Win32_System_Callbacks,
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
    Type_Render_Error,
    Type_Renderer,
    Type_Win32_Create_Directory_Result,
    Type_Win32_Enum_Window_Proc_Data,
    Type_Command_Line_Result,
};

// Utils
#include <stdint.h>
#define ENTITY_PATTERN(Type) PREPROC_CONCAT(UNION_OF_SUBCLASSES_INTERNAL_, Type)
#define PREPROC_CONCAT(a, b) a##b
#define ENUM_COUNT(name) PREPROC_CONCAT(internal_enum_, name)
static int generated_string_compare(char const *a, uint64_t a_len, char const *b, uint64_t b_len);
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
typedef uint32_t Lane_U32_Internal ;
typedef float Lane_F32_Internal ;
typedef Void Handle_Input_And_Render ( API * ) ;
typedef Void Init_Platform_Settings ( Settings * settings ) ;
typedef BOOL TranslateMessage_t ( const MSG * lpMsg ) ;
typedef LRESULT DispatchMessageA_t ( const MSG * lpMsg ) ;
typedef BOOL PeekMessageA_t ( LPMSG lpMsg , HWND hWnd , UINT wMsgFilterMin , UINT wMsgFilterMax , UINT wRemoveMsg ) ;
typedef LRESULT SendMessageA_t ( HWND hWnd , UINT Msg , WPARAM wParam , LPARAM lParam ) ;
typedef LRESULT DefWindowProcA_t ( HWND hWnd , UINT Msg , WPARAM wParam , LPARAM lParam ) ;
typedef ATOM RegisterClassA_t ( const WNDCLASSA * lpWndClass ) ;
typedef HWND CreateWindowExA_t ( DWORD dwExStyle , LPCSTR lpClassName , LPCSTR lpWindowName , DWORD dwStyle , int X , int Y , int nWidth , int nHeight , HWND hWndParent , HMENU hMenu , HINSTANCE hInstance , LPVOID lpParam ) ;
typedef BOOL PrintWindow_t ( HWND hwnd , HDC hdcBlt , UINT nFlags ) ;
typedef BOOL IsWindowVisible_t ( HWND hWnd ) ;
typedef HDC GetDC_t ( HWND hWnd ) ;
typedef int ReleaseDC_t ( HWND hWnd , HDC hDC ) ;
typedef BOOL SetWindowTextA_t ( HWND hWnd , LPCSTR lpString ) ;
typedef int GetWindowTextA_t ( HWND hWnd , LPSTR lpString , int nMaxCount ) ;
typedef BOOL GetClientRect_t ( HWND hWnd , LPRECT lpRect ) ;
typedef BOOL GetCursorPos_t ( LPPOINT lpPoint ) ;
typedef BOOL ScreenToClient_t ( HWND hWnd , LPPOINT lpPoint ) ;
typedef HWND FindWindowExA_t ( HWND hWndParent , HWND hWndChildAfter , LPCSTR lpszClass , LPCSTR lpszWindow ) ;
typedef BOOL EnumWindows_t ( WNDENUMPROC lpEnumFunc , LPARAM lParam ) ;
typedef BOOL EnumDesktopWindows_t ( HDESK hDesktop , WNDENUMPROC lpfn , LPARAM lParam ) ;
typedef int GetClassNameA_t ( HWND hWnd , LPSTR lpClassName , int nMaxCount ) ;
typedef HBITMAP CreateCompatibleBitmap_t ( HDC hdc , int cx , int cy ) ;
typedef HDC CreateCompatibleDC_t ( HDC hdc ) ;
typedef int GetDIBits_t ( HDC hdc , HBITMAP hbm , UINT start , UINT cLines , LPVOID lpvBits , LPBITMAPINFO lpbmi , UINT usage ) ;
typedef HGDIOBJ SelectObject_t ( HDC hdc , HGDIOBJ h ) ;
typedef int StretchDIBits_t ( HDC hdc , int xDest , int yDest , int DestWidth , int DestHeight , int xSrc , int ySrc , int SrcWidth , int SrcHeight , const VOID * lpBits , const BITMAPINFO * lpbmi , UINT iUsage , DWORD rop ) ;
typedef int ChoosePixelFormat_t ( HDC hdc , const PIXELFORMATDESCRIPTOR * ppfd ) ;
typedef int DescribePixelFormat_t ( HDC hdc , int iPixelFormat , UINT nBytes , LPPIXELFORMATDESCRIPTOR ppfd ) ;
typedef BOOL SetPixelFormat_t ( HDC hdc , int format , const PIXELFORMATDESCRIPTOR * ppfd ) ;
typedef BOOL SwapBuffers_t ( HDC unnamedParam1 ) ;
typedef HRESULT SHGetMalloc_t ( IMalloc * * ppMalloc ) ;
typedef BOOL SHGetPathFromIDListA_t ( PCIDLIST_ABSOLUTE pidl , LPSTR pszPath ) ;
typedef PIDLIST_ABSOLUTE SHBrowseForFolderA_t ( LPBROWSEINFOA lpbi ) ;
typedef HGLRC wglCreateContext_t ( HDC unnamedParam1 ) ;
typedef BOOL wglMakeCurrent_t ( HDC , HGLRC ) ;
typedef void WINAPI glBegin_t ( GLenum mode ) ;
typedef void WINAPI glLoadMatrixf_t ( const GLfloat * m ) ;
typedef void WINAPI glViewport_t ( GLint x , GLint y , GLsizei width , GLsizei height ) ;
typedef void WINAPI glBindTexture_t ( GLenum target , GLuint texture ) ;
typedef void WINAPI glTexImage2D_t ( GLenum target , GLint level , GLint internalformat , GLsizei width , GLsizei height , GLint border , GLint format , GLenum type , const GLvoid * pixels ) ;
typedef void WINAPI glTexParameteri_t ( GLenum target , GLenum pname , GLint param ) ;
typedef void WINAPI glTexEnvi_t ( GLenum target , GLenum pname , GLint param ) ;
typedef void WINAPI glEnable_t ( GLenum cap ) ;
typedef void WINAPI glClearColor_t ( GLclampf red , GLclampf green , GLclampf blue , GLclampf alpha ) ;
typedef void WINAPI glClear_t ( GLbitfield mask ) ;
typedef void WINAPI glMatrixMode_t ( GLenum mode ) ;
typedef void WINAPI glLoadIdentity_t ( void ) ;
typedef void WINAPI glColor4f_t ( GLfloat red , GLfloat green , GLfloat blue , GLfloat alpha ) ;
typedef void WINAPI glTexCoord2f_t ( GLfloat s , GLfloat t ) ;
typedef void WINAPI glEnd_t ( void ) ;
typedef void WINAPI glGenTextures_t ( GLsizei n , GLuint * textures ) ;
typedef void WINAPI glVertex2f_t ( GLfloat x , GLfloat y ) ;

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

struct Image;
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
struct Win32_System_Callbacks;
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
enum Render_Error : Int;

struct Renderer;
struct Win32_Create_Directory_Result;
struct Win32_Enum_Window_Proc_Data;
struct Command_Line_Result;

// Forward declaration of functions
uint64_t get_memory_base_size(int group_count );
Memory create_memory_base(void * base_memory , uintptr_t * inputs , uintptr_t inputs_count );
Memory_Group* get_memory_group(Memory * memory , uintptr_t buffer_index );
uint64_t get_size(void * ptr );
void memory_pop(Memory * memory , void * memory_buffer );
void memory_clear_entire_group(Memory * memory , uintptr_t buffer_index );
void* memory_push_internal(Memory * memory , uintptr_t buffer_index , uintptr_t size , char * fname , int line , uintptr_t count  );
 static uintptr_t internal_get_alignment_offset(Memory * memory , void * memory_base , uintptr_t current_index , uintptr_t alignment );
uint64_t get_memory_base_size(int group_count );
Memory create_memory_base(void * base_memory , uintptr_t * inputs , uintptr_t inputs_count );
 static void memory_arena_zero(void * dest , uintptr_t size );
Memory_Group* get_memory_group(Memory * memory , uintptr_t buffer_index );
void* memory_push_internal(Memory * memory , uintptr_t buffer_index , uintptr_t size , char * file , int line , uintptr_t count );
 static Internal_Push_Info* internal_get_push_info_for_pointer(void * ptr );
void memory_pop(Memory * memory , void * memory_buffer );
uint64_t get_size(void * ptr );
void memory_clear_entire_group(Memory * memory , uintptr_t buffer_index );
String create_string(char * s , uint64_t len  );
String create_string(char const * s , uint64_t len  );
String create_substring(String s , uint64_t start , uint64_t end );
int string_compare(String a , String b );
int operator==(String a , String b );
int operator!=(String a , String b );
int string_contains(String a , String b );
int string_contains(String s , uint32_t target );
Find_Index_Result find_index_of_char(String s , uint32_t target , int find_last  );
uint64_t string_length(char * s );
uint64_t string_length(char const * s );
uint64_t string_length(String s );
uint64_t string_byte_length(String s );
int is_empty(String s );
String_To_Int_Result string_to_int(String s );
String_To_Float_Result string_to_float(String s );
uint64_t string_copy(char * dst , char * src );
uint64_t string_copy(char const * dst , char const * src );
uint64_t string_copy(char * dst , char const * src );
uint64_t string_copy(char * dst , char * src , uint64_t len );
char to_upper(char c );
void to_upper(String s );
char to_lower(char c );
void to_lower(String s );
char* get_codepoint_at(String s , uint64_t idx );
void string_replace(String s , char target , char to_replace );
String create_string(char * s , uint64_t len );
String create_string(char const * s , uint64_t len );
char* get_codepoint_at(String s , uint64_t idx );
String create_substring(String s , uint64_t start_idx , uint64_t end_idx );
int string_compare(String a , String b );
int operator==(String a , String b );
int operator!=(String a , String b );
int string_contains(String a , String b );
int string_contains(String s , uint32_t target );
Find_Index_Result find_index_of_char(String s , uint32_t target , int find_last );
uint64_t string_length(char * s );
uint64_t string_length(char const * s );
uint64_t string_length(String s );
uint64_t string_byte_length(String s );
int is_empty(String s );
 static int internal_codepoint_to_int(uint32_t c );
String_To_Int_Result string_to_int(String s );
String_To_Float_Result string_to_float(String s );
uint64_t string_copy(char * dst , char * src );
uint64_t string_copy(char const * dst , char const * src );
uint64_t string_copy(char * dst , char const * src );
uint64_t string_copy(char const * dst , char * src );
uint64_t string_copy(char * dst , char * src , uint64_t len );
char to_lower(char c );
void to_lower(String s );
char to_upper(char c );
void to_upper(String s );
void string_replace(String s , char target , char to_replace );
int stbsp_vsprintf(char * buf , char const * fmt , va_list va );
int stbsp_vsnprintf(char * buf , int count , char const * fmt , va_list va );
int stbsp_vsprintfcb(STBSP_SPRINTFCB * callback , void * user , char * buf , char const * fmt , va_list va );
void stbsp_set_separators(char comma , char period );
 static int32_t stbsp__real_to_str(char const * * start , uint32_t * len , char * out , int32_t * decimal_pos , double value , uint32_t frac_digits );
 static int32_t stbsp__real_to_parts(int64_t * bits , int32_t * expo , double value );
void stbsp_set_separators(char pcomma , char pperiod );
int stbsp_vsprintfcb(STBSP_SPRINTFCB * callback , void * user , char * buf , char const * fmt , va_list va );
 static char* stbsp__clamp_callback(char * buf , void * user , int len );
int stbsp_vsnprintf(char * buf , int count , char const * fmt , va_list va );
int stbsp_vsprintf(char * buf , char const * fmt , va_list va );
 static int32_t stbsp__real_to_parts(int64_t * bits , int32_t * expo , double value );
 static U32 safe_truncate_size_64(U64 v );
 static Void zero(Void * m , U64 s );
 static Void copy(Void * dst , Void * src , U64 size );
 static Void set(Void * dst , U8 v , U64 size );
 static Void flip_image(Void * dst_pixels , Void * src_pixels , Int width , Int height );
 static Char* memory_push_string(Memory * mem , Memory_Index idx , String str , Int padding  );
 static F32 power(F32 x , Int y );
 static F32 fast_power(F32 a , F32 b );
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
void* memset(void * dst , int c , size_t cnt );
void* memcpy(void * dst , const void * src , size_t cnt );
 static File win32_read_file(Memory * memory , U32 memory_index_to_use , String fname , Bool null_terminate );
 static Bool win32_write_file(Memory * memory , String fname , U8 * data , U64 size );
 static Int win32_get_processor_count(Void );
 static U64 win32_locked_add(U64 volatile * a , U64 b );
 static F32 win32_safe_div(F32 a , F32 b );
 static Void win32_update_window(Memory * memory , Win32_System_Callbacks * sys_cb , HDC dc , RECT * wnd_rect , Void * input_bitmap_memory , BITMAPINFO * bitmap_info , Int bitmap_width , Int bitmap_height );
 static Key win32_key_to_our_key(WPARAM k );
 static F32 win32_get_seconds_elapsed(LARGE_INTEGER start , LARGE_INTEGER end , int64_t perf_cnt_freq );
 static Void win32_get_window_dimension(HWND wnd , Int * w , Int * h , Win32_System_Callbacks * sys_cb );
 static Void win32_init_opengl(HWND window , Win32_System_Callbacks * sys_cb );
 static Bool win32_add_work_queue_entry(API * api , Void * data , Void * cb );
 static Bool win32_do_next_work_queue_entry(Win32_Work_Queue * queue );
 static Void win32_complete_all_work(API * api );
 static Win32_Loaded_Code win32_load_code(Char * source_fname , Char * temp_fname );
 static Win32_Create_Directory_Result win32_create_directory(Memory * memory , String root , String dir , Bool save_directory_string  );
 static U64 win32_directory_index_to_use(Memory * mem , String session_prefix , String input_target_directory );
 static U64 win32_file_index_to_use(Memory * memory , String root_directory , String program_title );
 static Void run_screenshotting(API * api , Memory * memory , Win32_System_Callbacks * sys_cb , String root_directory );
 static String win32_create_root_directory(Memory * memory , String target_directory );
 static Void enum_windows(API * api , Win32_System_Callbacks * sys_cb );
 static int  CALLBACK win32_directory_browse_callback(HWND hwnd , UINT uMsg , LPARAM lParam , LPARAM lpData );
 static Void string_replace(Char * input , U64 length , Char t , Char s );
 static String win32_browse_for_directory(Memory * memory , String initial_path_input );
 static Win32_System_Callbacks load_system_callbacks(Void );
 static Command_Line_Result parse_command_line(Memory * memory );
int  CALLBACK WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nShowCmd );
void  __stdcall WinMainCRTStartup(void );
static char const *Key_to_string(Key e);
static Int Key_count(Key e);
static char const *Memory_Index_to_string(Memory_Index e);
static Int Memory_Index_count(Memory_Index e);
static char const *Render_Error_to_string(Render_Error e);
static Int Render_Error_count(Render_Error e);

// Helpers
#define internal_enum_Memory_Arena_Error (6)
#define internal_enum_Key (58)
#define internal_enum_Memory_Index (3)
#define internal_enum_Render_Error (2)
#define UNION_OF_SUBCLASSES_INTERNAL_Render_Entity union { Rect _Rect; Image_Rect _Image_Rect; Word _Word; Line _Line; }; 

// Forward declare print struct
static void print_type_char(char *buf, int max_size, char *param, char *name);

static void print_type_int(char *buf, int max_size, int *param, char *name);

static void print_type_short(char *buf, int max_size, short *param, char *name);

static void print_type_float(char *buf, int max_size, float *param, char *name);

static void print_type_double(char *buf, int max_size, double *param, char *name);

static void print_type_bool(char *buf, int max_size, bool *param, char *name);

static void print_type_uint8_t(char *buf, int max_size, uint8_t *param, char *name);

static void print_type_uint16_t(char *buf, int max_size, uint16_t *param, char *name);

static void print_type_uint32_t(char *buf, int max_size, uint32_t *param, char *name);

static void print_type_uint64_t(char *buf, int max_size, uint64_t *param, char *name);

static void print_type_int8_t(char *buf, int max_size, int8_t *param, char *name);

static void print_type_int16_t(char *buf, int max_size, int16_t *param, char *name);

static void print_type_int32_t(char *buf, int max_size, int32_t *param, char *name);

static void print_type_int64_t(char *buf, int max_size, int64_t *param, char *name);

static void print_type_uintptr_t(char *buf, int max_size, uintptr_t *param, char *name);

static void print_type_intptr_t(char *buf, int max_size, intptr_t *param, char *name);

static void print_type_Int(char *buf, int max_size, Int *param, char *name);

static void print_type_Char(char *buf, int max_size, Char *param, char *name);

static void print_type_Uintptr(char *buf, int max_size, Uintptr *param, char *name);

static void print_type_U8(char *buf, int max_size, U8 *param, char *name);

static void print_type_U16(char *buf, int max_size, U16 *param, char *name);

static void print_type_U32(char *buf, int max_size, U32 *param, char *name);

static void print_type_U64(char *buf, int max_size, U64 *param, char *name);

static void print_type_S8(char *buf, int max_size, S8 *param, char *name);

static void print_type_S16(char *buf, int max_size, S16 *param, char *name);

static void print_type_S32(char *buf, int max_size, S32 *param, char *name);

static void print_type_S64(char *buf, int max_size, S64 *param, char *name);

static void print_type_F32(char *buf, int max_size, F32 *param, char *name);

static void print_type_F64(char *buf, int max_size, F64 *param, char *name);

static void print_type_Lane_U32_Internal(char *buf, int max_size, Lane_U32_Internal *param, char *name);

static void print_type_Lane_F32_Internal(char *buf, int max_size, Lane_F32_Internal *param, char *name);

static void print_type_Memory_Arena_Error(char *buf, int *written, int max_size, Memory_Arena_Error *param, char *name);
static int print_type(char *buf, int max_size, Memory_Arena_Error *param);

static void print_type_Memory_Group(char *buf, int *written, int max_size, Memory_Group *param, char *name);
static int print_type(char *buf, int max_size, Memory_Group *param);

static void print_type_Memory(char *buf, int *written, int max_size, Memory *param, char *name);
static int print_type(char *buf, int max_size, Memory *param);

static void print_type_Internal_Push_Info(char *buf, int *written, int max_size, Internal_Push_Info *param, char *name);
static int print_type(char *buf, int max_size, Internal_Push_Info *param);

static void print_type_String(char *buf, int *written, int max_size, String *param, char *name);
static int print_type(char *buf, int max_size, String *param);

static void print_type_String_To_Int_Result(char *buf, int *written, int max_size, String_To_Int_Result *param, char *name);
static int print_type(char *buf, int max_size, String_To_Int_Result *param);

static void print_type_String_To_Float_Result(char *buf, int *written, int max_size, String_To_Float_Result *param, char *name);
static int print_type(char *buf, int max_size, String_To_Float_Result *param);

static void print_type_Find_Index_Result(char *buf, int *written, int max_size, Find_Index_Result *param, char *name);
static int print_type(char *buf, int max_size, Find_Index_Result *param);

static void print_type_stbsp__context(char *buf, int *written, int max_size, stbsp__context *param, char *name);
static int print_type(char *buf, int max_size, stbsp__context *param);

static void print_type_File(char *buf, int *written, int max_size, File *param, char *name);
static int print_type(char *buf, int max_size, File *param);

static void print_type_Key(char *buf, int *written, int max_size, Key *param, char *name);
static int print_type(char *buf, int max_size, Key *param);

static void print_type_Platform_Callbacks(char *buf, int *written, int max_size, Platform_Callbacks *param, char *name);
static int print_type(char *buf, int max_size, Platform_Callbacks *param);

static void print_type_Bitmap(char *buf, int *written, int max_size, Bitmap *param, char *name);
static int print_type(char *buf, int max_size, Bitmap *param);

static void print_type_Settings(char *buf, int *written, int max_size, Settings *param, char *name);
static int print_type(char *buf, int max_size, Settings *param);

static void print_type_Window_Info(char *buf, int *written, int max_size, Window_Info *param, char *name);
static int print_type(char *buf, int max_size, Window_Info *param);

static void print_type_API(char *buf, int *written, int max_size, API *param, char *name);
static int print_type(char *buf, int max_size, API *param);

static void print_type_Memory_Index(char *buf, int *written, int max_size, Memory_Index *param, char *name);
static int print_type(char *buf, int max_size, Memory_Index *param);

static void print_type_Image(char *buf, int *written, int max_size, Image *param, char *name);
static int print_type(char *buf, int max_size, Image *param);

static void print_type_V2(char *buf, int *written, int max_size, V2 *param, char *name);
static int print_type(char *buf, int max_size, V2 *param);

static void print_type_V3(char *buf, int *written, int max_size, V3 *param, char *name);
static int print_type(char *buf, int max_size, V3 *param);

static void print_type_V4(char *buf, int *written, int max_size, V4 *param, char *name);
static int print_type(char *buf, int max_size, V4 *param);

static void print_type_Lane_F32(char *buf, int *written, int max_size, Lane_F32 *param, char *name);
static int print_type(char *buf, int max_size, Lane_F32 *param);

static void print_type_Lane_U32(char *buf, int *written, int max_size, Lane_U32 *param, char *name);
static int print_type(char *buf, int max_size, Lane_U32 *param);

static void print_type_Lane_V2(char *buf, int *written, int max_size, Lane_V2 *param, char *name);
static int print_type(char *buf, int max_size, Lane_V2 *param);

static void print_type_Lane_V3(char *buf, int *written, int max_size, Lane_V3 *param, char *name);
static int print_type(char *buf, int max_size, Lane_V3 *param);

static void print_type_Lane_V4(char *buf, int *written, int max_size, Lane_V4 *param, char *name);
static int print_type(char *buf, int max_size, Lane_V4 *param);

static void print_type_Lane_M2x2(char *buf, int *written, int max_size, Lane_M2x2 *param, char *name);
static int print_type(char *buf, int max_size, Lane_M2x2 *param);

static void print_type_Win32_Work_Queue_Entry(char *buf, int *written, int max_size, Win32_Work_Queue_Entry *param, char *name);
static int print_type(char *buf, int max_size, Win32_Work_Queue_Entry *param);

static void print_type_Win32_Work_Queue(char *buf, int *written, int max_size, Win32_Work_Queue *param, char *name);
static int print_type(char *buf, int max_size, Win32_Work_Queue *param);

static void print_type_Win32_Loaded_Code(char *buf, int *written, int max_size, Win32_Loaded_Code *param, char *name);
static int print_type(char *buf, int max_size, Win32_Loaded_Code *param);

static void print_type_Win32_Debug_Window(char *buf, int *written, int max_size, Win32_Debug_Window *param, char *name);
static int print_type(char *buf, int max_size, Win32_Debug_Window *param);

static void print_type_Win32_API(char *buf, int *written, int max_size, Win32_API *param, char *name);
static int print_type(char *buf, int max_size, Win32_API *param);

static void print_type_Win32_System_Callbacks(char *buf, int *written, int max_size, Win32_System_Callbacks *param, char *name);
static int print_type(char *buf, int max_size, Win32_System_Callbacks *param);

static void print_type_V2u(char *buf, int *written, int max_size, V2u *param, char *name);
static int print_type(char *buf, int max_size, V2u *param);

static void print_type_BB(char *buf, int *written, int max_size, BB *param, char *name);
static int print_type(char *buf, int max_size, BB *param);

static void print_type_Render_Entity(char *buf, int *written, int max_size, Render_Entity *param, char *name);
static int print_type(char *buf, int max_size, Render_Entity *param);

static void print_type_Image_Letter(char *buf, int *written, int max_size, Image_Letter *param, char *name);
static int print_type(char *buf, int max_size, Image_Letter *param);

static void print_type_Rect(char *buf, int *written, int max_size, Rect *param, char *name);
static int print_type(char *buf, int max_size, Rect *param);

static void print_type_Image_Rect(char *buf, int *written, int max_size, Image_Rect *param, char *name);
static int print_type(char *buf, int max_size, Image_Rect *param);

static void print_type_Word(char *buf, int *written, int max_size, Word *param, char *name);
static int print_type(char *buf, int max_size, Word *param);

static void print_type_Line(char *buf, int *written, int max_size, Line *param, char *name);
static int print_type(char *buf, int max_size, Line *param);

static void print_type_Render_Entity_For_Size(char *buf, int *written, int max_size, Render_Entity_For_Size *param, char *name);
static int print_type(char *buf, int max_size, Render_Entity_For_Size *param);

static void print_type_Render_Image(char *buf, int *written, int max_size, Render_Image *param, char *name);
static int print_type(char *buf, int max_size, Render_Image *param);

static void print_type_Internal(char *buf, int *written, int max_size, Internal *param, char *name);
static int print_type(char *buf, int max_size, Internal *param);

static void print_type_Font(char *buf, int *written, int max_size, Font *param, char *name);
static int print_type(char *buf, int max_size, Font *param);

static void print_type_Render_Error(char *buf, int *written, int max_size, Render_Error *param, char *name);
static int print_type(char *buf, int max_size, Render_Error *param);

static void print_type_Renderer(char *buf, int *written, int max_size, Renderer *param, char *name);
static int print_type(char *buf, int max_size, Renderer *param);

static void print_type_Win32_Create_Directory_Result(char *buf, int *written, int max_size, Win32_Create_Directory_Result *param, char *name);
static int print_type(char *buf, int max_size, Win32_Create_Directory_Result *param);

static void print_type_Win32_Enum_Window_Proc_Data(char *buf, int *written, int max_size, Win32_Enum_Window_Proc_Data *param, char *name);
static int print_type(char *buf, int max_size, Win32_Enum_Window_Proc_Data *param);

static void print_type_Command_Line_Result(char *buf, int *written, int max_size, Command_Line_Result *param, char *name);
static int print_type(char *buf, int max_size, Command_Line_Result *param);
