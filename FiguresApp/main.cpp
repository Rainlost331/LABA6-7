#include "framework.h"
#include "FiguresApp.h"

#define MAX_LOADSTRING 100
#define OBJ_FIGURE_ARRAY_SIZE 3
#define EVENT_UNIQUE_ID L"FIGURES"

struct FigureThread {
    Figure* pFigure;
    HANDLE hEvent;
};

HANDLE figures_console_event;
HANDLE figures_events[OBJ_FIGURE_ARRAY_SIZE];
FigureThread figures_thread_data[OBJ_FIGURE_ARRAY_SIZE];

int flag = 0;

Figure* pF[OBJ_FIGURE_ARRAY_SIZE];

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

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


    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FIGURESAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIGURESAPP));

    MSG msg;

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

DWORD WINAPI FiguresThreadFunction(LPVOID obj)
{
    FigureThread* pFigureData = (FigureThread*)obj;
    WaitForSingleObject(figures_console_event, INFINITE);

    while (WaitForSingleObject(figures_console_event, 0) == WAIT_OBJECT_0)
    {
        pFigureData->pFigure->draw(1);
        Sleep(20);
        pFigureData->pFigure->draw(0);
        pFigureData->pFigure->step();
    }
    SetEvent(pFigureData->hEvent);
    return 1;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_FIGURESAPP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FIGURESAPP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; 

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_CREATE:
    {
        figures_console_event = CreateEvent(
            0,
            true,
            false,
            EVENT_UNIQUE_ID
        );

        pF[0] = new Line(hWnd, 100, 5, 10, HORIZONTAL, RGB(255, 0, 255));
        pF[1] = new MyPolygon(hWnd, 50, 3, 3, HORIZONTAL, RGB(0, 255, 255), 4);
        pF[2] = new MyRavPriamougTreug(hWnd, 100, 7, 7, HORIZONTAL, RGB(255, 0, 255));

        for (int i = 0; i < OBJ_FIGURE_ARRAY_SIZE; i++)
        {
            figures_thread_data[i].pFigure = pF[i];
            figures_thread_data[i].hEvent = figures_events[i] = CreateEvent(0, false, false, 0);
            CreateThread(0, 0, FiguresThreadFunction, &figures_thread_data[i], 0, 0);
        }
    }
    break;
    case WM_COMMAND:
    {
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            flag = 0;
            WaitForMultipleObjects(OBJ_FIGURE_ARRAY_SIZE, figures_events, TRUE, INFINITE);
            for (int i = 0; i < OBJ_FIGURE_ARRAY_SIZE; i++)
            {
                delete pF[i];
                CloseHandle(figures_events[i]);
            }
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    }
    break;
    case WM_DESTROY:
        flag = 0;
        WaitForMultipleObjects(OBJ_FIGURE_ARRAY_SIZE, figures_events, TRUE, INFINITE);
        for (int i = 0; i < OBJ_FIGURE_ARRAY_SIZE; i++)
        {
            delete pF[i];
            CloseHandle(figures_events[i]);
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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