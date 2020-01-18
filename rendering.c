#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"

// game states :
#define POST_PLAYING 0
#define PLAYING_PREP 1
#define PLAYING 2


int login_x=487, login_y=361;
int singup_x=331,singup_y=361;
int play_gest_x=171,play_gest_y=361;
int top_players_x=394,top_players_y=413;
int how_to_x=234,how_to_y=413;


// file to texture
SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

// render texture on (x,y):
void render_on_xy(const char* file_name,SDL_Renderer *renderer,int x,int y){
    SDL_Texture * texture = initialize_texture_from_file(file_name, renderer);
    int height;int width;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.w = width;
    destination.h = height;
    SDL_RenderCopy(renderer,texture, NULL, &destination);
    SDL_DestroyTexture(texture);
}

// render all menu to screen
void render_menu(SDL_Renderer *renderer){

    render_on_xy(MENU_BG,renderer,0,0);
    render_on_xy(LOG_IN,renderer,login_x,login_y);
    render_on_xy(SING_UP,renderer,singup_x,singup_y);
    render_on_xy(PLAY_GEST,renderer,play_gest_x,play_gest_y);
    render_on_xy(TOP_PLAYERS,renderer,top_players_x,top_players_y);
    render_on_xy(HOW_TO,renderer,how_to_x,how_to_y);

    int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if (mouse_x > login_x && mouse_x < login_x + BOTTON_H && mouse_y > login_y && mouse_y < login_y + BOTTON_W)
        { render_on_xy(LOG_IN,renderer,login_x+4,login_y);}
        if (mouse_x > singup_x && mouse_x < singup_x + BOTTON_H && mouse_y > singup_y && mouse_y < singup_y + BOTTON_W)
        { render_on_xy(SING_UP,renderer,singup_x+4,singup_y);}
        if (mouse_x > play_gest_x && mouse_x < play_gest_x + BOTTON_H && mouse_y > play_gest_y && mouse_y < play_gest_y + BOTTON_W)
        { render_on_xy(PLAY_GEST,renderer,play_gest_x+4,play_gest_y);}
        if (mouse_x > top_players_x && mouse_x < top_players_x + BOTTON_H && mouse_y > top_players_y && mouse_y < top_players_y + BOTTON_W)
        { render_on_xy(TOP_PLAYERS,renderer,top_players_x+4,top_players_y);}
        if (mouse_x > how_to_x && mouse_x < how_to_x + BOTTON_H && mouse_y > how_to_y && mouse_y < how_to_y + BOTTON_W)
        { render_on_xy(HOW_TO,renderer,how_to_x+4,how_to_y);}
}


void click_on_menu(SDL_Renderer *renderer){
    render_on_xy(GAME_BG,renderer,0,0);
}