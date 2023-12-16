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
extern std::vector<void(*)(void)> FUNCTION_POINTER_ID; // Pointers to the void function for each element
extern std::vector<HWND> ELEMENTS; // Contains handle to all elements added to the window

// Global Functions
void HelperRegisterWindow(const char *ClassName);
void HelperCreateWindow(const char *WindowTitle, const uint32_t width, const uint32_t height);
void HelperStartWindow(void);
int HelperCreateButton(const char *ButtonText, const uint32_t x, const uint32_t y, void(*function)(void));
int HelperCreateLabel(const char *LabelText, const uint32_t x, const uint32_t y, void(*function)(void));
void HelperSetElementText(int ElementID, const char *Text);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void None(void); // This function exists if the function pointer should do nothing