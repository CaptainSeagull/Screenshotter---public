
#define MEMORY_ARENA_IMPLEMENTATION
#if INTERNAL
    #define MEMORY_ARENA_WRITE_ERRORS
#endif
#define STRING_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION

#include "common.cpp"
#define LANE_PUBLIC_DEC static
#define LANE_WIDTH 1 // TODO: Mirror isn't handling this being different correctly.
#include "../shared/lane/lane.cpp"

#include <windows.h>
#include <shlobj.h>
#include <gl/gl.h>
#include <intrin.h>

#include "platform_win32.h"
#include "platform_win32_generated.h"
#include "renderer.h"

#define MAX_SCREEN_BITMAP_SIZE (1920 * 1080 * 4) // TODO: Change to 4k?

// TODO: Go through this file and tidy it up.

// TODO: Globals... :-(
internal_global BITMAPINFO global_bmp_info;
internal_global API *global_api;
internal_global GLuint global_gl_blit_texture_handle;
internal_global Win32_System_Callbacks *global_sys_cb;

internal File
win32_read_file(Memory *memory, U32 memory_index_to_use, String fname, Bool null_terminate) {
    File res = {};

    Char *fname_copy = (Char *)memory_push_string(memory, Memory_Index_internal_temp, fname);
    ASSERT(fname_copy);
    if(fname_copy) {
        HANDLE fhandle = CreateFileA(fname_copy, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
        if(fhandle != INVALID_HANDLE_VALUE) {
            LARGE_INTEGER fsize;
            if(GetFileSizeEx(fhandle, &fsize)) {
                DWORD fsize32 = safe_truncate_size_64(fsize.QuadPart);
                Void *file_memory = memory_push(memory, memory_index_to_use, (null_terminate) ? fsize32 + 1 : fsize32);
                ASSERT(file_memory);
                if(file_memory) {
                    DWORD bytes_read = 0;
                    if(ReadFile(fhandle, file_memory, fsize32, &bytes_read, 0)) {
                        if(bytes_read != fsize32) {
                            ASSERT(0);
                        } else {
                            res.fname = fname; // TODO: Change to full path not relative.
                            res.size = fsize32;
                            res.e = (U8 *)file_memory;
                            res.e[res.size] = 0;
                        }
                    }
                }
            }

            CloseHandle(fhandle);
        }

        memory_pop(memory, fname_copy);
    }

    return(res);
}

internal Bool
win32_write_file(Memory *memory, String fname, U8 *data, U64 size) {
    Bool res = false;

    Char *fname_copy = (Char *)memory_push_string(memory, Memory_Index_internal_temp, fname);
    ASSERT(fname_copy);
    if(fname_copy) {
        HANDLE fhandle = CreateFileA(fname_copy, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
        if(fhandle != INVALID_HANDLE_VALUE) {

            DWORD fsize32;
#if ENVIRONMENT32
            fsize32 = file.size;
#else
            fsize32 = safe_truncate_size_64(size);
#endif
            DWORD bytes_written = 0;
            if(WriteFile(fhandle, data, fsize32, &bytes_written, 0)) {
                if(bytes_written != fsize32) {
                    ASSERT(0);
                } else {
                    res = true;
                }
            }

            CloseHandle(fhandle);
        }

        memory_pop(memory, fname_copy);
    }

    return(res);
}

internal Int
win32_get_processor_count(Void) {
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    U32 res = info.dwNumberOfProcessors;

    return(res);
}

internal U64
win32_locked_add(U64 volatile *a, U64 b) {
    U64 r = InterlockedExchangeAdd64((S64 volatile *)a, b);
    return(r);
}

internal F32
win32_safe_div(F32 a, F32 b) {
    F32 r = a;
    if(b != 0) {
        r = a / b;
    }

    return(r);
}

internal Void
win32_update_window(Memory *memory, HDC dc, RECT  *wnd_rect, Void *input_bitmap_memory, BITMAPINFO *bitmap_info,
                    Int bitmap_width, Int bitmap_height) {
    Int wnd_w = wnd_rect->right - wnd_rect->left;
    Int wnd_h = wnd_rect->bottom - wnd_rect->top;

    Void *bitmap_memory = input_bitmap_memory;

    Bool should_flip_image = true;

    if(should_flip_image) {
        bitmap_memory = memory_push(memory, Memory_Index_temp, bitmap_width * bitmap_height * 4);
        flip_image(bitmap_memory, input_bitmap_memory, bitmap_width, bitmap_height);
    }

#if USE_OPENGL_WINDOW

    // Could be moved to platform-independent code.
    {
        global_sys_cb->glViewport(0, 0, wnd_w, wnd_h);

        global_sys_cb->glBindTexture(GL_TEXTURE_2D, global_gl_blit_texture_handle);

        global_sys_cb->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, bitmap_width, bitmap_height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmap_memory);

        global_sys_cb->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        global_sys_cb->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        global_sys_cb->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP);
        global_sys_cb->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP);

        global_sys_cb->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        global_sys_cb->glEnable(GL_TEXTURE_2D); // TODO: Move above glBindTexture?
#if INTERNAL
        global_sys_cb->glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
#else
        global_sys_cb->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
#endif
        global_sys_cb->glClear(GL_COLOR_BUFFER_BIT);

        global_sys_cb->glMatrixMode(GL_MODELVIEW); global_sys_cb->glLoadIdentity();

        global_sys_cb->glMatrixMode(GL_PROJECTION);

        // This is pre-transposted
        F32 proj[16] = {win32_safe_div(2.0f, bitmap_width), 0,                                   0, 0,
                        0,                                  win32_safe_div(2.0f, bitmap_height), 0, 0,
                        0,                                  0,                                   1, 0,
                        -1,                                 -1,                                  0, 1
                       };
        global_sys_cb->glLoadMatrixf(proj);
        global_sys_cb->glMatrixMode(GL_TEXTURE); global_sys_cb->glLoadIdentity();

        global_sys_cb->glBegin(GL_TRIANGLES);

        // TODO: How to handle aspect ratio - black bars or crop?

        F32 min_x = 0;
        F32 min_y = 0;
        F32 max_x = bitmap_width;
        F32 max_y = bitmap_height;

        F32 colour[4] = { 1, 1, 1, 1 };
        global_sys_cb->glColor4f(colour[0], colour[1], colour[2], colour[3]);

        global_sys_cb->glTexCoord2f(0, 0); global_sys_cb->glVertex2f(min_x, min_y);
        global_sys_cb->glTexCoord2f(1, 0); global_sys_cb->glVertex2f(max_x, min_y);
        global_sys_cb->glTexCoord2f(1, 1); global_sys_cb->glVertex2f(max_x, max_y);

        global_sys_cb->glTexCoord2f(0, 0); global_sys_cb->glVertex2f(min_x, min_y);
        global_sys_cb->glTexCoord2f(1, 1); global_sys_cb->glVertex2f(max_x, max_y);
        global_sys_cb->glTexCoord2f(0, 1); global_sys_cb->glVertex2f(min_x, max_y);
        global_sys_cb->glEnd();
    }

    global_sys_cb->SwapBuffers(dc);
