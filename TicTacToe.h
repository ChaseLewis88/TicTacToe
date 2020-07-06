/*
Name: Chase Lewis
Date: 2/19/20
Description: A game of Tic Tac Toe
*/

#include <iostream>
using namespace std;

// displays menu and takes in user option
int menu_select(void);

// print game rules
void print_rules(void);

// starts game
void play_game(void);

// prints board
void print_board(char board[][3]);

// does single player turn
void player_turn(int player, char board[][3]);

// returns 1 if a player won, 0 if game is still going
int check_winner(int player, char board[][3]);