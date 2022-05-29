#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

const int x = 211;
const int y = 49;
int Enemies = 2;
int EnemiesAlive = Enemies;
int wave = 0;
string screen[y][x];
bool game = true;
string RiadkovyText = "";
int spawner = 0;



string randomTextury[] = { "X","$","+","*" };

//bullety
vector<int> BulletL;

void farba(int);

void clear();

void draw();

void pozadie();

void playerDraw(int, int, int, int, string);

int random(int a, int b);









void clear()
{
    system("CLS");
}


void draw()
{
    for (int i = 0; i < y; i++)

    {
        for (int j = 0; j < x; j++)
        {
            RiadkovyText += screen[i][j];
        }
        cout << RiadkovyText << endl;
        RiadkovyText = "";
    }


}
void pozadie()
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    screen[i][j] = "#";
                    continue;
                }
                if (j == x - 1)
                {
                    screen[i][j] = "#";
                    continue;
                }
                screen[i][j] = "-";
            }
            else if (i == y - 1)
            {
                if (j == 0)
                {
                    screen[i][j] = "#";
                    continue;
                }

                if (j == x - 1)
                {
                    screen[i][j] = "#";
                    continue;
                }
                screen[i][j] = "-";
            }
            else if (j == 0)
            {

                screen[i][j] = "|";
            }
            else if (j == x - 1)
            {
                screen[i][j] = "|";
            }
            else
            {
                screen[i][j] = ' ';
            }
        }
    }
}


void playerDraw(int x, int y, int W, int H, string rotation)
{

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (i == 0)
            {
                if (j == 0 || j == W - 1)
                {
                    screen[y + i][x + j] = " ";
                    continue;
                }
            }
            if (i == H - 1)
            {
                if (j == 0 || j == W - 1)
                {
                    screen[y + i][x + j] = " ";
                    continue;
                }
            }


            screen[y + i][x + j] = "M";
        }
    }
    if (rotation == "vpravo")
    {
        screen[y + (H / 2)][x + W] = "-";
        screen[y + (H / 2)][x + W + 1] = "-";
    }
    if (rotation == "vlavo")
    {
        screen[y + (H / 2)][x - 1] = "-";
        screen[y + (H / 2)][x - 2] = "-";
    }
    if (rotation == "hore")
    {
        screen[y - 1][x + (W / 2)] = "\u007C";
    }
    if (rotation == "dole")
    {
        screen[y + H][x + (W / 2)] = "\u007C";
    }
}








int random(int a, int b)
{

    int randomNum = rand() % b + a;
    return randomNum;

}


