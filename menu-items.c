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


game_options_ game_options = { // defalt values 
    .select=0,
    .hover = 0,
    .nbr_letters=6,
    .nbr_time=20,

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



//render top players :

void render_top_players(SDL_Renderer *renderer){
    render_on_xy(TOP_PLAYERS_BG,renderer,0,0);
}


void render_game_menu(SDL_Renderer *renderer){

    int x1=24,y1=242,nxt=54;  // x1,y1 pos of first botton, nxt : how far is next pos 
    render_on_xy(GAME_BG,renderer,0,0);


    render_on_xy(NBR_6,renderer,x1,y1);
    render_on_xy(NBR_7,renderer,x1,y1+nxt);
    render_on_xy(NBR_8,renderer,x1,y1+2*nxt);
    render_on_xy(NBR_9,renderer,x1,y1+3*nxt);
    render_on_xy(NBR_10,renderer,x1,y1+4*nxt);

    int x2=716,y2=250,nxt2=70;
    render_on_xy(TIME_10,renderer,x2,y2);
    render_on_xy(TIME_15,renderer,x2,y2+nxt2);
    render_on_xy(TIME_20,renderer,x2,y2+2*nxt2);

    int y3=533;
    render_on_xy(START_BT,renderer,445,y3);
    render_on_xy(RESET_BT,renderer,445-BOTTON_H-30,y3);
    render_on_xy(LOGOUT_BT,renderer,445-2*BOTTON_H-60,y3);


    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    
    // bottons hover effect : /////////////////////////////////////////////////////////
    if (mouse_x > 445 && mouse_x < 445 + BOTTON_H && mouse_y > y3 && mouse_y < y3 + BOTTON_W){
         render_on_xy(START_BT,renderer,445+4,y3);
            game_options.hover=START_SELECTED;
    }

    if (mouse_x > 445-BOTTON_H-30 && mouse_x < 445-BOTTON_H-30 + BOTTON_H && mouse_y > y3 && mouse_y < y3 + BOTTON_W){
         render_on_xy(RESET_BT,renderer,445-BOTTON_H-30+4,y3);
            game_options.hover=RESET_SELECTED;
    }    
    
    if (mouse_x > 445-2*BOTTON_H-60 && mouse_x < 445-2*BOTTON_H-60 + BOTTON_H && mouse_y > y3 && mouse_y < y3 + BOTTON_W){
         render_on_xy(LOGOUT_BT,renderer,445-2*BOTTON_H-60+4,y3);
            game_options.hover=LOGOUT_SELECTED;
    }
    // nbr arrows effects : ///////////////////////////////////////////////////////////
    if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1 && mouse_y < y1 + ARROW_W){
        render_on_xy(NBR_6,renderer,x1+1,y1);
        game_options.hover=NBR_6_SELECTED;
    }
if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1+nxt && mouse_y < y1+nxt + ARROW_W){
        render_on_xy(NBR_7,renderer,x1+1,y1+nxt);
        game_options.hover=NBR_7_SELECTED; 
}
if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1+2*nxt && mouse_y < y1+2*nxt + ARROW_W){
        render_on_xy(NBR_8,renderer,x1+1,y1+2*nxt);
        game_options.hover=NBR_8_SELECTED;   
}
if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1+3*nxt && mouse_y < y1+3*nxt + ARROW_W){
        render_on_xy(NBR_9,renderer,x1+1,y1+3*nxt);
        game_options.hover=NBR_9_SELECTED;
}
if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1+4*nxt && mouse_y < y1+4*nxt + ARROW_W){
        render_on_xy(NBR_10,renderer,x1+1,y1+4*nxt);
        game_options.hover=NBR_10_SELECTED;
}

// nbr arrows effects : ///////////////////////////////////////////////////////////

    if (mouse_x > x2 && mouse_x < x2 + ARROW_H && mouse_y > y2 && mouse_y < y2 + ARROW_W){
        render_on_xy(TIME_10,renderer,x2-1,y2);
        game_options.hover=TIME_10_SELECTED;
    }
    if (mouse_x > x2 && mouse_x < x2 + ARROW_H && mouse_y > y2+nxt2 && mouse_y < y2+nxt2 + ARROW_W){
        render_on_xy(TIME_15,renderer,x2-1,y2+nxt2);
        game_options.hover=TIME_15_SELECTED;
    }
    if (mouse_x > x2 && mouse_x < x2 + ARROW_H && mouse_y > y2+2*nxt2 && mouse_y < y2+2*nxt2 + ARROW_W){
        render_on_xy(TIME_20,renderer,x2-1,y2+2*nxt2);
        game_options.hover=TIME_20_SELECTED;
    }

}




/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

// menu_loop :
void menu_loop(SDL_Renderer *renderer){



     //loop
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
                         "Your Progress wont be saved :(",
                         NULL);
                menu.select=NOT_SELECTED; // temp
                break;
            case TOP_PLAYERS_SELECTED:
                render_top_players(renderer);
                break;
            case HOW_TO_PLAY_SELECTED:
                render_on_xy(HOW_TO_BG,renderer,0,0);
                break;
        }



        
        SDL_RenderPresent(renderer);  // Show what was drawn
    }
    
}


// game state loop ; 
//////////////////////////////////////////////////////////////////////////////////////////////////
void game_loop(SDL_Renderer *renderer){

     //loop
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
                 game_options.select = game_options.hover; // if mouse inside botton borders + botton click => SELECTED
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode){
                    case SDL_SCANCODE_ESCAPE: // Escape + return keys => return to menu
                        game_options.select=NOT_SELECTED;
                        break;
                    }
        }

       

        }
    SDL_RenderClear(renderer);
    // cases: 

    render_game_menu(renderer);

    SDL_RenderPresent(renderer); 
    }
}