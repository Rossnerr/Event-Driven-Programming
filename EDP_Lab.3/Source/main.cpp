#include <windows.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";
HWND hDlgModeless;
UINT tool;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND hButtonDelete;
    HDC hdc;
    static POINT p[4];
    POINT Pt[4] = { {0, 100}, {200, 100}, {200, 0} };
    static int i = 0;
    static int iPrevX,iPrevY, iNextX, iNextY;
    static HBRUSH hBrush;
    static HPEN hPen;

    switch(msg)
    {
        case WM_CREATE:
            hButtonDelete = CreateWindow(TEXT("button"),
                                         TEXT("Clean"),
                                         WS_CHILD | WS_VISIBLE,
                                         330,
                                         260,
                                         50,
                                         20,
                                         hwnd,
                                         (HMENU)ID_DELETE,
                                         NULL,
                                         NULL);
        break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDM_DRAW_LINE:
                    hdc = GetDC(hwnd);
                    SelectObject(hdc, hPen);
                    SelectObject(hdc, hBrush);
                    LineTo(hdc, 250, 250);
                    ReleaseDC(hwnd, hdc);
                break;

                case IDM_DRAW_SQUARE:
                    hdc = GetDC(hwnd);
                    SelectObject(hdc, hPen);
                    SelectObject(hdc, hBrush);
                    Rectangle(hdc, 250, 250, 100, 100);
                    ReleaseDC(hwnd, hdc);
                break;

                case IDM_DRAW_ELLIPSE:
                    hdc = GetDC(hwnd);
                    SelectObject(hdc, hPen);
                    SelectObject(hdc, hBrush);
                    Ellipse(hdc, 300, 300, 100, 100);
                    ReleaseDC(hwnd, hdc);
                break;

                case IDM_DRAW_PIE:
                    hdc = GetDC(hwnd);
                    SelectObject(hdc, hPen);
                    SelectObject(hdc, hBrush);
                    Pie(hdc, 100, 100, 300, 300, 200, 100, 300, 200);
                    ReleaseDC(hwnd, hdc);
                break;

                case IDM_DRAW_BEZIER_CURVE:
                    hdc = GetDC(hwnd);
                    SelectObject(hdc, hPen);
                    SelectObject(hdc, hBrush);
                    PolyBezierTo(hdc, Pt, 3);
                    ReleaseDC(hwnd, hdc);
                break;

                case IDM_BRUSH_RED:
                    hBrush = CreateSolidBrush(RGB(255, 0, 0));
                break;

                case IDM_BRUSH_GREEN:
                    hBrush = CreateSolidBrush(RGB(0, 255, 0));
                break;

                case IDM_BRUSH_BLUE:
                    hBrush = CreateSolidBrush(RGB(0, 0, 255));
                break;

                case IDM_BRUSH_DEFAULT:
                    hBrush = CreateSolidBrush(RGB(255, 255, 255));
                break;

                case IDM_THIN_PEN_RED:
                    hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
                break;

                case IDM_THIN_PEN_GREEN:
                    hPen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
                break;

                case IDM_THIN_PEN_BLUE:
                    hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 255));
                break;

                case IDM_THIN_PEN_BLACK:
                    hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
                break;

                case IDM_MEDIUM_PEN_RED:
                    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
                break;

                case IDM_MEDIUM_PEN_GREEN:
                    hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
                break;

                case IDM_MEDIUM_PEN_BLUE:
                    hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
                break;

                case IDM_MEDIUM_PEN_BLACK:
                    hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
                break;

                case IDM_WIDE_PEN_RED:
                    hPen = CreatePen(PS_SOLID, 6, RGB(255, 0, 0));
                break;

                case IDM_WIDE_PEN_GREEN:
                    hPen = CreatePen(PS_SOLID, 6, RGB(0, 255, 0));
                break;

                case IDM_WIDE_PEN_BLUE:
                    hPen = CreatePen(PS_SOLID, 6, RGB(0, 0, 255));
                break;

                case IDM_WIDE_PEN_BLACK:
                    hPen = CreatePen(PS_SOLID, 6, RGB(0, 0, 0));
                break;

                case IDM_PEN_DEFAULT:
                    hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
                break;

                case IDM_DRAWM_LINE:
                    tool = LOWORD(wParam);
                break;

                case IDM_DRAWM_RECTANGLE:
                    tool = LOWORD(wParam);
                break;

                case IDM_DRAWM_ELLIPSE:
                    tool = LOWORD(wParam);
                break;

                case IDM_DRAWM_BEZIER_CURVE:
                    tool = LOWORD(wParam);
                break;

                case IDM_ERASER_SMALL:
                    tool = LOWORD(wParam);
                break;

                case IDM_ERASER_MEDIUM:
                    tool = LOWORD(wParam);
                break;

                case IDM_ERASER_LARGE:
                    tool = LOWORD(wParam);
                break;

                case ID_DELETE:
                    InvalidateRect(hwnd, NULL, TRUE);
                break;
            }
        break;

        case WM_LBUTTONDOWN:
            if(tool == IDM_DRAWM_BEZIER_CURVE)
            {
                iPrevX = LOWORD(lParam);
                p[i].x = iPrevX;
                iPrevY = HIWORD(lParam);
                p[i].y = iPrevY;
                i++;
                if(i == 4)
                {
                    hdc = GetDC(hwnd);
                    SelectObject(hdc, hPen);
                    MoveToEx(hdc, p[0].x, p[0].y, NULL);
                    PolyBezier(hdc, p, 4);
                    ReleaseDC(hwnd, hdc);
                    InvalidateRect(hwnd, NULL, FALSE);
                    i = 0;
                }
                break;
            }

            if(tool == IDM_ERASER_SMALL)
            {
                iPrevX = LOWORD(lParam);
                iPrevY = HIWORD(lParam);
                hdc = GetDC(hwnd);
                hPen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
                SelectObject(hdc,hPen);
                Rectangle(hdc, iPrevX - 5, iPrevY - 5, iPrevX + 5, iPrevY + 5);
                DeleteObject(hPen);
                ReleaseDC(hwnd, hdc);
            }

            if(tool == IDM_ERASER_MEDIUM)
            {
                iPrevX = LOWORD(lParam);
                iPrevY = HIWORD(lParam);
                hdc = GetDC(hwnd);
                hPen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
                SelectObject(hdc,hPen);
                Rectangle(hdc, iPrevX - 10, iPrevY - 10, iPrevX + 10, iPrevY + 10);
                DeleteObject(hPen);
                ReleaseDC(hwnd, hdc);
            }

            if(tool == IDM_ERASER_LARGE)
            {
                iPrevX = LOWORD(lParam);
                iPrevY = HIWORD(lParam);
                hdc = GetDC(hwnd);
                hPen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
                SelectObject(hdc,hPen);
                Rectangle(hdc, iPrevX - 15, iPrevY - 15, iPrevX + 15, iPrevY + 15);
                DeleteObject(hPen);
                ReleaseDC(hwnd, hdc);
            }

            else
            {
                iPrevX = LOWORD(lParam);
                iPrevY = HIWORD(lParam);
            }
        break;

        case WM_LBUTTONUP:
            iNextX = LOWORD(lParam);
            iNextY = HIWORD(lParam);
            switch(tool)
            {
                case IDM_DRAWM_LINE:
                    hdc = GetDC(hwnd);
                    MoveToEx(hdc, iPrevX, iPrevY, NULL);
                    SelectObject(hdc, hPen);
                    LineTo(hdc, iNextX, iNextY);
                    iPrevX = LOWORD(lParam);
                    iPrevY = HIWORD(lParam);
                    ReleaseDC(hwnd, hdc);
                    InvalidateRect(hwnd, NULL, FALSE);
                break;

                case IDM_DRAWM_RECTANGLE:
                    hdc = GetDC(hwnd);
                    MoveToEx(hdc, iPrevX, iPrevY, NULL);
                    SelectObject(hdc, hPen);
                    Rectangle(hdc, iPrevX, iPrevY, iNextX, iNextY);
                    iPrevX = LOWORD(lParam);
                    iPrevY = HIWORD(lParam);
                    ReleaseDC(hwnd, hdc);
                    InvalidateRect(hwnd, NULL, FALSE);
                break;

                case IDM_DRAWM_ELLIPSE:
                    hdc = GetDC(hwnd);
                    MoveToEx(hdc, iPrevX, iPrevY, NULL);
                    SelectObject(hdc, hPen);
                    Ellipse(hdc, iPrevX, iPrevY, iNextX, iNextY);
                    iPrevX = LOWORD(lParam);
                    iPrevY = HIWORD(lParam);
                    ReleaseDC(hwnd,hdc);
                    InvalidateRect(hwnd, NULL, FALSE);
                break;
            }
        break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        0,
        g_szClassName,
        "EDP_Lab.3",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        720,
        360,
        NULL,
        NULL,
        hInstance,
        NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