#else
    // TODO: Bitblt may be faster than StretchDIBits
    global_sys_cb->StretchDIBits(dc,
                                 0, 0, bitmap_width, bitmap_height,
                                 0, 0, wnd_w, wnd_h,
                                 bitmap_memory, bitmap_info, DIB_RGB_COLORS, SRCCOPY);
#endif

    if(should_flip_image) {
        memory_pop(memory, bitmap_memory);
    }
}

internal LRESULT CALLBACK
win32_window_proc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    LRESULT res = 0;
    switch(msg) {
        case WM_QUIT: case WM_CLOSE: { global_api->running = false; } break;

        case WM_SIZE: {
            RECT cr;
            global_sys_cb->GetClientRect(wnd, &cr);
            Int w = cr.right - cr.left;
            Int h = cr.bottom - cr.top;

            // May be faster to allocate new memory / free old memory. But works for now.
            if(global_api->screen_bitmap.memory) {
                zero(global_api->screen_bitmap.memory, MAX_SCREEN_BITMAP_SIZE);
            }

            global_bmp_info.bmiHeader.biSize = sizeof(global_bmp_info.bmiHeader);
            global_bmp_info.bmiHeader.biWidth = w;
            global_bmp_info.bmiHeader.biHeight = h;
            global_bmp_info.bmiHeader.biPlanes = 1;
            global_bmp_info.bmiHeader.biBitCount = 32;
            global_bmp_info.bmiHeader.biCompression = BI_RGB;
            global_bmp_info.bmiHeader.biSizeImage = 0;
            global_bmp_info.bmiHeader.biXPelsPerMeter = 0;
            global_bmp_info.bmiHeader.biYPelsPerMeter = 0;
            global_bmp_info.bmiHeader.biClrUsed = 0;
            global_bmp_info.bmiHeader.biClrImportant = 0;

            global_api->screen_bitmap.width = w;
            global_api->screen_bitmap.height = h;

            global_api->screen_image_size_change = true;
        } break;

        // TODO: This never seems to be called. Is it nessessary?
        /*case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC dc = BeginPaint(wnd, &ps);
            RECT cr;
            GetClientRect(wnd, &cr);
            win32_update_window(global_api->memory, dc, &cr, global_api->screen_bitmap.memory, &global_bmp_info,
                                global_api->screen_bitmap.width, global_api->screen_bitmap.height);
            EndPaint(wnd, &ps);
        } break;*/

        default: {
            res = global_sys_cb->DefWindowProcA(wnd, msg, w_param, l_param);
        }
    }

    return(res);
};

internal Key
win32_key_to_our_key(WPARAM k) {
    Key res = key_unknown;
    switch(k) {
        case VK_CONTROL: { res = key_ctrl;   } break;
        case VK_SHIFT:   { res = key_shift;  } break;
        //case VK_ALT:     { res = key_alt;    } break;
        case VK_SPACE:   { res = key_space;  } break;
        case VK_ESCAPE:  { res = key_escape; } break;

        case VK_LEFT:    { res = key_left;  } break;
        case VK_RIGHT:   { res = key_right; } break;
        case VK_UP:      { res = key_up;    } break;
        case VK_DOWN:    { res = key_down;  } break;

        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
        case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
        case 'V': case 'W': case 'X': case 'Y': case 'Z': {
            res = (Key)k;
        } break;

        case '0': { res = (Key)0; } break;
        case '1': { res = (Key)1; } break;
        case '2': { res = (Key)2; } break;
        case '3': { res = (Key)3; } break;
        case '4': { res = (Key)4; } break;
        case '5': { res = (Key)5; } break;
        case '6': { res = (Key)6; } break;
        case '7': { res = (Key)7; } break;
        case '8': { res = (Key)8; } break;
        case '9': { res = (Key)9; } break;
    }

    return(res);
}

internal F32
win32_get_seconds_elapsed(LARGE_INTEGER start, LARGE_INTEGER end, int64_t perf_cnt_freq) {
    F32 r = (F32)(end.QuadPart - start.QuadPart) / (F32)perf_cnt_freq;
    return(r);
}

internal LARGE_INTEGER
win32_get_wall_clock(Void) {
    LARGE_INTEGER res;
    Bool s = QueryPerformanceCounter(&res); // Apparently can't fail post XP... not that I trust the docs :-)
    ASSERT(s);

    return(res);
}

internal Void
win32_get_window_dimension(HWND wnd, Int *w, Int *h, Win32_System_Callbacks *sys_cb) {
    RECT cr;
    Bool s = sys_cb->GetClientRect(wnd, &cr);
    ASSERT_IF(s) {
        *w = (cr.right - cr.left);
        *h = (cr.bottom - cr.top);
    }
}

