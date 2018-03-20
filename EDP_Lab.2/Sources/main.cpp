#include <windows.h>
#include <stdlib.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
		return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hwnd, IDOK);
				break;

				case IDCANCEL:
					EndDialog(hwnd, IDCANCEL);
				break;
			}
		break;

		default:
			return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	HWND hWndHorzColorScroll, hWndHorzMoveScroll, hWndHorzWidthScroll;
	HWND hWndVertMoveScroll, hWndVertHeightScroll;
	HWND hWndListBox;
	HWND hWndEdit;
	HWND hWndAddButton, hWndCleanButton, hWndRemoveButton;
	HWND hWndEditBg;
	int xNewPos;
	RECT rc;

	switch(Message)
	{
        case WM_CREATE:
            SetScrollRange(hwnd, SB_HORZ, 0, 4, TRUE);
            SetScrollPos(hwnd, SB_HORZ, 0, TRUE);

            SetScrollRange(hwnd, SB_VERT, 0, 4, TRUE);
            SetScrollPos(hwnd, SB_VERT, 0, TRUE);

            hWndHorzColorScroll = CreateWindow("SCROLLBAR",
                                               NULL,
                                               WS_CHILD | WS_VISIBLE | SBS_HORZ,
                                               10,
                                               10,
                                               215,
                                               11,
                                               hwnd,
                                               (HMENU) SCROLL_BAR_HORZ_COLOR,
                                               NULL,
                                               NULL);

            SetScrollRange(hWndHorzColorScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndHorzColorScroll, SB_CTL, 0, TRUE);

            hWndHorzMoveScroll = CreateWindow("SCROLLBAR",
                                               NULL,
                                               WS_CHILD | WS_VISIBLE | SBS_HORZ,
                                               10,
                                               30,
                                               215,
                                               11,
                                               hwnd,
                                               (HMENU) SCROLL_BAR_HORZ_MOVE,
                                               NULL,
                                               NULL);

            SetScrollRange(hWndHorzMoveScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndHorzMoveScroll, SB_CTL, 0, TRUE);

            hWndHorzWidthScroll = CreateWindow("SCROLLBAR",
                                               NULL,
                                               WS_CHILD | WS_VISIBLE | SBS_HORZ,
                                               10,
                                               50,
                                               215,
                                               11,
                                               hwnd,
                                               (HMENU) SCROLL_BAR_HORZ_WIDTH,
                                               NULL,
                                               NULL);

            SetScrollRange(hWndHorzWidthScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndHorzWidthScroll, SB_CTL, 0, TRUE);

            hWndVertMoveScroll = CreateWindow("SCROLLBAR",
                                               NULL,
                                               WS_CHILD | WS_VISIBLE | SBS_VERT,
                                               235,
                                               10,
                                               11,
                                               215,
                                               hwnd,
                                               (HMENU) SCROLL_BAR_VERT_MOVE,
                                               NULL,
                                               NULL);

            SetScrollRange(hWndVertMoveScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndVertMoveScroll, SB_CTL, 0, TRUE);

            hWndVertHeightScroll = CreateWindow("SCROLLBAR",
                                               NULL,
                                               WS_CHILD | WS_VISIBLE | SBS_VERT,
                                               255,
                                               10,
                                               11,
                                               215,
                                               hwnd,
                                               (HMENU) SCROLL_BAR_VERT_HEIGHT,
                                               NULL,
                                               NULL);

            SetScrollRange(hWndVertHeightScroll, SB_CTL, 0, 4, TRUE);
            SetScrollPos(hWndVertHeightScroll, SB_CTL, 0, TRUE);

            hWndListBox = CreateWindowEx(WS_EX_CLIENTEDGE,
                                         "LISTBOX",
                                         NULL,
                                         WS_CHILD | WS_VISIBLE,
                                         295,
                                         10,
                                         200,
                                         250,
                                         hwnd,
                                         (HMENU) LIST_BOX,
                                         NULL,
                                         NULL);

            hWndEdit = CreateWindow("EDIT",
                                    NULL,
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    535,
                                    10,
                                    100,
                                    20,
                                    hwnd,
                                    (HMENU) EDIT,
                                    NULL,
                                    NULL);

            hWndAddButton = CreateWindowEx(WS_EX_CLIENTEDGE,
                                           "Button",
                                           "Generate",
                                           WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                           535,
                                           50,
                                           100,
                                           20,
                                           hwnd,
                                           (HMENU) BUTTON_ADD,
                                           NULL,
                                           NULL);

            hWndCleanButton = CreateWindowEx(WS_EX_CLIENTEDGE,
                                             "Button",
                                             "Clean",
                                             WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                             295,
                                             270,
                                             100,
                                             20,
                                             hwnd,
                                             (HMENU) BUTTON_CLEAN,
                                             NULL,
                                             NULL);

            hWndRemoveButton = CreateWindowEx(WS_EX_CLIENTEDGE,
                                             "Button",
                                             "Remove",
                                             WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                             415,
                                             270,
                                             100,
                                             20,
                                             hwnd,
                                             (HMENU) BUTTON_REMOVE,
                                             NULL,
                                             NULL);

            RegisterHotKey(hwnd, HOTKEY_ALT_P, MOD_ALT, 'P');
            RegisterHotKey(hwnd, HOTKEY_CTRL_A, MOD_CONTROL, 'A');

        break;

		case WM_HSCROLL:
		    if(wParam)
            {
                int nScrollCode = (int)LOWORD(wParam);
                int nPos = (short int)HIWORD(wParam);

                SCROLLINFO si = {sizeof(SCROLLINFO),
                                 SIF_PAGE|SIF_POS|SIF_RANGE|SIF_TRACKPOS, 0, 0, 0, 0,
                                 0};
                GetScrollInfo (hwnd, SB_HORZ, &si);

                int nNewPos = si.nPos;

                switch (nScrollCode)
                {
                    case SB_LINELEFT:
                        nNewPos--;
                    break;

                    case SB_LINERIGHT:
                        nNewPos++;
                    break;

                    case SB_THUMBPOSITION:
                        nNewPos = nPos + si.nMin;
                    break;
                }

                si.fMask = SIF_POS;
                si.nPos = nNewPos;
                SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
            }

		    if(lParam)
            {
                int iScrollId = GetDlgCtrlID((HWND)lParam);

                switch(iScrollId)
                {
                    case SCROLL_BAR_HORZ_COLOR:
                        hWndHorzColorScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndHorzColorScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        switch(xNewPos)
                        {
                            case 0:
                                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 255, 255)));
                                InvalidateRect(hwnd, NULL, TRUE);
                                UpdateWindow(hwnd);
                            break;

                            case 1:
                                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 0, 0)));
                                InvalidateRect(hwnd, NULL, TRUE);
                                UpdateWindow(hwnd);
                            break;

                            case 2:
                                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 255, 0)));
                                InvalidateRect(hwnd, NULL, TRUE);
                                UpdateWindow(hwnd);
                            break;

                            case 3:
                                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 255)));
                                InvalidateRect(hwnd, NULL, TRUE);
                                UpdateWindow(hwnd);
                            break;

                            case 4:
                                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 0)));
                                InvalidateRect(hwnd, NULL, TRUE);
                                UpdateWindow(hwnd);
                            break;
                        }
                        SetScrollPos(hWndHorzColorScroll, SB_CTL, xNewPos, TRUE);
                    break;

                    case SCROLL_BAR_HORZ_MOVE:
                        hWndHorzMoveScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndHorzMoveScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        if(xNewPos >= 0 && xNewPos <= 4)
                        {
                            MoveWindow(hwnd, 10 + xNewPos * 100, 10, 600, 360, TRUE);
                        }
                        SetScrollPos(hWndHorzMoveScroll, SB_CTL, xNewPos, TRUE);
                    break;

                    case SCROLL_BAR_HORZ_WIDTH:
                        hWndHorzWidthScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndHorzWidthScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        if(xNewPos >= 0 && xNewPos <= 4)
                        {
                            MoveWindow(hwnd, 10, 10, 600 + xNewPos * 100, 360, TRUE);
                        }
                        SetScrollPos(hWndHorzWidthScroll, SB_CTL, xNewPos, TRUE);
                    break;
                }
            }
        break;

        case WM_VSCROLL:
		    if(wParam)
            {
                int nScrollCode = (int)LOWORD(wParam);
                int nPos = (short int)HIWORD(wParam);

                SCROLLINFO si = {sizeof(SCROLLINFO),
                                 SIF_PAGE|SIF_POS|SIF_RANGE|SIF_TRACKPOS, 0, 0, 0, 0,
                                 0};
                GetScrollInfo (hwnd, SB_VERT, &si);

                int nNewPos = si.nPos;

                switch (nScrollCode)
                {
                    case SB_LINELEFT:
                        nNewPos--;
                    break;

                    case SB_LINERIGHT:
                        nNewPos++;
                    break;

                    case SB_THUMBPOSITION:
                        nNewPos = nPos + si.nMin;
                    break;
                }

                si.fMask = SIF_POS;
                si.nPos = nNewPos;
                SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
            }

		    if(lParam)
            {
                int iscrollid = GetDlgCtrlID((HWND)lParam);

                switch(iscrollid)
                {
                    case SCROLL_BAR_VERT_MOVE:
                        hWndVertMoveScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndVertMoveScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        if(xNewPos >= 0 && xNewPos <= 4)
                        {
                            MoveWindow(hwnd, 10, 10 + xNewPos * 100, 600, 360, TRUE);
                        }
                        SetScrollPos(hWndVertMoveScroll, SB_CTL, xNewPos, TRUE);
                    break;

                    case SCROLL_BAR_VERT_HEIGHT:
                        hWndVertHeightScroll = (HWND)lParam;
                        xNewPos = GetScrollPos(hWndVertHeightScroll, SB_CTL);
                        switch(LOWORD(wParam))
                        {
                            case SB_LINELEFT:
                                xNewPos--;
                            break;

                            case SB_LINERIGHT:
                                xNewPos++;
                            break;

                            case SB_THUMBPOSITION:
                                xNewPos = HIWORD(wParam);
                            break;
                        }
                        if(xNewPos >= 0 && xNewPos <= 4)
                        {
                            MoveWindow(hwnd, 10, 10, 600, 360 + xNewPos * 100, TRUE);
                        }
                        SetScrollPos(hWndVertHeightScroll, SB_CTL, xNewPos, TRUE);
                    break;
                }
            }

        break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_FILE_EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
				break;

				case ID_HELP_ABOUT:
				{
					int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
					if(ret == IDOK){
						MessageBox(hwnd, "Dialog exited with IDOK.", "Notice", MB_OK | MB_ICONINFORMATION);
					}
					else if(ret == IDCANCEL){
						MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice", MB_OK | MB_ICONINFORMATION);
					}
					else if(ret == -1){
						MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
					}
				}
				break;

                case ID_FILE_EDIT:
                    MessageBox(NULL, "Try to play with first scroll bar and you'll see some changes!", "Error", MB_ICONEXCLAMATION | MB_OK);
                break;

                case BUTTON_ADD:
                {
                    char name[10];
                    GetDlgItemText(hwnd, EDIT, name, 10);
                    int index = SendDlgItemMessage(hwnd, LIST_BOX, LB_ADDSTRING, 0, (LPARAM)name);
                    SendDlgItemMessage(hwnd, LIST_BOX, LB_SETITEMDATA, (WPARAM)index, NULL);
                }
                break;

                case BUTTON_CLEAN:
					SendDlgItemMessage(hwnd, LIST_BOX, LB_RESETCONTENT, 0, 0);
				break;

				case BUTTON_REMOVE:
                    int iElemID = SendDlgItemMessage(hwnd, LIST_BOX, LB_GETCURSEL, 0, 0);
                    if(iElemID != LB_ERR)
                    {
                        SendDlgItemMessage(hwnd, LIST_BOX, LB_DELETESTRING, iElemID, 0);
                    }
                break;
			}
		break;

        case WM_HOTKEY:
            switch(wParam)
            {
                case HOTKEY_ALT_P:
                    PostQuitMessage(0);
                break;

                case HOTKEY_CTRL_A:
                    ShowWindow(hwnd, SW_MAXIMIZE);
                break;
            }
        break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;

        case WM_CLOSE:
			DestroyWindow(hwnd);
		break;

		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
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
    wc.style         = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_ASTERISK);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                          g_szClassName,
                          "The title of my window",
                          WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
                          10,
                          10,
                          720,
                          480,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
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
