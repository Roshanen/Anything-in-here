#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int table[6][6] = {0};
int tube[6][6];
int win = 0;
int x = 0, y = 0;
char kb = ' ';
void set_table()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
            table[i][j] = 0;
    }
    table[rand() % 4 + 1][rand() % 4 + 1] = 2;
    table[rand() % 4 + 1][rand() % 4 + 1] = 2;
}
void print_table()
{
    for (int i = 1; i < 5; i++) // printf
    {
        for (int j = 1; j < 5; j++)
        {
            int digit = table[i][j];
            for (int k = 1; k < 5; k++)
            {
                if (digit / 10 == 0)
                    printf(" ");
                digit /= 10;
            }
            printf("%d ", table[i][j]);
            tube[i][j] = table[i][j];
        }
        printf("\n");
    }
}
int movable()
{
    for (int i = 1; i < 5; i++) // check movable
    {
        for (int j = 1; j < 5; j++)
        {
            if ((table[i + 1][j] == table[i][j]) ||
                (table[i - 1][j] == table[i][j]) ||
                (table[i][j + 1] == table[i][j]) ||
                (table[i][j - 1] == table[i][j]))
                return 1;
        }
    }
    return 0;
}
int zero()
{
    for (int i = 1; i < 5; i++) // check movable
    {
        for (int j = 1; j < 5; j++)
        {
            if (table[i][j] == 0)
                return 1;
        }
    }
    return 0;
}
int same()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (tube[i][j] != table[i][j])
                return 0;
        }
    }
    return 1;
}
void random2()
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
    table[x][y] = (rand() % 100 >= 20) ? 2 : 4;
}
int main()
{
    srand(time(NULL));
    while (1)
    {
        set_table();
        win = 0;
        while (movable() == 1 || zero() == 1)
        {
            print_table();
            kb = ' ';
            printf("\ninput ((W)U, (X)D, (A)L, (D)R, F to exit) : ");
            scanf(" %c", &kb);
            fflush(stdin);
            printf("\n");
            if (kb == 'F' || kb == 'f')
            {
                printf("Bye bye.");
                return 0;
            }
            else if (kb != 'A' && kb != 'W' && kb != 'S' && kb != 'D' &&
                     kb != 'a' && kb != 'w' && kb != 's' && kb != 'd')
            {
                printf("invalid input!\n");
                continue;
            }
            if (kb == 'W' || kb == 'w') // Up
            {
                for (int col = 1; col < 5; col++) // k
                {
                    for (int cur = 1; cur < 5; cur++) // cur =
                    {
                        if (table[cur][col] == 0) // 1 2 3 4
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
            else if (kb == 'S' || kb == 's') // Down
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
            else if (kb == 'A' || kb == 'a') // Left
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
            else if (kb == 'D' || kb == 'd') // Right
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
            if (win == 1)
                break;
            if (zero() == 1 && same() == 0)
                random2();
        }
        if (win == 1)
        {
            print_table();
            printf("You win 2048 Game.\n");
            printf("Again (Y/else)? : ");
            scanf("%c", &kb);
            if (kb == 'Y' || kb == 'y')
                continue;
            else
                break;
        }
        else if (movable() == 0)
        {
            print_table();
            printf("Nice try.\n");
            printf("Again (Y/N)? : ");
            scanf("%c", &kb);
            if (kb == 'Y' || kb == 'y')
                continue;
            else
                break;
        }
    }
    return 0;
}
