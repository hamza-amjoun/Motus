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
#define MENU_STATE 0
#define PLAYING_STATE 1
#define GAME_OVER_STATE 2
#define CHECKING_STATE 3
#define QUIT_STATE 4


// nbrs of menu :
#define NBR_NO_SELECT 0
#define NBR_L_6 6 
#define NBR_L_7 7
#define NBR_L_8 8
#define NBR_L_9 9
#define NBR_L_10 10

//nbrs of time : 
#define TIME_L_10 1
#define TIME_L_15 2
#define TIME_L_20 3
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
}login_txt_;

//sing up input
typedef struct {
	char id[25];
	char passwd[25];
} singup_txt_;


#endif  // GAME_H_