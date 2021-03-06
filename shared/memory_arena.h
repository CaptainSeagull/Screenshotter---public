/*  memory_arena.h - v0.3 - public domain helper library - no warranty implied; use at your own risk

    Utility for create memory arenas in C++

    Write #define MEMORY_ARENA_IMPLEMENTATION in ONE of the C/C++ files to create the implementation.

    // It should look like this.
    #define MEMORY_ARENA_IMPLEMENTATION
    #include "memory_arena.h"

    // Some defines to change behaviour of the file. MUST be in the same file as MEMORY_ARENA_IMPLEMENTATION.
    #define MEMORY_ARENA_ASSERT(expression)       - Override the default ASSERT used.
    #define MEMORY_ARENA_ALLOW_ASSERT             - Whether to turn ASSERTS on/off. Has no effect if MEMORY_ARENA_ASSERT is defined.
    #define MEMORY_PUBLIC_DEC                     - Allows functions to have a declaration. Can use static or inline if required.
    #define MEMORY_ARENA_DEFAULT_MEMORY_ALIGNMENT - Override returned alignment of memory allocations. Defaults to 8.
    #define MEMORY_ARENA_WRITE_ERRORS             - Write errirs to the the memory struct.

    Usage:

    #define MEMORY_ARENA_ALLOW_ASSERT // Optional
    #define MEMORY_ARENA_WRITE_ERRORS // Optional
    #define MEMORY_ARENA_IMPLEMENTATION
    #include "../shared/memory_arena.h"

    enum Memory_Index {
        Memory_Index_permanent,
        Memory_Index_temp,
    };
    int main(int argc, char **argv) {
        // TODO: The interface for creating this is terrible (the usage is OK though). Tidy that at some point.

        int start_buffer_size = sizeof(Memory_Group) * 2;
        int permanent_size = 1024;
        int temp_size = 1024;

        int total_size = start_buffer_size + permanent_size + temp_size;

        void *all_memory = malloc(total_size);
        int group_inputs[] = {permanent_size, temp_size};

        int group_inputs_size = 2;
        Memory memory = create_memory_base(all_memory, group_inputs, group_inputs_size);

        // Example 1:
        {
            int *array1 = (int *)memory_push(&memory, Memory_Index_permanent, sizeof(int) * 3);
            int *array2 = (int *)memory_push(&memory, Memory_Index_permanent, sizeof(int) * 4);

            // Do stuff with memory

            // The order MATTERS here, because array1 and array2 are from the same group.
            memory_pop(&memory, array2);
            memory_pop(&memory, array1);
        }

        // Example 2:
        {
            int *array1 = (int *)memory_push(&memory, Memory_Index_permanent, sizeof(int) * 3);
            int *array2 = (int *)memory_push(&memory, Memory_Index_temp, sizeof(int) * 4);

            // Do stuff with memory

            // The order DOES NOT matter here, because array1 and array2 are from different groups.
            memory_pop(&memory, array1);
            memory_pop(&memory, array2);
        }

        // Check for errors (can do this after each call).
        ASSERT(memory->error = Memory_Arena_Error_success);

        free(all_memory);

        return(0);
    }


    LICENSE at end of file.
*/

#if !defined(_MEMORY_ARENA_H_INCLUDE)
#define _MEMORY_ARENA_H_INCLUDE

#include <stdint.h>

#if !defined(MEMORY_PUBLIC_DEC)
    #define MEMORY_PUBLIC_DEC
#endif

#if !defined(MEMORY_ARENA_DEFAULT_MEMORY_ALIGNMENT)
    #define MEMORY_ARENA_DEFAULT_MEMORY_ALIGNMENT 8
#endif

enum Memory_Arena_Error {
    Memory_Arena_Error_success,
    Memory_Arena_Error_invalid_group_buffer_index,
    Memory_Arena_Error_size_too_big,
    Memory_Arena_Error_invalid_input,
    Memory_Arena_Error_internal_error,
    Memory_Arena_Error_wrong_free_order,
};

struct Memory_Group {
    void *base;

    uintptr_t used;
    uintptr_t size;
};

struct Memory {
    void *base;

    Memory_Group *group;
    uintptr_t group_count;

    Memory_Arena_Error error;
};

MEMORY_PUBLIC_DEC uint64_t get_memory_base_size(int group_count);
MEMORY_PUBLIC_DEC Memory create_memory_base(void *base_memory, uintptr_t *inputs, uintptr_t inputs_count);
MEMORY_PUBLIC_DEC Memory_Group *get_memory_group(Memory *memory, uintptr_t buffer_index);

