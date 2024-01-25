#pragma once
#include "framework.h"
#include "Resource.h"
#define MAX_LOADSTRING 100

class CWndBase
{
private:
	CWinApp* m_winApp;
protected:


public:
	HWND m_hWnd = NULL;

	CWndBase(VOID);
	CWndBase(CWinApp* app);

	virtual ~CWndBase(VOID);

	BOOL InitInstace(int cmdShow);

	ATOM RegisterMainClass();

	LONG_PTR GetWindowLong(int index);

	LONG_PTR SetWindowLong(int index, LONG_PTR dwNewLong);

};
