#include "framework.h"
#include "CWndBase.h"

LRESULT CALLBACK WndProcBase(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    CWndBase* wnd = (CWndBase*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch (message)
    {
        case WM_NCCREATE:
        {
            LPCREATESTRUCT lpCreate = (LPCREATESTRUCT)lParam;
            wnd = (CWndBase*)(lpCreate->lpCreateParams);
            wnd->SetWindowLongW(GWLP_USERDATA, (LONG_PTR)wnd);
            return ::DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
        case WM_CREATE:
        {
            if (wnd == nullptr)
            {
                wnd = (CWndBase*)(lParam);
                wnd->SetWindowLongW(GWLP_USERDATA, (LONG_PTR)wnd);
            }
            return ::DefWindowProc(hWnd, message, wParam, lParam);
        }
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_EXIT:
                ::DestroyWindow(hWnd);
                break;
            default:
                return ::DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            break;
        default:
            return ::DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

CWndBase::CWndBase(VOID) : m_hWnd(NULL), m_winApp(NULL)
{
}

CWndBase::CWndBase(CWinApp* app)
{
    m_hWnd = NULL;
    m_winApp = app;
}

CWndBase::~CWndBase(VOID)
{
}

BOOL CWndBase::InitInstace(int nCmdShow)
{
    m_hWnd = m_winApp->CreateMainWindow(0, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, (LPVOID)this);

    //m_hWnd = ::CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE, m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
    //    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, (LPVOID)this);

    if (!m_hWnd) return FALSE;

    //::SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG)this);

    ::ShowWindow(m_hWnd, nCmdShow);
    ::UpdateWindow(m_hWnd);

    return TRUE;
}

ATOM CWndBase::RegisterMainClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProcBase;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    m_winApp->InitWindowClass(&wcex);

    return ::RegisterClassEx(&wcex);
}

LONG_PTR CWndBase::GetWindowLong(int index)
{
    return ::GetWindowLongPtr(m_hWnd, index);
}

LONG_PTR CWndBase::SetWindowLong(int index, LONG_PTR dwNewLong)
{
    return ::SetWindowLongPtr(m_hWnd, index, dwNewLong);
}
