#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"
#include "menu-items.h"

int press;

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



    bool running = true; 
    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
         

        switch(event.type){
            case SDL_QUIT:
                running = false; break;// X botton XD
            case SDL_BUTTON_LEFT: /* Clic de la souris */
                break;
            }


       
}

        SDL_RenderClear(renderer);// Clear screen
        render_menu(renderer);   // Draw
        SDL_RenderPresent(renderer);  // Show what was drawn
    }

    // Release resources
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}