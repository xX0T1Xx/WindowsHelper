/**
 *  This file contains functions intended to make working with the Windows API for GUI applications easier.
*/
#pragma once

// Definitions
#define NONE &None

// Includes
#include <vector>
#include <windows.h>
#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <CommCtrl.h>
#include <uxtheme.h>

// Global Variables
extern WNDCLASS WC; // Contains WNDCLASS Struct
extern char CLASS_NAME[50]; // Contains The CLASS_NAME atom
extern HWND WINDOW_HANDLE; // Handle to the window
extern int ID_COUNTER; // Counter for each new element added to window
extern std::vector<void(*)(int)> FUNCTION_POINTER_ID; // Pointers to the void function for each element
extern std::vector<HWND> ELEMENTS; // Contains handle to all elements added to the window
extern HBRUSH STATIC_BRUSH; // Global brush for static elements
extern COLORREF STATIC_COLOR; // Global text color for static elements
extern void(*UPDATE_FUNCTION)(void); // Function that gets called every second
extern HFONT FONT; // The GUI Font

// Global Functions
void HelperRegisterWindow(const char *ClassName);
void HelperCreateWindow(const char *WindowTitle, const int width, const int height);
void HelperCreateWindowBorderless(const char *WindowTitle, const int x, const int y, const int width, const int height);
void HelperStartWindow(void);
void HelperWindowOnTop(void);
void HelperMoveWindow(int x, int y);
int HelperCreateButton(const char *ButtonText, const int x, const int y, const int width, const int height, void(*function)(int));
int HelperCreateLabel(const char *LabelText, const int x, const int y, const int width, const int height, void(*function)(int));
int HelperCreateTextBox(const int x, const int y, const int width, const int height, void(*function)(int));
void HelperSetElementText(int ElementID, const char *Text);
void HelperSetUpdateFunction(void(*Function)(void), int interval);
void HelperSetTextColor(int R, int G, int B);
void HelperSetElementFontSize(int ElementID, int FontSize);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void None(int ElementID); // This function exists if the function pointer should do nothing
void Update(void); // This function exists as the default update function