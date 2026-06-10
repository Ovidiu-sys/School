#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>
#include <stdlib.h>

using namespace std;

typedef struct
{
    float x, y;
} punct;

int n; // numarul de puncte

punct p[100];

typedef struct
{
    float x, y;
} vector;

float produs_scalar(vector u, vector v)
{
    return (u.x * v.x + u.y * v.y);
}

float cos_unghi(vector u, vector v)
{
    return (produs_scalar(u, v) /
            (sqrt((produs_scalar(u, u)) * (produs_scalar(v, v)))));
}

int jos_stanga()
{
    int imin = 1, i;

    for (i = 1; i <= n; i++)
    {
        if ((p[i].y < p[imin].y) ||
            ((p[i].y == p[imin].y) && (p[i].x < p[imin].x)))
        {
            imin = i;
        }
    }

    return imin;
}

void initializare()
{
    printf(" dati nr. de puncte n=");
    scanf("%d", &n);

    // PLEACA DE FIECARE DATA DIN ALT PUNCT

    for (int i = 1; i <= n; i++)
    {
        p[i].x = rand() % 500 + 50;
        p[i].y = rand() % 500 + 143;
    }
}

void desenare()
{
    char c[3];
    int i;

    setcolor(1);

    for (i = 1; i <= n; i++)
    {
        itoa(i, c, 10);

        setcolor(1);
        circle(p[i].x, p[i].y, 2);

        setcolor(4);
        outtextxy(p[i].x, p[i].y, c);
    }
}

void drum()
{
    punct aux;
    float cos_max;
    vector dc, vi, viplus1;
    int ord, i;

    int imin = jos_stanga();

    dc.x = 1;
    dc.y = 0;

    aux.x = p[imin].x;
    aux.y = p[imin].y;

    p[imin].x = p[n].x;
    p[imin].y = p[n].y;

    p[n].x = aux.x;
    p[n].y = aux.y;

    p[0].x = p[n].x;
    p[0].y = p[n].y;

    printf("\n Pozitia minimului a fost %d", imin);

    // ordonarea punctelor

    do
    {
        ord = 1;

        for (i = 1; i < n - 1; i++)
        {
            vi.x = p[i].x - p[0].x;
            vi.y = p[i].y - p[0].y;

            viplus1.x = p[i + 1].x - p[0].x;
            viplus1.y = p[i + 1].y - p[0].y;

            if (cos_unghi(vi, dc) < cos_unghi(viplus1, dc))
            {
                ord = 0;

                aux.x = p[i].x;
                aux.y = p[i].y;

                p[i].x = p[i + 1].x;
                p[i].y = p[i + 1].y;

                p[i + 1].x = aux.x;
                p[i + 1].y = aux.y;
            }
        }
    }
    while (ord == 0);

    // afisare drum

    setcolor(2);

    for (i = 0; i < n; i++)
    {
        line(p[i].x, p[i].y, p[i + 1].x, p[i + 1].y);
    }
}

void afisare()
{
    for (int i = 1; i <= n; i++)
    {
        cout << "Punctul " << i << " are coord: "
             << p[i].x << ",\t" << p[i].y << "\n";
    }
}

int main()
{
    initializare();

    // int gd=DETECT,gm;

    // clrscr();

    initwindow(800, 800, "Drum simplu inchis");

    setbkcolor(15);
    cleardevice();

    desenare();
    afisare();
    drum();

    getch();

    closegraph();
}
