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

// structs:


// game
typedef struct {
	int state;
}game_;



// menu : 
typedef struct {
	int select;
	int hover;
}menu_;


// user :
typedef struct {
	char id[25];
	char passwd[25];
}user_;





#endif  // GAME_H_