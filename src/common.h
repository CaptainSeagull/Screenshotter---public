
// TODO: sglg_Type_Bool is missing in screenshotter_generated.h. Investigate this...
#include <stdint.h>

#define ASSERT(exp) { }
#if ALLOW_ASSERTS
    #undef ASSERT
    #define ASSERT(exp) do { if(!(exp)) {*(uint64_t volatile *)0 = 0; } } while(0)
    #define MEMORY_ARENA_ALLOW_ASSERT
    #define STRING_ALLOW_ASSERT
#endif

#include "../shared/memory_arena.h"
#include "../shared/string.h"
#include "../shared/stb_sprintf.h"

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

#define internal_global static
#define internal static

#define ASSERT_IF(exp) ASSERT((exp)); if((exp))
#define ARRAY_COUNT(arr) (sizeof(arr) / (sizeof(*(arr))))
#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(a, l, u) MIN(MAX((a), (l)), (u))
#define CLAMP01(a) CLAMP((a), 0, 1)

#define FLOOR(n) (F32)(((S32)(n)))
#define CEIL(n) (F32)((S32)(((F32)(n)) + 0.5f))
#define ABS(n) ((n) > 0) ? ((n)) : (-(n))

#define BYTES(v)     ((v)            * (8LL))
#define KILOBYTES(v) ((v)            * (1024LL))
#define MEGABYTES(v) ((KILOBYTES(v)) * (1024LL))
#define GIGABYTES(v) ((MEGABYTES(v)) * (1024LL))

#include "platform.h"

enum Memory_Index : Int {
    Memory_Index_permanent,
    Memory_Index_temp,
    Memory_Index_internal_temp,
};
