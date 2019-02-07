// Exercise1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Exercise1.h"
#include <vector> 
#include "Car.h"
#include <iterator>
#include <algorithm>
#include <map>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	SannsynlighetProc(HWND, UINT, WPARAM, LPARAM);


void				lagBil(int);
void				oppdaterBiler();
void				drawBiler(HDC);
void				drawRoad(HDC);
bool				sjekkLedig(Car);
void				TegnSannsynlighet(HDC, double, double);

using namespace		std;
static				vector<Car> biler;
static				map <int,pair < int, int>> ledig;
int					bilId = 0;
static int			teller = 0;
static int			tid = 0;

static double		sannsynligVest = 0.10;
static double		sannsynligNord = 0.10;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EXERCISE1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXERCISE1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXERCISE1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EXERCISE1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   SetTimer(hWnd, 1, 300, NULL);


   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
void drawBiler(HDC hdc) {
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 69, 0));
	HGDIOBJ	hOrg = SelectObject(hdc, hBrush);

	for (Car &c : biler) {
		Rectangle(hdc, c.getLeft(), c.getTop(), c.getRight(), c.getBottom());
	}

	DeleteObject(hBrush);
	DeleteObject(hOrg);
}
void drawRoad(HDC hdc) {

	HBRUSH hBrush = CreateSolidBrush(RGB(100, 100, 100));
	HGDIOBJ	hOrg = SelectObject(hdc, hBrush);

	Rectangle(hdc, 0, 200, 1000, 300);
	Rectangle(hdc, 450, 0, 550, 600);
	Rectangle(hdc, 450, 200, 550, 300);

	HPEN hPen = CreatePen(PS_DASH, 1, RGB(200, 200, 0));
	hOrg = SelectObject(hdc, hPen);
	SetBkMode(hdc, TRANSPARENT);

	MoveToEx(hdc, 0, 250, 0);
	LineTo(hdc, 450, 250);
	MoveToEx(hdc, 550, 250, 0);
	LineTo(hdc, 1000, 250);
	MoveToEx(hdc, 500, 0, 0);
	LineTo(hdc, 500, 200);
	MoveToEx(hdc, 500, 300, 0);
	LineTo(hdc, 500, 600);

	DeleteObject(hBrush);
	DeleteObject(hPen);
	DeleteObject(hOrg);
}
void oppdaterBiler() {

	for (Car &c : biler) {
		if (sjekkLedig(c)) {
			if (c.getRetning() == 0) {
				pair<int, int> par = pair<int, int>(c.getRight(), c.getBottom());
				ledig.insert(pair<int, pair<int, int>>(c.getId(), par));

				if (!(c.getRight() == 440) || teller == 2 || teller == 3) {
					
					c.setLeft(c.getLeft() + 10);
					c.setRight(c.getRight() + 10);
				}
			}
			if (c.getRetning() == 1) {
				if (!(c.getBottom() == 190) || teller == 1 || teller == 0) {
					c.setTop(c.getTop() + 10);
					c.setBottom(c.getBottom() + 10);
				}
			}
		}
		map <int, pair < int, int>>::iterator itit = ledig.find(c.getId());
		if (itit != ledig.end()) {
			ledig.erase(itit);
		}
			
	}
	auto it = biler.begin();
	while (it != biler.end()) {
		if (it->getRight() == 1000 || it->getBottom() == 600) {
			it = biler.erase(it);
		}
		else {
			++it;
		}
	}

}
bool sjekkLedig(Car c1){
	for (auto &testPos : ledig) {
		if (c1.getRetning() == 0) {
			if ((c1.getLeft() + 40) == testPos.second.second) {
				return false;
			}
		}
		else {
			if (c1.getBottom() + 40 == testPos.second.second) {
				return false;
			}
		}
	}
	return true;
}
void lagBil(int ret) {
	Car car = Car(bilId);
	if (ret == 0) {
		car.setLeft(0);
		car.setTop(210);
		car.setRight(40);
		car.setBottom(240);
		car.setRetning(0);
	}
	if (ret == 1) {
		car.setLeft(460);
		car.setTop(0);
		car.setRight(490);
		car.setBottom(40);
		car.setRetning(1);
	}
	biler.push_back(car);
	bilId++;
}
void TegnSannsynlighet(HDC hdc, double nord, double vest) {
	
	
	TCHAR text[256];
	swprintf_s(text, 256, L"Sannsynlighet Vest: %lf", vest);
	TextOut(hdc, 10, 70, text, wcslen(text));
	swprintf_s(text, 256, L"Sannsynlighet Nord: %lf", nord);
	TextOut(hdc, 10, 85, text, wcslen(text));

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_SANNSYNLIGHET_DIALOGVALG:
				//MessageBox(hWnd, _T("Menykommandoen funker !!"), _T(""), MB_OK);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SANNSYNLIGHET), hWnd, SannsynlighetProc);
				break;
			case ID_SANN2:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SANNDIALOG2), hWnd, SannsynlighetProc);
				break;
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
		HBRUSH hBrush;
		HGDIOBJ hOrg;

		drawRoad(hdc);
		drawBiler(hdc);

		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hOrg = SelectObject(hdc, hBrush);
		Rectangle(hdc, 390, 50, 440, 190);
		SelectObject(hdc, hOrg);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hOrg = SelectObject(hdc, hBrush);
		Rectangle(hdc, 560, 310, 610, 450);
		SelectObject(hdc, hOrg);
		DeleteObject(hBrush);

		if (teller == 0) {
			// lys 1
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 55, 435, 95);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 100, 435, 140);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 145, 435, 185);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			// lys 2
			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 315, 605, 355);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 360, 605, 400);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 405, 605, 445);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);
		}

		if (teller == 1) {
			// lys 1
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 55, 435, 95);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 100, 435, 140);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 145, 435, 185);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			// lys 2
			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 315, 605, 355);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 360, 605, 400);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 405, 605, 445);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);
		}

		if (teller == 2) {
			// lys 1
			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 55, 435, 95);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 100, 435, 140);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 145, 435, 185);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			// lys 2
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 315, 605, 355);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 360, 605, 400);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 405, 605, 445);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);
		}

		if (teller == 3) {
			// lys 1
			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 55, 435, 95);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 100, 435, 140);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 395, 145, 435, 185);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			// lys 2
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 315, 605, 355);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 360, 605, 400);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			hOrg = SelectObject(hdc, hBrush);
			Ellipse(hdc, 565, 405, 605, 445);
			SelectObject(hdc, hOrg);
			DeleteObject(hBrush);
		}

		TegnSannsynlighet(hdc, sannsynligNord, sannsynligVest);

		EndPaint(hWnd, &ps);
	}
	break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
		lagBil(0);
		break;
	case WM_RBUTTONDOWN:
		lagBil(1);
		break;
	case WM_TIMER: {
		if (tid % 10 == 0) {
			if (teller == 0) {
				teller = 1;
			}
			else if (teller == 1) {
				teller = 2;
			}
			else if (teller == 2) {
				teller = 3;
			}
			else if (teller == 3) {
				teller = 0;
			}
		}
		tid++;
		oppdaterBiler();

		double val = (double)rand() / RAND_MAX;
		if (val < sannsynligNord) {
			lagBil(1);
		}
		double val1 = (double)rand() / RAND_MAX;
		if (val1 < sannsynligVest) {
			lagBil(0);
		}

		InvalidateRect(hWnd, 0, true);
		break;
	}
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			if(sannsynligVest > 0)
			sannsynligVest = sannsynligVest - 0.10;
			break;
		case VK_RIGHT:
			if (sannsynligVest < 0.9)
			sannsynligVest = sannsynligVest + 0.10;
			break;
		case VK_UP:
			if (sannsynligNord > 0)
			sannsynligNord = sannsynligNord - 0.10;
			break;
		case VK_DOWN:
			if (sannsynligNord < 0.9)
			sannsynligNord = sannsynligNord + 0.10;
			break;
		}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

