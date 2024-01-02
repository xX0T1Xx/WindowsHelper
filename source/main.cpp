#include "WindowsHelper.h"
#include <stdio.h>

int main(void)
{
    HelperRegisterWindow("MyWindowClass");
    HelperCreateWindow("Application", 640, 360);
    HelperSetTextColor(255, 255, 255);

    int label = HelperCreateLabel("This is a label.", 50, 50, 30, NONE);

    int button = HelperCreateButton("Button", 100, 100, 250, 50, NONE);
    HelperSetElementFont(button, 30, "Consolas");

    HelperWindowOnTop();
    HelperStartWindow();
    return 0;
}