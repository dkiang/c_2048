#define _XOPEN_SOURCE
#define DIM 4
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define QUIT 'q'

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <time.h>

void draw(int board[][DIM]);
void init(int board[][DIM]);
void spawn(int board[][DIM]);
void score(void);
int combine_row(int arr[]);
void move(int board[][DIM], char c);
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
		srand48(time(NULL));
		int board[DIM][DIM] =  {{0, 0, 0, 0},
				                {0, 0, 0, 0},
                                {0, 0, 0, 0},
                                {0, 0, 0, 0}};
		init(board);
		draw(board);
		char c;
		do
		{
			c = get_char("Move: \n");
			move(board, c);
			draw(board);
		}
		while (c != QUIT);
}

// Picks two empty spots and fills them with 2
void init(int board[][DIM])
{
	int counter = 0;
	do
	{
		int x = (int)(drand48() * DIM);
		int y = (int)(drand48() * DIM);
		if (board[x][y] == 0)
		{
			board[x][y] = 2;
			counter++;
		}
	}
	while (counter < 2);
}

// Spawns a new value in an empty space on the board
// 10% chance of a 4, 90% chance of a 2
void spawn(int board[][DIM])
{
	int x = 0;
	int y = 0;
	do
	{
		x = (int)(drand48() * DIM);
		y = (int)(drand48() * DIM);
	}
	while (board[x][y] != 0);
	board[x][y] = (drand48() < 0.100) ? 4 : 2;
}

void draw(int board[][DIM])
{
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			{
			if (board[i][j] == 0)
			{
				printf("%4c",'-');
			}
			else
			{
				printf("%4i",board[i][j]);
			}
		}
		printf("\n");
	}
}

int combine_row(int arr[])
{
	int points = 0;
	int i = 0;
	while (i < DIM - 1)
	{
		int index = i + 1;
		while (arr[index] == 0 && index < DIM - 1)
		{
			index++;
		}
		if (arr[i] == arr[index])
		{
			arr[i] *= 2;
			arr[index] = 0;
			points += arr[i];
			i = index + 1;
		}
		else
		{
			i = index;
		}
	}
	return points;
}

void move(int board[][DIM], char c)
{
	for (int i = 0; i < DIM; i++)
	{
		int temp[DIM];
		// Load temp array from board
		for (int j = 0; j < DIM; j++)
		{
			temp[j] = board[i][j];
		}
		combine_row(temp);
		// Move zeros to left
		for (int k = 0; k < DIM - 1; k++)
		{
			for (int l = k + 1; l < DIM; l++)
			{
				if (temp[k] == 0 && temp[l] > 0)
				{
					temp[k] = temp[l];
					temp[l] = 0;
				}
			}
		}
		switch(c)
		{
			case LEFT:
				// Copy values back into board from left to right
				for (int j = 0; j < DIM; j++)
				{
					board[i][j] = temp[j];
				}
				break;
			case RIGHT:
				// Copy values back into board from right to left
				for (int j = 0; j < DIM; j++)
				{
					board[i][DIM - 1 - j] = temp[j];
				}
				break;
		}
	}
}

// void moveRight(int board[])
// {
// 	for (int i = 0; i < DIM; i++)
// 	{
// 		combine_row(board[i]);

// 		for (int k = 0; k < DIM - 1; k++)
// 		{
// 			for (int l = k + 1; l < DIM; l++)
// 			{
// 				if (board[l] == 0 && board[k] > 0)
// 				{
// 					board[l] = board[k];
// 					board[k] = 0;
// 				}
// 			}
// 		}
// 	}
// }



// #define _XOPEN_SOURCE
// #define DIM 4

// #include <stdio.h>
// #include <cs50.h>
// #include <stdlib.h>
// #include <time.h>

// void draw(int board[]);
// void init(int board[]);
// void spawn(void);
// void score(void);
// void combine_row(int board[]);
// void moveLeft(int board[]);
// void moveRight(int board[]);
// void check(void);
// void play(void);



// int main(void)
// {
//     play();
//     return 0;
// }

// void play(void)
// {
//         int board[4] = {0, 0, 0, 0};
//         init(board);
//         draw(board);
//         char c;
//         do
//         {
//             c = get_char("Move: \n");
//             switch (c)
//             {
//                 case 'a':
//                     moveLeft(board);
//                     break;
//                 case 'd':
//                     moveRight(board);
//                     break;
//             }
//             draw(board);
//         }
//         while (c != 'q');
// }

// void init(int board[])
// {
//     srand48(time(NULL));
//     int counter = 0;
//     do
//     {
//         int place = (int)(drand48() * 4);
//         if (board[place] == 0)
//         {
//             board[place] = (drand48() < 0.100) ? 4 : 2;
//             counter++;
//         }
//     }
//     while (counter < 2);
// }

// void draw(int board[])
// {
//     for (int i = 0; i < 4; i++)
//     {
//         if (board[i] == 0)
//         {
//             printf("%4c",'-');
//         }
//         else
//         {
//             printf("%4i",board[i]);
//         }
//     }
//     printf("\n");
// }

// void combine_row(int board[])
// {
//     int i = 0;
//     int j = 1;
//     while (i < 3)
//     {
//         while (board[j] == 0 && j < 4)
//         {
//             j++;
//         }
//         if (board[i] == board[j])
//         {
//             board[i] *= 2;
//             board[j] = 0;
//         }
//         i = j;
//         j++;
//     }
// }

// void moveLeft(int board[])
// {
//     combine_row(board);
//     for (int k = 0; k < 3; k++)
//     {
//         for (int l = k + 1; l < 4; l++)
//         {
//             if (board[k] == 0 && board[l] > 0)
//             {
//                 board[k] = board[l];
//                 board[l] = 0;
//             }
//         }
//     }
// }

// void moveRight(int board[])
// {
//     combine_row(board);

//     for (int k = 0; k < 3; k++)
//     {
//         for (int l = k + 1; l < 4; l++)
//         {
//             if (board[l] == 0 && board[k] > 0)
//             {
//                 board[l] = board[k];
//                 board[k] = 0;
//             }
//         }
//     }
// }

