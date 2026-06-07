
#include "SDLWindow.h"

int main()
{
    SDLWindow window{};

    while (window.GetShouldContinue())
    {
        window.Update();
    }

    return 0;
}