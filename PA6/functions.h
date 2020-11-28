#ifndef BATTLESHIP
#define BATTLESHIP
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


void print_welcome_screen();

typedef struct cell {
	char display_char;
	char actual_char;
	int is_hit;
}Cell;

void initialize_game_board(Cell player1Board[10][10], Cell player2Board[10][10]);

void print_welcome_screen();

void wait_for_user_to_press_enter();

void get_target(int* row, int* col);

int select_starting_player();

void manually_place_ships_on_board(Cell player_board[10][10]);

void randomly_place_ships_on_board(Cell player_board[10][10]);

void check_shot(int row, int col, Cell player_board[10][10], int* playerHits, int* playerMisses, int ship_hits[5]);

int is_winner(int player1Hits, int player2Hits);

void update_board(Cell player_board[10][10]);

void display_board(Cell player_board[10][10], char display_option);

void output_current_move(FILE* outFile, int col, int row, int current_player);

void check_if_sunk_ship(int ship_hits[5]);

void output_stats();
#endif