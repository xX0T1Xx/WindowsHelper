#include "WindowsHelper.h"
#include <stdio.h>

int labelID;
int labelID2;
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

    labelID = HelperCreateLabel("Counter: 0", 50, 50, 250, 20, NONE);
    labelID2 = HelperCreateLabel("This is some example text ", 50, 80, 223, 20, NONE);

    HelperSetElementFontSize(labelID, 24);
    HelperSetElementFontSize(labelID2, 24);


    HelperSetUpdateFunction(count, 1000);

    HelperWindowOnTop();
    HelperStartWindow();
    return 0;
}