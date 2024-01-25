#pragma once
#include "framework.h"
#include "Resource.h"
#define MAX_LOADSTRING 100 

class CWinApp
{
private:
	HINSTANCE m_hInst = NULL;
	WCHAR m_szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // the main window class name
	WCHAR m_szMenuName[MAX_LOADSTRING];				  // = MAKEINTRESOURCEW(IDC_SINGLETONAPP);
	HMENU m_hMenu;
	HICON m_hIcon;
	HICON m_hIconSmall;// = ::LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_SMALL));
	HCURSOR m_hCursor;// = ::LoadCursor(m_hInst, IDC_ARROW);

	HBRUSH m_hbrBackground;// = (HBRUSH)(COLOR_WINDOW + 1);
	MSG m_msg;

	HANDLE m_hEvent;
public:
	CWinApp(VOID);
	CWinApp(HINSTANCE hInst);

	bool InitApp();
	void InitWindowClass(_In_ WNDCLASSEXW* lpWndClass);
	HWND CreateMainWindow(DWORD dwExStyle, DWORD dwStyle, int x, int y, int nWidth, int nHeight, LPVOID lpParam);
	MSG ProcessMessages();
};

