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

//game menu selection :
typedef struct{
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