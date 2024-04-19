#include "Game.h"
#include "MyTriangle.h"
#include "Constants.h"
#include <string>
#include <assert.h>
#include <time.h>
#include <windows.h>
#include <gdiplus.h>
#pragma warning (disable:28251)

// GDI+ libraries 
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;
using namespace std;


// Declare globals 
Bitmap* g_bitmap;
Game* g_myGame;


void getDisplayResolution(int& x, int& y)
{
	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);
}

void getWindowBorderDimensions(HWND hWnd, int& width, int& height)
{
	RECT clientRect;
	RECT windowRect;
	GetClientRect(hWnd, &clientRect); // Relative to itself
	GetWindowRect(hWnd, &windowRect); // Screen coordinates
	int newWidth = (windowRect.right - windowRect.left) - clientRect.right;
	int newHeight = (windowRect.bottom - windowRect.top) - clientRect.bottom;
	width = newWidth;
	height = newHeight;
}

void loadBackgroundImage(string fileName)
{
	wstring wName = wstring(fileName.begin(), fileName.end()); // Convert to wide char's


	// GDI+ supports BMP, GIF, JPEG, PNG, TIFF, Exif, WMF, and EMF. 
	if (g_bitmap)
	{
		// If we already have one loaded, destroy it
		delete g_bitmap;
	}
	g_bitmap = new Bitmap(wName.c_str());

	assert(g_bitmap != nullptr);
	return;
}

void drawImages(HDC hdc, int g_elapsed)
{
	if (g_bitmap)
	{
		Graphics graphics(hdc);
		Bitmap bufBitmap(g_bitmap->GetWidth(), g_bitmap->GetHeight(), PixelFormat32bppPARGB);
		Graphics buffer(&bufBitmap); // graphics object for the buffer
		Rect rect(0, 0, g_bitmap->GetWidth(), g_bitmap->GetHeight());
		buffer.DrawImage(g_bitmap, rect);
		g_myGame->render(buffer, g_elapsed);
		graphics.DrawImage(&bufBitmap, 0, 0);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int x = rand() % 900;
	int y = rand() % 700;
	int directionX = 0;
	int directionY = 0;
	if (wParam == VK_LEFT || wParam == VK_RIGHT)
		directionX = wParam == VK_RIGHT ? 10 : -10;
	else if (wParam == VK_UP || wParam == VK_DOWN)
		directionY = wParam == VK_DOWN ? 10 : -10;

	switch (msg)
	{
	case WM_CREATE:
		g_myGame = new Game(hWnd);
		loadBackgroundImage("images\\14960493_5532920.bmp");
		if (g_bitmap->GetLastStatus() != Ok)
		{
			MessageBoxA(hWnd, "Unable to load file!", "Error", MB_OK);
			delete g_bitmap;// if the file fails to load, g_bitmap still has data
			g_bitmap = nullptr;
		}
		else
		{
			int bW, bH, wX, wY;
			getWindowBorderDimensions(hWnd, bW, bH);
			getDisplayResolution(wX, wY);
			// Verify the image is smaller than screen or SetWindowPos() will fail. Display scaling affects the reported resolution
			if ((UINT)wX >= g_bitmap->GetWidth() + bW && (UINT)wY >= g_bitmap->GetHeight() + bH)
			{
				SetWindowPos(hWnd, HWND_TOP, (wX - (g_bitmap->GetWidth() + bW)) / 2, (wY - (g_bitmap->GetHeight() + bH)) / 2, g_bitmap->GetWidth() + bW, g_bitmap->GetHeight() + bH, SWP_SHOWWINDOW);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		
		break;
	case WM_RBUTTONDOWN:

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
unsigned long g_elapsed = 0;

int getElapsedTime()
{
	return g_elapsed;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int showCmd)
{ 
	srand((unsigned int)time(NULL));
	HWND windowHandle = 0;
	HINSTANCE applicationInstance = 0;
	int windowClientWidth = 800;
	int windowClientHeight = 600;

	applicationInstance = hInstance;

	unsigned long lastTick = (unsigned long)GetTickCount64();
	unsigned long curTick = lastTick;
	unsigned long localTime = 0;

	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIconSm = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = applicationInstance;
	wc.hCursor = LoadCursor(0, IDC_ARROW); // cursor to use for the class

	wc.lpszMenuName = 0;
	wc.lpszClassName = "GDI Window Class";
	//COLORREF r = 0x00FF0000;  // BGR 
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)); // background brush for the window
	RegisterClassEx(&wc);

	// Set the width and height of your window.
	int windowWidth = 800;
	int windowHeight = 600;
	// Set the initial position of your window. 
	int windowXPosition = 0;
	int windowYPosition = 0;

	getDisplayResolution(windowWidth, windowHeight); // call the template function to get display size

	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	windowHandle = CreateWindowEx(WS_EX_ACCEPTFILES,
		"GDI Window Class",
		c_GameName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		windowXPosition,
		windowYPosition,
		windowWidth,
		windowHeight,
		0,
		0,
		applicationInstance, 0);

	if (0 == windowHandle)
	{
		MessageBoxA(0, "CreateWindow Failed", "Application Error Message", 0);
		return false;
	}

	ShowWindow(windowHandle, showCmd);

	UpdateWindow(windowHandle);


	// Get the border and title bar dimensions so we can accurately resize our window in WM_PAINT
	RECT clientRectangle = {};
	RECT windowRectangle = {};

	GetClientRect(windowHandle, &clientRectangle);
	GetWindowRect(windowHandle, &windowRectangle);
	windowClientWidth = (windowRectangle.right - windowRectangle.left) - clientRectangle.right;
	windowClientHeight = (windowRectangle.bottom - windowRectangle.top) - clientRectangle.bottom;


	MSG msg;
	SecureZeroMemory(&msg, sizeof(MSG));

	int returnValue = 0; //  Used to check if GetMessage failed

	HDC hdc = GetDC(windowHandle);
	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			curTick = (unsigned long)GetTickCount64();
		    g_elapsed = min(curTick - lastTick, 1000);
			lastTick = curTick;
			g_myGame->update(g_elapsed);
			// Check collisions
			drawImages(hdc, g_elapsed);
		}
	}

	delete g_bitmap;
	delete g_myGame;
	GdiplusShutdown(gdiplusToken);

	DeleteObject(wc.hbrBackground);

	return (int)msg.wParam;
}
