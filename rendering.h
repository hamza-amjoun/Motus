#ifndef RENDERING_H_
#define RENDERING_H_

#define DEFAULT_FONT "res/Orbitron-Bold.ttf"

#define MENU_BG "res/menu.png"
#define LOGIN_BG "res/login.png"
#define SINGUP_BG "res/signup.png"
#define GAME_BG "res/Motus_bg.png"

// pics of nbr choises
#define NBR_6 "res/nbr_6.png" 
#define NBR_7 "res/nbr_7.png"
#define NBR_8 "res/nbr_8.png"
#define NBR_9 "res/nbr9_.png"
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

// grids ; 

#define GRID_6 "res/grid_6.png"
// sing in menu :

// how to play frame : 


#define BOTTON_H 158 // H of used Bottons
#define BOTTON_W 43 // W  of used Bottons



SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer); // img to textur
void render_on_xy(const char* file_name,SDL_Renderer *renderer,int x,int y); // ren,der texture on (X,y)
int render_menu(SDL_Renderer *renderer);
void render_login(SDL_Renderer *renderer);
void render_singup(SDL_Renderer *renderer);

void render_text_on_xy(SDL_Renderer* renderer,const char* text,int x,int y,SDL_Color color);




#endif  // RENDERING_H_