MEMORY_PUBLIC_DEC uint64_t get_size(void *ptr);

// TODO: Document these
#define memory_push_type(memory, buffer_index, Type, ...) \
    (Type *)memory_push_internal(memory, buffer_index, sizeof(Type), (char *)__FILE__, __LINE__, ##__VA_ARGS__)
#define memory_push_size(memory, buffer_index, size) \
    memory_push_internal(memory, buffer_index, size, (char *)__FILE__, __LINE__)
// TODO: Add a push_size_with_alignment macro
MEMORY_PUBLIC_DEC void memory_pop(Memory *memory, void *memory_buffer);
MEMORY_PUBLIC_DEC void memory_clear_entire_group(Memory *memory, uintptr_t buffer_index);

MEMORY_PUBLIC_DEC void *memory_push_internal(Memory *memory, uintptr_t buffer_index, uintptr_t size, char *fname, int line, uintptr_t count = 1);

#if defined(MEMORY_ARENA_IMPLEMENTATION)

#if !defined(MEMORY_ARENA_ASSERT)
    #if defined(MEMORY_ARENA_ALLOW_ASSERT)
        #define MEMORY_ARENA_ASSERT(exp) do { if(!(exp)) {*(uint64_t volatile *)0 = 0; } } while(0)
    #else
        #define MEMORY_ARENA_ASSERT(exp) {}
    #endif
#endif

struct Internal_Push_Info {
    void *base;
    uintptr_t size;
    uintptr_t alignment_offset;
    uintptr_t buffer_index;

    char *file;
    int line;
};

static uintptr_t internal_get_alignment_offset(Memory *memory, void *memory_base, uintptr_t current_index, uintptr_t alignment) {
    uintptr_t res = 0;
    if(memory_base) {
        uintptr_t result_pointer = (uintptr_t)memory_base + current_index;
        uintptr_t alignment_mask = alignment - 1;
        if(result_pointer & alignment_mask) {
            res = alignment - (result_pointer & alignment_mask);
        }
    }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
    else {
        memory->error = Memory_Arena_Error_internal_error;
        MEMORY_ARENA_ASSERT(0);
    }
#endif

    return(res);
}

MEMORY_PUBLIC_DEC uint64_t get_memory_base_size(int group_count) {
    uint64_t res = sizeof(Memory_Group) * group_count;
    return(res);
}

MEMORY_PUBLIC_DEC Memory create_memory_base(void *base_memory, uintptr_t *inputs, uintptr_t inputs_count) {
    Memory memory = {};
    if(base_memory && inputs && inputs_count > 0) {
        memory.group_count = inputs_count;
        memory.group = (Memory_Group *)base_memory;
        memory.base = base_memory;

        uintptr_t running_base_index = (sizeof(Memory_Group) * inputs_count);

        for(uintptr_t i = 0; (i < inputs_count); ++i) {
            uintptr_t alignment_offset = internal_get_alignment_offset(&memory, base_memory, running_base_index,
                                                                       MEMORY_ARENA_DEFAULT_MEMORY_ALIGNMENT);

            memory.group[i].base = (uint8_t *)base_memory + (running_base_index + alignment_offset);
            memory.group[i].used = 0;
            memory.group[i].size = inputs[i] - alignment_offset;

            running_base_index += (alignment_offset + inputs[i]);
        }
    }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
    else {
        memory.error = Memory_Arena_Error_invalid_input;
        MEMORY_ARENA_ASSERT(0);
    }
#endif

    return(memory);
}

static void memory_arena_zero(void *dest, uintptr_t size) {
    MEMORY_ARENA_ASSERT(dest && size > 0);

    uint8_t *dest8 = (uint8_t *)dest;
    for(uintptr_t i = 0; (i < size); ++i) {
        dest8[i] = 0;
    }
}

MEMORY_PUBLIC_DEC Memory_Group *get_memory_group(Memory *memory, uintptr_t buffer_index) {
    Memory_Group *res = 0;
    if(memory) {
        if(buffer_index < memory->group_count) {
            res = &memory->group[buffer_index];
        }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
        else {
            memory->error = Memory_Arena_Error_invalid_group_buffer_index;
            MEMORY_ARENA_ASSERT(0);
        }
#endif
    }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
    else {
        memory->error = Memory_Arena_Error_invalid_input;
        MEMORY_ARENA_ASSERT(0);
    }
#endif

    return(res);
}

MEMORY_PUBLIC_DEC void *
memory_push_internal(Memory *memory, uintptr_t buffer_index, uintptr_t size, char *file, int line, uintptr_t count/*= 1*/) {
    void *res = 0;

    uintptr_t alignment = MEMORY_ARENA_DEFAULT_MEMORY_ALIGNMENT;

    uintptr_t size_to_use = (size * count);

    if(memory && size_to_use > 0) {
        Memory_Group *group = get_memory_group(memory, buffer_index);
        if(group) {
            uintptr_t alignment_offset = internal_get_alignment_offset(memory, memory->base, group->used, alignment);
            if(group->used + alignment_offset + size_to_use < group->size) {
                // We store Internal_Push_Info before the memory returned from this method.
                Internal_Push_Info *push_info = (Internal_Push_Info *)(((uint8_t *)group->base) + group->used + alignment_offset);
                push_info->base = (((uint8_t *)push_info) + sizeof(Internal_Push_Info)); // Only store this so we can assert it in memory_pop
                push_info->size = size_to_use + sizeof(Internal_Push_Info);
                push_info->alignment_offset = alignment_offset;
                push_info->buffer_index = buffer_index;
                push_info->file = file;
                push_info->line = line;

                group->used += push_info->size + push_info->alignment_offset;

                res = push_info->base;

                memory_arena_zero(res, size_to_use); // Memory returned from memory_push should always be 0
            }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
            else {
                memory->error = Memory_Arena_Error_size_too_big;
                MEMORY_ARENA_ASSERT(0);
            }
#endif
        }
    }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
    else {
        memory->error = Memory_Arena_Error_invalid_input;
        MEMORY_ARENA_ASSERT(0);
    }
#endif

    return(res);
}

static Internal_Push_Info *
internal_get_push_info_for_pointer(void *ptr) {
    Internal_Push_Info *push_info = (Internal_Push_Info *)(((uint8_t *)ptr) - (sizeof(Internal_Push_Info)));
    return(push_info);
}

// TODO: If I store the buffer index in Internal_Push_Info struct we don't need to pass that in.
MEMORY_PUBLIC_DEC void
memory_pop(Memory *memory, void *memory_buffer) {
    if(memory) {
        if(memory_buffer) {
            // TODO: Do an MEMORY_ARENA_ASSERT in here to make sure we're "freeing" memory in the correct order.

            //Internal_Push_Info *push_info = (Internal_Push_Info *)(((uint8_t *)memory_buffer) - (sizeof(Internal_Push_Info)));
            Internal_Push_Info *push_info = internal_get_push_info_for_pointer(memory_buffer);
            Memory_Group *group = get_memory_group(memory, push_info->buffer_index);
            if(group) {
                uint64_t to_subtract = (push_info->size + push_info->alignment_offset);
                Internal_Push_Info *expected_push_info = (Internal_Push_Info *)((uint8_t *)group->base + (group->used - to_subtract) + push_info->alignment_offset);
                if(expected_push_info == push_info) {
                    group->used -= to_subtract;
                }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
                else {
                    memory->error = Memory_Arena_Error_wrong_free_order;
                    MEMORY_ARENA_ASSERT(0);
                }
#endif
            }
        }
    }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
    else {
        memory->error = Memory_Arena_Error_invalid_input;
        MEMORY_ARENA_ASSERT(0);
    }
#endif
}

MEMORY_PUBLIC_DEC uint64_t
get_size(void *ptr) {
    uint64_t size = 0;
    if(ptr) {
        Internal_Push_Info *push_info = internal_get_push_info_for_pointer(ptr);
        size = push_info->size - sizeof(Internal_Push_Info);
    }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
    else {
        // TODO: Pass "Memory" just so we can potentially write errors?
        MEMORY_ARENA_ASSERT(0);
    }
#endif

    return(size);
}

MEMORY_PUBLIC_DEC void memory_clear_entire_group(Memory *memory, uintptr_t buffer_index) {
    if(memory) {
        Memory_Group *group = get_memory_group(memory, buffer_index);
        if(group) {
            group->used = 0;
        }
    }
#if defined(MEMORY_ARENA_WRITE_ERRORS)
    else {
        memory->error = Memory_Arena_Error_invalid_input;
        MEMORY_ARENA_ASSERT(0);
    }
#endif
}

#endif // defined(MEMORY_ARENA_IMPLEMENTATION)

#endif // !defined(_MEMORY_ARENA_H_INCLUDE)


/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2021 Jonathan Livingstone
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
