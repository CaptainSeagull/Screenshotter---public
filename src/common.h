
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

#define internal_global static
#define internal static

#define ARRAY_COUNT(arr) (sizeof(arr) / (sizeof(*(arr))))
#define BYTES(v)     ((v)            * (8LL))
#define KILOBYTES(v) ((v)            * (1024LL))
#define MEGABYTES(v) ((KILOBYTES(v)) * (1024LL))
#define GIGABYTES(v) ((MEGABYTES(v)) * (1024LL))
