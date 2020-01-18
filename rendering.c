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
#

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
    render_on_xy(LOG_IN,renderer,487,361);
    render_on_xy(SING_UP,renderer,331,361);
    render_on_xy(PLAY_GEST,renderer,171,361);
    render_on_xy(TOP_PLAYERS,renderer,394,413);
    render_on_xy(HOW_TO,renderer,234,413);



}