internal Void
win32_init_opengl(HWND window, Win32_System_Callbacks *sys_cb) {
    HDC dc = sys_cb->GetDC(window);

    PIXELFORMATDESCRIPTOR desired_pfd = {};
    desired_pfd.nSize = sizeof(desired_pfd);
    desired_pfd.nVersion = 1;
    desired_pfd.iPixelType = PFD_TYPE_RGBA;
    desired_pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER; // TODO: PFD_DOUBLEBUFFER can have issues with streaming...
    desired_pfd.cColorBits = 32; // TODO: Or 24 or 32?
    desired_pfd.cAlphaBits = 8;
    desired_pfd.iLayerType = PFD_MAIN_PLANE;

    Int suggested_pfd_i = sys_cb->ChoosePixelFormat(dc, &desired_pfd);
    PIXELFORMATDESCRIPTOR suggested_pfd;
    sys_cb->DescribePixelFormat(dc, suggested_pfd_i, sizeof(suggested_pfd), &suggested_pfd);
    sys_cb->SetPixelFormat(dc, suggested_pfd_i, &suggested_pfd);

    HGLRC rc = sys_cb->wglCreateContext(dc);
    if(sys_cb->wglMakeCurrent(dc, rc)) {
        sys_cb->glGenTextures(1, &global_gl_blit_texture_handle);
    } else {
        ASSERT(0); // TODO: Something went wrong. Not sure how to handle this error...
    }

    sys_cb->ReleaseDC(window, dc);
}

//
// Threading
internal Bool
win32_add_work_queue_entry(API *api, Void *data, Void (*cb)(Void *data)) {
    Bool res = false;

    Win32_API *win32_api = (Win32_API *)api->platform_specific;
    Win32_Work_Queue *queue = &win32_api->queue;

    // % entry_count because it's a circular buffer!
    Int new_next_entry_to_write = (queue->next_entry_to_write + 1) % queue->entry_count;

    // This is a circular buffer, so these should never match!
    if(new_next_entry_to_write != queue->next_entry_to_read) {
        res = true;

        Win32_Work_Queue_Entry *entry = &queue->entries[queue->next_entry_to_write];
        entry->cb = cb;
        entry->data = data;

        ++queue->completion_goal;

        _WriteBarrier(); _mm_sfence();

        queue->next_entry_to_write = new_next_entry_to_write;
        ReleaseSemaphore(queue->semaphore, 1, 0);
    }

    return(res);
}

// Returns true if we actually did any work.
internal Bool
win32_do_next_work_queue_entry(Win32_Work_Queue *queue) {
    Bool res = false;

    // Store next_entry_to_read and DON'T read it again in case the value's changed by other threads. We do a InterlockedCompareExchange
    // below to validate it's still correct before actually doing any work.
    Int original_next_entry_to_read = queue->next_entry_to_read;
    Int new_entry_to_read = (original_next_entry_to_read + 1) % queue->entry_count; // % entry_count because it's a circular buffer!

    // Check if we've caught-up to the write cursor.
    if(original_next_entry_to_read != queue->next_entry_to_write) {
        res = true;

        // Do a thread-safe exchange and see if we get back the original.
        Int idx = InterlockedCompareExchange((LONG volatile *)&queue->next_entry_to_read, new_entry_to_read, original_next_entry_to_read);
        if(idx == original_next_entry_to_read) {
            Win32_Work_Queue_Entry *entry = &queue->entries[idx];
            entry->cb(entry->data);

            InterlockedIncrement((LONG volatile *)&queue->completion_count);
        }
    }

    return(res);
}

internal Void
win32_complete_all_work(API *api) {
    Win32_API *win32_api = (Win32_API *)api->platform_specific;
    Win32_Work_Queue *queue = &win32_api->queue;

    while(queue->completion_goal != queue->completion_count) {
        win32_do_next_work_queue_entry(queue);
    }

    queue->completion_goal = 0;
    queue->completion_count = 0;
}

internal DWORD WINAPI
win32_thread_proc(Void *p) {
    Win32_Work_Queue *queue = (Win32_Work_Queue *)p;
    for(;;) {
        if(!win32_do_next_work_queue_entry(queue)) {
            WaitForSingleObjectEx(queue->semaphore, INFINITE, 0);
        }
    }

    //return(0);
}

//
// Code for reloading DLL
internal FILETIME
win32_get_last_write_time(Char *fname) {
    FILETIME res = {};
    WIN32_FIND_DATA find_data = {};
    HANDLE find_handle = FindFirstFileA(fname, &find_data);
    if(find_handle != INVALID_HANDLE_VALUE) {
        res = find_data.ftLastWriteTime;
        FindClose(find_handle);
    }

    return(res);
}

internal Win32_Loaded_Code
win32_load_code(Char *source_fname, Char *temp_fname) {
    Win32_Loaded_Code res = {};

    res.dll_last_write_time = win32_get_last_write_time(source_fname);
    CopyFile(source_fname, temp_fname, FALSE);

    res.dll = LoadLibraryA(temp_fname);
    ASSERT(res.dll);
    if(res.dll) {
        res.init_platform_settings  = (Init_Platform_Settings *) GetProcAddress(res.dll, "init_platform_settings"          );
        res.handle_input_and_render = (Handle_Input_And_Render *)GetProcAddress(res.dll, "handle_input_and_render");
        res.success = (res.handle_input_and_render && res.init_platform_settings);
        ASSERT(res.success);
    }

    return(res);
}

internal HWND
win32_find_window_from_class_name(Memory *memory, String window_title, Win32_System_Callbacks *sys_cb) {
    HWND window = 0;

    Char *window_title_raw = (Char *)memory_push(memory, Memory_Index_temp, window_title.len + 1); // Nul-terminate
    ASSERT(window_title_raw);
    if(window_title_raw) {
        string_copy(window_title_raw, window_title.e, window_title.len);
        window = sys_cb->FindWindowExA(0, 0, TEXT(window_title_raw), 0);
        ASSERT(window);

        memory_pop(memory, window_title_raw);
    }

    return(window);
}

