
struct Win32_Work_Queue_Entry {
    Void (*cb)(Void *data);
    Void *data;
};

struct Win32_Work_Queue {
    U32 volatile completion_goal;
    U32 volatile completion_count;

    U32 volatile next_entry_to_write;
    U32 volatile next_entry_to_read;

    HANDLE semaphore;

    Win32_Work_Queue_Entry *entries;
    Int entry_count;
};

typedef Void Handle_Input_And_Render(API *);
typedef Void Init_Platform_Settings(Settings *settings);
struct Win32_Loaded_Code {
    Bool success;

    HMODULE dll;
    FILETIME dll_last_write_time;
    Handle_Input_And_Render *handle_input_and_render;
    Init_Platform_Settings *init_platform_settings;
};

struct Win32_Debug_Window {
    Bool success;
    HWND hwnd;

    Int width, height;

    BITMAPINFO bitmap_info;
    Void *bitmap_memory;
    Int bitmap_width;
    Int bitmap_height;
    Int image_size_change;
    Bool image_size_changed;
};

struct Win32_API {
    Win32_Work_Queue queue;
};

#define ADD(name) name##_t *name;

// User32
typedef BOOL TranslateMessage_t(const MSG *lpMsg);
typedef LRESULT DispatchMessageA_t(const MSG *lpMsg);
typedef BOOL PeekMessageA_t(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg);
typedef LRESULT SendMessageA_t(HWND   hWnd, UINT   Msg, WPARAM wParam, LPARAM lParam);
typedef LRESULT DefWindowProcA_t(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
typedef ATOM RegisterClassA_t(const WNDCLASSA *lpWndClass);
typedef HWND CreateWindowExA_t(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight,
                               HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam );
typedef BOOL PrintWindow_t(HWND hwnd, HDC  hdcBlt, UINT nFlags);
typedef BOOL IsWindowVisible_t(HWND hWnd);
typedef HDC GetDC_t(HWND hWnd);
typedef int ReleaseDC_t(HWND hWnd, HDC  hDC);
typedef BOOL SetWindowTextA_t(HWND   hWnd, LPCSTR lpString );
typedef int GetWindowTextA_t(HWND  hWnd, LPSTR lpString, int   nMaxCount);
typedef BOOL GetClientRect_t(HWND   hWnd, LPRECT lpRect);
typedef BOOL GetCursorPos_t(LPPOINT lpPoint);
typedef BOOL ScreenToClient_t(HWND hWnd, LPPOINT lpPoint);
typedef HWND FindWindowExA_t(HWND   hWndParent, HWND   hWndChildAfter, LPCSTR lpszClass, LPCSTR lpszWindow);
typedef BOOL EnumWindows_t(WNDENUMPROC lpEnumFunc, LPARAM lParam );
typedef BOOL EnumDesktopWindows_t(HDESK hDesktop, WNDENUMPROC lpfn, LPARAM lParam );
typedef int GetClassNameA_t(HWND  hWnd, LPSTR lpClassName, int   nMaxCount );

// GDI32
typedef HBITMAP CreateCompatibleBitmap_t(HDC hdc, int cx, int cy );
typedef HDC CreateCompatibleDC_t(HDC hdc);
typedef int GetDIBits_t(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage );
typedef HGDIOBJ SelectObject_t(HDC hdc, HGDIOBJ h);
typedef int StretchDIBits_t(HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, int SrcHeight,
                            const VOID *lpBits, const BITMAPINFO *lpbmi, UINT iUsage, DWORD rop );
typedef int ChoosePixelFormat_t(HDC hdc, const PIXELFORMATDESCRIPTOR *ppfd);
typedef int DescribePixelFormat_t(HDC hdc, int iPixelFormat, UINT nBytes, LPPIXELFORMATDESCRIPTOR ppfd);
typedef BOOL SetPixelFormat_t(HDC hdc, int format, const PIXELFORMATDESCRIPTOR *ppfd);
typedef BOOL SwapBuffers_t(HDC unnamedParam1);

// Shell32
typedef HRESULT SHGetMalloc_t(IMalloc **ppMalloc);
typedef BOOL SHGetPathFromIDListA_t(PCIDLIST_ABSOLUTE pidl, LPSTR pszPath);
typedef PIDLIST_ABSOLUTE SHBrowseForFolderA_t(LPBROWSEINFOA lpbi);

// OpenGL
typedef HGLRC wglCreateContext_t(HDC unnamedParam1);
typedef BOOL wglMakeCurrent_t(HDC , HGLRC);
typedef void WINAPI glBegin_t(GLenum mode);
typedef void WINAPI glLoadMatrixf_t(const GLfloat *m);
typedef void WINAPI glViewport_t(GLint x, GLint y, GLsizei width, GLsizei height );
typedef void WINAPI glBindTexture_t(GLenum target, GLuint texture);
typedef void WINAPI glTexImage2D_t(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border,
                                   GLint format, GLenum type, const GLvoid *pixels );
typedef void WINAPI glTexParameteri_t(GLenum target, GLenum pname, GLint param);
typedef void WINAPI glTexEnvi_t(GLenum target, GLenum pname, GLint  param);
typedef void WINAPI glEnable_t(GLenum cap);
typedef void WINAPI glClearColor_t(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void WINAPI glClear_t(GLbitfield mask);
typedef void WINAPI glMatrixMode_t(GLenum mode);
typedef void WINAPI glLoadIdentity_t(void);
typedef void WINAPI glColor4f_t(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void WINAPI glTexCoord2f_t(GLfloat s, GLfloat t);
typedef void WINAPI glEnd_t(void);
typedef void WINAPI glGenTextures_t(GLsizei n, GLuint *textures);
typedef void WINAPI glVertex2f_t(GLfloat x, GLfloat y);

struct Win32_System_Callbacks {
    Bool success;

    // User32
    ADD(TranslateMessage);
    ADD(DispatchMessageA);
    ADD(PeekMessageA);
    ADD(SendMessageA);
    ADD(DefWindowProcA);
    ADD(RegisterClassA);
    ADD(CreateWindowExA);
    ADD(PrintWindow);
    ADD(IsWindowVisible);
    ADD(GetDC);
    ADD(ReleaseDC);
    ADD(SetWindowTextA);
    ADD(GetWindowTextA);
    ADD(GetClientRect);
    ADD(GetCursorPos);
    ADD(ScreenToClient);
    ADD(FindWindowExA);
    ADD(EnumWindows);
    ADD(EnumDesktopWindows);
    ADD(GetClassNameA);

    // GDI32
    ADD(CreateCompatibleBitmap);
    ADD(CreateCompatibleDC);
    ADD(GetDIBits);
    ADD(SelectObject);
    ADD(StretchDIBits);
    ADD(ChoosePixelFormat);
    ADD(DescribePixelFormat);
    ADD(SetPixelFormat);
    ADD(SwapBuffers);

    // Shell32
    ADD(SHGetMalloc);
    ADD(SHGetPathFromIDListA);
    ADD(SHBrowseForFolderA);

    // OpenGL
    ADD(wglCreateContext);
    ADD(wglMakeCurrent);
    ADD(glBegin);
    ADD(glLoadMatrixf);
    ADD(glViewport);
    ADD(glBindTexture);
    ADD(glTexImage2D);
    ADD(glTexParameteri);
    ADD(glTexEnvi);
    ADD(glEnable);
    ADD(glClearColor);
    ADD(glClear);
    ADD(glMatrixMode);
    ADD(glLoadIdentity);
    ADD(glColor4f);
    ADD(glTexCoord2f);
    ADD(glEnd);
    ADD(glGenTextures);
    ADD(glVertex2f);
};
