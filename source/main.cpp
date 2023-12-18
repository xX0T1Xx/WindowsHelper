#include "WindowsHelper.h"
#include <stdio.h>

int labelID;
int counter = 0;

void fuck() {
    counter++;
    char buffer[20];
    sprintf(buffer, "Counter: %d", counter);
    HelperSetElementText(labelID, buffer);
}

int main(void)
{
    HelperRegisterWindow("MyWindowClass");
    HelperCreateWindow("Window Title", 250, 250);

    labelID = HelperCreateLabel("This is a label", 50, 50, 250, 30, NONE);
    
    HelperSetUpdateFunction(fuck, 250);

    HelperSetTextColor(0, 255, 0);
    HelperSetElementFontSize(labelID, 24);

    HelperWindowOnTop();
    HelperStartWindow();
    return 0;
}