struct Win32_Create_Directory_Result {
    String directory;
    Bool success;
};
internal Win32_Create_Directory_Result
win32_create_directory(Memory *memory, String root, String dir, Bool save_directory_string = false) {
    Win32_Create_Directory_Result res = {};

    // Create the per-app directories
    Int max_size = root.len + 256; // 256 is padding
    Char *output_file_directory = (Char *)memory_push(memory, (save_directory_string) ? Memory_Index_permanent : Memory_Index_temp, max_size);
    ASSERT(output_file_directory);
    if(output_file_directory) {
        Int bytes_written = stbsp_snprintf(output_file_directory, max_size, "%.*s\\%.*s",
                                           root.len, root.e,
                                           dir.len, dir.e);
        ASSERT(bytes_written < max_size);

        Bool success = CreateDirectory(output_file_directory, NULL) != 0;
        if(!success) {
            success = (GetLastError() == ERROR_ALREADY_EXISTS);
        }

        if(success) {
            res.success = true;
            if(save_directory_string) {
                res.directory = output_file_directory;
            }
        }

        if(!save_directory_string) {
            memory_pop(memory, output_file_directory);
        }
    }

    return(res);
}

internal Int
win32_directory_index_to_use(Memory *mem, String session_prefix, String input_target_directory) {
    Int res = 0;

    Char *target_directory = memory_push_string(mem, Memory_Index_temp, input_target_directory, 3); // Padding for "\\*"
    ASSERT(target_directory);
    if(target_directory) {
        target_directory[input_target_directory.len + 0] = '\\';
        target_directory[input_target_directory.len + 1] = '*';
        target_directory[input_target_directory.len + 2] = 0;

        WIN32_FIND_DATA find_data = {};
        HANDLE handle = FindFirstFile(target_directory, &find_data);

        if(handle != INVALID_HANDLE_VALUE) {
            do {
                String fname = find_data.cFileName + session_prefix.len;
                String_To_Int_Result r = string_to_int(fname);
                if(r.success) {
                    res = maxu32(res, r.v + 1);
                }
            } while(FindNextFile(handle, &find_data));
        }

        memory_pop(mem, target_directory);
    }

    return(res);
}

internal Bool
run_screenshotting(API *api, Memory *memory, Config *config, Win32_System_Callbacks *sys_cb, String root_directory, U64 iteration_count) {
    Bool res = false;

    for(Int window_i = 0; (window_i < config->target_window_count); ++window_i) {
        ASSERT(config->windows[window_i].class_name.len > 0 &&
               config->windows[window_i].title.len > 0);
        HWND window = win32_find_window_from_class_name(memory, config->windows[window_i].class_name, sys_cb);

        RECT rect = {};
        sys_cb->GetClientRect(window, &rect);
        Int width = rect.right - rect.left;
        Int height = rect.bottom - rect.top;

        // TODO: If the window is minified then the width/height will be 0
        //       See https://www.codeproject.com/Articles/20651/Capturing-Minimized-Window-A-Kid-s-Trick for how to handle.
        if(width > 0 && height > 0) {
            HDC dc = sys_cb->GetDC(0);
            HDC capture_dc = sys_cb->CreateCompatibleDC(dc);
            HBITMAP bitmap =  sys_cb->CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);

            HGDIOBJ gdiObj = sys_cb->SelectObject(capture_dc, bitmap);

            sys_cb->PrintWindow(window, capture_dc, (config->include_title_bar) ? 0 : PW_CLIENTONLY);

            // TODO: This sometimes captures the current window, not the target for some reason...
            //BitBlt(capture_dc, 0, 0, width, height, dc, 0, 0, SRCCOPY | CAPTUREBLT);
            //SelectObject(capture_dc, gdiObj);
#if 0
            // Test code to copy to clipboard.
            OpenClipboard(0);
            EmptyClipboard();
            SetClipboardData(CF_BITMAP, bitmap);
            CloseClipboard();
#endif
            BITMAPINFOHEADER bmp_header = {};
            bmp_header.biSize = sizeof(BITMAPINFOHEADER);
            bmp_header.biWidth = width;
            bmp_header.biHeight = height;
            bmp_header.biPlanes = 1;
            bmp_header.biBitCount = 32;

            U32 image_size = ((width * bmp_header.biBitCount + 31) / 32) * 4 * height; // TODO: Why 31 / 32?? Why not just width * height * 4?
            U8 *image_data = (U8 *)memory_push(memory, Memory_Index_temp, image_size);
            ASSERT(image_data);
            if(image_data) {
                sys_cb->GetDIBits(dc, bitmap, 0, height, image_data, (BITMAPINFO *)&bmp_header, DIB_RGB_COLORS);

                // Try and create using the Window title. And if that fails use the classname.
                Bool created_directory = false;
                String program_title = config->windows[window_i].title;
                Win32_Create_Directory_Result create_dir_r = win32_create_directory(memory, root_directory, program_title);
                created_directory = create_dir_r.success;
                if(!created_directory) {
                    program_title = config->windows[window_i].class_name;
                    create_dir_r = win32_create_directory(memory, root_directory, program_title);
                    created_directory = create_dir_r.success;
                }

                if(created_directory) {

                    Int output_filename_size = root_directory.len + 256; // 256 is padding
                    Char *output_filename = (Char *)memory_push(memory, Memory_Index_temp, output_filename_size);
                    ASSERT(output_filename);
                    if(output_filename) {

                        // TODO: Instead of using iteration_count it'd be better to read the previous highest-number in the file and
                        //       just +1 to that.
                        Int bytes_written = stbsp_snprintf(output_filename, output_filename_size, "%.*s/%.*s/%I64d.bmp",
                                                           root_directory.len, root_directory.e,
                                                           program_title.len, program_title.e,
                                                           iteration_count);
                        ASSERT(bytes_written < output_filename_size);

                        Image image = {};
                        image.width = width;
                        image.height = height;
                        image.pixels = (U32 * )image_data;
                        write_image_to_disk(api, memory, &image, output_filename);

                        res = true;

                        memory_pop(memory, output_filename);
                    }
                }

                memory_pop(memory, image_data);
            }

            sys_cb->ReleaseDC(0, dc);
        }
    }

    return(res);
}

