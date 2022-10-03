#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int x = rand() % 4 + 1, y = rand() % 4 + 1; // initial random two 2
    srand(time(NULL));
    int table[6][6] = {0};
    table[x][y] = 2;
    table[(x + rand()) % 4 + 1][(y + rand()) % 4 + 1] = 2;
    int tube[6][6];
    int win = 0;
    int movable = 1;
    while (movable == 1 && win == 0)
    {
        for (int i = 1; i < 5; i++) // printf
        {
            for (int j = 1; j < 5; j++)
            {
                int bottle = table[i][j];
                for (int k = 1; k < 5; k++)
                {
                    if (bottle / 10 == 0)
                        printf(" ");
                    bottle /= 10;
                }
                printf("%d ", table[i][j]);
                tube[i][j] = table[i][j];
            }
            printf("\n");
        }

        char kb = ' '; // input
        printf("\ninput (U,D,L,R,F to exit) : ");
        scanf(" %c", &kb);
        printf("\n");
        kb = toupper(kb);

        if (kb == 'F')
        {
            printf("Bye bye.");
            return 0;
        }
        else if (kb != 'U' && kb != 'D' && kb != 'L' && kb != 'R')
        {
            printf("invalid input!\n");
            continue;
        }
        movable = 0;
        for (int i = 1; i < 5; i++) // check movable
        {
            for (int j = 1; j < 5; j++)
            {
                if ((table[i][j] == 0) ||
                    (table[i + 1][j] == table[i][j]) ||
                    (table[i - 1][j] == table[i][j]) ||
                    (table[i][j + 1] == table[i][j]) ||
                    (table[i][j - 1] == table[i][j]))
                {
                    movable = 1;
                    break;
                }
            }
        }
        if (kb == 'U') // Up
        {
            for (int col = 1; col < 5; col++)
            {
                for (int cur = 1; cur < 5; cur++)
                {
                    if (table[cur][col] == 0)
                    {
                        for (int i = cur + 1; i < 5; i++)
                        {
                            if (table[i][col] != 0)
                            {
                                table[cur][col] = table[i][col];
                                table[i][col] = 0;
                                break;
                            }
                        }
                    }
                    if (table[cur][col] != 0)
                    {
                        for (int i = cur + 1; i < 5; i++)
                        {
                            if (table[i][col] == table[cur][col])
                            {
                                table[cur][col] *= 2;
                                win = (table[cur][col] == 2048) ? 1 : 0;
                                table[i][col] = 0;
                                break;
                            }
                            else if (table[i][col] != table[cur][col] && table[i][col] != 0)
                                break;
                        }
                    }
                }
            }
        }
        else if (kb == 'D') // Down
        {
            for (int col = 1; col < 5; col++)
            {
                for (int cur = 4; cur >= 1; cur--)
                {
                    if (table[cur][col] == 0)
                    {
                        for (int i = cur - 1; i >= 1; i--)
                        {
                            if (table[i][col] != 0)
                            {
                                table[cur][col] = table[i][col];
                                table[i][col] = 0;
                                break;
                            }
                        }
                    }
                    if (table[cur][col] != 0)
                    {
                        for (int i = cur - 1; i >= 1; i--)
                        {
                            if (table[i][col] == table[cur][col])
                            {
                                table[cur][col] *= 2;
                                win = (table[cur][col] == 2048) ? 1 : 0;
                                table[i][col] = 0;
                                break;
                            }
                            else if (table[i][col] != table[cur][col] && table[i][col] != 0)
                                break;
                        }
                    }
                }
            }
        }
        else if (kb == 'L') // Left
        {
            for (int col = 1; col < 5; col++)
            {
                for (int cur = 1; cur < 5; cur++)
                {
                    if (table[col][cur] == 0)
                    {
                        for (int i = cur + 1; i < 5; i++)
                        {
                            if (table[col][i] != 0)
                            {
                                table[col][cur] = table[col][i];
                                table[col][i] = 0;
                                break;
                            }
                        }
                    }
                    if (table[col][cur] != 0)
                    {
                        for (int i = cur + 1; i < 5; i++)
                        {
                            if (table[col][i] == table[col][cur])
                            {
                                table[col][cur] *= 2;
                                win = (table[col][cur] == 2048) ? 1 : 0;
                                table[col][i] = 0;
                                break;
                            }
                            else if (table[col][i] != table[col][cur] && table[col][i] != 0)
                                break;
                        }
                    }
                }
            }
        }
        else if (kb == 'R') // Right
        {
            for (int col = 1; col < 5; col++)
            {
                for (int cur = 4; cur >= 1; cur--)
                {
                    if (table[col][cur] == 0)
                    {
                        for (int i = cur - 1; i >= 1; i--)
                        {
                            if (table[col][i] != 0)
                            {
                                table[col][cur] = table[col][i];
                                table[col][i] = 0;
                                break;
                            }
                        }
                    }
                    if (table[col][cur] != 0)
                    {
                        for (int i = cur - 1; i >= 1; i--)
                        {
                            if (table[col][i] == table[col][cur])
                            {
                                table[col][cur] *= 2;
                                win = (table[col][cur] == 2048) ? 1 : 0;
                                table[col][i] = 0;
                                break;
                            }
                            else if (table[col][i] != table[col][cur] && table[col][i] != 0)
                                break;
                        }
                    }
                }
            }
        }
        int same = 1;
        for (int i = 1; i < 5; i++)
        {
            for (int j = 1; j < 5; j++)
            {
                if (tube[i][j] != table[i][j])
                {
                    same = 0;
                    break;
                }
            }
        }
        if (same == 0)
        {
            x = rand() % 4 + 1;
            y = rand() % 4 + 1;
            while (table[x][y] != 0) // rand2
            {
                x = rand() % 4 + 1;
                y = rand() % 4 + 1;
                if (table[x][y] == 0)
                    break;
            }
            table[x][y] = 2;
        }
    }
    if (win == 1)
        printf("You win 2048 Game.");
    else
        printf("Nice try.");
    return 0;
}
