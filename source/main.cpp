#include "WindowsHelper.h"
#include <stdio.h>

int main(void)
{
    HelperRegisterWindow("MyWindowClass");
    HelperCreateWindow("Window Title", 500, 500);
    HelperCreateButton("YEET", 250, 250, 50, 50, NONE);
    HelperCreateLabel("YEET", 0, 0, 250, 50, NONE);
    HelperWindowOnTop();
    HelperStartWindow();
    return 0;
}