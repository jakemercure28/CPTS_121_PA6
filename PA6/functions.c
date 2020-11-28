#include "functions.h"

void print_welcome_screen(){
	printf("Welcome to the game of Battleship!\n\nRules of the game:\n1. This is a two player game\n2. You are Player 1, the computer is Player 2\n3. 5 ships are placed on a 2 dimentional array.\nThey are Carrier (5), Destroyer(4), Cruiser(3), Submarine(3) and Destroyer(2)\n4. The oposing player will choose a target to 'shoot' at.\n5. If the target hits a boat, the ship is hit. You have to hit all parts of the ship to sink it.\n6. Sink every ship before the other player an you win the game!\n");
}

void initialize_game_board(Cell player1Board[10][10], Cell player2Board[10][10]){
	
	for (int i = 0; i < 10; i++){

		for (int j = 0; j < 10; j++){
			player1Board[i][j].display_char = '~';
			player1Board[i][j].actual_char = '~';
			player1Board[i][j].is_hit = 0;
			player2Board[i][j].display_char = '~';
			player2Board[i][j].actual_char = '~';
			player2Board[i][j].is_hit = 0;
		}
	}
}

void wait_for_user_to_press_enter() {

	int bruh = 0;
	printf("\n1. Continue\n");
	scanf("%d", &bruh);
}

int select_starting_player(){
	
	return rand() % 2;
}

void manually_place_ships_on_board(Cell player_board[10][10]){

	int row = 0, col = 0;

	int ship_size[5] = { 5, 4, 3, 3, 2 };
//	int placement[5] = { 0,0,0,0,0 };
	char ship_display[5] = { 'C', 'B', 'R', 'S', 'D' };

	printf("Enter 1 coordinate at a time\n\"row col\" (enter)");
	

	// run 5 times, 5 is the amount of ships to manually place
	for (int i = 0; i < 5; i++) {
		
		// scan in the amount of coordinates for the cooresponding ship size
		for (int j = 0; j < ship_size[i]; j++) {

			printf("\nPlease enter %d cells to place the %c across: ", ship_size[i], ship_display[i]);

			// sets coordinates to the cooresponding ship display char.
			scanf("%d %d", &row, &col);

			player_board[row][col].actual_char = ship_display[i];
		}
	}

}
void randomly_place_ships_on_board(Cell player_board[10][10]){

	int ship_size[5] = { 5, 4, 3, 3, 2 };
	char ship_display[5] = { 'C', 'B', 'R', 'S', 'D' };

	//using a do-while
	//generate a random starting position based on size of the boat
	//generate orientation right or down
	//check with a for loop that goes from 0 to size of boat
	//goodPoint (check variable)
	//check all the points after that of the boat size

	//place the boat on the board
	//move on to the next boat

	for (int i = 0; i < 5; i++){

		int check = 0, direction = 0, row = 0, col = 0;

		do {
			check = 1;
			row = rand() % (9 - ship_size[i]);
			col = rand() % (9 - ship_size[i]);
			direction = rand() % 2; //0 is down, 1 is right

			for (int j = 0; j < ship_size[i]; j++){
				if (direction == 0){

					if (player_board[row + j][col].actual_char != '~'){
						check = 0;
						break;
					}
				}
				else if (player_board[row][col + j].actual_char != '~'){
						check = 0;
						break;
					
				}
			}
		} while (check == 0);

		for (int j = 0; j < ship_size[i]; j++) {
			if (direction == 0)
			{
				player_board[row + j][col].actual_char = ship_display[i];
			}
			else
			{
				player_board[row][col + j].actual_char = ship_display[i];
			}
		}

	}


}

void get_target(int* row, int* col) {
	printf("\nEnter a target: ");
	scanf("%d%d", row, col);
}

//data passed in is specific to each character! including ship_hits array
void check_shot(int row, int col, Cell player_board[10][10], int* playerHits, int* playerMisses, int ship_hits[5]) {

	// if the shot location isnt water
	if (player_board[row][col].actual_char != '~') {

		//mark it as a hit, increment hits and set is_hit to true
		player_board[row][col].display_char = '*';
		(*playerHits)++;
		player_board[row][col].is_hit = 1;
		printf("\nThat was a hit!\n");

		//add the type of boat to the ship hits array
		switch (player_board[row][col].actual_char) {

		case 'C': ship_hits[0]++;
			break;
		case 'B': ship_hits[1]++;
			break;
		case 'R': ship_hits[2]++;
			break;
		case 'S': ship_hits[3]++;
			break;
		case 'D': ship_hits[4]++;
			break;
		}
	}
	//if it is water, mark a miss on the board, increment misses and set is_hit to true
	else {
		player_board[row][col].display_char = 'M'; // 'M' for miss
		(*playerMisses)++;
		player_board[row][col].is_hit = 1;
		printf("\nThat was a miss!\n");
	}
}
int is_winner(int player1Hits, int player2Hits) {

}
void update_board(Cell player_board[10][10]) {

	for (int i = 0; i < 10; i++) {

		for (int j = 0; j < 10; j++) {

			if (player_board[i][j].is_hit == 1) {
				player_board[i][j].actual_char = player_board[i][j].display_char;
			}
		}
	}
}

void display_board(Cell player_board[10][10], char display_option) {

	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (int i = 0; i < 10; i++) {

		printf("%d", i);
		for (int j = 0; j < 10; j++) {

			if (display_option == 'd') {
				printf(" %c", player_board[i][j].display_char);
			}
			else if (display_option == 'a') {
				printf(" %c", player_board[i][j].actual_char);
			}

		}
		putchar('\n');
	}
}
void output_current_move(FILE* outFile, int col, int row, int current_player) {
	fprintf(outFile, "Current player: %d, row: %d, col: %d\n", current_player, row, col);

}
void check_if_sunk_ship(int ship_hits[5]) {

	if (ship_hits[0] == 5) {
		printf("\nThe carrier has been sunk!\n");
		return 0;
	}
	else if (ship_hits[1] == 4) {
		printf("\nThe battleship has been sunk!\n", ship_hits[1]);
		return 1;
	}
	else if (ship_hits[2] == 3) {
		printf("\nThe cruiser has been sunk!\n", ship_hits[2]);
		return 2;
	}
	else if (ship_hits[3] == 3) {
		printf("\nThe submarine has been sunk!\n", ship_hits[3]);
		return 3;
	}
	else if (ship_hits[4] == 2) {
		printf("\nThe battleship has been sunk!\n", ship_hits[4]);
		return 4;
	}
	else return -1;
}
void output_stats(){


}