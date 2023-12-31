#include "WindowsHelper.h"
#include <stdio.h>

int labelID;
int buttonID;
int counter = 0;

void count() {
    counter++;
    char buffer[20];
    sprintf(buffer, "Counter: %d", counter);
    HelperSetElementText(labelID, buffer);
}

int main(void)
{
    HelperRegisterWindow("MyWindowClass");
    HelperCreateWindow("Window Title", 640, 360);
    HelperSetTextColor(255, 255, 255);

    labelID = HelperCreateLabel("Counter: 0", 50, 50, 250, 50, NONE);
    HelperSetElementFontSize(labelID, 50);

    HelperSetUpdateFunction(count, 1000);

    HelperWindowOnTop();
    HelperStartWindow();
    return 0;
}