internal String
win32_create_root_directory(Memory *memory, String target_directory) {
    String res = {};

    String prefix = "Screenshotter_";

    Int idx = win32_directory_index_to_use(memory, prefix, target_directory);
    Int size = target_directory.len + prefix.len + 32; // TODO: 32 is padding for number
    Char *directory = (Char *)memory_push(memory, Memory_Index_permanent, size);
    ASSERT_IF(directory) {
        Int written = stbsp_snprintf(directory, size, "%.*s%d",
                                     prefix.len, prefix.e,
                                     idx);
        ASSERT(written < size);

        // TODO: Memory leak.
        Win32_Create_Directory_Result create_directory_result = win32_create_directory(memory, target_directory,
                                                                                       directory, true);
        ASSERT(create_directory_result.success);
        res = create_directory_result.directory;
    }

    return(res);
}

internal BOOL CALLBACK
enum_windows_proc(HWND hwnd, LPARAM param) {
    API *api = (API *)param;
    Memory *memory = api->memory;

    Bool success = false;

    Int max_string_length = 1024;

    Char *title = (Char *)memory_push(memory, Memory_Index_window_titles, max_string_length);
    Char *class_name = (Char *)memory_push(memory, Memory_Index_window_titles, max_string_length);
    ASSERT(title && class_name);
    if(title && class_name) {
        if(global_sys_cb->IsWindowVisible(hwnd)) {
            global_sys_cb->GetWindowText(hwnd, (LPSTR)title, max_string_length);
            global_sys_cb->GetClassName(hwnd, (LPSTR)class_name, max_string_length);

            Int title_len = string_length(title);
            Int class_name_len = string_length(class_name);

            if(title_len > 0 && class_name_len > 0) {
                ASSERT(api->window_count < ARRAY_COUNT(api->windows));
                if(api->window_count < ARRAY_COUNT(api->windows)) {
                    Window_Info *wi = &api->windows[api->window_count++];
                    wi->title = create_string(title, title_len);
                    wi->class_name = create_string(class_name, class_name_len);
                    success = true;
                }
            }
        }
    }

    if(!success) {
        if(class_name) { memory_pop(memory, class_name); }
        if(title)      { memory_pop(memory, title); }
    }

    return(TRUE);
}

internal int CALLBACK
win32_directory_browse_callback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
    if(uMsg == BFFM_INITIALIZED) {
        global_sys_cb->SendMessageA(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }

    return 0;
}

internal String
win32_browse_for_directory(Memory *memory, String initial_path) {
    String res = {};

    // TODO: Replace '/' in input path with '\\'.
    Char *initial_path_copy = (Char *)memory_push_string(memory, Memory_Index_internal_temp, initial_path);
    ASSERT(initial_path_copy);
    if(initial_path_copy) {
        BROWSEINFO bi = { };
        bi.lpszTitle = "Select directory...";
        bi.ulFlags   = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
        bi.lpfn      = win32_directory_browse_callback;
        bi.lParam    = (LPARAM)initial_path_copy;

        LPITEMIDLIST pidl = global_sys_cb->SHBrowseForFolder(&bi);
        if(pidl) {
            TCHAR path[MAX_PATH];
            global_sys_cb->SHGetPathFromIDList(pidl, path);

            IMalloc *imalloc = 0;
            if(SUCCEEDED(global_sys_cb->SHGetMalloc(&imalloc))) {
                imalloc->Free(pidl);
                imalloc->Release();
            }

            // TODO: Memory leak - if the user keeps browsing for directories then this will eventually run out of memory.
            Char *internal_string = memory_push_string(memory, Memory_Index_permanent, path);
            ASSERT_IF(internal_string) {
                res = internal_string;
            }
        }

        memory_pop(memory, initial_path_copy);
    }

    return(res);
}

