#ifndef MENU_ITEMS_H_
#define MENU_ITEMS_H_

#define INPUT_S_ID 1
#define INPUT_S_PASSWD 2


void menu_loop(SDL_Renderer *renderer);
void game_loop(SDL_Renderer *renderer);
void main_loop(SDL_Renderer *renderer);


void play_game(SDL_Renderer *renderer);


void reset_input();
void login_txt_input(SDL_Renderer* renderer,char* text);
void login_passwd_input(SDL_Renderer* renderer,char* text);
void singup_txt_input(SDL_Renderer* renderer,char* text);
void singup_passwd_input(SDL_Renderer* renderer,char* text);
void render_game_menu(SDL_Renderer *renderer);


void render_login(SDL_Renderer *renderer);
void render_singup(SDL_Renderer *renderer);
void render_top_players(SDL_Renderer *renderer);

// rendering lines :
void render_linge6(SDL_Renderer *renderer,linge6_ linge,int h_pose);
void render_linge7(SDL_Renderer *renderer,linge7_ linge,int h_pose);
void render_linge8(SDL_Renderer *renderer,linge8_ linge,int h_pose);
void render_linge9(SDL_Renderer *renderer,linge9_ linge,int h_pose);
void render_linge10(SDL_Renderer *renderer,linge10_ linge,int h_pose);

void render_linge_text6(SDL_Renderer *renderer,linge6_ linge,int h_pose);
void render_linge_text7(SDL_Renderer *renderer,linge7_ linge,int h_pose);
void render_linge_text8(SDL_Renderer *renderer,linge8_ linge,int h_pose);
void render_linge_text9(SDL_Renderer *renderer,linge9_ linge,int h_pose);
void render_linge_text10(SDL_Renderer *renderer,linge10_ linge,int h_pose);

void render_box_text(SDL_Renderer *renderer,int boxCH,int x,int y);

int player_input(SDL_Renderer* renderer ,char* text,int* chow,int* box,int nbr_letters);

void render_empty_grid6(SDL_Renderer *renderer);
void render_empty_grid7(SDL_Renderer *renderer);
void render_empty_grid8(SDL_Renderer *renderer);
void render_empty_grid9(SDL_Renderer *renderer);
void render_empty_grid10(SDL_Renderer *renderer);



int signup(singup_txt_ player);
int login(login_txt_ player);

#endif // MENU_ITEMS_H_