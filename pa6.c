#include "pa6.h"

void welcome_screen(void)
{
	printf("-----B A T T L E S H I P-----\n");
	printf("Rules:\n");
	printf("1. This is a 2 player game, 'Player1' is the computer and 'Player2' is the computer.\n");
	printf("2. Each player will have a 10x10 board with 5 different ships to place.\n");
	printf("3. Ships can only be placed horizontal or vertically.\n");
	printf("4. On the board, each piece represents one part of the ships.\n");
	printf("5. 'c' indicates carrier, 'b' for battleship, 'r' for cruiser, 's' for submarine, or 'd' for destroyer.\n");
	printf("6. A miss will be represented with 'm', and a hit will be represented with an 'h'.\n");
	printf("7. Whoever destroys the other player's entire fleet first wins.\n");
	system("pause");
	system("cls");
}

void initialize_game_board(char *board1[][10], char *board2[][10])
{

	int i = 0, j = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			board1[i][j] = '~';
			board2[i][j] = '~';
		}
	}

	display_board(&board1, &board2, 3);
}

int select_starter(void)
{
	int result = rand();
	result = (result % 2) + 1;

	return result;
}

void display_board(char *board1[][10], char *board2[][10], int disp_plr)
{
	printf("       -User's Board-\n");
	printf("     0 1 2 3 4 5 6 7 8 9\n");
	printf("    ----------------------\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d  | ", i);
		for (int j = 0; j < 10; j++)
		{
			if (disp_plr == 2 || disp_plr == 3)
			{
				if (board1[i][j] == '*' || board1[i][j] == 'm')
				{
					printf("%c ", board1[i][j]);
				}
				else
				{
					printf("~ ");
				}
			}
			else
			{
				printf("%c ", board1[i][j]);
			}
		}
		printf("|\n");
	}
	printf("   -----------------------\n\n");

	printf("     -Computer's Board-\n");
	printf("     0 1 2 3 4 5 6 7 8 9\n");
	printf("    ----------------------\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d  | ", i);
		for (int j = 0; j < 10; j++)
		{
			if (disp_plr == 1 || disp_plr == 3)
			{
				if (board2[i][j] == '*' || board2[i][j] == 'm')
				{
					printf("%c ", board2[i][j]);
				}
				else
				{
					printf("~ ");
				}
			}
			else
			{
				printf("%c ", board2[i][j]);
			}
		}
		printf("|\n");
	}
	printf("   -----------------------\n");
}

