static int sgl_generated_string_compare(char const *a, uint32_t a_len, char const *b, uint32_t b_len) {
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
static char const *sglg_Memory_Arena_Error_to_string(Memory_Arena_Error e) {
    switch(e) {
        case Memory_Arena_Error_success: { return("Memory_Arena_Error_success"); } break;
        case Memory_Arena_Error_invalid_group_buffer_index: { return("Memory_Arena_Error_invalid_group_buffer_index"); } break;
        case Memory_Arena_Error_size_too_big: { return("Memory_Arena_Error_size_too_big"); } break;
        case Memory_Arena_Error_invalid_input: { return("Memory_Arena_Error_invalid_input"); } break;
        case Memory_Arena_Error_internal_error: { return("Memory_Arena_Error_internal_error"); } break;
        case Memory_Arena_Error_wrong_free_order: { return("Memory_Arena_Error_wrong_free_order"); } break;
        case Memory_Arena_Error_count: { return("Memory_Arena_Error_count"); } break;
    }
    return(0);
}
static char const *sglg_Key_to_string(Key e) {
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
static char const *sglg_Memory_Index_to_string(Memory_Index e) {
    switch(e) {
        case Memory_Index_permanent: { return("Memory_Index_permanent"); } break;
        case Memory_Index_temp: { return("Memory_Index_temp"); } break;
        case Memory_Index_internal_temp: { return("Memory_Index_internal_temp"); } break;
        case Memory_Index_bitmap: { return("Memory_Index_bitmap"); } break;
        case Memory_Index_renderer: { return("Memory_Index_renderer"); } break;
        case Memory_Index_malloc_nofree_size: { return("Memory_Index_malloc_nofree_size"); } break;
        case Memory_Index_font_data: { return("Memory_Index_font_data"); } break;
    }
    return(0);
}
static Memory_Arena_Error sglg_Memory_Arena_Error_from_string(char const *s, uint32_t l) {
    if(0) {}
    else if(sgl_generated_string_compare("Memory_Arena_Error_success", 26, s, l)) { return(Memory_Arena_Error_success); }
    else if(sgl_generated_string_compare("Memory_Arena_Error_invalid_group_buffer_index", 45, s, l)) { return(Memory_Arena_Error_invalid_group_buffer_index); }
    else if(sgl_generated_string_compare("Memory_Arena_Error_size_too_big", 31, s, l)) { return(Memory_Arena_Error_size_too_big); }
    else if(sgl_generated_string_compare("Memory_Arena_Error_invalid_input", 32, s, l)) { return(Memory_Arena_Error_invalid_input); }
    else if(sgl_generated_string_compare("Memory_Arena_Error_internal_error", 33, s, l)) { return(Memory_Arena_Error_internal_error); }
    else if(sgl_generated_string_compare("Memory_Arena_Error_wrong_free_order", 35, s, l)) { return(Memory_Arena_Error_wrong_free_order); }
    else if(sgl_generated_string_compare("Memory_Arena_Error_count", 24, s, l)) { return(Memory_Arena_Error_count); }
    return((Memory_Arena_Error)0);
}
static Key sglg_Key_from_string(char const *s, uint32_t l) {
    if(0) {}
    else if(sgl_generated_string_compare("key_unknown", 11, s, l)) { return(key_unknown); }
    else if(sgl_generated_string_compare("key_ctrl", 8, s, l)) { return(key_ctrl); }
    else if(sgl_generated_string_compare("key_shift", 9, s, l)) { return(key_shift); }
    else if(sgl_generated_string_compare("key_alt", 7, s, l)) { return(key_alt); }
    else if(sgl_generated_string_compare("key_space", 9, s, l)) { return(key_space); }
    else if(sgl_generated_string_compare("key_escape", 10, s, l)) { return(key_escape); }
    else if(sgl_generated_string_compare("key_left", 8, s, l)) { return(key_left); }
    else if(sgl_generated_string_compare("key_right", 9, s, l)) { return(key_right); }
    else if(sgl_generated_string_compare("key_up", 6, s, l)) { return(key_up); }
    else if(sgl_generated_string_compare("key_down", 8, s, l)) { return(key_down); }
    else if(sgl_generated_string_compare("key_mouse_left", 14, s, l)) { return(key_mouse_left); }
    else if(sgl_generated_string_compare("key_mouse_middle", 16, s, l)) { return(key_mouse_middle); }
    else if(sgl_generated_string_compare("key_mouse_right", 15, s, l)) { return(key_mouse_right); }
    else if(sgl_generated_string_compare("left_stick_x", 12, s, l)) { return(left_stick_x); }
    else if(sgl_generated_string_compare("left_stick_y", 12, s, l)) { return(left_stick_y); }
    else if(sgl_generated_string_compare("right_stick_x", 13, s, l)) { return(right_stick_x); }
    else if(sgl_generated_string_compare("right_stick_y", 13, s, l)) { return(right_stick_y); }
    else if(sgl_generated_string_compare("dpad_right", 10, s, l)) { return(dpad_right); }
    else if(sgl_generated_string_compare("dpad_up", 7, s, l)) { return(dpad_up); }
    else if(sgl_generated_string_compare("dpad_down", 9, s, l)) { return(dpad_down); }
    else if(sgl_generated_string_compare("dpad_left", 9, s, l)) { return(dpad_left); }
    else if(sgl_generated_string_compare("start", 5, s, l)) { return(start); }
    else if(sgl_generated_string_compare("back", 4, s, l)) { return(back); }
    else if(sgl_generated_string_compare("left_shoulder", 13, s, l)) { return(left_shoulder); }
    else if(sgl_generated_string_compare("right_shoulder", 14, s, l)) { return(right_shoulder); }
    else if(sgl_generated_string_compare("left_thumb", 10, s, l)) { return(left_thumb); }
    else if(sgl_generated_string_compare("right_thumb", 11, s, l)) { return(right_thumb); }
    else if(sgl_generated_string_compare("controller_a", 12, s, l)) { return(controller_a); }
    else if(sgl_generated_string_compare("controller_b", 12, s, l)) { return(controller_b); }
    else if(sgl_generated_string_compare("controller_x", 12, s, l)) { return(controller_x); }
    else if(sgl_generated_string_compare("controller_y", 12, s, l)) { return(controller_y); }
    else if(sgl_generated_string_compare("key_A", 5, s, l)) { return(key_A); }
    else if(sgl_generated_string_compare("key_B", 5, s, l)) { return(key_B); }
    else if(sgl_generated_string_compare("key_C", 5, s, l)) { return(key_C); }
    else if(sgl_generated_string_compare("key_D", 5, s, l)) { return(key_D); }
    else if(sgl_generated_string_compare("key_E", 5, s, l)) { return(key_E); }
    else if(sgl_generated_string_compare("key_F", 5, s, l)) { return(key_F); }
    else if(sgl_generated_string_compare("key_G", 5, s, l)) { return(key_G); }
    else if(sgl_generated_string_compare("key_H", 5, s, l)) { return(key_H); }
    else if(sgl_generated_string_compare("key_I", 5, s, l)) { return(key_I); }
    else if(sgl_generated_string_compare("key_J", 5, s, l)) { return(key_J); }
    else if(sgl_generated_string_compare("key_K", 5, s, l)) { return(key_K); }
    else if(sgl_generated_string_compare("key_L", 5, s, l)) { return(key_L); }
    else if(sgl_generated_string_compare("key_M", 5, s, l)) { return(key_M); }
    else if(sgl_generated_string_compare("key_N", 5, s, l)) { return(key_N); }
    else if(sgl_generated_string_compare("key_O", 5, s, l)) { return(key_O); }
    else if(sgl_generated_string_compare("key_P", 5, s, l)) { return(key_P); }
    else if(sgl_generated_string_compare("key_Q", 5, s, l)) { return(key_Q); }
    else if(sgl_generated_string_compare("key_R", 5, s, l)) { return(key_R); }
    else if(sgl_generated_string_compare("key_S", 5, s, l)) { return(key_S); }
    else if(sgl_generated_string_compare("key_T", 5, s, l)) { return(key_T); }
    else if(sgl_generated_string_compare("key_U", 5, s, l)) { return(key_U); }
    else if(sgl_generated_string_compare("key_V", 5, s, l)) { return(key_V); }
    else if(sgl_generated_string_compare("key_W", 5, s, l)) { return(key_W); }
    else if(sgl_generated_string_compare("key_X", 5, s, l)) { return(key_X); }
    else if(sgl_generated_string_compare("key_Y", 5, s, l)) { return(key_Y); }
    else if(sgl_generated_string_compare("key_Z", 5, s, l)) { return(key_Z); }
    else if(sgl_generated_string_compare("key_cnt", 7, s, l)) { return(key_cnt); }
    return((Key)0);
}
static Memory_Index sglg_Memory_Index_from_string(char const *s, uint32_t l) {
    if(0) {}
    else if(sgl_generated_string_compare("Memory_Index_permanent", 22, s, l)) { return(Memory_Index_permanent); }
    else if(sgl_generated_string_compare("Memory_Index_temp", 17, s, l)) { return(Memory_Index_temp); }
    else if(sgl_generated_string_compare("Memory_Index_internal_temp", 26, s, l)) { return(Memory_Index_internal_temp); }
    else if(sgl_generated_string_compare("Memory_Index_bitmap", 19, s, l)) { return(Memory_Index_bitmap); }
    else if(sgl_generated_string_compare("Memory_Index_renderer", 21, s, l)) { return(Memory_Index_renderer); }
    else if(sgl_generated_string_compare("Memory_Index_malloc_nofree_size", 31, s, l)) { return(Memory_Index_malloc_nofree_size); }
    else if(sgl_generated_string_compare("Memory_Index_font_data", 22, s, l)) { return(Memory_Index_font_data); }
    return((Memory_Index)0);
}
// sglg_Type
static uint64_t sglg_get_enum_count(sglg_Type type) {
    switch(type) {
        case sglg_Type_Memory_Arena_Error: { return(7); } break;
        case sglg_Type_Key: { return(58); } break;
        case sglg_Type_Memory_Index: { return(7); } break;
    }
    return(0);
}
static uint64_t sglg_type_to_size(sglg_Type type) {
    switch(type) {
        case sglg_Type_Memory_Arena_Error: { return(sizeof(Memory_Arena_Error)); } break;
        case sglg_Type_Memory_Group: { return(sizeof(Memory_Group)); } break;
        case sglg_Type_Memory: { return(sizeof(Memory)); } break;
        case sglg_Type_Internal_Push_Info: { return(sizeof(Internal_Push_Info)); } break;
        case sglg_Type_String: { return(sizeof(String)); } break;
        case sglg_Type_String_To_Int_Result: { return(sizeof(String_To_Int_Result)); } break;
        case sglg_Type_String_To_Float_Result: { return(sizeof(String_To_Float_Result)); } break;
        case sglg_Type_File: { return(sizeof(File)); } break;
        case sglg_Type_Key: { return(sizeof(Key)); } break;
        case sglg_Type_Platform_Callbacks: { return(sizeof(Platform_Callbacks)); } break;
        case sglg_Type_Bitmap: { return(sizeof(Bitmap)); } break;
        case sglg_Type_Settings: { return(sizeof(Settings)); } break;
        case sglg_Type_API: { return(sizeof(API)); } break;
        case sglg_Type_Memory_Index: { return(sizeof(Memory_Index)); } break;
        case sglg_Type_Config: { return(sizeof(Config)); } break;
        case sglg_Type_Image: { return(sizeof(Image)); } break;
        case sglg_Type_Bitmap_Header: { return(sizeof(Bitmap_Header)); } break;
        case sglg_Type_V2: { return(sizeof(V2)); } break;
        case sglg_Type_V3: { return(sizeof(V3)); } break;
        case sglg_Type_V4: { return(sizeof(V4)); } break;
        case sglg_Type_Lane_F32: { return(sizeof(Lane_F32)); } break;
        case sglg_Type_Lane_U32: { return(sizeof(Lane_U32)); } break;
        case sglg_Type_Lane_V2: { return(sizeof(Lane_V2)); } break;
        case sglg_Type_Lane_V3: { return(sizeof(Lane_V3)); } break;
        case sglg_Type_Lane_V4: { return(sizeof(Lane_V4)); } break;
        case sglg_Type_Lane_M2x2: { return(sizeof(Lane_M2x2)); } break;
        case sglg_Type_V2u: { return(sizeof(V2u)); } break;
        case sglg_Type_Rect: { return(sizeof(Rect)); } break;
        case sglg_Type_Image_Rect: { return(sizeof(Image_Rect)); } break;
        case sglg_Type_Render_Entity: { return(sizeof(Render_Entity)); } break;
        case sglg_Type_Render_Image: { return(sizeof(Render_Image)); } break;
        case sglg_Type_Renderer: { return(sizeof(Renderer)); } break;
        case sglg_Type_DLL_Data: { return(sizeof(DLL_Data)); } break;
    }
    return(0);
}
static sglg_Type sglg_string_to_type(char const *s, uint64_t l) {
    if(0) {}
    else if(sgl_generated_string_compare("Memory_Arena_Error", 18, s, l)) { return(sglg_Type_Memory_Arena_Error); }
    else if(sgl_generated_string_compare("Memory_Group", 12, s, l)) { return(sglg_Type_Memory_Group); }
    else if(sgl_generated_string_compare("Memory", 6, s, l)) { return(sglg_Type_Memory); }
    else if(sgl_generated_string_compare("Internal_Push_Info", 18, s, l)) { return(sglg_Type_Internal_Push_Info); }
    else if(sgl_generated_string_compare("String", 6, s, l)) { return(sglg_Type_String); }
    else if(sgl_generated_string_compare("String_To_Int_Result", 20, s, l)) { return(sglg_Type_String_To_Int_Result); }
    else if(sgl_generated_string_compare("String_To_Float_Result", 22, s, l)) { return(sglg_Type_String_To_Float_Result); }
    else if(sgl_generated_string_compare("File", 4, s, l)) { return(sglg_Type_File); }
    else if(sgl_generated_string_compare("Key", 3, s, l)) { return(sglg_Type_Key); }
    else if(sgl_generated_string_compare("Platform_Callbacks", 18, s, l)) { return(sglg_Type_Platform_Callbacks); }
    else if(sgl_generated_string_compare("Bitmap", 6, s, l)) { return(sglg_Type_Bitmap); }
    else if(sgl_generated_string_compare("Settings", 8, s, l)) { return(sglg_Type_Settings); }
    else if(sgl_generated_string_compare("API", 3, s, l)) { return(sglg_Type_API); }
    else if(sgl_generated_string_compare("Memory_Index", 12, s, l)) { return(sglg_Type_Memory_Index); }
    else if(sgl_generated_string_compare("Config", 6, s, l)) { return(sglg_Type_Config); }
    else if(sgl_generated_string_compare("Image", 5, s, l)) { return(sglg_Type_Image); }
    else if(sgl_generated_string_compare("Bitmap_Header", 13, s, l)) { return(sglg_Type_Bitmap_Header); }
    else if(sgl_generated_string_compare("V2", 2, s, l)) { return(sglg_Type_V2); }
    else if(sgl_generated_string_compare("V3", 2, s, l)) { return(sglg_Type_V3); }
    else if(sgl_generated_string_compare("V4", 2, s, l)) { return(sglg_Type_V4); }
    else if(sgl_generated_string_compare("Lane_F32", 8, s, l)) { return(sglg_Type_Lane_F32); }
    else if(sgl_generated_string_compare("Lane_U32", 8, s, l)) { return(sglg_Type_Lane_U32); }
    else if(sgl_generated_string_compare("Lane_V2", 7, s, l)) { return(sglg_Type_Lane_V2); }
    else if(sgl_generated_string_compare("Lane_V3", 7, s, l)) { return(sglg_Type_Lane_V3); }
    else if(sgl_generated_string_compare("Lane_V4", 7, s, l)) { return(sglg_Type_Lane_V4); }
    else if(sgl_generated_string_compare("Lane_M2x2", 9, s, l)) { return(sglg_Type_Lane_M2x2); }
    else if(sgl_generated_string_compare("V2u", 3, s, l)) { return(sglg_Type_V2u); }
    else if(sgl_generated_string_compare("Rect", 4, s, l)) { return(sglg_Type_Rect); }
    else if(sgl_generated_string_compare("Image_Rect", 10, s, l)) { return(sglg_Type_Image_Rect); }
    else if(sgl_generated_string_compare("Render_Entity", 13, s, l)) { return(sglg_Type_Render_Entity); }
    else if(sgl_generated_string_compare("Render_Image", 12, s, l)) { return(sglg_Type_Render_Image); }
    else if(sgl_generated_string_compare("Renderer", 8, s, l)) { return(sglg_Type_Renderer); }
    else if(sgl_generated_string_compare("DLL_Data", 8, s, l)) { return(sglg_Type_DLL_Data); }
    return(sglg_Type_unknown);
}
