#include <windows.h>
#include <stdlib.h>

const char g_szClassName[] = "myWindowClass";

HWND hName, hPoints, hOut;

HFONT g_hfFont = NULL;
COLORREF g_rgbText = RGB(0, 0, 0);
COLORREF g_rgbBackground = RGB(255, 255, 255);

void DrawClientSize(HDC hdc, RECT* prc, HFONT hf)
{
	char szSize[100];
	char szTitle[] = "This text will be fixed in this position.";
    HFONT hfOld = (HFONT)SelectObject(hdc, hf);

    SetBkColor(hdc, g_rgbBackground);
	SetTextColor(hdc, g_rgbText);

	DrawText(hdc, szTitle, -1, prc, DT_WORDBREAK);

	wsprintf(szSize, "This text will be in window's center.", prc->left, prc->top, prc->right, prc->bottom);

	DrawText(hdc, szSize, -1, prc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    SelectObject(hdc, hfOld);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            CreateWindow(
                         TEXT("BUTTON"),
                         TEXT("Quit"),
                         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_FLAT,
                         50,
                         50,
                         100,
                         40,
                         hwnd,
                         (HMENU) 1,
                         (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                         NULL);

            CreateWindow(
                         TEXT("BUTTON"),
                         TEXT("Go"),
                         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_RIGHT,
                         170,
                         50,
                         100,
                         40,
                         hwnd,
                         (HMENU) 2,
                         (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                         NULL);

            CreateWindow(
                         TEXT("BUTTON"),
                         TEXT("Style of the text"),
                         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_LEFT,
                         390,
                         50,
                         120,
                         60,
                         hwnd,
                         (HMENU) 3,
                         (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                         NULL
                         );

            CreateWindow(
                         TEXT("BUTTON"),
                         TEXT("Background"),
                         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         510,
                         50,
                         120,
                         60,
                         hwnd,
                         (HMENU) 4,
                         (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                         NULL
                         );

            hPoints = CreateWindow(
                         TEXT("Edit"),
                         TEXT("Points"),
                         WS_VISIBLE | WS_CHILD | WS_BORDER,
                         100,
                         230,
                         100,
                         30,
                         hwnd,
                         NULL,
                         NULL,
                         NULL
                         );

            hName = CreateWindow(
                         TEXT("Edit"),
                         TEXT("Name"),
                         WS_VISIBLE | WS_CHILD | WS_BORDER,
                         100,
                         170,
                         100,
                         30,
                         hwnd,
                         NULL,
                         NULL,
                         NULL
                         );

            hOut = CreateWindow(
                         TEXT("Edit"),
                         TEXT(""),
                         WS_VISIBLE | WS_CHILD | WS_BORDER,
                         420,
                         170,
                         200,
                         100,
                         hwnd,
                         NULL,
                         NULL,
                         NULL
                         );

            CreateWindow(
                         TEXT("Button"),
                         TEXT("Generate"),
                         WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         220,
                         200,
                         100,
                         40,
                         hwnd,
                         (HMENU) 5,
                         (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                         NULL
                         );

            break;
        }

        case WM_COMMAND:
        {
            if(LOWORD(wParam) == 1)
            {
                int msgboxID = MessageBox(NULL, "Are you sure about this?", "Quit the window", MB_ICONASTERISK | MB_OKCANCEL);
                switch(msgboxID)
                {
                    case IDOK:
                        MessageBox(NULL, "It is too obviously. Try another option!", "Quit the window", MB_ICONEXCLAMATION | MB_OK);
                        break;

                    case IDCANCEL:
                        PostQuitMessage(0);
                        break;

                }
            }

            if(LOWORD(wParam) == 2)
            {
                MessageBox(NULL, "Are you good bro?", "Error", MB_ICONEXCLAMATION | MB_OK);
            }

            if(LOWORD(wParam) == 3)
            {
                g_hfFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
                g_rgbText = RGB(255, 0, 0);
                g_rgbBackground = RGB(0, 255, 0);

                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }

            if(LOWORD(wParam) == 4)
            {
                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, COLOR_HIGHLIGHT + 1);

                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }

            if(LOWORD(wParam) == 5)
            {
                char name[15], points[10], out[50];

                GetWindowText(hName, name, 30);
                GetWindowText(hPoints, points, 10);

                strcpy(out, name);
                strcat(out, " got ");
                strcat(out, points);
                strcat(out, " points.");

                SetWindowText(hOut, out);
            }

            break;
        }

        case WM_KEYUP:
        {
            switch(wParam)
            {
                case VK_ESCAPE:
                {
                    MoveWindow(hwnd, 100, 100, 960, 720, TRUE);
                    break;
                }
                break;
            }
            break;
        }

        case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO pMMInfo;
            pMMInfo = (LPMINMAXINFO)lParam;

            RECT rct;

            rct.left = 0;
            rct.top = 0;
            rct.right = 700;
            rct.bottom = 300;

            AdjustWindowRectEx(&rct, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

            POINT minSize;
            minSize.x = rct.right - rct.left;
            minSize.y = rct.bottom - rct.top;

            pMMInfo->ptMinTrackSize = minSize;

            break;
        }

        case WM_CLOSE:
            MessageBox(NULL, "Is too early!", "Error", MB_ICONEXCLAMATION | MB_OK);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_PAINT:
        {
            RECT rcClient;
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rcClient);

			DrawClientSize(hdc, &rcClient, g_hfFont);

			EndPaint(hwnd, &ps);

        }


        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
                          WS_EX_CLIENTEDGE,
                          g_szClassName,
                          "My First Window",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          320,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
