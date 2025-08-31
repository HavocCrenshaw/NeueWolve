#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT msg, WPARAM basicParams, LPARAM extraParams);

int WINAPI wWinMain(
    _In_ HINSTANCE appHandle,
    _In_opt_ HINSTANCE /* Unused */,
    _In_ PWSTR commandLine,
    _In_ int windowPresentation
) {
    HICON iconHandle = static_cast<HICON>(LoadImageW(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
    HCURSOR cursorHandle = static_cast<HCURSOR>(LoadImageW(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
    constexpr WCHAR CLASS_NAME[] = L"WindowClass";

    WNDCLASSEXW windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEXW);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProcedure;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = appHandle;
    windowClass.hIcon = iconHandle;
    windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = CLASS_NAME;
    windowClass.hIconSm = iconHandle;

    if (RegisterClassExW(&windowClass) == 0) {
        return 1;
    }

    HWND windowHandle = CreateWindowExW(
        0,
        CLASS_NAME,
        L"NeueWolve",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        nullptr,
        appHandle,
        nullptr
    );
    if (windowHandle == nullptr) {
        return 1;
    }

    ShowWindow(windowHandle, windowPresentation);
    UpdateWindow(windowHandle);

    MSG msg = { 0 };

    bool running = true;
    while (running) {
        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        // Game code
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT msg, WPARAM basicParams, LPARAM extraParams)
{
    switch (msg) {
        case WM_ERASEBKGND: {
            return 1; // Say that we cleared the background, but we're painting everything in WM_PAINT
        }

        case WM_PAINT: {
            PAINTSTRUCT paintInfo;
            HDC deviceContextHandle = BeginPaint(windowHandle, &paintInfo);

            FillRect(deviceContextHandle, &paintInfo.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(windowHandle, &paintInfo);
            return 0;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(windowHandle, msg, basicParams, extraParams);
}