internal Win32_System_Callbacks
load_system_callbacks(Void) {
    Win32_System_Callbacks r = {};

#define LOAD(dll,name) r.name = (name##_t *)GetProcAddress(dll, #name); if(!r.name && r.success) { r.success = false; }

    r.success = true;

#define SPECIAL_IF(x) if(!x) { ASSERT(0); r.success = false; } else

    SPECIAL_IF(r.success) {
        HMODULE user32 = LoadLibraryA("user32.dll");
        SPECIAL_IF(user32) {
            LOAD(user32, TranslateMessage);
            LOAD(user32, DispatchMessageA);
            LOAD(user32, PeekMessageA);
            LOAD(user32, SendMessageA);
            LOAD(user32, DefWindowProcA);
            LOAD(user32, RegisterClassA);
            LOAD(user32, CreateWindowExA);
            LOAD(user32, PrintWindow);
            LOAD(user32, IsWindowVisible);
            LOAD(user32, GetDC);
            LOAD(user32, ReleaseDC);
            LOAD(user32, SetWindowTextA);
            LOAD(user32, GetWindowTextA);
            LOAD(user32, GetClientRect);
            LOAD(user32, GetCursorPos);
            LOAD(user32, ScreenToClient);
            LOAD(user32, FindWindowExA);
            LOAD(user32, EnumWindows);
            LOAD(user32, GetClassNameA);
        }
    }

    SPECIAL_IF(r.success) {
        HMODULE gdi32 = LoadLibraryA("gdi32.dll");
        SPECIAL_IF(gdi32) {
            LOAD(gdi32, CreateCompatibleBitmap);
            LOAD(gdi32, CreateCompatibleDC);
            LOAD(gdi32, GetDIBits);
            LOAD(gdi32, SelectObject);
            LOAD(gdi32, StretchDIBits);
            LOAD(gdi32, ChoosePixelFormat);
            LOAD(gdi32, DescribePixelFormat);
            LOAD(gdi32, SetPixelFormat);
            LOAD(gdi32, SwapBuffers);
        }
    }

    SPECIAL_IF(r.success) {
        HMODULE shell32 = LoadLibraryA("shell32.dll");
        SPECIAL_IF(shell32) {
            LOAD(shell32, SHGetMalloc);
            LOAD(shell32, SHGetPathFromIDListA);
            LOAD(shell32, SHBrowseForFolderA);
        }
    }

#if USE_OPENGL_WINDOW
    ASSERT_IF(r.success) {
        HMODULE opengl32 = LoadLibraryA("opengl32.dll");
        ASSERT_IF(opengl32) {
            LOAD(opengl32, wglCreateContext);
            LOAD(opengl32, wglMakeCurrent);
            LOAD(opengl32, glBegin);
            LOAD(opengl32, glLoadMatrixf);
            LOAD(opengl32, glViewport);
            LOAD(opengl32, glBindTexture);
            LOAD(opengl32, glTexImage2D);
            LOAD(opengl32, glTexParameteri);
            LOAD(opengl32, glTexEnvi);
            LOAD(opengl32, glEnable);
            LOAD(opengl32, glClearColor);
            LOAD(opengl32, glClear);
            LOAD(opengl32, glMatrixMode);
            LOAD(opengl32, glLoadIdentity);
            LOAD(opengl32, glColor4f);
            LOAD(opengl32, glTexCoord2f);
            LOAD(opengl32, glEnd);
            LOAD(opengl32, glGenTextures);
            LOAD(opengl32, glVertex2f);
        }
    }
#endif

    ASSERT(r.success);
    return(r);
}

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    int res = 0xFF;

    // TODO: Think about these sizes more. Because this app is meant to run in the background it should be as resource-light as possible.
    U64 permanent_size = GIGABYTES(4);
    U64 temp_size = GIGABYTES(4);
    U64 internal_temp_size = MEGABYTES(128);
    U64 bitmap_size = MAX_SCREEN_BITMAP_SIZE + 1;
    U64 renderer_size = MEGABYTES(128);
    U64 malloc_nofree_size = MEGABYTES(128);
    U32 font_size = sizeof(Image_Letter) * 256 + 1;
    U32 titles_size = MEGABYTES(1);
    U64 total_size = get_memory_base_size() + permanent_size + temp_size + internal_temp_size + bitmap_size +
                     renderer_size + malloc_nofree_size + font_size + titles_size;

    Void *all_memory = VirtualAlloc(0, total_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if(all_memory) {
        U64 group_inputs[] = { permanent_size, temp_size, internal_temp_size, bitmap_size,
                               renderer_size, malloc_nofree_size, font_size, titles_size
                             };
        ASSERT(SGLG_ENUM_COUNT(Memory_Index) == ARRAY_COUNT(group_inputs));
        Memory memory = create_memory_base(all_memory, group_inputs, ARRAY_COUNT(group_inputs));

        Bool successfully_parsed_command_line = false;

        // Get the command line arguments.
        Char *cmdline = GetCommandLineA();
        Int args_len = string_length(cmdline);

        // Count number of arguments.
        Int original_cnt = 1;
        Bool in_quotes = false;
        for(U64 i = 0; (i < args_len); ++i) {
            if(cmdline[i] == '"') {
                in_quotes = !in_quotes;
            } else if(cmdline[i] == ' ') {
                if(!in_quotes) {
                    ++original_cnt;
                }
            }
        }

        // Create copy of args.
        Char *arg_cpy = (Char *)memory_push(&memory, Memory_Index_permanent, args_len + 1);
        if(arg_cpy) {
            string_copy(arg_cpy, cmdline);

            for(Int i = 0; (i < args_len); ++i) {
                if(arg_cpy[i] == '"') {
                    in_quotes = !in_quotes;
                } else if(arg_cpy[i] == ' ') {
                    if(!in_quotes) {
                        arg_cpy[i] = 0;
                    }
                }
            }

            // Setup pointers.
            in_quotes = false;
            U64 mem_size = original_cnt * 2;
            Int argc = 1;
            Char **argv = (Char **)memory_push(&memory, Memory_Index_permanent, (sizeof(Char *) * mem_size));
            ASSERT_IF(argv) {
                Char **cur = argv;
                *cur++ = arg_cpy;
                for(Int i = 0; (i < args_len); ++i) {
                    if(!arg_cpy[i]) {
                        Char *str = arg_cpy + i + 1;
                        if(!string_contains(str, '*')) {
                            *cur = str;
                            ++cur;
                            ++argc;
                        } else {
                            WIN32_FIND_DATA find_data = {};
                            HANDLE fhandle = FindFirstFile(str, &find_data);

                            if(fhandle != INVALID_HANDLE_VALUE) {
                                do {
                                    ASSERT(argc + 1 < mem_size);

                                    *cur = find_data.cFileName;
                                    ++cur;
                                    ++argc;
                                } while(FindNextFile(fhandle, &find_data));
                            }
                        }
                    }
                }

                successfully_parsed_command_line = true;
                res = 0; // 0 is success
            }
        }

        // _Real_ entry point for program...
        if(successfully_parsed_command_line) {
            Char _path[1024] = {}; // TODO: MAX_PATH?
            GetModuleFileNameA(0, _path, ARRAY_COUNT(_path));
            String path = create_string(_path);
            Find_Index_Result fir = find_index(path, '\\', true);
            ASSERT(fir.success);

            Int last_slash = fir.idx + 1;

            // TODO: Instead of assuming we're running from the data directory and going relative from there could I find the path
            // to the current EXE and load the DLLs from there?

            Char src_dll_path[1024] = {};
            Char tmp_dll_path[1024] = {};

            string_copy(src_dll_path, _path);
            string_copy(&src_dll_path[last_slash], "screenshotter.dll");
            string_copy(tmp_dll_path, _path);
            string_copy(&tmp_dll_path[last_slash], "screenshotter_temp.dll");
            Win32_Loaded_Code loaded_code = win32_load_code(src_dll_path, tmp_dll_path);

            Win32_System_Callbacks sys_cb = load_system_callbacks();
            global_sys_cb = &sys_cb;

            API api = {};
            Settings settings = {};

            SYSTEM_INFO info;
            GetSystemInfo(&info);

            // Initial sizes
            settings.thread_count = info.dwNumberOfProcessors;
            settings.window_width = 1920 / 2;
            settings.window_width = 1080 / 2;

            loaded_code.init_platform_settings(&settings);
            api.screen_bitmap.memory = memory_push(&memory, Memory_Index_bitmap, MAX_SCREEN_BITMAP_SIZE);
            ASSERT(api.screen_bitmap.memory);
            if(api.screen_bitmap.memory) {
                global_api = &api;

                LARGE_INTEGER perf_cnt_freq_res;
                QueryPerformanceFrequency(&perf_cnt_freq_res);
                U64 perf_cnt_freq = perf_cnt_freq_res.QuadPart;

                WNDCLASS wnd_class = {};
                wnd_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
                wnd_class.hInstance = hInstance;
                wnd_class.lpszClassName = TEXT("Screenshotter Window Class");
                wnd_class.lpfnWndProc = win32_window_proc;

                // TODO: Is this part correct?
                Int frame_rate = 60; // TODO: Make configurable.
                Int game_update_hz = frame_rate;
                F32 target_seconds_per_frame = 1.0f / (F32)game_update_hz;
                F32 target_ms_per_frame = 16.66f; //(1.0f / (F32)frame_rate) * 1000.0f;

                // Make the frame rate more granular.
                {
                    HMODULE winmmdll = LoadLibraryA("winmm.dll");
                    ASSERT_IF(winmmdll) {
                        typedef MMRESULT timeBeginPeriod_t(UINT uPeriod);
                        timeBeginPeriod_t *winm_timeBeginPeriod = (timeBeginPeriod_t *)GetProcAddress(winmmdll, "timeBeginPeriod");
                        ASSERT_IF(winm_timeBeginPeriod) {
                            winm_timeBeginPeriod(1);
                        }

                        FreeLibrary(winmmdll);
                    }

                }

                if(sys_cb.RegisterClassA(&wnd_class)) {
                    Char *window_title = "Screenshotter";
                    HWND wnd = sys_cb.CreateWindowExA(0, wnd_class.lpszClassName, window_title,
                                                      WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT,
                                                      settings.window_width, settings.window_height, 0, 0, hInstance, 0);

#if USE_OPENGL_WINDOW
                    win32_init_opengl(wnd, &sys_cb);
#endif

                    win32_get_window_dimension(wnd, &api.window_width, &api.window_height, &sys_cb);

                    if((wnd) && (wnd != INVALID_HANDLE_VALUE)) {
                        LARGE_INTEGER last_counter = win32_get_wall_clock();
                        LARGE_INTEGER flip_wall_clock = win32_get_wall_clock();

                        float ms_per_frame = 16.6666f;

                        Win32_API win32_api = {};
                        win32_api.queue.entry_count = 2048;
                        win32_api.queue.entries = (Win32_Work_Queue_Entry *)memory_push(&memory, Memory_Index_permanent,
                                                                                        sizeof(Win32_Work_Queue_Entry) * win32_api.queue.entry_count);
                        ASSERT(win32_api.queue.entries);
                        if(settings.dll_data_struct_size) {
                            api.dll_data = memory_push(&memory, Memory_Index_permanent, settings.dll_data_struct_size);
                            ASSERT(api.dll_data); // TODO: Error handling.
                        }
                        api.platform_specific = (Void *)&win32_api;

                        api.max_work_queue_count = win32_api.queue.entry_count;
                        api.init = true;
                        api.screen_image_size_change = true;
                        api.running = true;
                        api.memory = &memory;

                        api.cb.read_file = win32_read_file;
                        api.cb.write_file = win32_write_file;
                        api.cb.locked_add = win32_locked_add;

                        api.cb.add_work_queue_entry = win32_add_work_queue_entry;
                        api.cb.complete_all_work = win32_complete_all_work;

                        api.cb.browse_for_directory = win32_browse_for_directory;

                        api.randomish_seed = win32_get_wall_clock().QuadPart;
                        //api.randomish_seed = xorshift64(&api.randomish_seed); // TODO: Copy over xorshift64

                        // TODO: Load config from settings on disk.
                        Config config = {};
                        api.config = &config;

                        config.include_title_bar = true;
                        config.target_output_directory = "C:\\tmp"; // TODO: Hardcoded
                        // TODO: Create directory here if it doesn't already exist?
                        config.amount_to_sleep = 1000;

                        // TODO: Read core_count from settings. Maybe pass in actual core_count to settings but let
                        //       DLL overwrite it.
                        for(Int i = 0; (i < settings.thread_count - 1); ++i) {
                            HANDLE h = CreateThread(0, 0, win32_thread_proc, &win32_api.queue, 0, 0);
                            ASSERT(h && h != INVALID_HANDLE_VALUE);
                            if(h && h != INVALID_HANDLE_VALUE) {
                                CloseHandle(h);
                            }
                        }

                        sys_cb.EnumWindows(enum_windows_proc, (LPARAM)&api); // TODO: Pass sys_cb and API in here

                        U64 iteration_count = 0;
                        U64 iteration_count_reset = 0;
                        F32 seconds_elapsed_for_last_frame = 0;
                        while(api.running) {
                            // TODO: Do rendering in separate thread and only have main thread process window messages? Maybe a good option
                            //       to have, but for Screenshotter we want the app to be as light as possible. So main
                            //       thread + 'screenshotting' threading should be all that's used.

                            // Unload the screenshotter DLL then reload it in.
                            FILETIME new_write_time = win32_get_last_write_time(src_dll_path);
                            if(CompareFileTime(&new_write_time, &loaded_code.dll_last_write_time) != 0) {
                                if(loaded_code.dll) {
                                    FreeLibrary(loaded_code.dll);

                                    loaded_code.dll = 0;
                                    loaded_code.handle_input_and_render = 0;
                                    loaded_code.init_platform_settings = 0;
                                }

                                loaded_code = win32_load_code(src_dll_path, tmp_dll_path);
                            }


                            for(Int i = 0; (i < ARRAY_COUNT(api.key)); ++i) {
                                api.previous_key[i] = api.key[i];
                            }

                            // Process pending messages
                            {
                                MSG msg;
                                while(sys_cb.PeekMessageA(&msg, wnd, 0, 0, PM_REMOVE)) {
                                    switch(msg.message) {
                                        case WM_QUIT: case WM_CLOSE: { api.running = false; } break; // TODO: Does this have to be here and inside the windowproc?

                                        case WM_KEYDOWN: { api.key[win32_key_to_our_key(msg.wParam)] = 1.0f; } break;
                                        case WM_KEYUP:   { api.key[win32_key_to_our_key(msg.wParam)] = 0.0f; } break;

                                        case WM_LBUTTONDOWN: { api.key[key_mouse_left]   = 1.0f; } break;
                                        case WM_MBUTTONDOWN: { api.key[key_mouse_middle] = 1.0f; } break;
                                        case WM_RBUTTONDOWN: { api.key[key_mouse_right]  = 1.0f; } break;

                                        case WM_LBUTTONUP: { api.key[key_mouse_left]   = 0.0f; } break;
                                        case WM_MBUTTONUP: { api.key[key_mouse_middle] = 0.0f; } break;
                                        case WM_RBUTTONUP: { api.key[key_mouse_right]  = 0.0f; } break;

                                        default: {
                                            sys_cb.TranslateMessage(&msg);
                                            sys_cb.DispatchMessageA(&msg);
                                        } break;
                                    }
                                }
                            }

                            // TODO: Zero-ing this memory to re-read it means we actually have to do more work to:
                            //         1. Regenerate the text in the renderer
                            //         2. Make sure we're not reading zero'd memory in win32_find_window_from_class_name.
                            //       Commenting out until I've fixed this bug.
                            /*Memory_Group *window_title_group = get_memory_group(api.memory, Memory_Index_window_titles);
                            zero(window_title_group->base, window_title_group->used);
                            window_title_group->used = 0;
                            api.window_count = 0;

                            EnumWindows(enum_windows_proc, (LPARAM)&api);*/

                            // Actual rendering
                            {
                                // Get mouse position
                                {
                                    POINT pt;
                                    sys_cb.GetCursorPos(&pt);
                                    sys_cb.ScreenToClient(wnd, &pt);

                                    api.previous_mouse_pos_x = api.mouse_pos_x;
                                    api.previous_mouse_pos_y = api.mouse_pos_y;

                                    F32 pos_x = (F32)pt.x / (F32)api.window_width;
                                    F32 pos_y = (F32)pt.y / (F32)api.window_height;

                                    // Only store this if we're inside the window
                                    if((pos_x >= 0 && pos_x <= 1) && (pos_y >= 0 && pos_y <= 1)) {
                                        api.mouse_pos_x = clamp01(pos_x);
                                        api.mouse_pos_y = clamp01(pos_y);
                                    }
                                }

                                RECT cr;
                                sys_cb.GetClientRect(wnd, &cr);

                                api.window_width = cr.right - cr.left;
                                api.window_height = cr.bottom - cr.top;

                                loaded_code.handle_input_and_render(&api);

                                if(!api.init) { api.screen_image_size_change = false; }
                                api.init = false;

                                HDC dc = sys_cb.GetDC(wnd);

                                win32_update_window(&memory, dc, &cr, api.screen_bitmap.memory, &global_bmp_info,
                                                    api.screen_bitmap.width, api.screen_bitmap.height);

#if SHOW_FPS
                                {
                                    Char buf[1024] = {};
                                    Int bytes_written = stbsp_snprintf(buf, ARRAY_COUNT(buf), "%s - %f",
                                                                       window_title, seconds_elapsed_for_last_frame);
                                    ASSERT(bytes_written < ARRAY_COUNT(buf));
                                    Bool success = sys_cb.SetWindowTextA(wnd, buf);
                                    ASSERT(success);
                                }
#endif

                                sys_cb.ReleaseDC(wnd, dc);
                            }

                            // Screenshotting
                            {
                                if(config.new_target_output_directory.len > 0) {
                                    String new_dir = win32_create_root_directory(&memory, config.new_target_output_directory);
                                    ASSERT_IF(new_dir.len > 0) {
                                        config.target_output_directory = config.new_target_output_directory;
                                        config.target_output_directory_full = new_dir;
                                        config.new_target_output_directory = "";
                                    }
                                }

                                ++iteration_count_reset;
                                if(iteration_count_reset == 60) {
                                    run_screenshotting(&api, &memory, &config, &sys_cb, config.target_output_directory_full, iteration_count);
                                    ++iteration_count;
                                    iteration_count_reset = 0;
                                }
                            }

                            // TODO: If the windows isn't in focus have an option to go to sleep here until it is in focus.

                            // Frame rate stuff.
                            {
                                F32 seconds_elapsed_for_frame = win32_get_seconds_elapsed(last_counter,
                                                                                          win32_get_wall_clock(),
                                                                                          perf_cnt_freq);
                                if(seconds_elapsed_for_frame < target_seconds_per_frame) {
                                    DWORD sleepms = (DWORD)(1000.0f * (target_seconds_per_frame - seconds_elapsed_for_frame));
                                    if(sleepms > 0) {
                                        Sleep(sleepms);
                                    }

                                    F32 test_seconds_elapsed_for_frame = win32_get_seconds_elapsed(last_counter,
                                                                                                   win32_get_wall_clock(),
                                                                                                   perf_cnt_freq);
                                    if(test_seconds_elapsed_for_frame < target_seconds_per_frame) {
                                        // TODO: Missed sleep
                                    }

                                    while(seconds_elapsed_for_frame < target_seconds_per_frame) {
                                        seconds_elapsed_for_frame = win32_get_seconds_elapsed(last_counter,
                                                                                              win32_get_wall_clock(),
                                                                                              perf_cnt_freq);
                                    }
                                } else {
                                    // TODO: Missed Frame Rate!
                                }

                                LARGE_INTEGER end_counter = win32_get_wall_clock();
                                ms_per_frame = 1000.0f * win32_get_seconds_elapsed(last_counter, end_counter, perf_cnt_freq);
                                last_counter = end_counter;

                                flip_wall_clock = win32_get_wall_clock();
                                seconds_elapsed_for_last_frame = seconds_elapsed_for_frame;
                            }

                        }
                    }
                }
            }
        }

        //VirtualFree(all_memory, 0, MEM_RELEASE); // Disabled for performance
    }

    return(res);
}

// TODO: Putting methods in extern "C" ruins mirror. Mirror forward declares them without the extern "C" so the linkage is different.
extern "C" {int _fltused = 0; }
void __stdcall
WinMainCRTStartup(Void) {
    int Result = WinMain(GetModuleHandle(0), 0, 0, 0);
    ExitProcess(Result);
}

#include "platform_win32_generated.cpp"
