#ifndef MENU_ITEMS_H_
#define MENU_ITEMS_H_

#define INPUT_S_ID 1
#define INPUT_S_PASSWD 2

void menu_loop(SDL_Renderer *renderer);
void game_loop(SDL_Renderer *renderer);

void login_txt_input(SDL_Renderer* renderer,char* text);
void login_passwd_input(SDL_Renderer* renderer,char* text);

void singup_txt_input(SDL_Renderer* renderer,char* text);
void singup_passwd_input(SDL_Renderer* renderer,char* text);

void render_game_menu(SDL_Renderer *renderer);

void render_linge(SDL_Renderer *renderer,linge6_ linge,int h_pose);

void render_linge_text(SDL_Renderer *renderer,linge6_ linge,int h_pose);

void render_box_text(SDL_Renderer *renderer,int boxCH,int x,int y);

char * player6_input(SDL_Renderer* renderer ,char* text,int* chow,int* box, int h_pose);

void render_empty_grid6(SDL_Renderer *renderer);




#endif // MENU_ITEMS_H_