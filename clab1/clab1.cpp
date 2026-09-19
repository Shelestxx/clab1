#include "framework.h"
#include "clab1.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Глобальні змінні:
HINSTANCE hInst;                                // поточний екземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст рядка заголовка
LPCWSTR szMyClassName = L"DenysOlaruShlapakOleh"; // Ім'я класу головного вікна (ім'я студента англійською)

// Оголошення функцій, включених у цей модуль коду:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Ініціалізація глобальних рядків
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

    MyRegisterClass(hInstance);

    // Виконати ініціалізацію програми:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLAB1));

    MSG msg;

    // Основний цикл повідомлень:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//  ФУНКЦІЯ: MyRegisterClass()
//Реєструє клас вікна.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_BYTEALIGNCLIENT; // Вирівнювання клієнтської області по горизонталі
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // Тип іконки
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Тип курсору
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Колір фону вікна - БІЛИЙ
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLAB1);
    wcex.lpszClassName = szMyClassName;
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

//Зберігає маркер екземпляра і створює головне вікно
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Зберегти маркер екземпляра в глобальній змінній

    // Створення вікна зі стилем WS_OVERLAPPEDWINDOW і позицією за замовчуванням
    HWND hWnd = CreateWindowW(szMyClassName, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}
//Обробляє повідомлення в головному вікні.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Отримання системних метрик
        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);
        int scrollW = GetSystemMetrics(SM_CXHSCROLL);
        int scrollH = GetSystemMetrics(SM_CYHSCROLL);
        int frameW = GetSystemMetrics(SM_CXSIZEFRAME);
        int frameH = GetSystemMetrics(SM_CYSIZEFRAME);

        // Формування рядка для виведення
        wchar_t text[256];
        swprintf_s(text, L"Екран (ширина/висота): %d x %d точок\nСмуга прокрутки: %d x %d\nРамка вікна: %d x %d",
            screenW, screenH, scrollW, scrollH, frameW, frameH);

        RECT rect;
        GetClientRect(hWnd, &rect);

        // Виведення тексту у вікно
        DrawTextW(hdc, text, -1, &rect, DT_LEFT | DT_TOP);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обробник повідомлень для вікна "Про програму".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}