#include <time.h>
#include <stdlib.h>

#include "win_glfw.h"

int main(void)
{
    srand(time(0));

    WinGLFW glfw;
    glfw.run();
}