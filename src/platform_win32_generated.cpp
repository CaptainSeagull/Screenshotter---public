#if !defined(SNPRINTF)
    #include<stdio.h>
    #define SNPRINTF snprintf
#endif
static int generated_string_compare(char const *a, uint32_t a_len, char const *b, uint32_t b_len) {
    int res = 0;
    if(a_len == b_len) {
        res = 1;
        for(uint32_t i = 0; (i < a_len); ++i, ++a, ++b) {
            if(*a != *b) {
                res = 0;
                break;
            }
        }
    }
    return(res);
}
static char const *Memory_Arena_Error_to_string(Memory_Arena_Error e) {
    switch(e) {
        case Memory_Arena_Error_success: { return("Memory_Arena_Error_success"); } break;
        case Memory_Arena_Error_invalid_group_buffer_index: { return("Memory_Arena_Error_invalid_group_buffer_index"); } break;
        case Memory_Arena_Error_size_too_big: { return("Memory_Arena_Error_size_too_big"); } break;
        case Memory_Arena_Error_invalid_input: { return("Memory_Arena_Error_invalid_input"); } break;
        case Memory_Arena_Error_internal_error: { return("Memory_Arena_Error_internal_error"); } break;
        case Memory_Arena_Error_wrong_free_order: { return("Memory_Arena_Error_wrong_free_order"); } break;
    }
    return(0);
}
static char const *Key_to_string(Key e) {
    switch(e) {
        case key_unknown: { return("key_unknown"); } break;
        case key_ctrl: { return("key_ctrl"); } break;
        case key_shift: { return("key_shift"); } break;
        case key_alt: { return("key_alt"); } break;
        case key_space: { return("key_space"); } break;
        case key_escape: { return("key_escape"); } break;
        case key_left: { return("key_left"); } break;
        case key_right: { return("key_right"); } break;
        case key_up: { return("key_up"); } break;
        case key_down: { return("key_down"); } break;
        case key_mouse_left: { return("key_mouse_left"); } break;
        case key_mouse_middle: { return("key_mouse_middle"); } break;
        case key_mouse_right: { return("key_mouse_right"); } break;
        case left_stick_x: { return("left_stick_x"); } break;
        case left_stick_y: { return("left_stick_y"); } break;
        case right_stick_x: { return("right_stick_x"); } break;
        case right_stick_y: { return("right_stick_y"); } break;
        case dpad_right: { return("dpad_right"); } break;
        case dpad_up: { return("dpad_up"); } break;
        case dpad_down: { return("dpad_down"); } break;
        case dpad_left: { return("dpad_left"); } break;
        case start: { return("start"); } break;
        case back: { return("back"); } break;
        case left_shoulder: { return("left_shoulder"); } break;
        case right_shoulder: { return("right_shoulder"); } break;
        case left_thumb: { return("left_thumb"); } break;
        case right_thumb: { return("right_thumb"); } break;
        case controller_a: { return("controller_a"); } break;
        case controller_b: { return("controller_b"); } break;
        case controller_x: { return("controller_x"); } break;
        case controller_y: { return("controller_y"); } break;
        case key_A: { return("key_A"); } break;
        case key_B: { return("key_B"); } break;
        case key_C: { return("key_C"); } break;
        case key_D: { return("key_D"); } break;
        case key_E: { return("key_E"); } break;
        case key_F: { return("key_F"); } break;
        case key_G: { return("key_G"); } break;
        case key_H: { return("key_H"); } break;
        case key_I: { return("key_I"); } break;
        case key_J: { return("key_J"); } break;
        case key_K: { return("key_K"); } break;
        case key_L: { return("key_L"); } break;
        case key_M: { return("key_M"); } break;
        case key_N: { return("key_N"); } break;
        case key_O: { return("key_O"); } break;
        case key_P: { return("key_P"); } break;
        case key_Q: { return("key_Q"); } break;
        case key_R: { return("key_R"); } break;
        case key_S: { return("key_S"); } break;
        case key_T: { return("key_T"); } break;
        case key_U: { return("key_U"); } break;
        case key_V: { return("key_V"); } break;
        case key_W: { return("key_W"); } break;
        case key_X: { return("key_X"); } break;
        case key_Y: { return("key_Y"); } break;
        case key_Z: { return("key_Z"); } break;
        case key_cnt: { return("key_cnt"); } break;
    }
    return(0);
}
static char const *Memory_Index_to_string(Memory_Index e) {
    switch(e) {
        case Memory_Index_permanent: { return("Memory_Index_permanent"); } break;
        case Memory_Index_temp: { return("Memory_Index_temp"); } break;
        case Memory_Index_internal_temp: { return("Memory_Index_internal_temp"); } break;
    }
    return(0);
}
static Memory_Arena_Error Memory_Arena_Error_from_string(char const *s, uint32_t l) {
    if(0) {}
    else if(generated_string_compare("Memory_Arena_Error_success", 26, s, l)) { return(Memory_Arena_Error_success); }
    else if(generated_string_compare("Memory_Arena_Error_invalid_group_buffer_index", 45, s, l)) { return(Memory_Arena_Error_invalid_group_buffer_index); }
    else if(generated_string_compare("Memory_Arena_Error_size_too_big", 31, s, l)) { return(Memory_Arena_Error_size_too_big); }
    else if(generated_string_compare("Memory_Arena_Error_invalid_input", 32, s, l)) { return(Memory_Arena_Error_invalid_input); }
    else if(generated_string_compare("Memory_Arena_Error_internal_error", 33, s, l)) { return(Memory_Arena_Error_internal_error); }
    else if(generated_string_compare("Memory_Arena_Error_wrong_free_order", 35, s, l)) { return(Memory_Arena_Error_wrong_free_order); }
    return((Memory_Arena_Error)0);
}
static Key Key_from_string(char const *s, uint32_t l) {
    if(0) {}
    else if(generated_string_compare("key_unknown", 11, s, l)) { return(key_unknown); }
    else if(generated_string_compare("key_ctrl", 8, s, l)) { return(key_ctrl); }
    else if(generated_string_compare("key_shift", 9, s, l)) { return(key_shift); }
    else if(generated_string_compare("key_alt", 7, s, l)) { return(key_alt); }
    else if(generated_string_compare("key_space", 9, s, l)) { return(key_space); }
    else if(generated_string_compare("key_escape", 10, s, l)) { return(key_escape); }
    else if(generated_string_compare("key_left", 8, s, l)) { return(key_left); }
    else if(generated_string_compare("key_right", 9, s, l)) { return(key_right); }
    else if(generated_string_compare("key_up", 6, s, l)) { return(key_up); }
    else if(generated_string_compare("key_down", 8, s, l)) { return(key_down); }
    else if(generated_string_compare("key_mouse_left", 14, s, l)) { return(key_mouse_left); }
    else if(generated_string_compare("key_mouse_middle", 16, s, l)) { return(key_mouse_middle); }
    else if(generated_string_compare("key_mouse_right", 15, s, l)) { return(key_mouse_right); }
    else if(generated_string_compare("left_stick_x", 12, s, l)) { return(left_stick_x); }
    else if(generated_string_compare("left_stick_y", 12, s, l)) { return(left_stick_y); }
    else if(generated_string_compare("right_stick_x", 13, s, l)) { return(right_stick_x); }
    else if(generated_string_compare("right_stick_y", 13, s, l)) { return(right_stick_y); }
    else if(generated_string_compare("dpad_right", 10, s, l)) { return(dpad_right); }
    else if(generated_string_compare("dpad_up", 7, s, l)) { return(dpad_up); }
    else if(generated_string_compare("dpad_down", 9, s, l)) { return(dpad_down); }
    else if(generated_string_compare("dpad_left", 9, s, l)) { return(dpad_left); }
    else if(generated_string_compare("start", 5, s, l)) { return(start); }
    else if(generated_string_compare("back", 4, s, l)) { return(back); }
    else if(generated_string_compare("left_shoulder", 13, s, l)) { return(left_shoulder); }
    else if(generated_string_compare("right_shoulder", 14, s, l)) { return(right_shoulder); }
    else if(generated_string_compare("left_thumb", 10, s, l)) { return(left_thumb); }
    else if(generated_string_compare("right_thumb", 11, s, l)) { return(right_thumb); }
    else if(generated_string_compare("controller_a", 12, s, l)) { return(controller_a); }
    else if(generated_string_compare("controller_b", 12, s, l)) { return(controller_b); }
    else if(generated_string_compare("controller_x", 12, s, l)) { return(controller_x); }
    else if(generated_string_compare("controller_y", 12, s, l)) { return(controller_y); }
    else if(generated_string_compare("key_A", 5, s, l)) { return(key_A); }
    else if(generated_string_compare("key_B", 5, s, l)) { return(key_B); }
    else if(generated_string_compare("key_C", 5, s, l)) { return(key_C); }
    else if(generated_string_compare("key_D", 5, s, l)) { return(key_D); }
    else if(generated_string_compare("key_E", 5, s, l)) { return(key_E); }
    else if(generated_string_compare("key_F", 5, s, l)) { return(key_F); }
    else if(generated_string_compare("key_G", 5, s, l)) { return(key_G); }
    else if(generated_string_compare("key_H", 5, s, l)) { return(key_H); }
    else if(generated_string_compare("key_I", 5, s, l)) { return(key_I); }
    else if(generated_string_compare("key_J", 5, s, l)) { return(key_J); }
    else if(generated_string_compare("key_K", 5, s, l)) { return(key_K); }
    else if(generated_string_compare("key_L", 5, s, l)) { return(key_L); }
    else if(generated_string_compare("key_M", 5, s, l)) { return(key_M); }
    else if(generated_string_compare("key_N", 5, s, l)) { return(key_N); }
    else if(generated_string_compare("key_O", 5, s, l)) { return(key_O); }
    else if(generated_string_compare("key_P", 5, s, l)) { return(key_P); }
    else if(generated_string_compare("key_Q", 5, s, l)) { return(key_Q); }
    else if(generated_string_compare("key_R", 5, s, l)) { return(key_R); }
    else if(generated_string_compare("key_S", 5, s, l)) { return(key_S); }
    else if(generated_string_compare("key_T", 5, s, l)) { return(key_T); }
    else if(generated_string_compare("key_U", 5, s, l)) { return(key_U); }
    else if(generated_string_compare("key_V", 5, s, l)) { return(key_V); }
    else if(generated_string_compare("key_W", 5, s, l)) { return(key_W); }
    else if(generated_string_compare("key_X", 5, s, l)) { return(key_X); }
    else if(generated_string_compare("key_Y", 5, s, l)) { return(key_Y); }
    else if(generated_string_compare("key_Z", 5, s, l)) { return(key_Z); }
    else if(generated_string_compare("key_cnt", 7, s, l)) { return(key_cnt); }
    return((Key)0);
}
static Memory_Index Memory_Index_from_string(char const *s, uint32_t l) {
    if(0) {}
    else if(generated_string_compare("Memory_Index_permanent", 22, s, l)) { return(Memory_Index_permanent); }
    else if(generated_string_compare("Memory_Index_temp", 17, s, l)) { return(Memory_Index_temp); }
    else if(generated_string_compare("Memory_Index_internal_temp", 26, s, l)) { return(Memory_Index_internal_temp); }
    return((Memory_Index)0);
}
// Type
static uint64_t get_enum_count(Type type) {
    switch(type) {
        case Type_Memory_Arena_Error: { return(6); } break;
        case Type_Key: { return(58); } break;
        case Type_Memory_Index: { return(3); } break;
    }
    return(0);
}
static uint64_t type_to_size(Type type) {
    switch(type) {
        case Type_Memory_Arena_Error: { return(sizeof(Memory_Arena_Error)); } break;
        case Type_Memory_Group: { return(sizeof(Memory_Group)); } break;
        case Type_Memory: { return(sizeof(Memory)); } break;
        case Type_Internal_Push_Info: { return(sizeof(Internal_Push_Info)); } break;
        case Type_String: { return(sizeof(String)); } break;
        case Type_String_To_Int_Result: { return(sizeof(String_To_Int_Result)); } break;
        case Type_String_To_Float_Result: { return(sizeof(String_To_Float_Result)); } break;
        case Type_Find_Index_Result: { return(sizeof(Find_Index_Result)); } break;
        case Type_stbsp__context: { return(sizeof(stbsp__context)); } break;
        case Type_File: { return(sizeof(File)); } break;
        case Type_Key: { return(sizeof(Key)); } break;
        case Type_Platform_Callbacks: { return(sizeof(Platform_Callbacks)); } break;
        case Type_Bitmap: { return(sizeof(Bitmap)); } break;
        case Type_Settings: { return(sizeof(Settings)); } break;
        case Type_Window_Info: { return(sizeof(Window_Info)); } break;
        case Type_API: { return(sizeof(API)); } break;
        case Type_Memory_Index: { return(sizeof(Memory_Index)); } break;
        case Type_Image: { return(sizeof(Image)); } break;
        case Type_V2: { return(sizeof(V2)); } break;
        case Type_V3: { return(sizeof(V3)); } break;
        case Type_V4: { return(sizeof(V4)); } break;
        case Type_Lane_F32: { return(sizeof(Lane_F32)); } break;
        case Type_Lane_U32: { return(sizeof(Lane_U32)); } break;
        case Type_Lane_V2: { return(sizeof(Lane_V2)); } break;
        case Type_Lane_V3: { return(sizeof(Lane_V3)); } break;
        case Type_Lane_V4: { return(sizeof(Lane_V4)); } break;
        case Type_Lane_M2x2: { return(sizeof(Lane_M2x2)); } break;
        case Type_Win32_Work_Queue_Entry: { return(sizeof(Win32_Work_Queue_Entry)); } break;
        case Type_Win32_Work_Queue: { return(sizeof(Win32_Work_Queue)); } break;
        case Type_Win32_Loaded_Code: { return(sizeof(Win32_Loaded_Code)); } break;
        case Type_Win32_Debug_Window: { return(sizeof(Win32_Debug_Window)); } break;
        case Type_Win32_API: { return(sizeof(Win32_API)); } break;
        case Type_Win32_System_Callbacks: { return(sizeof(Win32_System_Callbacks)); } break;
        case Type_V2u: { return(sizeof(V2u)); } break;
        case Type_BB: { return(sizeof(BB)); } break;
        case Type_Render_Entity: { return(sizeof(Render_Entity)); } break;
        case Type_Image_Letter: { return(sizeof(Image_Letter)); } break;
        case Type_Rect: { return(sizeof(Rect)); } break;
        case Type_Image_Rect: { return(sizeof(Image_Rect)); } break;
        case Type_Word: { return(sizeof(Word)); } break;
        case Type_Line: { return(sizeof(Line)); } break;
        case Type_Render_Entity_For_Size: { return(sizeof(Render_Entity_For_Size)); } break;
        case Type_Render_Image: { return(sizeof(Render_Image)); } break;
        case Type_Internal: { return(sizeof(Internal)); } break;
        case Type_Font: { return(sizeof(Font)); } break;
        case Type_Renderer: { return(sizeof(Renderer)); } break;
        case Type_Win32_Create_Directory_Result: { return(sizeof(Win32_Create_Directory_Result)); } break;
        case Type_Command_Line_Result: { return(sizeof(Command_Line_Result)); } break;
    }
    return(0);
}
static Type string_to_type(char const *s, uint64_t l) {
    if(0) {}
    else if(generated_string_compare("Memory_Arena_Error", 18, s, l)) { return(Type_Memory_Arena_Error); }
    else if(generated_string_compare("Memory_Group", 12, s, l)) { return(Type_Memory_Group); }
    else if(generated_string_compare("Memory", 6, s, l)) { return(Type_Memory); }
    else if(generated_string_compare("Internal_Push_Info", 18, s, l)) { return(Type_Internal_Push_Info); }
    else if(generated_string_compare("String", 6, s, l)) { return(Type_String); }
    else if(generated_string_compare("String_To_Int_Result", 20, s, l)) { return(Type_String_To_Int_Result); }
    else if(generated_string_compare("String_To_Float_Result", 22, s, l)) { return(Type_String_To_Float_Result); }
    else if(generated_string_compare("Find_Index_Result", 17, s, l)) { return(Type_Find_Index_Result); }
    else if(generated_string_compare("stbsp__context", 14, s, l)) { return(Type_stbsp__context); }
    else if(generated_string_compare("File", 4, s, l)) { return(Type_File); }
    else if(generated_string_compare("Key", 3, s, l)) { return(Type_Key); }
    else if(generated_string_compare("Platform_Callbacks", 18, s, l)) { return(Type_Platform_Callbacks); }
    else if(generated_string_compare("Bitmap", 6, s, l)) { return(Type_Bitmap); }
    else if(generated_string_compare("Settings", 8, s, l)) { return(Type_Settings); }
    else if(generated_string_compare("Window_Info", 11, s, l)) { return(Type_Window_Info); }
    else if(generated_string_compare("API", 3, s, l)) { return(Type_API); }
    else if(generated_string_compare("Memory_Index", 12, s, l)) { return(Type_Memory_Index); }
    else if(generated_string_compare("Image", 5, s, l)) { return(Type_Image); }
    else if(generated_string_compare("V2", 2, s, l)) { return(Type_V2); }
    else if(generated_string_compare("V3", 2, s, l)) { return(Type_V3); }
    else if(generated_string_compare("V4", 2, s, l)) { return(Type_V4); }
    else if(generated_string_compare("Lane_F32", 8, s, l)) { return(Type_Lane_F32); }
    else if(generated_string_compare("Lane_U32", 8, s, l)) { return(Type_Lane_U32); }
    else if(generated_string_compare("Lane_V2", 7, s, l)) { return(Type_Lane_V2); }
    else if(generated_string_compare("Lane_V3", 7, s, l)) { return(Type_Lane_V3); }
    else if(generated_string_compare("Lane_V4", 7, s, l)) { return(Type_Lane_V4); }
    else if(generated_string_compare("Lane_M2x2", 9, s, l)) { return(Type_Lane_M2x2); }
    else if(generated_string_compare("Win32_Work_Queue_Entry", 22, s, l)) { return(Type_Win32_Work_Queue_Entry); }
    else if(generated_string_compare("Win32_Work_Queue", 16, s, l)) { return(Type_Win32_Work_Queue); }
    else if(generated_string_compare("Win32_Loaded_Code", 17, s, l)) { return(Type_Win32_Loaded_Code); }
    else if(generated_string_compare("Win32_Debug_Window", 18, s, l)) { return(Type_Win32_Debug_Window); }
    else if(generated_string_compare("Win32_API", 9, s, l)) { return(Type_Win32_API); }
    else if(generated_string_compare("Win32_System_Callbacks", 22, s, l)) { return(Type_Win32_System_Callbacks); }
    else if(generated_string_compare("V2u", 3, s, l)) { return(Type_V2u); }
    else if(generated_string_compare("BB", 2, s, l)) { return(Type_BB); }
    else if(generated_string_compare("Render_Entity", 13, s, l)) { return(Type_Render_Entity); }
    else if(generated_string_compare("Image_Letter", 12, s, l)) { return(Type_Image_Letter); }
    else if(generated_string_compare("Rect", 4, s, l)) { return(Type_Rect); }
    else if(generated_string_compare("Image_Rect", 10, s, l)) { return(Type_Image_Rect); }
    else if(generated_string_compare("Word", 4, s, l)) { return(Type_Word); }
    else if(generated_string_compare("Line", 4, s, l)) { return(Type_Line); }
    else if(generated_string_compare("Render_Entity_For_Size", 22, s, l)) { return(Type_Render_Entity_For_Size); }
    else if(generated_string_compare("Render_Image", 12, s, l)) { return(Type_Render_Image); }
    else if(generated_string_compare("Internal", 8, s, l)) { return(Type_Internal); }
    else if(generated_string_compare("Font", 4, s, l)) { return(Type_Font); }
    else if(generated_string_compare("Renderer", 8, s, l)) { return(Type_Renderer); }
    else if(generated_string_compare("Win32_Create_Directory_Result", 29, s, l)) { return(Type_Win32_Create_Directory_Result); }
    else if(generated_string_compare("Command_Line_Result", 19, s, l)) { return(Type_Command_Line_Result); }
    return(Type_unknown);
}

