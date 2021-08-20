/*  string.h - v0.3 - public domain helper library - no warranty implied; use at your own risk

    Utility for working with strings in C++.
    Note that this class does NO ALLOCATIONS. It expects calling code to deal with mallocing/freeing of the memory.
    Makes sense in my projects... your milage may vary...

    Write #define STRING_IMPLEMENTATION in ONE of the C/C++ files to create the implementation.

    // It should look like this.
    #define STRING_IMPLEMENTATION
    #include "string.h"

    // Some defines to change behaviour of the file. MUST be in the same file as MEMORY_ARENA_IMPLEMENTATION.
    #define STRING_ASSERT(expression) - Override the default ASSERT used.
    #define STRING_ALLOW_ASSERT       - Whether to turn ASSERTS on/off. Has no effect if STRING_ASSERT is defined.
    #define STRING_PUBLIC_DEC         - Allows functions to have a declaration. Can use static or inline if required.
    #define uint64_t          - Change the type of the size member for the struct. By default it's an int.
    #define STRING_CONST_STRING       - Define this to change the type in struct String from "char *" to "char const *" (if that's your thing).

    Usage:

    #define STRING_IMPLEMENTATION
    #include "string.h"
    int main(int argc, char **argv) {
        String my_string = "Hello, World!"; // operator= is overloaded

        int number_of_codepoint = string_length(my_string); // Number of codepoints
        int byte_length = string_byte_length(my_string);

        char as_cstring[1024];
        memcpy(as_cstring, my_string.start, byte_length); // Assumes byte_length is < 1024

        String my_string2 = "2.44"
        String_To_Float_Result r = string_to_float(my_string2);
        if(r.success) {
            float as_float = r.v;
        }

        String a = "Test";
        String b = "Test";
        if(a == b) { // operator== is overloaded.
            // They're the same!
        }

        return(0);
    }

    LICENSE at end of file.
*/

// TODO: Make this a UTF8 string.
// Having a UTF8 -> UTF16 (and maybe UTF32?) codepoint would also be good. See:
//   https://stackoverflow.com/questions/6240055/manually-converting-unicode-codepoints-into-utf-8-and-utf-16
//   https://stackoverflow.com/questions/7153935/how-to-convert-utf-8-stdstring-to-utf-16-stdwstring
//   https://stackoverflow.com/questions/4063146/getting-the-actual-len-of-a-utf-8-encoded-stdstring

#if !defined(_STRING_H_INCLUDE)
#define _STRING_H_INCLUDE

#if !defined(STRING_ASSERT)
    #if defined(MEMORY_ARENA_ALLOW_ASSERT)
        #define STRING_ASSERT(exp) do { static int ignore = 0; if(!ignore) { if(!(exp)) {*(int volatile *)0 = 0; } } } while(0)
    #else
        #define STRING_ASSERT(exp) {}
    #endif
#endif

#include <stdint.h>

#if !defined(STRING_PUBLIC_DEC)
    #define STRING_PUBLIC_DEC
#endif

#define STRING_CONST_MODIFIER /*empty*/
#if defined(STRING_CONST_STRING)
    #undef STRING_CONST_MODIFIER
    #define STRING_CONST_MODIFIER const
#endif

struct String {
    struct {
        char *start = 0;
        char *end = 0;
    };

    String(void);
    String(char *c_string);
    String(char const *c_string);
};

struct String_To_Int_Result {
    int/*bool*/ success;
    int64_t v;
};

struct String_To_Float_Result {
    int/*bool*/ success;
    float v;
};

struct Find_Index_Result {
    int/*bool*/ success;
    uint64_t index;
};

STRING_PUBLIC_DEC String create_string(char *s, uint64_t len = 0);
STRING_PUBLIC_DEC String create_string(char const *s, uint64_t len = 0);

STRING_PUBLIC_DEC String create_substring(String s, uint64_t start, uint64_t end);

STRING_PUBLIC_DEC int/*bool*/ string_compare(String a, String b);
STRING_PUBLIC_DEC int/*bool*/ operator==(String a, String b);

STRING_PUBLIC_DEC int/*bool*/ string_contains(String a, String b);
STRING_PUBLIC_DEC int/*bool*/ string_contains(String s, uint32_t target);

STRING_PUBLIC_DEC Find_Index_Result find_index_of_char(String s, uint32_t target, int/*bool*/ find_last = false);

// TODO: Maybe rename "string_length" to "codepoint_count" or something? To make it more explicit.
STRING_PUBLIC_DEC uint64_t string_length(char *s);
STRING_PUBLIC_DEC uint64_t string_length(char const *s);
STRING_PUBLIC_DEC uint64_t string_length(String s);
STRING_PUBLIC_DEC uint64_t string_byte_length(String s);

