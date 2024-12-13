#include <Windows.h>

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t* CLASS_NAME = L"Main Class Window";

    WNDCLASS SoftwareMainClass = { 0 };
    SoftwareMainClass.lpszClassName = CLASS_NAME;
    SoftwareMainClass.lpfnWndProc = MainWindowProc;
    SoftwareMainClass.hInstance = hInstance;
    SoftwareMainClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    SoftwareMainClass.style = CS_VREDRAW | CS_HREDRAW;
    SoftwareMainClass.hCursor = LoadCursor(NULL, IDC_HAND);
    
    

    RegisterClass(&SoftwareMainClass);

    HWND hwndMain = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Owerlapped Window",
        WS_OVERLAPPEDWINDOW,
        0, 0, 1000, 800,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwndMain == NULL)
    {
        return 0;
    }

    ShowWindow(hwndMain, nCmdShow);

    MSG SoftwerMainMessage = { 0 };
    while (GetMessage(&SoftwerMainMessage, NULL, NULL, NULL))
    {
        TranslateMessage(&SoftwerMainMessage);
        DispatchMessage(&SoftwerMainMessage);
    }
    return 0;
};

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CLOSE: {
        DestroyWindow(hwnd);
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    case WM_PAINT: {
        RECT window;
        GetWindowRect(hwnd, &window);
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint(hwnd, &ps); // Получение контекста устройства

        // Создание пера
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN oPen = (HPEN)SelectObject(hDC, hPen);
        
        
        
        MoveToEx(hDC, window.left, window.bottom/2, NULL);
        LineTo(hDC, window.right, window.bottom/2);

        MoveToEx(hDC, window.right/2, window.top, NULL);
        LineTo(hDC, window.right/2, window.bottom);

        // Восстановление старого пера и удаление созданного
        SelectObject(hDC, oPen);
        DeleteObject(hPen);

        EndPaint(hwnd, &ps); // Завершение рисования
        return 0L;
    }
    }


        return DefWindowProc(hwnd, msg, wParam, lParam);
    
}