// Print structs
#if !defined(override_print_type_char)
static void print_type_char(char *buf, int *written, int max_size, char *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "char %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_int)
static void print_type_int(char *buf, int *written, int max_size, int *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "int %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_short)
static void print_type_short(char *buf, int *written, int max_size, short *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "short %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_float)
static void print_type_float(char *buf, int *written, int max_size, float *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "float %s: %f\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_double)
static void print_type_double(char *buf, int *written, int max_size, double *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "double %s: %f\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_bool)
static void print_type_bool(char *buf, int *written, int max_size, bool *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "bool %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_uint8_t)
static void print_type_uint8_t(char *buf, int *written, int max_size, uint8_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "uint8_t %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_uint16_t)
static void print_type_uint16_t(char *buf, int *written, int max_size, uint16_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "uint16_t %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_uint32_t)
static void print_type_uint32_t(char *buf, int *written, int max_size, uint32_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "uint32_t %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_uint64_t)
static void print_type_uint64_t(char *buf, int *written, int max_size, uint64_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "uint64_t %s: %Id\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_int8_t)
static void print_type_int8_t(char *buf, int *written, int max_size, int8_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "int8_t %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_int16_t)
static void print_type_int16_t(char *buf, int *written, int max_size, int16_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "int16_t %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_int32_t)
static void print_type_int32_t(char *buf, int *written, int max_size, int32_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "int32_t %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_int64_t)
static void print_type_int64_t(char *buf, int *written, int max_size, int64_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "int64_t %s: %I64d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_uintptr_t)
static void print_type_uintptr_t(char *buf, int *written, int max_size, uintptr_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "uintptr_t %s: %I64d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_intptr_t)
static void print_type_intptr_t(char *buf, int *written, int max_size, intptr_t *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "intptr_t %s: %Id\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_Int)
static void print_type_Int(char *buf, int *written, int max_size, Int *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Int %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_Char)
static void print_type_Char(char *buf, int *written, int max_size, Char *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Char %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_Uintptr)
static void print_type_Uintptr(char *buf, int *written, int max_size, Uintptr *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Uintptr %s: %I64d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_U8)
static void print_type_U8(char *buf, int *written, int max_size, U8 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "U8 %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_U16)
static void print_type_U16(char *buf, int *written, int max_size, U16 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "U16 %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_U32)
static void print_type_U32(char *buf, int *written, int max_size, U32 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "U32 %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_U64)
static void print_type_U64(char *buf, int *written, int max_size, U64 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "U64 %s: %Id\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_S8)
static void print_type_S8(char *buf, int *written, int max_size, S8 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "S8 %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_S16)
static void print_type_S16(char *buf, int *written, int max_size, S16 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "S16 %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_S32)
static void print_type_S32(char *buf, int *written, int max_size, S32 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "S32 %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_S64)
static void print_type_S64(char *buf, int *written, int max_size, S64 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "S64 %s: %I64d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_F32)
static void print_type_F32(char *buf, int *written, int max_size, F32 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "F32 %s: %f\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_F64)
static void print_type_F64(char *buf, int *written, int max_size, F64 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "F64 %s: %f\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_Lane_U32_Internal)
static void print_type_Lane_U32_Internal(char *buf, int *written, int max_size, Lane_U32_Internal *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Lane_U32_Internal %s: %d\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_Lane_F32_Internal)
static void print_type_Lane_F32_Internal(char *buf, int *written, int max_size, Lane_F32_Internal *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Lane_F32_Internal %s: %f\n", name, *param);
    if(r != -1) { *written += r; }
}
#endif
#if !defined(override_print_type_Memory_Arena_Error)
static void print_type_Memory_Arena_Error(char *buf, int *written, int max_size, Memory_Arena_Error *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Memory_Arena_Error %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Memory_Arena_Error *param) {
    int written = 0;
    print_type_Memory_Arena_Error(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Memory_Group)
static void print_type_Memory_Group(char *buf, int *written, int max_size, Memory_Group *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Memory_Group %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uintptr_t(buf, written, max_size, (uintptr_t *)&param->used, "used");
    print_type_uintptr_t(buf, written, max_size, (uintptr_t *)&param->size, "size");
}
#endif
static int print_type(char *buf, int max_size, Memory_Group *param) {
    int written = 0;
    print_type_Memory_Group(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Memory)
static void print_type_Memory(char *buf, int *written, int max_size, Memory *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Memory %s:\n", name);
    if(r != -1) { *written += r; }

    if(param->group) { print_type_Memory_Group(buf, written, max_size, (Memory_Group *)param->group, "group"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "Memory_Group group: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_uintptr_t(buf, written, max_size, (uintptr_t *)&param->group_count, "group_count");
    print_type_Memory_Arena_Error(buf, written, max_size, (Memory_Arena_Error *)&param->error, "error");
}
#endif
static int print_type(char *buf, int max_size, Memory *param) {
    int written = 0;
    print_type_Memory(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Internal_Push_Info)
static void print_type_Internal_Push_Info(char *buf, int *written, int max_size, Internal_Push_Info *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Internal_Push_Info %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uintptr_t(buf, written, max_size, (uintptr_t *)&param->size, "size");
    print_type_uintptr_t(buf, written, max_size, (uintptr_t *)&param->alignment_offset, "alignment_offset");
    print_type_uintptr_t(buf, written, max_size, (uintptr_t *)&param->buffer_index, "buffer_index");
    if(param->file) { print_type_char(buf, written, max_size, (char *)param->file, "file"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "char file: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_int(buf, written, max_size, (int *)&param->line, "line");
}
#endif
static int print_type(char *buf, int max_size, Internal_Push_Info *param) {
    int written = 0;
    print_type_Internal_Push_Info(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_String)
static void print_type_String(char *buf, int *written, int max_size, String *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "String %s:\n", name);
    if(r != -1) { *written += r; }

    if(param->e) { print_type_char(buf, written, max_size, (char *)param->e, "e"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "char e: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_int(buf, written, max_size, (int *)&param->len, "len");
}
#endif
static int print_type(char *buf, int max_size, String *param) {
    int written = 0;
    print_type_String(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_String_To_Int_Result)
static void print_type_String_To_Int_Result(char *buf, int *written, int max_size, String_To_Int_Result *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "String_To_Int_Result %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->success, "success");
    print_type_int(buf, written, max_size, (int *)&param->v, "v");
}
#endif
static int print_type(char *buf, int max_size, String_To_Int_Result *param) {
    int written = 0;
    print_type_String_To_Int_Result(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_String_To_Float_Result)
static void print_type_String_To_Float_Result(char *buf, int *written, int max_size, String_To_Float_Result *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "String_To_Float_Result %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->success, "success");
    print_type_float(buf, written, max_size, (float *)&param->v, "v");
}
#endif
static int print_type(char *buf, int max_size, String_To_Float_Result *param) {
    int written = 0;
    print_type_String_To_Float_Result(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Find_Index_Result)
static void print_type_Find_Index_Result(char *buf, int *written, int max_size, Find_Index_Result *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Find_Index_Result %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->success, "success");
    print_type_int(buf, written, max_size, (int *)&param->idx, "idx");
}
#endif
static int print_type(char *buf, int max_size, Find_Index_Result *param) {
    int written = 0;
    print_type_Find_Index_Result(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_stbsp__context)
static void print_type_stbsp__context(char *buf, int *written, int max_size, stbsp__context *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "stbsp__context %s:\n", name);
    if(r != -1) { *written += r; }

    if(param->buf) { print_type_char(buf, written, max_size, (char *)param->buf, "buf"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "char buf: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_int(buf, written, max_size, (int *)&param->count, "count");
    { int r2 = SNPRINTF(buf + *written, max_size - *written, "char tmp[%d]\n", (int)(sizeof(param->tmp) / (sizeof(*(param->tmp))))); if(r2 != -1) { *written += r2; } }
    for(int i = 0; (i < (sizeof(param->tmp) / (sizeof(*(param->tmp))))); ++i) {
        print_type_char(buf, written, max_size, (char *)&param->tmp[i], "");
    }
}
#endif
static int print_type(char *buf, int max_size, stbsp__context *param) {
    int written = 0;
    print_type_stbsp__context(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_File)
static void print_type_File(char *buf, int *written, int max_size, File *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "File %s:\n", name);
    if(r != -1) { *written += r; }

    if(param->e) { print_type_uint8_t(buf, written, max_size, (uint8_t *)param->e, "e"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "uint8_t e: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_uintptr_t(buf, written, max_size, (uintptr_t *)&param->size, "size");
    print_type_String(buf, written, max_size, (String *)&param->fname, "fname");
}
#endif
static int print_type(char *buf, int max_size, File *param) {
    int written = 0;
    print_type_File(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Key)
static void print_type_Key(char *buf, int *written, int max_size, Key *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Key %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Key *param) {
    int written = 0;
    print_type_Key(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Platform_Callbacks)
static void print_type_Platform_Callbacks(char *buf, int *written, int max_size, Platform_Callbacks *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Platform_Callbacks %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Platform_Callbacks *param) {
    int written = 0;
    print_type_Platform_Callbacks(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Bitmap)
static void print_type_Bitmap(char *buf, int *written, int max_size, Bitmap *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Bitmap %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->width, "width");
    print_type_int(buf, written, max_size, (int *)&param->height, "height");
}
#endif
static int print_type(char *buf, int max_size, Bitmap *param) {
    int written = 0;
    print_type_Bitmap(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Settings)
static void print_type_Settings(char *buf, int *written, int max_size, Settings *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Settings %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->dll_data_struct_size, "dll_data_struct_size");
    print_type_int(buf, written, max_size, (int *)&param->thread_count, "thread_count");
    print_type_int(buf, written, max_size, (int *)&param->window_width, "window_width");
    print_type_int(buf, written, max_size, (int *)&param->window_height, "window_height");
}
#endif
static int print_type(char *buf, int max_size, Settings *param) {
    int written = 0;
    print_type_Settings(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Window_Info)
static void print_type_Window_Info(char *buf, int *written, int max_size, Window_Info *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Window_Info %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_String(buf, written, max_size, (String *)&param->title, "title");
    print_type_String(buf, written, max_size, (String *)&param->class_name, "class_name");
    print_type_Int(buf, written, max_size, (Int *)&param->should_screenshot, "should_screenshot");
}
#endif
static int print_type(char *buf, int max_size, Window_Info *param) {
    int written = 0;
    print_type_Window_Info(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_API)
static void print_type_API(char *buf, int *written, int max_size, API *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "API %s:\n", name);
    if(r != -1) { *written += r; }

    { int r2 = SNPRINTF(buf + *written, max_size - *written, "float previous_key[%d]\n", (int)(sizeof(param->previous_key) / (sizeof(*(param->previous_key))))); if(r2 != -1) { *written += r2; } }
    for(int i = 0; (i < (sizeof(param->previous_key) / (sizeof(*(param->previous_key))))); ++i) {
        print_type_float(buf, written, max_size, (float *)&param->previous_key[i], "");
    }
    { int r2 = SNPRINTF(buf + *written, max_size - *written, "float key[%d]\n", (int)(sizeof(param->key) / (sizeof(*(param->key))))); if(r2 != -1) { *written += r2; } }
    for(int i = 0; (i < (sizeof(param->key) / (sizeof(*(param->key))))); ++i) {
        print_type_float(buf, written, max_size, (float *)&param->key[i], "");
    }
    if(param->memory) { print_type_Memory(buf, written, max_size, (Memory *)param->memory, "memory"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "Memory memory: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_Int(buf, written, max_size, (Int *)&param->init, "init");
    print_type_Int(buf, written, max_size, (Int *)&param->running, "running");
    print_type_float(buf, written, max_size, (float *)&param->dt, "dt");
    print_type_float(buf, written, max_size, (float *)&param->seconds_elapsed_for_last_frame, "seconds_elapsed_for_last_frame");
    print_type_float(buf, written, max_size, (float *)&param->previous_mouse_pos_x, "previous_mouse_pos_x");
    print_type_float(buf, written, max_size, (float *)&param->mouse_pos_x, "mouse_pos_x");
    print_type_int(buf, written, max_size, (int *)&param->window_width, "window_width");
    print_type_Bitmap(buf, written, max_size, (Bitmap *)&param->screen_bitmap, "screen_bitmap");
    print_type_Int(buf, written, max_size, (Int *)&param->screen_image_size_change, "screen_image_size_change");
    print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->randomish_seed, "randomish_seed");
    print_type_int(buf, written, max_size, (int *)&param->max_work_queue_count, "max_work_queue_count");
    print_type_Platform_Callbacks(buf, written, max_size, (Platform_Callbacks *)&param->cb, "cb");
    print_type_int(buf, written, max_size, (int *)&param->window_count, "window_count");
    { int r2 = SNPRINTF(buf + *written, max_size - *written, "Window_Info windows[%d]\n", (int)(sizeof(param->windows) / (sizeof(*(param->windows))))); if(r2 != -1) { *written += r2; } }
    for(int i = 0; (i < (sizeof(param->windows) / (sizeof(*(param->windows))))); ++i) {
        print_type_Window_Info(buf, written, max_size, (Window_Info *)&param->windows[i], "");
    }
    print_type_Int(buf, written, max_size, (Int *)&param->launch_browse_for_directory, "launch_browse_for_directory");
    print_type_Int(buf, written, max_size, (Int *)&param->include_title_bar, "include_title_bar");
    print_type_int(buf, written, max_size, (int *)&param->amount_to_sleep, "amount_to_sleep");
    print_type_String(buf, written, max_size, (String *)&param->target_output_directory, "target_output_directory");
    print_type_String(buf, written, max_size, (String *)&param->target_output_directory_full, "target_output_directory_full");
    print_type_String(buf, written, max_size, (String *)&param->new_target_output_directory, "new_target_output_directory");
}
#endif
static int print_type(char *buf, int max_size, API *param) {
    int written = 0;
    print_type_API(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Memory_Index)
static void print_type_Memory_Index(char *buf, int *written, int max_size, Memory_Index *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Memory_Index %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Memory_Index *param) {
    int written = 0;
    print_type_Memory_Index(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Image)
static void print_type_Image(char *buf, int *written, int max_size, Image *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Image %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->width, "width");
    print_type_int(buf, written, max_size, (int *)&param->height, "height");
    if(param->pixels) { print_type_uint32_t(buf, written, max_size, (uint32_t *)param->pixels, "pixels"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "uint32_t pixels: (NULL)\n"); if(r2 != -1) { *written += r2; } }
}
#endif
static int print_type(char *buf, int max_size, Image *param) {
    int written = 0;
    print_type_Image(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_V2)
static void print_type_V2(char *buf, int *written, int max_size, V2 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "V2 %s:\n", name);
    if(r != -1) { *written += r; }

    { int r2 = SNPRINTF(buf + *written, max_size - *written, "float e[%d]\n", (int)(sizeof(param->e) / (sizeof(*(param->e))))); if(r2 != -1) { *written += r2; } }
    for(int i = 0; (i < (sizeof(param->e) / (sizeof(*(param->e))))); ++i) {
        print_type_float(buf, written, max_size, (float *)&param->e[i], "");
    }
}
#endif
static int print_type(char *buf, int max_size, V2 *param) {
    int written = 0;
    print_type_V2(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_V3)
static void print_type_V3(char *buf, int *written, int max_size, V3 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "V3 %s:\n", name);
    if(r != -1) { *written += r; }

    { int r2 = SNPRINTF(buf + *written, max_size - *written, "float e[%d]\n", (int)(sizeof(param->e) / (sizeof(*(param->e))))); if(r2 != -1) { *written += r2; } }
    for(int i = 0; (i < (sizeof(param->e) / (sizeof(*(param->e))))); ++i) {
        print_type_float(buf, written, max_size, (float *)&param->e[i], "");
    }
}
#endif
static int print_type(char *buf, int max_size, V3 *param) {
    int written = 0;
    print_type_V3(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_V4)
static void print_type_V4(char *buf, int *written, int max_size, V4 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "V4 %s:\n", name);
    if(r != -1) { *written += r; }

    { int r2 = SNPRINTF(buf + *written, max_size - *written, "float e[%d]\n", (int)(sizeof(param->e) / (sizeof(*(param->e))))); if(r2 != -1) { *written += r2; } }
    for(int i = 0; (i < (sizeof(param->e) / (sizeof(*(param->e))))); ++i) {
        print_type_float(buf, written, max_size, (float *)&param->e[i], "");
    }
}
#endif
static int print_type(char *buf, int max_size, V4 *param) {
    int written = 0;
    print_type_V4(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Lane_F32)
static void print_type_Lane_F32(char *buf, int *written, int max_size, Lane_F32 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Lane_F32 %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_float(buf, written, max_size, (float *)&param->v, "v");
}
#endif
static int print_type(char *buf, int max_size, Lane_F32 *param) {
    int written = 0;
    print_type_Lane_F32(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Lane_U32)
static void print_type_Lane_U32(char *buf, int *written, int max_size, Lane_U32 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Lane_U32 %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uint32_t(buf, written, max_size, (uint32_t *)&param->v, "v");
}
#endif
static int print_type(char *buf, int max_size, Lane_U32 *param) {
    int written = 0;
    print_type_Lane_U32(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Lane_V2)
static void print_type_Lane_V2(char *buf, int *written, int max_size, Lane_V2 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Lane_V2 %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Lane_V2 *param) {
    int written = 0;
    print_type_Lane_V2(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Lane_V3)
static void print_type_Lane_V3(char *buf, int *written, int max_size, Lane_V3 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Lane_V3 %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Lane_V3 *param) {
    int written = 0;
    print_type_Lane_V3(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Lane_V4)
static void print_type_Lane_V4(char *buf, int *written, int max_size, Lane_V4 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Lane_V4 %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Lane_V4 *param) {
    int written = 0;
    print_type_Lane_V4(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Lane_M2x2)
static void print_type_Lane_M2x2(char *buf, int *written, int max_size, Lane_M2x2 *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Lane_M2x2 %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_Lane_F32(buf, written, max_size, (Lane_F32 *)&param->a, "a");
}
#endif
static int print_type(char *buf, int max_size, Lane_M2x2 *param) {
    int written = 0;
    print_type_Lane_M2x2(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Win32_Work_Queue_Entry)
static void print_type_Win32_Work_Queue_Entry(char *buf, int *written, int max_size, Win32_Work_Queue_Entry *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Win32_Work_Queue_Entry %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Win32_Work_Queue_Entry *param) {
    int written = 0;
    print_type_Win32_Work_Queue_Entry(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Win32_Work_Queue)
static void print_type_Win32_Work_Queue(char *buf, int *written, int max_size, Win32_Work_Queue *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Win32_Work_Queue %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uint32_t(buf, written, max_size, (uint32_t *)&param->completion_goal, "completion_goal");
    print_type_uint32_t(buf, written, max_size, (uint32_t *)&param->completion_count, "completion_count");
    print_type_uint32_t(buf, written, max_size, (uint32_t *)&param->next_entry_to_write, "next_entry_to_write");
    print_type_uint32_t(buf, written, max_size, (uint32_t *)&param->next_entry_to_read, "next_entry_to_read");
    if(param->entries) { print_type_Win32_Work_Queue_Entry(buf, written, max_size, (Win32_Work_Queue_Entry *)param->entries, "entries"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "Win32_Work_Queue_Entry entries: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_int(buf, written, max_size, (int *)&param->entry_count, "entry_count");
}
#endif
static int print_type(char *buf, int max_size, Win32_Work_Queue *param) {
    int written = 0;
    print_type_Win32_Work_Queue(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Win32_Loaded_Code)
static void print_type_Win32_Loaded_Code(char *buf, int *written, int max_size, Win32_Loaded_Code *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Win32_Loaded_Code %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_Int(buf, written, max_size, (Int *)&param->success, "success");
}
#endif
static int print_type(char *buf, int max_size, Win32_Loaded_Code *param) {
    int written = 0;
    print_type_Win32_Loaded_Code(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Win32_Debug_Window)
static void print_type_Win32_Debug_Window(char *buf, int *written, int max_size, Win32_Debug_Window *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Win32_Debug_Window %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_Int(buf, written, max_size, (Int *)&param->success, "success");
    print_type_int(buf, written, max_size, (int *)&param->width, "width");
    print_type_int(buf, written, max_size, (int *)&param->bitmap_width, "bitmap_width");
    print_type_int(buf, written, max_size, (int *)&param->bitmap_height, "bitmap_height");
    print_type_int(buf, written, max_size, (int *)&param->image_size_change, "image_size_change");
    print_type_Int(buf, written, max_size, (Int *)&param->image_size_changed, "image_size_changed");
}
#endif
static int print_type(char *buf, int max_size, Win32_Debug_Window *param) {
    int written = 0;
    print_type_Win32_Debug_Window(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Win32_API)
static void print_type_Win32_API(char *buf, int *written, int max_size, Win32_API *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Win32_API %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_Win32_Work_Queue(buf, written, max_size, (Win32_Work_Queue *)&param->queue, "queue");
}
#endif
static int print_type(char *buf, int max_size, Win32_API *param) {
    int written = 0;
    print_type_Win32_API(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Win32_System_Callbacks)
static void print_type_Win32_System_Callbacks(char *buf, int *written, int max_size, Win32_System_Callbacks *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Win32_System_Callbacks %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_Int(buf, written, max_size, (Int *)&param->success, "success");
}
#endif
static int print_type(char *buf, int max_size, Win32_System_Callbacks *param) {
    int written = 0;
    print_type_Win32_System_Callbacks(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_V2u)
static void print_type_V2u(char *buf, int *written, int max_size, V2u *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "V2u %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uint32_t(buf, written, max_size, (uint32_t *)&param->x, "x");
}
#endif
static int print_type(char *buf, int max_size, V2u *param) {
    int written = 0;
    print_type_V2u(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_BB)
static void print_type_BB(char *buf, int *written, int max_size, BB *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "BB %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->x, "x");
    print_type_int(buf, written, max_size, (int *)&param->width, "width");
}
#endif
static int print_type(char *buf, int max_size, BB *param) {
    int written = 0;
    print_type_BB(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Render_Entity)
static void print_type_Render_Entity(char *buf, int *written, int max_size, Render_Entity *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Render_Entity %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->x, "x");
    print_type_int(buf, written, max_size, (int *)&param->width, "width");
    print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->id, "id");
    print_type_Int(buf, written, max_size, (Int *)&param->visible, "visible");
}
#endif
static int print_type(char *buf, int max_size, Render_Entity *param) {
    int written = 0;
    print_type_Render_Entity(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Image_Letter)
static void print_type_Image_Letter(char *buf, int *written, int max_size, Image_Letter *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Image_Letter %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_Image(buf, written, max_size, (Image *)&param->img, "img");
    print_type_int(buf, written, max_size, (int *)&param->off_x, "off_x");
}
#endif
static int print_type(char *buf, int max_size, Image_Letter *param) {
    int written = 0;
    print_type_Image_Letter(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Rect)
static void print_type_Rect(char *buf, int *written, int max_size, Rect *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Rect %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_float(buf, written, max_size, (float *)&param->outline_thickness, "outline_thickness");
    print_type_uint32_t(buf, written, max_size, (uint32_t *)&param->inner_colour, "inner_colour");
    print_type_uint32_t(buf, written, max_size, (uint32_t *)&param->outer_colour, "outer_colour");
}
#endif
static int print_type(char *buf, int max_size, Rect *param) {
    int written = 0;
    print_type_Rect(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Image_Rect)
static void print_type_Image_Rect(char *buf, int *written, int max_size, Image_Rect *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Image_Rect %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->image_id, "image_id");
    print_type_int(buf, written, max_size, (int *)&param->sprite_x, "sprite_x");
    print_type_int(buf, written, max_size, (int *)&param->sprite_width, "sprite_width");
}
#endif
static int print_type(char *buf, int max_size, Image_Rect *param) {
    int written = 0;
    print_type_Image_Rect(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Word)
static void print_type_Word(char *buf, int *written, int max_size, Word *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Word %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_String(buf, written, max_size, (String *)&param->string, "string");
    print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->font_id, "font_id");
}
#endif
static int print_type(char *buf, int max_size, Word *param) {
    int written = 0;
    print_type_Word(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Line)
static void print_type_Line(char *buf, int *written, int max_size, Line *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Line %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->x2, "x2");
    print_type_float(buf, written, max_size, (float *)&param->thickness, "thickness");
}
#endif
static int print_type(char *buf, int max_size, Line *param) {
    int written = 0;
    print_type_Line(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Render_Entity_For_Size)
static void print_type_Render_Entity_For_Size(char *buf, int *written, int max_size, Render_Entity_For_Size *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Render_Entity_For_Size %s:\n", name);
    if(r != -1) { *written += r; }

}
#endif
static int print_type(char *buf, int max_size, Render_Entity_For_Size *param) {
    int written = 0;
    print_type_Render_Entity_For_Size(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Render_Image)
static void print_type_Render_Image(char *buf, int *written, int max_size, Render_Image *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Render_Image %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->width, "width");
    if(param->pixels) { print_type_uint32_t(buf, written, max_size, (uint32_t *)param->pixels, "pixels"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "uint32_t pixels: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_int(buf, written, max_size, (int *)&param->off_x, "off_x");
    print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->id, "id");
}
#endif
static int print_type(char *buf, int max_size, Render_Image *param) {
    int written = 0;
    print_type_Render_Image(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Internal)
static void print_type_Internal(char *buf, int *written, int max_size, Internal *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Internal %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->entity_id_count, "entity_id_count");
}
#endif
static int print_type(char *buf, int max_size, Internal *param) {
    int written = 0;
    print_type_Internal(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Font)
static void print_type_Font(char *buf, int *written, int max_size, Font *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Font %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->id, "id");
    { int r2 = SNPRINTF(buf + *written, max_size - *written, "uint64_t letter_ids[%d]\n", (int)(sizeof(param->letter_ids) / (sizeof(*(param->letter_ids))))); if(r2 != -1) { *written += r2; } }
    for(int i = 0; (i < (sizeof(param->letter_ids) / (sizeof(*(param->letter_ids))))); ++i) {
        print_type_uint64_t(buf, written, max_size, (uint64_t *)&param->letter_ids[i], "");
    }
    print_type_int(buf, written, max_size, (int *)&param->full_height, "full_height");
}
#endif
static int print_type(char *buf, int max_size, Font *param) {
    int written = 0;
    print_type_Font(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Renderer)
static void print_type_Renderer(char *buf, int *written, int max_size, Renderer *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Renderer %s:\n", name);
    if(r != -1) { *written += r; }

    if(param->root) { print_type_Render_Entity(buf, written, max_size, (Render_Entity *)param->root, "root"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "Render_Entity root: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    if(param->memory) { print_type_Memory(buf, written, max_size, (Memory *)param->memory, "memory"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "Memory memory: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    if(param->images) { print_type_Render_Image(buf, written, max_size, (Render_Image *)param->images, "images"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "Render_Image images: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_int(buf, written, max_size, (int *)&param->image_count_max, "image_count_max");
    if(param->fonts) { print_type_Font(buf, written, max_size, (Font *)param->fonts, "fonts"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "Font fonts: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_int(buf, written, max_size, (int *)&param->font_count_max, "font_count_max");
    print_type_Internal(buf, written, max_size, (Internal *)&param->_internal, "_internal");
}
#endif
static int print_type(char *buf, int max_size, Renderer *param) {
    int written = 0;
    print_type_Renderer(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Win32_Create_Directory_Result)
static void print_type_Win32_Create_Directory_Result(char *buf, int *written, int max_size, Win32_Create_Directory_Result *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Win32_Create_Directory_Result %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_String(buf, written, max_size, (String *)&param->directory, "directory");
    print_type_Int(buf, written, max_size, (Int *)&param->success, "success");
}
#endif
static int print_type(char *buf, int max_size, Win32_Create_Directory_Result *param) {
    int written = 0;
    print_type_Win32_Create_Directory_Result(buf, &written, max_size, param, "");
    return(written);
}

#if !defined(override_print_type_Command_Line_Result)
static void print_type_Command_Line_Result(char *buf, int *written, int max_size, Command_Line_Result *param, char *name) {
    int r = SNPRINTF(buf + *written, max_size - *written, "Command_Line_Result %s:\n", name);
    if(r != -1) { *written += r; }

    print_type_int(buf, written, max_size, (int *)&param->argc, "argc");
    if(param->argv) { print_type_char(buf, written, max_size, (char *)*param->argv, "argv"); }
    else { int r2 = SNPRINTF(buf + *written, max_size - *written, "char argv: (NULL)\n"); if(r2 != -1) { *written += r2; } }
    print_type_Int(buf, written, max_size, (Int *)&param->success, "success");
}
#endif
static int print_type(char *buf, int max_size, Command_Line_Result *param) {
    int written = 0;
    print_type_Command_Line_Result(buf, &written, max_size, param, "");
    return(written);
}

