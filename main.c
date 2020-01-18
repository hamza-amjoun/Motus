#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"
#include "menu-items.h"


SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

int main(int argc, char **argv)
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Motus V1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Texture * image_texture = initialize_texture_from_file(LOGIN_BG, renderer);
    int image_width, image_height;

    // Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;

    texture_destination.x = 0;
    texture_destination.y = 0;
    texture_destination.w = image_width;
    texture_destination.h = image_height;

    bool running = true;
    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);

        // Draw
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}