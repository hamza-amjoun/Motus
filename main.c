#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"
#include "menu-items.h"



int main(int argc, char **argv)
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Motus V1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);     // Initialize support for loading PNG and JPEG images

    //SDL_Texture * menu_texture = initialize_texture_from_file(MENU_BG, renderer);
    //SDL_Texture * login_texture = initialize_texture_from_file(LOG_IN, renderer);
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
       // render_on_xy(menu_texture,renderer,0,0);
        //render_on_xy(login_texture,renderer,487,361);
        render_menu(renderer);
        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
