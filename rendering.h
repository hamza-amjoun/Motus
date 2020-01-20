#ifndef RENDERING_H_
#define RENDERING_H_

#define DEFAULT_FONT "res/Orbitron-Bold.ttf"

#define MENU_BG "res/menu.png"
#define LOGIN_BG "res/login.png"
#define SINGUP_BG "res/signup.png"
#define TOP_PLAYERS_BG "res/top_players_bg.png"
#define HOW_TO_BG "res/how_to_play_bg.png"
#define GAME_BG "res/Motus_bg.png"

// pics of nbr choises
#define NBR_6 "res/nbr_6.png" 
#define NBR_7 "res/nbr_7.png"
#define NBR_8 "res/nbr_8.png"
#define NBR_9 "res/nbr_9.png"
#define NBR_10 "res/nbr_10.png"

// pics of Time choises
#define TIME_10 "res/time_10.png" 
#define TIME_15 "res/time_15.png"
#define TIME_20 "res/time_20.png"

// login menu items :  
#define PLAY_GEST "res/gest.png"
#define HOW_TO "res/how.png"
#define LOG_IN "res/log.png"
#define SING_UP "res/sing.png"
#define TOP_PLAYERS "res/top.png"

// game menu bottons :
#define START_BT "res/start.png"
#define RESET_BT "res/reset.png"
#define LOGOUT_BT "res/logout2.png"

// boxes background ;
#define BOX_BLACK_BG "res/box_black.png"
#define BOX_BLEU_BG "res/box_bleu.png"
#define BOX_RED_BG "res/box_red.png"
#define BOX_YELLOW_BG "res/box_yellow.png"

// ling select macros:
#define LN_1 1
#define LN_2 2
#define LN_3 3
#define LN_4 4
#define LN_5 5
#define LN_6 6
#define LN_7 7
// how to play frame : 


#define BOTTON_H 158 // H of used Bottons
#define BOTTON_W 43 // W  of used Bottons

#define ARROW_H 75
#define ARROW_W 57

#define BOX 51



SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer); // img to textur
void render_on_xy(const char* file_name,SDL_Renderer *renderer,int x,int y); // ren,der texture on (X,y)
int render_menu(SDL_Renderer *renderer);
void render_login(SDL_Renderer *renderer);
void render_singup(SDL_Renderer *renderer);

void render_text_on_xy(SDL_Renderer* renderer,const char* text,int x,int y,SDL_Color color);

void render_text_on_box(SDL_Renderer* renderer,const char* text, int x,int y,SDL_Color color);


#endif  // RENDERING_H_

