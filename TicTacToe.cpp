#include "TicTacToe.h"

// displays menu and takes in user option
int menu_select(void)
{
	int option = 0;
	// display options
	cout << "Please enter an option:\n\n"
		<< "1. Print Game Rules\n"
		<< "2. Play Game\n"
		<< "3. Exit\n";
	// take in user option
	cin >> option;

	return option;
}

// print game rules
void print_rules(void)
{
		cout << "Tic Tac Toe is a game with two players. The players take turns putting an 'X' or an 'O' in one space on a 3x3 grid.\n"
			"The goal is to get three in a row either vertically, horizontally, or diagonally. When one player does this, this player wins.\n"
			"If the nine spaces are filled and neither player has three in a row, the game ends in a tie.\n\n";
}

// starts game
void play_game(void)
{
	char board[3][3] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' } }; // game board

	int game_over = 0; // when a player has won, changes to 1 so that loop and end
	int i = 0;
	for (; i < 9 && game_over == 0; i++) // loops maximum 9 times, or ends early if a player wins
	{
		int player = i % 2 + 1; // player 1 turn for even i values, player 2 turn for odd i values
		print_board(board); // prints board
		player_turn(player, board); // conducts a single player's turn
		game_over = check_winner(player, board); // checks if the player has won so loop can end early if needed
	}

	print_board(board); // prints final game board
	if (game_over == 1) // there was a winner
	{
		int player = i % 2; // if a player won, then the player's whose turn it most recently was is the winner
		if (player == 0) 
			player = 2; // without this, player 2 is called "player 0"
		cout << "Player " << player << " wins!\n\n"; // user is told who wins
	}
	else // there wasnt a winner
	{
		cout << "Cat's game!\n\n"; // there was a tie
	}
}

// displays board to user
void print_board(char board[][3])
{
	system("cls"); // clear menu or previous board printings
	cout << "Player 1 (X)  -  Player 2 (O)\n\n"; // tell user which player gets which mark

	for (int i = 0; i < 3; i++) // loops through rows
	{
		// builds text-based picture of the game board
		cout << "     |     |\n"
			<< "  " << board[i][0] << "  |  " << board[i][1] << "  |  " << board[i][2] << endl; // rather than a j loop, the values of a row are printed all at once
		if (i != 2)
			cout << "_____|_____|_____\n"; // this doesn't go below the last row
	}
	cout << "     |     |\n\n";
}

// does single player turn
void player_turn(int player, char board[][3])
{
	cout << "It is player " << player << "'s turn.\n" // tells user who's turn it is
		"Please enter a number to select the space corresponding to it: ";

	int user_number = 0; // for user_input
	int check_num = 1; // equals 1 when the number is a correct input (in range, and not an already taken space), 0 otherwise
	do {
		check_num = 1; // reset to 1 at start of each loop
		cin >> user_number; // get input
		if (user_number < 1 || user_number > 9) // check range
		{
			cout << "That is outside the input range.\n"
				<< "Please enter a different number: \n";
			check_num = 0; // bad num. set to 0 so that loop can repeat
		}
		else // move on to next check
		{
			// translate from one dimensional user input to two dimensional array
			int i = 0;
			if (user_number <= 3) // 1, 2, 3 are in row 0
				i = 0;
			else if (user_number >= 4 && user_number <= 6) // 4, 5, 6 are in row 1
				i = 1;
			else // 7, 8, 9 are in row 2
				i = 2;

			int j = 0;
			if (user_number % 3 != 0) // num is in column 0 or 1
				j = user_number % 3 - 1; // num 1, 2, 4, 5, 7, or 8. modding by 3 and subtracting 1 gives correct column (0 or 1)
			else // num is 3, 6, or 9 and in column 2
				j = 2; 

			if (board[i][j] == 'X' || board[i][j] == 'O') // check if space is already filled
			{
				cout << "That space is already taken.\n"
					<< "Please enter a different number: ";
				check_num = 0; // bad num. set to 0 so that loop can repeat

			}
			else // num was good. board is edited with mark corresponding to current player's turn
			{
				if (player == 1)
					board[i][j] = 'X';
				else
					board[i][j] = 'O';
			}
		}
	} while (check_num == 0); // loop again if the num failed the check
}

// returns 1 if a player won, 0 if game is still going
int check_winner(int player, char board[][3])
{
	// determine mark based on who's turn it is. X for player 1, O for player 2
	char mark = 0;
	if (player == 1)
		mark = 'X';
	else
		mark = 'O';

	// check the three horizontals (rows) for three in a row
	for (int i = 0; i < 3; i++)
	{
		int row_count = 0;
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == mark) 
				row_count++; // track the count
		}
		if (row_count == 3) // if count equals 3, then theres a winner, so end function early and return 1
			return 1;
	}

	// check the three verticals (columns) for a three in a row
	for (int i = 0; i < 3; i++)
	{
		int col_count = 0;
		for (int j = 0; j < 3; j++)
		{
			if (board[j][i] == mark)
				col_count++; // track the count
		}
		if (col_count == 3) // if count equals 3, then theres a winner, so end function early and return 1
			return 1;
	}

	// check the two diagonals
	if (board[1][1] == mark) // first check center. center must be filled for either diagonal to have three in a row
	{
		if (board[0][0] == mark && board[2][2] == mark) // check top left and bottom right. if both are filled with mark, there's three in a row
			return 1;
		if (board[2][0] == mark && board[0][2] == mark) // check bottom left and top right. if both are filled with mark, there's three in a row
			return 1;
	}

	// if function hasn't ended yet, then there was no three in a row anywhere. return 0, since game is still going
	return 0;
}