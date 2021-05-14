// Move stuff mirror doesn't currently support in here.

#include <stdint.h>

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
