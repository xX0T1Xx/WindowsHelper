#include "WindowsHelper.h"
#include <stdio.h>

int main(void)
{
    HelperRegisterWindow("MyWindowClass");
    HelperCreateWindow("Window Title", 250, 250);

    HelperCreateLabel("This is a label", 100, 50, 125, 15, NONE);
    HelperCreateButton("Button", 100, 175, 50, 50, NONE);
    
    
    HelperWindowOnTop();


    HelperStartWindow();
    return 0;
}