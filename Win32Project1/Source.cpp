#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <Windows.h>
#include <windef.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void OnSize(HWND hwnd, UINT flag, int width, int height);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);


	// Create the window
	HWND hwnd = CreateWindowEx(
		0,							// optional window styles
		CLASS_NAME,					// Window class
		L"LearnToProgramWindows",	// Window text
		WS_OVERLAPPEDWINDOW,		// Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,		// parent window
		NULL,		// menu
		hInstance,	// instance handle
		NULL		// additional application data
		);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// run the message loop

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}


// This funtion is typically blocking, so use threads or asynchrony to avoid bottlenecking.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		{
			int width = LOWORD(lParam);		// macro to get low-order word (bit-shifting)
			int height = HIWORD(lParam);	// macro to get high-order word

			// respond to message.
			OnSize(hwnd, (UINT)wParam, width, height);
		}
		break;

	case WM_PAINT:
		{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		
		// all painting occurs between BeginPaint and EndPaint
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		
		EndPaint(hwnd, &ps);
		}
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, L"Really quit?", L"My Application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		// Else: user cancelled, do nothing
		return 0; // zero return val indicates you hasndled the msg.
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


// definition
void OnSize(HWND hwnd, UINT flag, int width, int height)
{
	// handle resizing...
}