STRING_PUBLIC_DEC String_To_Int_Result string_to_int(String s);
STRING_PUBLIC_DEC String_To_Float_Result string_to_float(String s);

STRING_PUBLIC_DEC uint64_t string_copy(char *dst, char *src);
STRING_PUBLIC_DEC uint64_t string_copy(char const *dst, char const *src);
STRING_PUBLIC_DEC uint64_t string_copy(char *dst, char const *src);
STRING_PUBLIC_DEC uint64_t string_copy(char *dst, char *src, uint64_t len);

STRING_PUBLIC_DEC char to_upper(char c);
STRING_PUBLIC_DEC void to_upper(String s);
STRING_PUBLIC_DEC char to_lower(char c);
STRING_PUBLIC_DEC void to_lower(String s);

STRING_PUBLIC_DEC char *get_codepoint_at(String s, uint64_t idx);

STRING_PUBLIC_DEC void string_replace(String s, char target, char to_replace);

#if defined(STRING_IMPLEMENTATION)

String::String(void) {
    // Do nothing
}

String::String(char *c_string) {
    STRING_ASSERT(c_string);

    String s = create_string(c_string);
    this->start = s.start;
    this->end = s.end;
}

String::String(char const *c_string) {
    STRING_ASSERT(c_string);

    String s = create_string((char *)c_string);
    this->start = s.start;
    this->end = s.end;
}

STRING_PUBLIC_DEC String
create_string(char *s, uint64_t len/*= 0*/) {
    STRING_ASSERT(s);

    if(!len) {
        len = string_length(s);
    }

    String r;
    r.start = s;
    r.end = r.start + len;

    return(r);
}

STRING_PUBLIC_DEC String
create_string(char const *s, uint64_t len/*= 0*/) {
    STRING_ASSERT(s);

    String r = create_string((char *)s, len);
    return(r);
}

STRING_PUBLIC_DEC char *
get_codepoint_at(String s, uint64_t idx) {
    char *r = 0;

    char *at = s.start;
    for(uint64_t i = 0; (at != s.end); ++i) { // Is there a faster way to do this?
        if(i == idx) {
            r = at;
            break;
        }

        at += (*at & 0xc0) != 0x80;
    }

    return(r);
}

STRING_PUBLIC_DEC String
create_substring(String s, uint64_t start_idx, uint64_t end_idx) {
    String r = {};

    char *start = get_codepoint_at(s, start_idx);
    char *end = get_codepoint_at(s, end_idx);
    if(start && end) {
        uint64_t len = (end - start);
        r = create_string(start, len);
    }

    return(r);
}

STRING_PUBLIC_DEC int/*bool*/
string_compare(String a, String b) {
    // TODO: Can we use the SSE4.1 string compare functions (like "_mm_cmpestra") to make some of this faster?
    //       If not a faster memcmp would also be good.

    int/*bool*/ r = false;

    if(a.start == b.start && a.end == b.end) {
        r = true; // Initial test - just see if the pointers are the same.
    } else {
        uint64_t a_len = string_byte_length(a);
        uint64_t b_len = string_byte_length(b);

        if(a_len == b_len) {
            r = true;
            for(char *a_it = a.start, *b_it = b.start; (a_it != a.end && b_it != b.end); ++a_it, ++b_it) {
                if(*a_it != *b_it) {
                    r = false;
                    break; // for
                }
            }
        }
    }

    return(r);
}

STRING_PUBLIC_DEC int/*bool*/
operator==(String a, String b) {
    int/*bool*/ r = string_compare(a, b);
    return(r);
}

STRING_PUBLIC_DEC int/*bool*/
string_contains(String a, String b) {
    int/*bool*/ r = false;

    uint64_t b_length = string_byte_length(b);

    for(char *at = a.start; (at != a.end); ++at) {
        // TODO: need to check (a.end - at)
        String a_tmp = create_string(at, b_length);
        if(string_compare(a_tmp, b)) {
            r = true;
            break; // for
        }
    }

    return(r);
}

STRING_PUBLIC_DEC int/*bool*/
string_contains(String s, uint32_t target) {
    int/*bool*/ r = false;

    for(uint64_t i = 0, len = string_length(s); (i < len); ++i) {
        char current_codepoint = s.start[i]; // TODO: Way to read current codepoint properly
        if(current_codepoint == target) {
            r = true;
            break;
        }
    }

    return(r);
}

STRING_PUBLIC_DEC Find_Index_Result
find_index_of_char(String s, uint32_t target, int/*bool*/ find_last/*= false*/) {
    Find_Index_Result r = {};

    uint64_t len = string_length(s);

    // TODO: Make UTF8 aware and read codepoints properly.
    if(!find_last) {
        for(uint64_t i = 0; (i < len); ++i) {
            if(s.start[i] == target) {
                r.index = i;
                r.success = true;
                break; // for
            }
        }

    } else {
        for(uint64_t i = 0, j = len - 1; (i < len); ++i, --j) {
            if(s.start[j] == target) {
                r.index = j;
                r.success = true;
                break; // for
            }
        }
    }

    return(r);
}

