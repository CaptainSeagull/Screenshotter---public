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
static char const *sglg_Memory_Index_to_string(Memory_Index e) {
    switch(e) {
        case Memory_Index_permanent: { return("Memory_Index_permanent"); } break;
        case Memory_Index_temp: { return("Memory_Index_temp"); } break;
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
static Memory_Index sglg_Memory_Index_from_string(char const *s, uint32_t l) {
    if(0) {}
    else if(sgl_generated_string_compare("Memory_Index_permanent", 22, s, l)) { return(Memory_Index_permanent); }
    else if(sgl_generated_string_compare("Memory_Index_temp", 17, s, l)) { return(Memory_Index_temp); }
    return((Memory_Index)0);
}
// sglg_Type
static uint64_t sglg_get_enum_count(sglg_Type type) {
    switch(type) {
        case sglg_Type_Memory_Arena_Error: { return(7); } break;
        case sglg_Type_Memory_Index: { return(2); } break;
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
        case sglg_Type_Memory_Index: { return(sizeof(Memory_Index)); } break;
        case sglg_Type_Image: { return(sizeof(Image)); } break;
        case sglg_Type_Bitmap_Header: { return(sizeof(Bitmap_Header)); } break;
        case sglg_Type_Config: { return(sizeof(Config)); } break;
        case sglg_Type_Thread_Parameters: { return(sizeof(Thread_Parameters)); } break;
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
    else if(sgl_generated_string_compare("Memory_Index", 12, s, l)) { return(sglg_Type_Memory_Index); }
    else if(sgl_generated_string_compare("Image", 5, s, l)) { return(sglg_Type_Image); }
    else if(sgl_generated_string_compare("Bitmap_Header", 13, s, l)) { return(sglg_Type_Bitmap_Header); }
    else if(sgl_generated_string_compare("Config", 6, s, l)) { return(sglg_Type_Config); }
    else if(sgl_generated_string_compare("Thread_Parameters", 17, s, l)) { return(sglg_Type_Thread_Parameters); }
    return(sglg_Type_unknown);
}
