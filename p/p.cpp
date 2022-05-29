#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "header.h"
#include <ctype.h>
using namespace std;













class player {
public:
    int x = 103;
    int y = 22;
    int width = 5;
    int height = 3;
    int health = 1;

    int speedY = 1;
    int speedX = 2;


    int fireRate = 5;
    int fireCounter = 5;




    string rotation = "vpravo";



};

class Bullet {
public:
    int x;
    int y;
    int dmg = 1;
    int speedX = 4;
    int speedY = 2;


    string rot;
    string tvar;
    bool exist = true;

    Bullet(int playerX, int playerY, string rotation, int playerW, int playerH, bool Exist)
    {

        if (rotation == "vpravo")
        {
            x = playerX + playerW + 2;
            y = playerY + (playerH / 2);
        }
        else if (rotation == "vlavo")
        {
            x = playerX - 3;
            y = playerY + (playerH / 2);
        }
        else if (rotation == "hore")
        {
            x = playerX + (playerW / 2);
            y = playerY - 2;
        }
        else if (rotation == "dole")
        {
            x = playerX + (playerW / 2);
            y = playerY + playerH + 1;
        }

        rot = rotation;
        exist = Exist;
        tvar = "o";

    }



};
//---------ENEMY-------------
class Enemy {
public:
    int x;
    int y;

    int width = 5;
    int height = 3;

    bool alive = true;
    int health = 1;
    int dmg;
    int speedX = 2;
    int speedY = 1;

    int EnemySlower = 2;
    int EnemySlowerTick = 0;
    int smer = 0;
};

int kills = 0;