STRING_PUBLIC_DEC uint64_t
string_length(char *s) {
    STRING_ASSERT(s);

    uint64_t r = 0;
#if 0
    while(*s++) { ++r; }
#else
    // TODO: UTF8 string_length. Gives the number of codepoints NOT the len in bytes.
    while(*s) {
        r += (*s++ & 0xc0) != 0x80;
    }
#endif

    return(r);
}

STRING_PUBLIC_DEC uint64_t
string_length(char const *s) {
    STRING_ASSERT(s);

    uint64_t r = string_length((char *)s);
    return(r);
}

STRING_PUBLIC_DEC uint64_t
string_length(String s) {
    uint64_t r = 0;

#if 0
    r = (s.end - s.start);
#else
    // TODO: UTF8 string_length. Gives the number of codepoints NOT the len in bytes.
    for(char *at = s.start; (at != s.end); ++at) {
        r += (*at & 0xc0) != 0x80;
    }
#endif

    return(r);
}

STRING_PUBLIC_DEC uint64_t
string_byte_length(String s) {
    uint64_t r = (s.end - s.start);
    return(r);
}

static int
internal_codepoint_to_int(uint32_t c) {
    // TODO: return String_To_Int_Result instead?
    int r = -1;
    switch(c) {
        case '0': { r = 0; } break;
        case '1': { r = 1; } break;
        case '2': { r = 2; } break;
        case '3': { r = 3; } break;
        case '4': { r = 4; } break;
        case '5': { r = 5; } break;
        case '6': { r = 6; } break;
        case '7': { r = 7; } break;
        case '8': { r = 8; } break;
        case '9': { r = 9; } break;
    }

    return(r);
}

STRING_PUBLIC_DEC String_To_Int_Result
string_to_int(String s) {
    int64_t integer = 0;
    int/*bool*/ is_negative = (s.start[0] == '-') ? true : false;

    uint64_t len = string_length(s);

    String_To_Int_Result r = {};
    for(uint64_t i = (is_negative) ? 1 : 0; (i < len); ++i) {
        int t = internal_codepoint_to_int(s.start[i]);
        if(t == -1) {
            break; // for - something went wrong
        } else {
            integer *= 10;
            integer += t;

            if(i == (len - 1)) {
                r.v = (is_negative) ? -integer : integer;
                r.success = true;
            }
        }
    }

    return(r);
}

STRING_PUBLIC_DEC String_To_Float_Result
string_to_float(String s) {
    // a is before decimal point, b is after.
    float before_dec = 0.0f, after_dec = 0.0f;
    int/*Bool*/ before_dec_success = false, after_dec_success = false;
    int/*Bool*/ is_negative = (s.start[0] == '-') ? true : false;

    // TODO: Maybe we can do this by only having one for loop. We keep track of where the decimal point is
    //       relative to the end of the string, and just divide the result by that?

    uint64_t len = string_length(s);

    for(uint64_t i = (is_negative) ? 1 : 0; (i < len); ++i) {
        if(s.start[i] == '.') {
            before_dec_success = true;
            break;
        } else {
            int t = internal_codepoint_to_int(s.start[i]);
            if(t == -1) {
                break; // for - something went wrong
            } else {
                before_dec *= 10.0f;
                before_dec += (float)t;

                if(i == (len - 1)) {
                    // String had no decimal point
                    before_dec_success = true;
                    after_dec_success = true;
                }
            }
        }
    }

    if(!after_dec_success) { // Only called if string has a decimal point
        for(uint64_t i = 0, j = len - 1; (i < len); ++i, --j) {
            if(s.start[j] == '.') {
                after_dec_success = true;
                break;
            } else {
                int t = internal_codepoint_to_int(s.start[j]);
                if(t == -1) {
                    break; // for - something went wrong
                } else {
                    after_dec /= 10.0f;
                    after_dec -= 0.1f * (float)t;
                }
            }
        }
    }

    String_To_Float_Result r = {};
    if(before_dec_success && after_dec_success) {
        // We calculate after_dec as the negative of itself, so invert it before adding the result together.
        r.v = before_dec + -after_dec;
        if(is_negative) { r.v = -r.v; }
        r.success = true;
    }

    return(r);
}

STRING_PUBLIC_DEC uint64_t
string_copy(char *dst, char *src) {
    STRING_ASSERT((dst) && (src));

    uint64_t r = 0;
    while(*src) {
        *dst = *src;
        ++dst;
        ++src;
        ++r; // TODO: Could calculate at end, rather than increment every time through the loop?
    }

    return(r);
}

