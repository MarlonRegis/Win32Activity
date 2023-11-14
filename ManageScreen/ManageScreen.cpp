#ifndef UNICODE
#define UNICODE
#endif 

#define WM_MINHA_MENSAGEM

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddControls(HWND hwnd);
void ShowOutput(HWND hwnd);

HWND hData;
#define WM_MINHA_MENSAGEM (WM_USER + 1)
#define BTN_OK  1
#define TEXT_BOX  103

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	const wchar_t CLASS_NAME[] = L"Learning Win32";

	WNDCLASSW wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	if (!RegisterClassW(&wc))
		return -1;

	HWND hwnd = CreateWindowExW(
		WS_CLIPCHILDREN,    
		CLASS_NAME,         
		L"Desktop Win32 App", 
		WS_OVERLAPPEDWINDOW,        

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,

		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (hwnd == nullptr)
	{
		MessageBox(nullptr, L"Call to CreateWindow failed!", L"Windows Desktop Guided Tour", NULL);
		return -1;
	}
	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.
	MSG msg = { };
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case 1:
			if (LOWORD(wParam) == BTN_OK)
			{
				PostMessage(hwnd, WM_MINHA_MENSAGEM, wParam, lParam);
			}
		}
		break;
	}
	case WM_CREATE:
	{
		AddControls(hwnd);
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_MINHA_MENSAGEM:
		ShowOutput(hwnd);
		break;
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
}

void AddControls(HWND hwnd) {
	hData = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 160, 100, 140, 50, hwnd, (HMENU)TEXT_BOX, NULL, NULL);
	CreateWindowW(L"Button", L"Show Message", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 160, 152, 140, 50, hwnd, (HMENU)BTN_OK, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}

void ShowOutput(HWND hwnd)
{
	wchar_t buffer[256];

	HWND edit = GetDlgItem(hwnd, TEXT_BOX);
	GetWindowText(edit, buffer, sizeof(buffer)/ sizeof(buffer[0]));
	if (wcslen(buffer) > 0) {
		MessageBox(nullptr, buffer, L"Win32 Popup", MB_OK | MB_ICONINFORMATION);
	}
	else {
		MessageBox(nullptr, L"Not found text here", L"Win32 Popup", MB_OK | MB_ICONINFORMATION);
	}
}