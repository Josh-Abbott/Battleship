#include "pa6.h"

int main(void)
{
	int curr_plr = 0, selection = 0, loop_num = 0, game_loop = 0, row = 0, col = 0,
		shot_status = 0, sunk_status = 0, won = 0;
	char *player1_board[10][10];
	char *player2_board[10][10];

	stats player1_stats;
	stats player2_stats;
	player1_stats.hits = 0;
	player1_stats.misses = 0;
	player1_stats.sunk = 0;
	player2_stats.hits = 0;
	player2_stats.misses = 0;
	player2_stats.sunk = 0;

	FILE* outfile = NULL;
	outfile = fopen("battleship.log", "w");

	srand(time(NULL));

	welcome_screen();
	initialize_game_board(&player1_board, &player2_board);

	system("pause");
	system("cls");

	while (loop_num == 0)
	{
		system("cls");
		printf("--Hello! Before you can start the game, select a placement method:--");
		printf("\n1. Place ships manually");
		printf("\n2. Place ships automatically\n");
		scanf("%d", &selection);
		if (selection == 1 || selection == 2)
		{
			loop_num = 1;
		}
	}

	curr_plr = select_starter();
	printf("Player %d has been chosen to start.\n", curr_plr);

	system("pause");
	system("cls");

	char ships[5][15] = {
		"Carrier", 
		"Battleship", 
		"Cruiser", 
		"Submarine", 
		"Destroyer"
	};
	int i = 0, ship_num = 0;

	switch (selection)
	{
	case 1: 
		for (i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				ship_num = 5;
			}
			else if (i == 1)
			{
				ship_num = 4;
			}
			else if (i == 2)
			{
				ship_num = 3;
			}
			else if (i == 3)
			{
				ship_num = 3;
			}
			else if (i == 4)
			{
				ship_num = 2;
			}
			ship_placement(&player1_board, selection, ships[i], ship_num);
		}
		break;
	case 2:
		for (i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				ship_num = 5;
			}
			else if (i == 1)
			{
				ship_num = 4;
			}
			else if (i == 2)
			{
				ship_num = 3;
			}
			else if (i == 3)
			{
				ship_num = 3;
			}
			else if (i == 4)
			{
				ship_num = 2;
			}
			ship_placement(&player1_board, selection, ships[i], ship_num);
		}
		break;
	}

	for (i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			ship_num = 5;
		}
		else if (i == 1)
		{
			ship_num = 4;
		}
		else if (i == 2)
		{
			ship_num = 3;
		}
		else if (i == 3)
		{
			ship_num = 3;
		}
		else if (i == 4)
		{
			ship_num = 2;
		}
		ship_placement(&player2_board, 2, ships[i], ship_num);
	}


	while (game_loop == 0)
	{
		loop_num = 0;
		if (curr_plr == 1)
		{
			display_board(&player1_board, &player2_board, 1);

			while (loop_num == 0)
			{
				printf("===PREPARING TO ATTACK===");
				printf("\nEnter where you would like to fire (row col): \n");
				scanf("%d %d", &row, &col);
				if (row >= 0 && row <= 9 && col >= 0 && col <= 9)
				{
					if (player2_board[row][col] == 'm' || player2_board[row][col] == '*')
					{
						printf("You've already shot here before!\n");
						system("pause");
						system("cls");
						display_board(&player1_board, &player2_board, 1);

					}
					else
					{
						loop_num = 1;
					}
				}
				else
				{
					printf("This isn't a valid position!\n");
					system("pause");
					system("cls");
					display_board(&player1_board, &player2_board, 1);

				}
			}

			char ship_type = player2_board[row][col];
			shot_status = check_shot(&player2_board, row, col);
			if (shot_status == 1)
			{
				player2_board[row][col] = 'm';
			}
			else if (shot_status == 2)
			{
				player2_board[row][col] = '*';
			}
			sunk_status = check_if_sunk(&player2_board, row, col, ship_type);
			output_move(outfile, 1, row, col, shot_status, sunk_status);
			loop_num = 1;
			curr_plr = 2;
			if (shot_status == 1)
			{
				player1_stats.misses += 1;
				printf("It was a miss!\n");
			}
			else if (shot_status == 2)
			{
				player1_stats.hits += 1;
				printf("You hit a ship!\n");
			}
			if (sunk_status == 0)
			{
				player1_stats.sunk += 1;
				printf("You sunk a ship!\n");
			}
			system("pause");
			won = is_winner(&player2_board);
			if (won == 0)
			{
				printf("**You win!**\n");
				output_stats(outfile, 1, &player1_stats);
				output_stats(outfile, 2, &player2_stats);
				printf("Game stats have been outputted in the log!");
				game_loop = 1;
			}
			else if (won == 1)
			{
				system("cls");
			}
		}
		else if (curr_plr == 2)
		{
			display_board(&player1_board, &player2_board, 1);

			while (loop_num == 0)
			{
				row = rand();
				row = (row % 9);
				col = rand();
				col = (col % 9);
				if (player1_board[row][col] != '*' && player1_board[row][col] != 'm')
				{
					loop_num = 1;
				}
			}

			shot_status = check_shot(&player1_board, row, col);
			char ship_type = player1_board[row][col];
			if (shot_status == 1)
			{
				player1_board[row][col] = 'm';
			}
			else if (shot_status == 2)
			{
				player1_board[row][col] = '*';
			}
			sunk_status = check_if_sunk(&player1_board, row, col, ship_type);
			output_move(outfile, 2, row, col, shot_status, sunk_status);
			loop_num = 1;
			curr_plr = 1;
			printf("\nPlayer 2 shot at %d %d", row, col);
			if (shot_status == 1)
			{
				player2_stats.misses += 1;
				printf("\nIt was a miss!\n");
			}
			else if (shot_status == 2)
			{
				player2_stats.hits += 1;
				printf("\nThey hit a ship!\n");
			}
			if (sunk_status == 0)
			{
				player2_stats.sunk += 1;
				printf("They sunk a ship!\n");
			}	
			system("pause");
			won = is_winner(&player1_board);
			if (won == 0)
			{
				printf("**Player2 wins!**\n");
				output_stats(outfile, 1, &player1_stats);
				output_stats(outfile, 2, &player2_stats);
				printf("Game stats have been outputted in the log!");
				game_loop = 1;
			}
			else if (won == 1)
			{
				system("cls");
			}
		}
	}
	fclose(outfile);
}