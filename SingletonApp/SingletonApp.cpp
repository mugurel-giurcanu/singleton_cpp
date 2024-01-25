// SingletonApp.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SingletonApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    CWinApp winApp(hInstance);

    if (!winApp.InitApp())
    {
        return -1;
    }

    CWndBase wnd(&winApp);
    wnd.RegisterMainClass();
    wnd.InitInstace(nCmdShow);

    MSG msg;

    msg = winApp.ProcessMessages();

    return (int)msg.wParam;
}
