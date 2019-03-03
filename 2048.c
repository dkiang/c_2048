#define _XOPEN_SOURCE
#define DIM 4

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <time.h>

void draw(int board[]);
void init(int board[]);
void spawn(void);
void score(void);
void moveLeft(int board[]);
void moveRight(int board[]);
void check(void);
void play(void);



int main(void)
{
    play();
    return 0;
}

void play(void)
{
        int board[4] = {0, 0, 0, 0};
        init(board);
        draw(board);
        char c;
        do
        {
            c = get_char("Move: \n");
            switch (c)
            {
                case 'a':
                    moveLeft(board);
                    break;
                case 'd':
                    //moveRight(board);
                    break;
            }
            draw(board);
        }
        while (c != 'q');
}

void init(int board[])
{
    srand48(time(NULL));
    int counter = 0;
    do
    {
        int place = (int)(drand48() * 4);
        if (board[place] == 0)
        {
            board[place] = (drand48() < 0.100) ? 4 : 2;
            counter++;
        }
    }
    while (counter < 2);
}

void draw(int board[])
{
    for (int i = 0; i < 4; i++)
    {
        if (board[i] == 0)
        {
            printf("%4c",'-');
        }
        else
        {
            printf("%4i",board[i]);
        }
    }
    printf("\n");
}

void moveLeft(int board[])
{
    int i = 0;
    int j = 1;
    while (i < 3)
    {
        while (board[j] == 0 && j < 4)
        {
            j++;
        }
        if (board[i] == board[j])
        {
            board[i] *= 2;
            board[j] = 0;
        }
        i = j;
        j++;
    }

    for (int k = 0; k < 3; k++)
    {
        for (int l = k + 1; l < 4; l++)
        {
            if (board[k] == 0 && board[l] > 0)
            {
                board[k] = board[l];
                board[l] = 0;
            }
        }
    }
}

// void moveRight(int board[])
// {
//     for (int i = 0; i < 3; i++)
//     {
//         if (board[i] == board[i + 1])
//         {
//             board[i] *= 2;
//             board[i + 1] = 0;
//         }
//     }


    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = i + 1; j < 4; j++)
    //     {
    //         if (board[j] == 0 && board[i] > 0)
    //         {
    //             board[j] = board[i];
    //             board[i] = 0;
    //         }
    //     }
    // }
// }

