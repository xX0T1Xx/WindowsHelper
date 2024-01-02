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
extern COLORREF BACKGROUND_COLOR; // The background color for all elements

// Window Management Functions
void HelperRegisterWindow(const char *ClassName);
void HelperCreateWindow(const char *WindowTitle, const int width, const int height);
void HelperCreateWindowBorderless(const char *WindowTitle, const int x, const int y, const int width, const int height);
void HelperStartWindow(void);
void HelperWindowOnTop(void);
void HelperMoveWindow(int x, int y);

// Element Creation Functions
int HelperCreateButton(const char *ButtonText, const int x, const int y, const int width, const int height, void(*function)(int));
int HelperCreateLabel(const char *LabelText, const int x, const int y, const int fontSize, void(*function)(int));
int HelperCreateTextBox(const int x, const int y, const int width, const int height, void(*function)(int));
int HelperCreateGenericElement(char *className, char *text, int styles, int x, int y, int width, int height, void(*function)(int));

// Element Editing Functions
void HelperSetElementText(int ElementID, const char *Text);
void HelperSetUpdateFunction(void(*Function)(void), int interval);
void HelperSetTextColor(int R, int G, int B);
void HelperSetElementFont(int ElementID, int FontSize, char *FontName);
void HelperSetElementPosition(int ElementID, int x, int y);

// Miscellaneous
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProcLabel(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void None(int ElementID); // This function exists if the function pointer should do nothing
void Update(void); // This function exists as the default update function