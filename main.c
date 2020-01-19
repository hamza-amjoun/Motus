#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"
#include "menu-items.h"


char *m;

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


    // struct menu initialisation
    menu_ menu = {
        .select=0,
        .hover = 0
     };


    bool running = true; // game loop
    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
         

        switch(event.type){
            case SDL_QUIT:
                running = false; break;// X botton XD
             
            case SDL_MOUSEBUTTONDOWN:
                 menu.select = menu.hover; // if mouse inside botton borders + botton click => SELECTED
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode){
                    case SDL_SCANCODE_ESCAPE: // Escape + return keys => return to menu
                    case SDL_SCANCODE_RETURN:
                        menu.select=NOT_SELECTED;
                        break;
                    }
}

       
        }

        SDL_RenderClear(renderer);
        switch(menu.select) {
            case NOT_SELECTED:
                menu.hover = render_menu(renderer); break;
            case LOGIN_SELECTED:
                render_login(renderer); break;
            case SINGUP_SELECTED :
                render_singup(renderer);
                break;  
            case PLAY_AS_GUEST_SELECTED:
                break;
            case TOP_PLAYERS_SELECTED:
                m = "top players HERE";
                render_text_on_xy(renderer,m, 300,300);
                break;
            case HOW_TO_PLAY_SELECTED:
                m ="how to play HERE";
                render_text_on_xy(renderer,m, 300,300);
                break;
        }



        
        SDL_RenderPresent(renderer);  // Show what was drawn
    }
    
    SDL_Delay(1000/30);
    SDL_FlushEvent(SDL_KEYDOWN);
    SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
    SDL_FlushEvent(SDL_MOUSEMOTION);
    // Release resources
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}