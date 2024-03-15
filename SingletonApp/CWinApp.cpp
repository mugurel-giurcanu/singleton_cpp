#include "framework.h"
#include "CWinApp.h" 


CWinApp::CWinApp(VOID) : m_hInst(NULL),
m_hMenu(NULL), m_hIcon(NULL), m_hIconSmall(NULL), m_hCursor(NULL), m_hbrBackground(NULL),
m_szTitle(), m_szMenuName(), m_szWindowClass()
{

}

CWinApp::CWinApp(HINSTANCE hInst) : m_hInst(hInst),
m_hMenu(NULL), m_hIcon(NULL), m_hIconSmall(NULL), m_hCursor(NULL), m_hbrBackground(NULL),
m_szTitle(), m_szMenuName(), m_szWindowClass()
{
}

bool CWinApp::InitApp()
{
    m_hEvent = ::CreateMutex(NULL, FALSE, TEXT("Global\\SingletonApp"));

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ::MessageBox(NULL, _T("Ole!!"), _T("SingleTon"), MB_OK);
        // show the 
        return false;
    }

    // resourse loading 
    ::LoadString(m_hInst, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
    ::LoadString(m_hInst, IDC_SINGLETONAPP, m_szWindowClass, MAX_LOADSTRING);
    ::LoadString(m_hInst, IDC_SINGLETONAPP, m_szMenuName, MAX_LOADSTRING);

    m_hIcon = ::LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_SINGLETONAPP));
    m_hIconSmall = ::LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_SMALL));
    m_hCursor = ::LoadCursor(m_hInst, IDC_ARROW);
    m_hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    m_hMenu = ::LoadMenu(m_hInst, MAKEINTRESOURCE(IDC_SINGLETONAPP));

    return true;
}


void CWinApp::InitWindowClass(_In_ WNDCLASSEXW* lpWndClass)
{
    lpWndClass->hInstance = m_hInst;
    lpWndClass->hIcon = m_hIcon;
    lpWndClass->hCursor = m_hCursor;
    lpWndClass->hbrBackground = m_hbrBackground;
    lpWndClass->lpszMenuName = MAKEINTRESOURCE(IDC_SINGLETONAPP);
    lpWndClass->lpszClassName = m_szWindowClass;
    lpWndClass->hIconSm = m_hIconSmall;
}

HWND CWinApp::CreateMainWindow(DWORD dwExStyle, DWORD dwStyle, int x, int y, int nWidth, int nHeight, LPVOID lpParam)
{
    return ::CreateWindowEx(dwExStyle, m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, lpParam);

}

MSG CWinApp::ProcessMessages()
{
    HACCEL hAccelTable = LoadAccelerators(m_hInst, MAKEINTRESOURCE(IDC_SINGLETONAPP));

    // Main message loop:
    while (::GetMessage(&m_msg, nullptr, 0, 0))
    {
        if (!::TranslateAccelerator(m_msg.hwnd, hAccelTable, &m_msg))
        {
            ::TranslateMessage(&m_msg);
            ::DispatchMessage(&m_msg);
        }
    }

    CloseHandle(m_hEvent);
    return m_msg;
}
