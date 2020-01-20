#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "game.h"
#include "logic.h"
#include "menu-items.h"	
#include "rendering.h"

char *m;
login_txt_ login_data;
singup_txt_ singup_data;
bool running = true;

int i=0;
char hide[25];

int input_state = 1;


// struct menu initialisation
menu_ menu = {
	.select=0,
	.hover = 0,
    .input_state = 1
};

const SDL_Color white = { .r = 255, .g = 255, .b = 255};
const SDL_Color black = { .r = 0, .g = 0, .b = 0};


void reset_input(){
    i=0;
    while(i<25){
        login_data.id[i]=0;
        login_data.passwd[i]=0;
        singup_data.id[i]=0;
        singup_data.passwd[i]=0;
        i++;
    }

    menu.input_state=1;
}

void login_txt_input(SDL_Renderer* renderer,char* text){
    SDL_StartTextInput();
 
    SDL_Event event;
    while(SDL_PollEvent(&event) && menu.input_state == INPUT_S_ID){
        switch (event.type){
        	case SDL_QUIT:
                running = false; break;
            case SDL_TEXTINPUT: // Get input from keyboard
                if (strlen(text) < 25) strcat(text, event.text.text);
                    break;
            case SDL_KEYDOWN: // Spesial keys cases
                switch (event.key.keysym.scancode){ 
                    case SDL_SCANCODE_ESCAPE: // go back
                        menu.select=NOT_SELECTED;
                        reset_input();
                        menu.input_state = INPUT_S_ID;
                        break;
                    case SDL_SCANCODE_BACKSPACE: // del last element :
                        text[strlen(text)-1] = 0;
                        break;
                    case SDL_SCANCODE_RETURN:
                        menu.input_state = INPUT_S_PASSWD;
                        break;

                }
        }
    }

        render_text_on_xy(renderer,text,340,315,black);
}


void login_passwd_input(SDL_Renderer* renderer,char* text){
    SDL_StartTextInput();
    SDL_Event event;
    while(SDL_PollEvent(&event) && menu.input_state == INPUT_S_PASSWD){
        switch (event.type){
        	case SDL_QUIT:
                running = false; break;
            case SDL_TEXTINPUT: // Get input from keyboard
                if (strlen(text) < 25) {
                    strcat(text, event.text.text);
                }
                    break;
            case SDL_KEYDOWN: // Spesial keys cases
                switch (event.key.keysym.scancode){ 
                    case SDL_SCANCODE_ESCAPE: // go back
                        menu.select=NOT_SELECTED;
                        reset_input();
                        break;
                    case SDL_SCANCODE_BACKSPACE: // del last element :
                        text[strlen(text)-1] = 0;
                        break;
                    case SDL_SCANCODE_RETURN:
                        // look for data in file
                        break;

                }
        }
    }
       
        render_text_on_xy(renderer,login_data.id,340,315,black);
        
        i=0;
        while(i<strlen(text)){
            hide[i]='*';
            i++;
        }

        render_text_on_xy(renderer,hide,340,395,black);       
        i=0;
        while(i<25){
            hide[i]=0;
            i++;
        }
}




void render_login(SDL_Renderer *renderer){
    render_on_xy(LOGIN_BG,renderer,0,0);
    render_on_xy(LOG_IN,renderer,329,479);
    switch (menu.input_state){
        case INPUT_S_ID :
            login_txt_input(renderer,login_data.id);
        case INPUT_S_PASSWD :
            login_passwd_input(renderer,login_data.passwd);

    // hover        
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if (mouse_x > 329 && mouse_x < 329 + BOTTON_H && mouse_y > 479 && mouse_y < 479 + BOTTON_W)
    { render_on_xy(LOG_IN,renderer,329+4,479);}
    }
    

    }










void singup_txt_input(SDL_Renderer* renderer,char* text){
    SDL_StartTextInput();
 
    SDL_Event event;
    while(SDL_PollEvent(&event) && menu.input_state == INPUT_S_ID){
        switch (event.type){
            case SDL_QUIT:
                running = false; break;
            case SDL_TEXTINPUT: // Get input from keyboard
                if (strlen(text) < 25) strcat(text, event.text.text);
                    break;
            case SDL_KEYDOWN: // Spesial keys cases
                switch (event.key.keysym.scancode){ 
                    case SDL_SCANCODE_ESCAPE: // go back
                        menu.select=NOT_SELECTED;
                        reset_input();
                        menu.input_state = INPUT_S_ID;
                        break;
                    case SDL_SCANCODE_BACKSPACE: // del last element :
                        text[strlen(text)-1] = 0;
                        break;
                    case SDL_SCANCODE_RETURN:
                        menu.input_state = INPUT_S_PASSWD;
                        break;

                }
        }
    }

        render_text_on_xy(renderer,text,340,315,black);
}


void singup_passwd_input(SDL_Renderer* renderer,char* text){
    SDL_StartTextInput();
    SDL_Event event;
    while(SDL_PollEvent(&event) && menu.input_state == INPUT_S_PASSWD){
        switch (event.type){
            case SDL_QUIT:
                running = false; break;
            case SDL_TEXTINPUT: // Get input from keyboard
                if (strlen(text) < 25) {
                    strcat(text, event.text.text);
                }
                    break;
            case SDL_KEYDOWN: // Spesial keys cases
                switch (event.key.keysym.scancode){ 
                    case SDL_SCANCODE_ESCAPE: // go back
                        menu.select=NOT_SELECTED;
                        reset_input();
                        break;
                    case SDL_SCANCODE_BACKSPACE: // del last element :
                        text[strlen(text)-1] = 0;
                        break;
                    case SDL_SCANCODE_RETURN:
                        // look for data in file
                        break;

                }
        }
    }
       
        render_text_on_xy(renderer,singup_data.id,340,315,black);
        
        i=0;
        while(i<strlen(text)){
            hide[i]='*';
            i++;
        }

        render_text_on_xy(renderer,hide,340,395,black);       
        i=0;
        while(i<25){
            hide[i]=0;
            i++;
        }
}




void render_singup(SDL_Renderer *renderer){
    render_on_xy(SINGUP_BG,renderer,0,0);
    render_on_xy(SING_UP,renderer,329,479); // login botton
    switch (menu.input_state){
        case INPUT_S_ID :
            singup_txt_input(renderer,singup_data.id);
        case INPUT_S_PASSWD :
            singup_passwd_input(renderer,singup_data.passwd);

    // hover        
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if (mouse_x > 329 && mouse_x < 329 + BOTTON_H && mouse_y > 479 && mouse_y < 479 + BOTTON_W)
    { render_on_xy(SING_UP,renderer,329+4,479);}
}
}

// menu_loop :
void menu_loop(SDL_Renderer *renderer){



     // game loop
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

                render_login(renderer);
                
            
                 break;
            case SINGUP_SELECTED :
                render_singup(renderer);
                break;  
            case PLAY_AS_GUEST_SELECTED:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
                         "WARNING",
                         "Your Progress will not be saved :(",
                         NULL);

                break;
            case TOP_PLAYERS_SELECTED:
                m = "top players HERE";
                render_text_on_xy(renderer,m, 300,300,white);
                break;
            case HOW_TO_PLAY_SELECTED:
                m ="how to play HERE";
                render_text_on_xy(renderer,m, 300,300,white);
                break;
        }



        
        SDL_RenderPresent(renderer);  // Show what was drawn
    }
    
}


// game state loop ; 