STRING_PUBLIC_DEC uint64_t
string_copy(char const *dst, char const *src) {
    STRING_ASSERT((dst) && (src));

    uint64_t r = string_copy((char *)dst, (char *)src);
    return(r);
}

STRING_PUBLIC_DEC uint64_t
string_copy(char *dst, char const *src) {
    STRING_ASSERT((dst) && (src));

    uint64_t r = string_copy(dst, (char *)src);
    return(r);
}

STRING_PUBLIC_DEC uint64_t
string_copy(char const *dst, char *src) {
    STRING_ASSERT((dst) && (src));

    uint64_t r = string_copy((char *)dst, src);
    return(r);
}


STRING_PUBLIC_DEC uint64_t
string_copy(char *dst, char *src, uint64_t len) {
    STRING_ASSERT((dst) && (src) && ((len) > 0));

    uint64_t i;
    for(i = 0; (i < len); ++i, ++dst, ++src) {
        *dst = *src;
    }

    return(i);
}

STRING_PUBLIC_DEC char
to_lower(char c) {
    char r = c;
    if((c >= 'A') && (c <= 'Z')) {
        r += 32; // 'a' - 'A'
    }

    return(r);
}

STRING_PUBLIC_DEC void
to_lower(String s) {
    for(char *at = s.start; (at != s.end); ++at) {
        if((*at >= 'A') && (*at <= 'Z')) {
            *at += 32; // 'a' - 'A'
        }
    }
}

STRING_PUBLIC_DEC char
to_upper(char c) {
    char r = c;
    if((c >= 'a') && (c <= 'z')) {
        r -= 32; // 'a' - 'A'
    }

    return(r);
}

STRING_PUBLIC_DEC void
to_upper(String s) {
    for(char *at = s.start; (at != s.end); ++at) {
        if((*at >= 'a') && (*at <= 'z')) {
            *at -= 32; // 'a' - 'A'
        }
    }
}

STRING_PUBLIC_DEC void
string_replace(String s, char target, char to_replace) {
    for(char *at = s.start; (at != s.end); ++at) {
        if(*at == target) {
            *at = to_replace;
        }
    }
}

#endif // STRING_IMPLEMENTATION

#endif // _STRING_H_INCLUDE

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


/*

// TODO: Untested UTF8 -> UTF16 code
#include <stddef.h>

namespace utf_converter {
namespace detail {
constexpr bool utf8_trail_byte(char8_t const in, char32_t& out) noexcept {
  if (in < 0x80 || 0xBF < in)
    return false;

  out = (out << 6) | (in & 0x3F);
  return true;
}

// Returns number of trailing bytes.
// -1 on illegal header bytes.
constexpr int utf8_header_byte(char8_t const in, char32_t& out) noexcept {
  if (in < 0x80) {  // ASCII
    out = in;
    return 0;
  }
  if (in < 0xC0) {  // not a header
    return -1;
  }
  if (in < 0xE0) {
    out = in & 0x1F;
    return 1;
  }
  if (in < 0xF0) {
    out = in & 0x0F;
    return 2;
  }
  if (in < 0xF8) {
    out = in & 0x7;
    return 3;
  }
  return -1;
}
}  // namespace detail

constexpr ptrdiff_t utf8_to_utf16(char8_t const* u8_begin,
                                  char8_t const* const u8_end,
                                  char16_t* u16out) noexcept {
  ptrdiff_t outstr_size = 0;
  while (u8_begin < u8_end) {
    char32_t code_point = 0;
    auto const byte_cnt = detail::utf8_header_byte(*u8_begin++, code_point);

    if (byte_cnt < 0 || byte_cnt > u8_end - u8_begin)
      return false;

    for (int i = 0; i < byte_cnt; ++i)
      if (!detail::utf8_trail_byte(*u8_begin++, code_point))
        return -1;

    if (code_point < 0xFFFF) {
      if (u16out)
        *u16out++ = static_cast<char16_t>(code_point);
      ++outstr_size;
    } else {
      if (u16out) {
        code_point -= 0x10000;
        *u16out++ = static_cast<char16_t>((code_point >> 10) + 0xD800);
        *u16out++ = static_cast<char16_t>((code_point & 0x3FF) + 0xDC00);
      }
      outstr_size += 2;
    }
  }
  return outstr_size;
}
}  // namespace utf_converter


// Example test on Windows where wchar_t is utf16

#include <Windows.h>

int main() {
  using utf_converter::utf8_to_utf16;

  char8_t constexpr u8[] = u8"\u7EDD\u4E0D\u4F1A\u653E\u5F03\u4F60";
  auto constexpr u16sz = utf8_to_utf16(u8, u8 + sizeof u8, nullptr);
  char16_t u16[u16sz];
  utf8_to_utf16(u8, u8 + sizeof u8, u16);

  MessageBoxW(nullptr, (wchar_t*)u16, L"UTF-16 text", MB_OK);
}
*/