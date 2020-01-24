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
#define GAME_OVER_STATE 3 // game is donne the playing state will start


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

#define A 41
#define B 42
#define C 43
#define D 44
#define E 45
#define F 46
#define G 47
#define H 48
#define I 49
#define J 50
#define K 51
#define L 52
#define M 53
#define N 54
#define O 55
#define P 56
#define Q 57
#define R 58
#define S 59
#define T 60
#define U 61
#define V 62
#define W 63
#define X 64
#define Y 65
#define Z 66

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

typedef struct {
	char generated[6];
}playing_data6_;

typedef struct {
	char generated[7];
}playing_data7_;

typedef struct {
	char generated[8];
}playing_data8_;

typedef struct {
	char generated[9];
}playing_data9_;

typedef struct {
	char generated[10];
}playing_data10_;


// all data of all lings : we have to show them all xd
typedef struct {
	linge6_ linge1;
	linge6_ linge2;
	linge6_ linge3;
	linge6_ linge4;
	linge6_ linge5;
	linge6_ linge6;
	linge6_ linge7;
	int* h_pos; // what line are we playing in
	int reds_chow[6]; // reviled letters will be saved here
	int reds_box[6]; // the reviled boxes BG here
} data_grid6_;


typedef struct {
	linge7_ linge1;
	linge7_ linge2;
	linge7_ linge3;
	linge7_ linge4;
	linge7_ linge5;
	linge7_ linge6;
	linge7_ linge7;
	int h_pos; // what line are we playing in
	int reds_chow[7]; // reviled letters will be saved here
	int reds_box[7]; // the reviled boxes BG here

} data_grid7_;

typedef struct {
	linge8_ linge1;
	linge8_ linge2;
	linge8_ linge3;
	linge8_ linge4;
	linge8_ linge5;
	linge8_ linge6;
	linge8_ linge7;
	int h_pos; // what line are we playing in
	int reds_chow[8]; // reviled letters will be saved here
	int reds_box[8]; // the reviled boxes BG here
} data_grid8_;

typedef struct {
	linge9_ linge1;
	linge9_ linge2;
	linge9_ linge3;
	linge9_ linge4;
	linge9_ linge5;
	linge9_ linge6;
	linge9_ linge7;
	int h_pos; // what line are we playing in
	int reds_chow[9]; // reviled letters will be saved here
	int reds_box[9]; // the reviled boxes BG here
} data_grid9_;

typedef struct {
	linge10_ linge1;
	linge10_ linge2;
	linge10_ linge3;
	linge10_ linge4;
	linge10_ linge5;
	linge10_ linge6;
	linge10_ linge7;
	int h_pos; // what line are we playing in
	int reds_chow[10]; // reviled letters will be saved here
	int reds_box[10]; // the reviled boxes BG here
} data_grid10_;

typedef struct{
    char id[25];
    int score;
}topPlayer;
typedef struct{
    char ligne[40];
}affichageTop;


#endif  // GAME_H_