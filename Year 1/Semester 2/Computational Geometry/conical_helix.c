#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define pi 3.1415

float x1, x2, yy1, yy2, alfa = 3.1415 / 8;
int xemax, yemax;

int xe(float x) // normalizarea coordonatei x
{
    return ((int)floor((x - x1) / (x2 - x1) * xemax));
}

int ze(float z) // normalizarea coordonatei y
{
    return ((int)floor((yy2 - z) / (yy2 - yy1) * yemax));
}

void putpixel3D(float x, float y, float z, int c)
{
    putpixel(xe(x - y * cos(alfa)),
             ze(z - y * sin(alfa)),
             c);
}

void line3d(float x0, float y0, float z0,
            float x, float y, float z)
{
    line(
        xe(x0 - y0 * cos(alfa)),
        ze(z0 - y0 * sin(alfa)),
        xe(x - y * cos(alfa)),
        ze(z - y * sin(alfa))
    );
}

void axe()
{
    setcolor(11);

    outtextxy(xe(0) - 15, ze(0) - 15, "O");
    outtextxy(xe(x2) - 20, ze(0) - 20, "x");
    outtextxy(xe(x2) - 6, ze(0) - 7, ">");
    outtextxy(xe(0) + 15, ze(yy2) + 5, "z");
    outtextxy(xe(0) - 1, ze(yy2) + 1, "^");
    outtextxy(xe(x1 * cos(alfa)), ze(x1 * sin(alfa)), "y");

    line3d(0, 0, 0, x2, 0, 0);
    line3d(0, 0, 0, 0, x2, 0);
    line3d(0, 0, 0, 0, 0, yy2);
}

void grafic()
{
    int i, j, N = 4000;

    float t, h, theta = 3.1415 / 36;
    float x[5000], y[5000], z[5000];
    float pie = 3.1415;
    float xaux, zaux;

    t = 0;
    h = pie / 600;

    for (i = 0; i < N; i++)
    {
        x[i] = 0.2 * t * cos(3 * t);
        y[i] = 0.2 * t * sin(3 * t);
        z[i] = 0.4 * t;
        t = t + h;
    }

    for (j = 0; j < 15; j++)
    {
        for (i = 0; i < N; i++)
            putpixel3D(x[i], y[i], z[i], 14);

        getch();

        for (i = 0; i < N; i++)
            putpixel3D(x[i], y[i], z[i], 0); // sterge

        for (i = 0; i < N; i++)
        {
            xaux = x[i] * cos(theta) + z[i] * sin(theta);
            zaux = -x[i] * sin(theta) + z[i] * cos(theta);

            x[i] = xaux;
            z[i] = zaux;
        }
    }
}

int main()
{
    printf("Limitele domeniului orizontal:\n");

    printf("x1=");
    scanf("%f", &x1);

    printf("x2=");
    scanf("%f", &x2);

    yy1 = x1;
    yy2 = x2;

    initwindow(800, 800, "Elice simpla", 200, 200);

    xemax = getmaxx();
    yemax = getmaxy();

    axe();

    setcolor(YELLOW);

    grafic();

    getch();
    getch();

    closegraph();

    return 0;
}
