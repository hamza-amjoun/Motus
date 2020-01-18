#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"

// texture from image
SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path){
    //The final texture
    SDL_Texture* new_texture = NULL;

    //Load image at specified path
    SDL_Surface* loaded_surface = IMG_Load(path);
    if(loaded_surface == NULL){
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        //Create texture from surface pixels
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(new_texture == NULL){
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loaded_surface);
    }

    return new_texture;
}

// screen from texture
void render_screen(SDL_Renderer* renderer, const char* path){
    // simply show the chosen end screen
	SDL_Texture* texture = load_texture(renderer, path);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

}


	