int main() {



    player player;

    typedef std::vector<Bullet> bullet_list_t;

    bullet_list_t bullet_list;


    typedef std::vector<Enemy> enemy_list_t;
    Enemy enemy;
    // Create the vector.
    enemy_list_t enemy_list;




    while (game)
    {
        srand(time(NULL) + random(0, 500));

        Bullet bullet(player.x, player.y, player.rotation, player.width, player.height, true);


        //-----------------dynamicka aktualizacia pre constructor----------
        player.fireCounter += 1;




        if (GetKeyState('D') & 0x8000)
        {
            if (player.x < x - player.speedX - player.width - 1)
            {
                player.x += player.speedX;
            }
        }
        if (GetKeyState('A') & 0x8000)
        {
            if (player.x > 0 + player.speedX + 1)
            {
                player.x -= player.speedX;
            }

        }
        if (GetKeyState('W') & 0x8000)
        {
            if (player.y > 0 + player.speedY + 1)
            {
                player.y -= player.speedY;
            }
        }
        if (GetKeyState('S') & 0x8000)
        {
            if (player.y < y - player.speedY - player.height - 1)
            {
                player.y += player.speedY;
            }
        }
        //-----------rotacia-----------
        if (GetKeyState('L') & 0x8000)
        {
            player.rotation = "vpravo";
        }
        else if (GetKeyState('J') & 0x8000)
        {
            player.rotation = "vlavo";
        }
        else if (GetKeyState('I') & 0x8000)
        {
            player.rotation = "hore";
        }
        else if (GetKeyState('K') & 0x8000)
        {
            player.rotation = "dole";
        }
        if (GetKeyState(32) & 0x8000) // t.j. medzerník

        {




            //prida bullet

            if (player.fireCounter >= player.fireRate)
            {
                bullet_list.push_back(bullet);
                player.fireCounter = 0;




            }


        }

        if (GetKeyState(27) & 0x8000) // esc
        {
            game = false;
            char close = ' ';
            cout << "close?(Y/N)";
            cin >> close;
            close = ((char)toupper(close));
            if (close == 'Y')
                break;
            else
                game = true;
        }



        //----------HIT-------------------
        for (int enemy = 0; enemy < enemy_list.size(); enemy++)
        {
            if (enemy_list[enemy].alive)
            {
                for (int bullet = 0; bullet < bullet_list.size(); bullet++)
                {
                    if (bullet_list[bullet].exist)
                    {
                        if (bullet_list[bullet].x >= enemy_list[enemy].x)
                        {
                            if (bullet_list[bullet].x <= enemy_list[enemy].x + enemy_list[enemy].width)
                            {
                                if (bullet_list[bullet].y >= enemy_list[enemy].y)
                                {
                                    if (bullet_list[bullet].y <= enemy_list[enemy].y + enemy_list[enemy].height)
                                    {

                                        enemy_list[enemy].health -= bullet_list[bullet].dmg;
                                        bullet_list[bullet].exist = false;

                                        if (enemy_list[enemy].health <= 0)
                                        {
                                            enemy_list[enemy].alive = false;
                                            kills++;

                                        }

                                    }
                                }

                            }
                        }

                    }
                }
            }
        }
        //--------KONTROLA ALIVE ENEMAKOV A KONIEC KOLA -------------
        EnemiesAlive = 0;
        for (int i = 0; i < enemy_list.size(); i++)
        {
            if (enemy_list[i].alive) {
                EnemiesAlive += 1;
            }
        }







        //-----------ENEMY MOVE----------------------

        for (int enemy = 0; enemy < enemy_list.size(); enemy++)
        {

            if (enemy_list[enemy].alive)
            {
                if (enemy_list[enemy].EnemySlowerTick >= enemy_list[enemy].EnemySlower)
                {

                    if (enemy_list[enemy].smer == 0)
                    {
                        if (enemy_list[enemy].y - enemy_list[enemy].speedY <= 0)
                        {
                            enemy_list[enemy].alive = false;

                        }
                        else
                        {
                            enemy_list[enemy].y -= enemy_list[enemy].speedY;
                        }
                    }
                    if (enemy_list[enemy].smer == 1)
                    {
                        if (enemy_list[enemy].y - enemy_list[enemy].speedY <= 0)
                        {

                            if (enemy_list[enemy].x + enemy_list[enemy].width + enemy_list[enemy].speedX >= x)

                            {
                                enemy_list[enemy].alive = false;
                                continue;
                            }
                            enemy_list[enemy].alive = false;
                            continue;

                        }
                        enemy_list[enemy].y -= enemy_list[enemy].speedY;
                        enemy_list[enemy].x += enemy_list[enemy].speedX;
                    }
                    if (enemy_list[enemy].smer == 2)
                    {
                        if (enemy_list[enemy].x + enemy_list[enemy].width + enemy_list[enemy].speedX >= x)
                        {
                            enemy_list[enemy].alive = false;

                        }
                        else
                        {
                            enemy_list[enemy].x += enemy_list[enemy].speedX;
                        }
                    }
                    if (enemy_list[enemy].smer == 3)
                    {
                        if (enemy_list[enemy].y + enemy_list[enemy].height + enemy_list[enemy].speedY >= y)
                        {

                            if (enemy_list[enemy].x + enemy_list[enemy].width + enemy_list[enemy].speedX >= x)

                            {
                                enemy_list[enemy].alive = false;
                                continue;
                            }
                            enemy_list[enemy].alive = false;
                            continue;

                        }
                        enemy_list[enemy].y += enemy_list[enemy].speedY;
                        enemy_list[enemy].x += enemy_list[enemy].speedX;
                    }
                    if (enemy_list[enemy].smer == 4)
                    {

                        if (enemy_list[enemy].y + enemy_list[enemy].height + enemy_list[enemy].speedY >= y)
                        {
                            enemy_list[enemy].alive = false;

                        }
                        else
                        {
                            enemy_list[enemy].y += enemy_list[enemy].speedY;
                        }
                    }
                    if (enemy_list[enemy].smer == 5)
                    {

                        if (enemy_list[enemy].y + enemy_list[enemy].height + enemy_list[enemy].speedY >= y)
                        {

                            if (enemy_list[enemy].x - enemy_list[enemy].speedX <= 0)

                            {
                                enemy_list[enemy].alive = false;
                                continue;
                            }
                            enemy_list[enemy].alive = false;
                            continue;

                        }
                        enemy_list[enemy].y += enemy_list[enemy].speedY;
                        enemy_list[enemy].x -= enemy_list[enemy].speedX;
                    }
                    if (enemy_list[enemy].smer == 6)
                    {
                        if (enemy_list[enemy].x - enemy_list[enemy].speedX <= 0)
                        {
                            enemy_list[enemy].alive = false;

                        }
                        else
                        {
                            enemy_list[enemy].x -= enemy_list[enemy].speedX;
                        }
                    }
                    if (enemy_list[enemy].smer == 7)
                    {
                        if (enemy_list[enemy].y - enemy_list[enemy].speedY <= 0)
                        {

                            if (enemy_list[enemy].x - enemy_list[enemy].speedX <= 0)

                            {
                                enemy_list[enemy].alive = false;
                                continue;
                            }
                            enemy_list[enemy].alive = false;
                            continue;

                        }
                        enemy_list[enemy].y -= enemy_list[enemy].speedY;
                        enemy_list[enemy].x -= enemy_list[enemy].speedX;
                    }



                    enemy_list[enemy].EnemySlowerTick = 0;

                }

                enemy_list[enemy].EnemySlowerTick++;
            }
        }

        spawner++;
        if (spawner > 20) {
            printf("novy enemy");
            spawner = 0;
        }

        if (EnemiesAlive == 0)
        {
            enemy_list.clear();
            wave += 1;
            Enemies += wave;

            //----------SPAWN----------------

            for (int i = 0; i < Enemies; i++)
            {
                int r = random(0, 4);

                if (r == 0)
                {
                    enemy_list.push_back(enemy);
                    enemy_list[i].y = 1;
                    enemy_list[i].x = random(1, 203);
                    int smer = random(0, 3);

                    switch (smer)
                    {
                    case 0:
                        enemy_list[i].smer = 5;
                        break;
                    case 1:
                        enemy_list[i].smer = 4;
                        break;
                    case 2:
                        enemy_list[i].smer = 3;
                        break;
                    }


                }
                else if (r == 1)
                {
                    enemy_list.push_back(enemy);
                    enemy_list[i].x = 1;
                    enemy_list[i].y = random(1, 44);
                    int smer = random(0, 3);

                    switch (smer)
                    {
                    case 0:
                        enemy_list[i].smer = 1;
                        break;
                    case 1:
                        enemy_list[i].smer = 2;
                        break;
                    case 2:
                        enemy_list[i].smer = 3;
                        break;
                    }

                }
                else if (r == 2)
                {
                    enemy_list.push_back(enemy);
                    enemy_list[i].y = 45;
                    enemy_list[i].x = random(1, 205);
                    int smer = random(0, 3);
                    switch (smer)
                    {
                    case 0:
                        enemy_list[i].smer = 7;
                        break;
                    case 1:
                        enemy_list[i].smer = 0;
                        break;
                    case 2:
                        enemy_list[i].smer = 1;
                        break;

                    }

                }
                else if (r == 3)
                {
                    enemy_list.push_back(enemy);
                    enemy_list[i].y = random(1, 45);
                    enemy_list[i].x = 205;
                    int smer = random(0, 3);

                    switch (smer)
                    {
                    case 0:
                        enemy_list[i].smer = 7;
                        break;
                    case 1:
                        enemy_list[i].smer = 6;
                        break;
                    case 2:
                        enemy_list[i].smer = 5;
                        break;

                    }

                }
                enemy_list[i].EnemySlower = random(1, 3);
                enemy_list[i].dmg = random(1, 3);

            }

        }

        //-------------ENEMY touch -------------------------
        for (int enemy = 0; enemy < enemy_list.size(); enemy++)
        {
            if (enemy_list[enemy].alive)
            {
                if (enemy_list[enemy].x + enemy_list[enemy].width >= player.x)
                {
                    if (enemy_list[enemy].x <= player.x + player.width)
                    {
                        if (enemy_list[enemy].y + enemy_list[enemy].height >= player.y)
                        {
                            if (enemy_list[enemy].y <= player.y + player.height)
                            {

                                player.health = 0;

                            }
                        }
                    }
                }
            }
        }





        pozadie();

        playerDraw(player.x, player.y, player.width, player.height, player.rotation);














        //bullet draw
        for (int i = 0; i < bullet_list.size(); i++)
        {
            if (bullet_list[i].exist)
            {

                int By = bullet_list[i].y;
                int Bx = bullet_list[i].x;
                string Bt = bullet_list[i].tvar;
                string Br = bullet_list[i].rot;





                screen[By][Bx] = Bt;

                //bullet move
                if (Br == "vpravo")
                {
                    if (Bx < 211 - bullet_list[i].speedX) {
                        bullet_list[i].x += bullet_list[i].speedX;
                    }
                    else {
                        bullet_list[i].exist = false;
                    }
                }
                else if (Br == "vlavo")
                {
                    if (Bx > 0 + bullet_list[i].speedX) {
                        bullet_list[i].x -= bullet_list[i].speedX;
                    }
                    else {
                        bullet_list[i].exist = false;
                    }
                }
                else if (Br == "hore")
                {
                    if (By > 0 + bullet_list[i].speedY) {
                        bullet_list[i].y -= bullet_list[i].speedY;
                    }
                    else {
                        bullet_list[i].exist = false;
                    }
                }
                else if (Br == "dole")
                {
                    if (By < 49 - bullet_list[i].speedY) {
                        bullet_list[i].y += bullet_list[i].speedY;
                    }
                    else {
                        bullet_list[i].exist = false;
                    }
                }
            }

        }




        //------------ENEMY-------------------
        for (int k = 0; k < enemy_list.size(); k++)
        {
            if (enemy_list[k].alive)
            {
                for (int i = 0; i < enemy_list[k].width; i++)
                {
                    for (int j = 0; j < enemy_list[k].height; j++)
                    {
                        if (j == 0)
                        {
                            if (i == 0 || i == enemy_list[k].width - 1)
                            {
                                screen[enemy_list[k].y + j][enemy_list[k].x + i] = " ";
                                continue;
                            }
                        }
                        else if (j == enemy_list[k].height - 1)
                        {
                            if (i == 0 || i == enemy_list[k].width - 1)
                            {
                                screen[enemy_list[k].y + j][enemy_list[k].x + i] = " ";
                                continue;
                            }
                        }



                        screen[enemy_list[k].y + j][enemy_list[k].x + i] = randomTextury[random(0, (sizeof(randomTextury) / sizeof(randomTextury[0])))];

                    }
                }
            }
        }





        if (player.health == 0)
        {
            game = false;
            clear();
            pozadie();
            screen[y / 2][103] = "K";
            screen[y / 2][104] = "O";
            screen[y / 2][105] = "N";
            screen[y / 2][106] = "I";
            screen[y / 2][107] = "E";
            screen[y / 2][108] = "C";
            while (true)
            {
                draw();
                cout << "score: " << kills;
                clear();
            }
        }



        clear();
        cout << "Points: " << kills << "\t " << player.health << endl;
        draw();

    }


    clear();
    return 0;
}