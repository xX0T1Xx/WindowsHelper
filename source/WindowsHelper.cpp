#include "WindowsHelper.h"

// Defining Globals
WNDCLASSA WC = {0};
char CLASS_NAME[50] = {0};
HWND WINDOW_HANDLE = 0;
int ID_COUNTER = -1;
std::vector<void(*)(void)> FUNCTION_POINTER_ID;
std::vector<HWND> ELEMENTS;

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
void HelperCreateWindow(const char *WindowTitle, const uint32_t width, const uint32_t height) {
    WINDOW_HANDLE = CreateWindowExA(
        0, CLASS_NAME, WindowTitle, // Class and Title
        WS_OVERLAPPEDWINDOW, // Style
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, // Size And Position
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

// Event Callback Function
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND: // The Element Was Clicked
            printf("wParam: %d, lParam: %d\n", wParam, lParam);
            FUNCTION_POINTER_ID.at((int)wParam)(); // Call the function associated with this element
            break;

        case WM_DESTROY: // X Button Clicked
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// This is the None function, it's required by WindowProc
void None(void) {
    return;
}


// ---------------------------------------------------------------------------------------------------------- //
//                                          ELEMENTS CREATION CODE                                            //
// ---------------------------------------------------------------------------------------------------------- //

// Creates a button and returns it's id
int HelperCreateButton(const char *ButtonText, const uint32_t x, const uint32_t y, void(*function)(void)) {
    ID_COUNTER++;
    FUNCTION_POINTER_ID.push_back(function);
    HWND button = CreateWindowA(
        "BUTTON", ButtonText, // Class + Text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        x, y, 100, 30, // Position + Size
        WINDOW_HANDLE, (HMENU)ID_COUNTER, WC.hInstance, NULL // Extra Data
    );
    ELEMENTS.push_back(button);
    return ID_COUNTER;
}

// Creates a button and returns it's id
int HelperCreateLabel(const char *LabelText, const uint32_t x, const uint32_t y, void(*function)(void)) {
    ID_COUNTER++;
    FUNCTION_POINTER_ID.push_back(function);
    HWND label = CreateWindowA(
        "STATIC", LabelText, // Class + Text
        WS_VISIBLE | WS_CHILD, // Styles
        x, y, 250, 15, // Position + Size
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