#ifndef RENDERING_H_
#define RENDERING_H_

#define DEFAULT_FONT "res/Orbitron-Bold.ttf"

#define MENU_BG "res/menu.png"
#define LOGIN_BG "res/login.png"
#define SINGUP_BG "res/signup.png"
#define TOP_PLAYERS_BG "res/top_players_bg.png"
#define HOW_TO_BG "res/how_to_play_bg.png"
#define GAME_BG "res/Motus_bg.png"
#define WON_BG "res/won_bg.png"
#define LOSE_BG "res/loser_bg.png"

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


// alphabets : haerd worker I know xd
#define A_R "res/a.png"
#define B_R "res/b.png"
#define C_R "res/c.png"
#define D_R "res/d.png"
#define E_R "res/e.png"
#define F_R "res/f.png"
#define G_R "res/g.png"
#define H_R "res/h.png"
#define I_R "res/i.png"
#define J_R "res/j.png"
#define K_R "res/k.png"
#define L_R "res/l.png"
#define M_R "res/m.png"
#define N_R "res/n.png"
#define O_R "res/o.png"
#define P_R "res/p.png"
#define Q_R "res/q.png"
#define R_R "res/r.png"
#define S_R "res/s.png"
#define T_R "res/t.png"
#define U_R "res/u.png"
#define V_R "res/v.png"
#define W_R "res/w.png"
#define X_R "res/x.png"
#define Y_R "res/y.png"
#define Z_R "res/z.png"

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


void render_linge_text6(SDL_Renderer *renderer,linge6_ linge,int h_pose);
void render_linge_text7(SDL_Renderer *renderer,linge7_ linge,int h_pose);
void render_linge_text8(SDL_Renderer *renderer,linge8_ linge,int h_pose);
void render_linge_text9(SDL_Renderer *renderer,linge9_ linge,int h_pose);
void render_linge_text10(SDL_Renderer *renderer,linge10_ linge,int h_pose);

// rendering lines :
void render_linge6(SDL_Renderer *renderer,linge6_ linge,int h_pose);
void render_linge7(SDL_Renderer *renderer,linge7_ linge,int h_pose);
void render_linge8(SDL_Renderer *renderer,linge8_ linge,int h_pose);
void render_linge9(SDL_Renderer *renderer,linge9_ linge,int h_pose);
void render_linge10(SDL_Renderer *renderer,linge10_ linge,int h_pose);

int txt_to_chow(char* text,int indice);


void render_box_text(SDL_Renderer *renderer,int boxCH,int x,int y);

#endif  // RENDERING_H_

