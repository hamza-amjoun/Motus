#ifndef GAME_H_
#define GAME_H_

// screen parameters : 
#define SCREEN_WIDTH  820.0
#define SCREEN_HEIGHT 600.0

// menu selects :
#define NOT_SELECTED 0
#define LOGIN_SELECTED 1
#define SINGUP_SELECTED 2
#define PLAY_AS_GUEST_SELECTED 3
#define TOP_PLAYERS_SELECTED 4
#define HOW_TO_PLAY_SELECTED 5

// game_menu selects:
#define NOT_SELECTED 0
#define START_SELECTED 1
#define RESET_SELECTED 2
#define LOGOUT_SELECTED 3
#define NBR_6_SELECTED 6
#define NBR_7_SELECTED 7
#define NBR_8_SELECTED 8
#define NBR_9_SELECTED 9
#define NBR_10_SELECTED 10
#define TIME_10_SELECTED 11
#define TIME_15_SELECTED 12
#define TIME_20_SELECTED 13

//game states : 
#define MENU_STATE 0 // 1st menu
#define PLAYING_PARAMETERS_STATE 1 // befor Start botton
#define PLAYING_STATE 2 // player is playing the game with the parameters he wants :
#define CHECKING_STATE 3 // checking the input and changing 
#define DONNE_STATE 4 // game is donne the playing state will start


// nbrs of menu :
#define NBR_L_6 6 
#define NBR_L_7 7
#define NBR_L_8 8
#define NBR_L_9 9
#define NBR_L_10 10

//nbrs of time : 
#define TIME_L_10 10
#define TIME_L_15 15
#define TIME_L_20 20

// box rundring state :
#define BOX_R_BLACK 1
#define BOX_R_BLEU 2
#define BOX_R_RED 3
#define BOX_R_YELLOW 4


// boxes letters enums :

#define A 97
#define B 98
#define C 99
#define D 100
#define E 101
#define F 102
#define G 103
#define H 104
#define I 105
#define J 106
#define K 107
#define L 108
#define M 109
#define N 110
#define O 111
#define P 112
#define Q 113
#define R 114
#define S 115
#define T 116
#define U 117
#define V 118
#define W 119
#define X 120
#define Y 121
#define Z 122

//////////////////////////////////////////////////////////////////////////:::::://::::
// structs:


// game
typedef struct {
	int state;
}game_;



// menu : 
typedef struct {
	int select;
	int hover;
	int input_state;
}menu_;

//game_menu selection :
typedef struct{
	int select;
	int hover;
	int nbr_letters;
	int nbr_time;
	int score;
}game_options_;


// user :
typedef struct {
	char id[25];
	char passwd[25];
	int score;
}user_;

//login input from user
typedef struct {
	char id[25];
	char passwd[25];
	int score;
}login_txt_;

//sing up input
typedef struct {
	char id[25];
	char passwd[25];
	int score;
} singup_txt_;




// linge  data : 6
typedef struct {
	// boxes BG
	int box[6];
	// entred data :
	char text[6];
	// boxes text
	int chow[6];
}linge6_;

// linge  data : 7
typedef struct {
	// boxes BG
	int box[7];
	// entred data :
	char text[7];
	// boxes text
	int chow[7];
}linge7_;


// linge  data : 8
typedef struct {
	// boxes BG
	int box[8];
	// entred data :
	char text[8];
	// boxes text
	int chow[8];
}linge8_;

// linge  data : 9
typedef struct {
	// boxes BG
	int box[9];
	// entred data :
	char text[9];
	// boxes text
	int chow[9];
}linge9_;

// linge  data : 10
typedef struct {
	// boxes BG
	int box[10];
	// entred data :
	char text[10];
	// boxes text
	int chow[10];
}linge10_;



// all data of all lings : we have to show them all xd
typedef struct {
	linge6_ linge1;
	linge6_ linge2;
	linge6_ linge3;
	linge6_ linge4;
	linge6_ linge5;
	linge6_ linge6;
	linge6_ linge7;
} data_grid6_;


typedef struct {
	linge7_ linge1;
	linge7_ linge2;
	linge7_ linge3;
	linge7_ linge4;
	linge7_ linge5;
	linge7_ linge6;
	linge7_ linge7;
} data_grid7_;

typedef struct {
	linge8_ linge1;
	linge8_ linge2;
	linge8_ linge3;
	linge8_ linge4;
	linge8_ linge5;
	linge8_ linge6;
	linge8_ linge7;
} data_grid8_;

typedef struct {
	linge9_ linge1;
	linge9_ linge2;
	linge9_ linge3;
	linge9_ linge4;
	linge9_ linge5;
	linge9_ linge6;
	linge9_ linge7;
} data_grid9_;

typedef struct {
	linge10_ linge1;
	linge10_ linge2;
	linge10_ linge3;
	linge10_ linge4;
	linge10_ linge5;
	linge10_ linge6;
	linge10_ linge7;
} data_grid10_;



#endif  // GAME_H_