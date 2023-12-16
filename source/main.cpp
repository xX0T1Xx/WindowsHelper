#include "WindowsHelper.h"

void onButton(void) {
    HelperSetElementText(0, "This is the NEW TEXT");
}

int main(void)
{
    HelperRegisterWindow("MyWindowClass");
    HelperCreateWindow("Window Title", 500, 500);
    HelperCreateButton("Close", 0, 0, &onButton);
    HelperCreateLabel("This is some text", 155, 155, NONE);
    HelperStartWindow();
    return 0;
}