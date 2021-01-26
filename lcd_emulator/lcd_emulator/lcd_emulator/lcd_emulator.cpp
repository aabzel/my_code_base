#include<stdio.h>
#include<conio.h>
#include<graphics.h>

int main()
{
    float x, y;

    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode,(char *) "");

    x = -10;
    moveto(x, x * x);

    do
    {
        y = x * x;
        lineto(x * 50 + getmaxx() / 2, getmaxy() / 2 - (y * 20));
        x = x + 0.02;
    } while (x < 10);

    closegraph();
    return 0;
}