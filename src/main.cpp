#include <time.h>
#include <stdlib.h>

#include "win_glfw.h"
#include "win_freeglut.h"

#include "ad_openal.h"

int main(void)
{
    srand(time(0));

    //AudioSystemAL audioOpenAL("./samples/iamtheprotectorofthissystem.wav");
    //AudioSystemAL audioOpenAL("./samples/drums.mp3");
    AudioSystemAL audioOpenAL("./samples/sample.ogg");
    //AudioSystemAL audioOpenAL("./samples/sample4.aiff");
    //AudioSystemAL audioOpenAL("./samples/sample4.flac");

    //WinGLFW glfw;
    //glfw.run();

    WinFreeGLUT glut;
}