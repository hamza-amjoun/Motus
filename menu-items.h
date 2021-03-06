#ifndef MENU_ITEMS_H_
#define MENU_ITEMS_H_

#define INPUT_S_ID 1
#define INPUT_S_PASSWD 2

// main loops functions
void menu_loop(SDL_Renderer *renderer);
void game_loop(SDL_Renderer *renderer);
void main_loop(SDL_Renderer *renderer);

void play_game(SDL_Renderer *renderer);
void game_over(SDL_Renderer* renderer,int pop,char* word);

void reset_input();
void login_txt_input(SDL_Renderer* renderer,char* text);
void login_passwd_input(SDL_Renderer* renderer,char* text);
void singup_txt_input(SDL_Renderer* renderer,char* text);
void singup_passwd_input(SDL_Renderer* renderer,char* text);
void render_game_menu(SDL_Renderer *renderer);

void render_login(SDL_Renderer *renderer);
void render_singup(SDL_Renderer *renderer);
void render_top_players(SDL_Renderer *renderer);
void reset_data();
void player_input(SDL_Renderer* renderer ,char* text,int* chow,int* box,int nbr_letters);

void render_empty_grid6(SDL_Renderer *renderer);
void render_empty_grid7(SDL_Renderer *renderer);
void render_empty_grid8(SDL_Renderer *renderer);
void render_empty_grid9(SDL_Renderer *renderer);
void render_empty_grid10(SDL_Renderer *renderer);


void render_time(SDL_Renderer* renderer);
void render_score(SDL_Renderer* renderer);


int signup(singup_txt_ player);
int login(login_txt_ player);

#endif // MENU_ITEMS_H_