INT_PTR CALLBACK SannsynlighetProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	static HWND tekst1;
	static HWND tekst2;

	static HWND skrivTekst1;
	static HWND skrivTekst2;

	static int len = 0;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		tekst1 = ::GetDlgItem(hDlg, IDC_STATIC1);
		::SetWindowText(tekst1, _T("Sannsynlighet Vest"));
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			len = GetWindowTextLength(GetDlgItem(hDlg, IDC_RICHEDIT22));
			if (len > 0) {
				len += 1;
				std::wstring str(len, L'\0');
				GetWindowText(GetDlgItem(hDlg, IDC_RICHEDIT22), &str[0], len);
				sannsynligVest = (double)_wtof(str.c_str());
			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	//switch (message) {
	//

	//case WM_INITDIALOG:
	//{
	//	tekst1 = ::GetDlgItem(hDlg, IDC_STATIC_1);
	//	::SetWindowText(tekst1, _T("Sannsynlighet Vest"));
	//	tekst2 = ::GetDlgItem(hDlg, IDC_STATIC_2);
	//	::SetWindowText(tekst2, _T("Sannsynlighet Nord"));
	//	return TRUE;
	//}
	//case WM_COMMAND:
	//	switch (LOWORD(wParam)) {
	//	case IDOK:
	//	{
	//		//len = GetWindowTextLength(GetDlgItem(hDlg, IDC_RICHEDIT21));
	//		if (len > 0) {
	//			len += 1;
	//			std::wstring str(len, L'\0');
	//			GetWindowText(GetDlgItem(hDlg, IDC_RICHEDIT21), &str[0], len);
	//			sannsynligNord = (double)_wtof(str.c_str());
	//		}
	//		//len = GetWindowTextLength(GetDlgItem(hDlg, IDC_RICHEDIT22));
	//		if (len > 0) {
	//			len += 1;
	//			std::wstring str(len, L'\0');
	//			GetWindowText(GetDlgItem(hDlg, IDC_RICHEDIT22), &str[0], len);
	//			sannsynligVest = (double)_wtof(str.c_str());
	//		}
	//	}
	//	case IDCANCEL:
	//		EndDialog(hDlg, LOWORD(wParam));
	//		return TRUE;
	//	}
	//	break;
//	}
	//
	return FALSE;
}