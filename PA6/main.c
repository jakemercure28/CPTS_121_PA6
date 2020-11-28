#include "functions.h"

int main(void){

	srand((unsigned int)time(NULL));

	// user
	Cell player1Board[10][10];
	// computer
	Cell player2Board[10][10];

	int player1Hits = 0, player2Hits = 0, numberRounds = 0, player1Misses = 0,
		player2Misses = 0, number_sunk = 0, target_row = 0, target_column = 0,
		current_shot = 0, ship_hits[5] = { 0 }, winner = 0, option = 0;


	// logfile
	FILE* outFile = NULL;
	outFile = fopen("Battleship.log", "w+");  

	fprintf(outFile, "%s", "Hello");

	// initializes both player boards to water '~'
	initialize_game_board(player1Board, player2Board);

	// print instructions
	print_welcome_screen();

	// press enter to continue
	wait_for_user_to_press_enter();

	// place player 1 ships on board
	do {
		printf("\nPlease select from the following menu:\n1. Enter positions of ships manually.\n2. Allow the program to randomly select positions of ships.");
		scanf("%d", &option);
	} while (option != 1 && option != 2);

	switch (option) {
	case 1:manually_place_ships_on_board(player1Board);
		break;
	case 2:randomly_place_ships_on_board(player1Board);
		printf("\nPlayer 1's board has been generated.\n");
	}

	// place player 2 ships on board
	randomly_place_ships_on_board(player2Board);
	printf("\nPlayer 2's board has been generated.\n");

	// pick random player to start game (0 or 1)
	int current_player = select_starting_player();

	printf("\nPlayer %d has been randomly selected to go first.\n", current_player+1);

	// display boards
	printf("\nPlayer 1's Board:\n");
	display_board(player1Board, 'a');
	printf("\nPlayer 2's Board:\n");
	display_board(player2Board, 'd');
	
	// press enter to continue
	wait_for_user_to_press_enter();
	system("cls");

	// while there is no winner, the game will continue to run
	int is_winner = 0;
	while (!is_winner)
	{
		
		// player 1's turn
		if (current_player == 0)
		{
			system("cls");
			printf("\nPlayer 1's turn!\n");
			
			// print player 2 displayboard 
			printf("\nPlayer 2's Board:\n");
			display_board(player2Board, 'd');

			// prompt user for target coordinates
			get_target(&target_row, &target_column);
			system("cls");
			
			// checks if shot is a hit or miss, points 'M' or '*' to the display character 
			check_shot(target_row, target_column, player2Board, &player2Hits, &player2Misses, ship_hits);

			// check if ship is sunk after shooting
			check_if_sunk_ship(ship_hits);


			// I dont need update_board()
			// update board
			//update_board(player2Board);

			
			//print player 2 displayboard
			printf("\nPlayer 2's Board:\n");
			display_board(player2Board, 'd');

			// press enter to continue
			wait_for_user_to_press_enter();


			// copy to log file
			output_current_move(outFile, target_column, target_row, current_player);

			// change to player 2
			current_player = 1;
		}

		//player 2 starts first
		else{
			system("cls");
			printf("\nPlayer 2's turn!\n");

			// get random shot for computer
			target_row = (rand() % 9) - 1;
			target_column = (rand() % 9) - 1;

			// check random shot
			check_shot(target_row, target_column, player1Board, &player1Hits, &player1Misses, ship_hits);

			// check if ship is sunk after shooting
			check_if_sunk_ship(ship_hits);

			//update board
			update_board(player1Board);

			// print the player's actual board
			printf("\n\nPlayer 1's Board:\n");
			display_board(player1Board, 'a');

			// press enter to continue
			wait_for_user_to_press_enter();

			// copy to log file
			output_current_move(outFile, target_column, target_row, current_player);

			// change to player 1
			current_player = 0;
			
		}

		// check for winner, 16 hits is a win
		if (player1Hits == 16){
			// player 1 wins game
			is_winner = 1;
				printf("\nPlayer 1 wins!");
		}
		if (player2Hits == 16) {
			// player 2 wins game
			is_winner = 1;
				printf("\nPlayer 2 wins!");
		}

	}
	// output stats to log file
	fprintf(outFile, "\n\nPlayer 1 hits:%d\nPlayer 1 misses:%d\nPlayer 2 hits: %d\nPlayer 2 misses: %d",
		player1Hits, player1Misses, player2Hits, player2Misses);
	fclose(outFile);

	return 0;
}