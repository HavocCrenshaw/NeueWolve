#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

int WINAPI wWinMain(
    _In_ HINSTANCE appHandle,
    _In_opt_ HINSTANCE /* Unused */,
    _In_ PWSTR commandLine,
    _In_ int windowPresentation
) {
    return 0;
}
