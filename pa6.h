#ifndef PA6_H
#define PA6_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void welcome_screen(void);
void initialize_game_board(char *board1[][10], char *board2[][10]);
int select_starter(void);
void display_board(char *board1[][10], char *board2[][10], int disp_plr);
void ship_placement(char *board[][10], int type, char ship[], int ship_num);
int check_shot(char *board[][10], int row, int col);
int check_if_sunk(char *board[][10], int row, int col, char ship_type);
void output_move(FILE* outfile, int plr, int row, int col, int shot_status, int sunk_status);
int is_winner(char *board[][10]);
void output_stats(FILE* outfile, int plr, struct stats *plr_stats);

typedef struct stats
{
	int hits;
	int misses;
	int sunk;
}stats;

#endif