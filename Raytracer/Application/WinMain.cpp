#include <Windows.h>
#include <cstdint>
#include "Application/Sample.h"

HWND CreateAppWindow(const HINSTANCE hInstance, const int nCmdShow);
LRESULT CALLBACK WndProc(const HWND hwnd, const UINT message, const WPARAM wParam, const LPARAM lParam);
void OnPaint(const HWND hwnd);

int CALLBACK WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const LPSTR lpCmdLine, const int nCmdShow)
{
    // Create main application window.
    const HWND hwnd = CreateAppWindow(hInstance, nCmdShow);
    if (hwnd == 0)
    {
        return 0;
    }

    // Message loop.
    MSG  msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

HWND CreateAppWindow(const HINSTANCE hInstance, const int nCmdShow)
{
    const auto className = TEXT("MainWindow");

    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = className;
    wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        return 0;
    }
    
    const auto hwnd = CreateWindow(
        className,
        TEXT("Raytracer - Richard Cervinka"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (hwnd == 0)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return hwnd;
}

LRESULT CALLBACK WndProc(const HWND hwnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        OnPaint(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

void OnPaint(const HWND hwnd)
{
    static Sample sample;
    static Framebuffer framebuffer(FramebufferFormat::BGRA8);

    PAINTSTRUCT ps;
    const auto hdc = BeginPaint(hwnd, &ps);

    // Get client area dimensions.
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    const int width = static_cast<int>(clientRect.right - clientRect.left);
    const int height = static_cast<int>(clientRect.bottom - clientRect.top);

    // Resize framebuffer.
    framebuffer.Resize(width, height);

    // Draw scene to the framebuffer.
    sample.Draw(framebuffer);

    // Create a GDI bitmap containing framebuffer data.
    const auto bitmapDC = CreateCompatibleDC(hdc);
    const auto bitmap = CreateBitmap(width, height, 1, 4 * 8, framebuffer.Data());
    const auto replacedObject = SelectObject(bitmapDC, bitmap);

    // Blit bittmap to the window.
    BitBlt(hdc, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);

    // WinAPI cleanup.
    SelectObject(bitmapDC, replacedObject);
    DeleteObject(bitmap);
    DeleteDC(bitmapDC);

    EndPaint(hwnd, &ps);
}