// 2048 by Douglas Kiang
// 2019

// git add .
// git commit -m "Commit"
// git push -u origin master

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
void shift(int temp[]);

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
			spawn(board);
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

// Looks for duplicate numbers that are adjacent or separated
// by zeroes, combines them, and returns the value of any combined sums.
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

		switch(c)
		{
			case LEFT:
			// Load row into temporary array
    			for (int j = 0; j < DIM; j++)
        		{
        			temp[j] = board[i][j];
        		}

        	    // Combine numbers
        		combine_row(temp);
        		// Shift all zeros to right
        		shift(temp);

				// Copy values back into board from left to right
				for (int j = 0; j < DIM; j++)
				{
					board[i][j] = temp[j];
				}
				break;
			case RIGHT:
    			for (int j = 0; j < DIM; j++)
        		{
        			temp[j] = board[i][DIM - 1 - j];
        		}
        		combine_row(temp);
        		shift(temp);
				// Copy values back into board from right to left
				for (int j = 0; j < DIM; j++)
				{
					board[i][DIM - 1 - j] = temp[j];
				}
				break;
			case UP:
    			for (int j = 0; j < DIM; j++)
        		{
        			temp[j] = board[j][i];
        		}
        		combine_row(temp);
        		shift(temp);
				// Copy values back into column from up to down
				for (int j = 0; j < DIM; j++)
				{
					board[j][i] = temp[j];
				}
				break;
			case DOWN:
    			for (int j = 0; j < DIM; j++)
        		{
        			temp[j] = board[DIM - 1 - j][i];
        		}
        		combine_row(temp);
        		shift(temp);
				// Copy values back into column from down to up
				for (int j = 0; j < DIM; j++)
				{
					board[DIM - 1 - j][i] = temp[j];
				}
				break;
		}
	}
}

// Moves all zeros in array to the right
void shift(int temp[])
{
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
}
