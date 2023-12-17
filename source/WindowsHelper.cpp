#include "WindowsHelper.h"

// Defining Globals
WNDCLASSA WC = {0};
char CLASS_NAME[50] = {0};
HWND WINDOW_HANDLE = 0;
int ID_COUNTER = -1;
std::vector<void(*)(int)> FUNCTION_POINTER_ID;
std::vector<HWND> ELEMENTS;
HBRUSH STATIC_BRUSH = CreateSolidBrush(RGB(255, 255, 255));
COLORREF STATIC_COLOR = RGB(0, 0, 0);

// ---------------------------------------------------------------------------------------------------------- //
//                                           WINDOW CREATION CODE                                             //
// ---------------------------------------------------------------------------------------------------------- //

// Registers The Window Atom
void HelperRegisterWindow(const char *ClassName) {
    strncpy(CLASS_NAME, ClassName, sizeof(CLASS_NAME));
    WC.lpfnWndProc = WindowProc;
    WC.hInstance = GetModuleHandle(NULL);
    WC.lpszClassName = ClassName;
    WC.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassA(&WC);
}

// Creates A Window
void HelperCreateWindow(const char *WindowTitle, const int width, const int height) {
    WINDOW_HANDLE = CreateWindowExA(
        0, CLASS_NAME, WindowTitle, // Class and Title
        WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX, // Style
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, // Size And Position
        NULL, NULL, WC.hInstance, NULL // Extra
    );
}

// Creates A Window Without Border
void HelperCreateWindowBorderless(const char *WindowTitle, const int x, const int y, const int width, const int height) {
    WINDOW_HANDLE = CreateWindowExA(
        0, CLASS_NAME, WindowTitle, // Class and Title
        WS_POPUP, // Style
        x, y, width, height, // Size And Position
        NULL, NULL, WC.hInstance, NULL // Extra
    );
}

// Starts The Window Loop
void HelperStartWindow(void) {
    // Show The Window
    ShowWindow(WINDOW_HANDLE, SW_SHOW);

    // Poll for messages and update window display
    MSG msg{};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        UpdateWindow(WINDOW_HANDLE);
    }
}

// Sets the window to always be on top
void HelperWindowOnTop(void) {
    SetWindowPos(WINDOW_HANDLE, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

// Moves the window
void HelperMoveWindow(int x, int y) {
    SetWindowPos(WINDOW_HANDLE, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

// Event Callback Function
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {

        // The Element Was Clicked
        case WM_COMMAND: {
            FUNCTION_POINTER_ID.at((int)wParam)((int)wParam); // Call the function associated with this element
            break;
        }
            
        // Color for STATIC objects
        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            SetTextColor(hdcStatic, STATIC_COLOR);
            SetBkMode(hdcStatic, TRANSPARENT);
            return (LRESULT)STATIC_BRUSH;
        }

        // X Button Clicked
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// This is the None function, it's required by WindowProc
void None(int ElementID) {
    return;
}


// ---------------------------------------------------------------------------------------------------------- //
//                                          ELEMENTS CREATION CODE                                            //
// ---------------------------------------------------------------------------------------------------------- //

// Creates a button and returns it's id
int HelperCreateButton(const char *ButtonText, const int x, const int y, const int width, const int height, void(*function)(int)) {
    ID_COUNTER++;
    FUNCTION_POINTER_ID.push_back(function);
    HWND button = CreateWindowA(
        "BUTTON", ButtonText, // Class + Text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        x, y, width, height, // Position + Size
        WINDOW_HANDLE, (HMENU)ID_COUNTER, WC.hInstance, NULL // Extra Data
    );
    ELEMENTS.push_back(button);
    return ID_COUNTER;
}

// Creates a button and returns it's id
int HelperCreateLabel(const char *LabelText, const int x, const int y, const int width, const int height, void(*function)(int)) {
    ID_COUNTER++;
    FUNCTION_POINTER_ID.push_back(function);
    HWND label = CreateWindowA(
        "STATIC", LabelText, // Class + Text
        WS_VISIBLE | WS_CHILD, // Styles
        x, y, width, height, // Position + Size
        WINDOW_HANDLE, (HMENU)ID_COUNTER, WC.hInstance, NULL // Extra Data
    );
    ELEMENTS.push_back(label);
    return ID_COUNTER;
}


// ---------------------------------------------------------------------------------------------------------- //
//                                          ELEMENTS EDITING CODE                                             //
// ---------------------------------------------------------------------------------------------------------- //

void HelperSetElementText(int ElementID, const char *Text) {
    SetWindowTextA(ELEMENTS.at(ElementID), Text);
}