void ship_placement(char *board[][10], int type, char ship[], int ship_num)
{

	int i = 1, j = 0, row1 = 0, row2 = 0, col1 = 0, col2 = 0, row = -1,
		col = -1, main_check = 0, loop_check = 0;

	if (type == 1)
	{
		while (main_check == 0)
		{
			row = -1;
			col = -1;
			loop_check = 0;
			while (loop_check == 0)
			{
				printf("Please enter the starting cell for the %s (row col): \n", ship);
				scanf("%d %d", &row, &col);
				if (row >= 0 && row <= 9 && col >= 0 && col <= 9)
				{
					if (board[row][col] == '~')
					{
						row1 = row;
						col1 = col;
						loop_check = 1;
					}
					else
					{
						printf("You can't place a ship there!\n");
					}
				}
				else
				{
					printf("This isn't a valid position!\n");
				}
			}

			row = -1;
			col = -1;
			loop_check = 0;

			while (loop_check == 0)
			{
				printf("Please enter the ending cell for the %s (row col): \n", ship);
				scanf("%d %d", &row, &col);
				if (row >= 0 && row <= 9 && col >= 0 && col <= 9)
				{
					if (board[row][col] == '~')
					{
						row2 = row;
						col2 = col;
						loop_check = 1;
					}
					else
					{
						printf("You can't place a ship there!\n");
					}
				}
				else
				{
					printf("This isn't a valid position!\n");
				}
			}
			if (row2 - row1 == ship_num || col2 - col1 == ship_num)
			{
				int counter = 0;
				for (i = row1; i < row2; i++)
				{
					if (board[i][j] == '~')
					{
						if (ship[0] == 'C' && ship[1] == 'r')
						{
							board[i][j] = 'R';
							counter += 1;
						}
						else
						{
							board[i][j] = ship[0];
							counter += 1;
						}
					}
				}
				for (j = col1; j < col2; j++)
				{
					if (board[i][j] == '~')
					{
						if (ship[0] == 'C' && ship[1] == 'r')
						{
							board[i][j] = 'R';
							counter += 1;
						}
						else
						{
							board[i][j] = ship[0];
							counter += 1;
						}
					}
				}
				if (counter == ship_num && (row2 != row1 || col2 != col1))
				{
					main_check = 1;
				}
				else
				{
					printf("This isn't a valid placement area!\n");
				}
			}
			else
			{
				printf("This isn't a valid placement area!\n");
			}
		}
	}
	else if (type == 2)
	{
		int direction = rand();
		direction = (direction % 2) + 1;

		while (main_check == 0)
		{
			int pos_check = 0;
			while (pos_check == 0)
			{
				row1 = rand();
				row1 = (row1 % 9);
				col1 = rand();
				col1 = (col1 % 9);
				if (direction == 1)
				{
					row2 = row1 + ship_num;
					col2 = col1;
				}
				else if (direction == 2)
				{
					row2 = row1;
					col2 = col1 + ship_num;
				}
				if (board[row1][col1] == '~' && col2 < 10 && row2 < 10)
				{
					pos_check = 1;
				}
			}
			if (row2 - row1 == ship_num || col2 - col1 == ship_num)
			{
				int counter = 0;
				for (i = row1; i < row2; i++)
				{
					if (board[i][j] == '~')
					{
						counter += 1;
					}
				}
				for (j = col1; j < col2; j++)
				{
					if (board[i][j] == '~')
					{
						counter += 1;
					}
				}
				if (counter == ship_num && (row2 != row1 || col2 != col1))
				{
					main_check = 1;
					for (i = row1; i < row2; i++)
					{
						if (board[i][j] == '~')
						{
							if (ship[0] == 'C' && ship[1] == 'r')
							{
								board[i][j] = 'R';
								counter += 1;
							}
							else
							{
								board[i][j] = ship[0];
								counter += 1;
							}
						}
					}
					for (j = col1; j < col2; j++)
					{
						if (board[i][j] == '~')
						{
							if (ship[0] == 'C' && ship[1] == 'r')
							{
								board[i][j] = 'R';
								counter += 1;
							}
							else
							{
								board[i][j] = ship[0];
								counter += 1;
							}
						}
					}
				}
			}
		}
	}
}

int check_shot(char *board[][10], int row, int col)
{
	if (board[row][col] == '~' || board[row][col] == 'm' || board[row][col] == '*')
	{
		return 1;
	}
	else if (board[row][col] != '~' || board[row][col] != 'm' || board[row][col] != '*')
	{
		return 2;
	}
}

int check_if_sunk(char *board[][10], int row, int col, char ship_type)
{
	int i = 0, j = 0, found = 0;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (board[i][j] == ship_type)
			{
				found = 1;
			}
		}
	}
	return found;
}

void output_move(FILE* outfile, int plr, int row, int col, int shot_status, int sunk_status)
{
	fprintf(outfile, "Player %d fired a shot at %d %d\n", plr, row, col);
	if (shot_status == 1)
	{
		fprintf(outfile, "Miss!\n");
	}
	else if (shot_status == 2)
	{
		fprintf(outfile, "HIT!\n");
	}

	if (sunk_status == 1)
	{
		fprintf(outfile, "It didn't sink!\n\n");
	}
	else if (sunk_status == 0)
	{
		fprintf(outfile, "The ship sunk!\n\n");
	}
}

int is_winner(char *board[][10])
{
	int i = 0, j = 0, found = 0;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (board[i][j] != '~' && board[i][j] != '*' && board[i][j] != 'm')
			{
				found = 1;
			}
		}
	}
	return found;
}

void output_stats(FILE* outfile, int plr, struct stats *plr_board)
{
	fprintf(outfile, "\n==PLAYER %d GAME STATISTICS==", plr);
	fprintf(outfile, "\nSHIPS SUNK: %d", plr_board->sunk);
	fprintf(outfile, "\nHITS: %d", plr_board->hits);
	fprintf(outfile, "\nMISSES: %d\n", plr_board->misses);
}

