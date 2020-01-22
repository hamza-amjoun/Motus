#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

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
menu_ menu = {.select=0,.hover = 0,.input_state = 1};


game_options_ game_options = { // defalt values 
    .select=0,
    .hover = 0,
    .nbr_letters=0,
    .nbr_time=20,

};


/// game state
game_ game= {.state= MENU_STATE,};

user_ user;
// player data :
singup_txt_ singup_player;


// temp lings for testing:
linge6_ linge6_1 = { .box[0]=1,.box[1]=2,.box[2]=3,.box[3]=4,.box[4]=1,.box[5]=3,};
linge9_ linge9_1 = { .box[0]=1,.box[1]=2,.box[2]=3,.box[3]=4,.box[4]=1,.box[5]=3,};

// empty linges data for rundring :
linge6_ empty_linge6 = {  .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,};
linge7_ empty_linge7 = {  .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,.box[6]=1};
linge8_ empty_linge8 = {  .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,.box[6]=1,.box[7]=1};
linge9_ empty_linge9 = {  .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,.box[6]=1,.box[7]=1,.box[8]=1};
linge10_ empty_linge10 ={ .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,.box[6]=1,.box[7]=1,.box[8]=1,.box[9]=1,};


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
                        if (login(login_data)==1) {
                            game.state=PLAYING_STATE;
                        } else {
                            reset_input();
                        }
                        
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
                        signup(singup_data);
                        strcpy(singup_data.id,"");
                        strcpy(singup_data.passwd,"");
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



    //play_game(renderer,6,20,user);
    //render_empty_grid9(renderer);
    //player_input(renderer ,linge9_1.text,linge9_1.chow,linge9_1.box, 1);
    //render_linge9(renderer,linge9_1,LN_1);
    //render_linge_text9(renderer,linge9_1,LN_1);


    
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

// render box : 
void render_box(SDL_Renderer *renderer,int boxBG,int x,int y){
    switch (boxBG){
        case BOX_R_BLACK:
            render_on_xy(BOX_BLACK_BG,renderer,x,y);
            break;
        case BOX_R_BLEU:
            render_on_xy(BOX_BLEU_BG,renderer,x,y); break;
        case BOX_R_RED:
            render_on_xy(BOX_RED_BG,renderer,x,y); break;
        case BOX_R_YELLOW:
            render_on_xy(BOX_YELLOW_BG,renderer,x,y); break;
    }
}


// render box text : 
void render_box_text(SDL_Renderer *renderer,int boxCH,int x,int y){
    switch (boxCH){
        case A:
            render_on_xy(A_R,renderer,x,y);break;
        case B:
            render_on_xy(B_R,renderer,x,y);break;
        case C:
            render_on_xy(C_R,renderer,x,y);break;
        case D:
            render_on_xy(D_R,renderer,x,y);break;
        case E:
            render_on_xy(E_R,renderer,x,y);break;
        case F:
            render_on_xy(F_R,renderer,x,y);break;
        case G:
            render_on_xy(G_R,renderer,x,y);break;
        case H:
            render_on_xy(H_R,renderer,x,y);break;
        case I:
            render_on_xy(I_R,renderer,x,y);break;
        case J:
            render_on_xy(J_R,renderer,x,y);break;
        case K:
            render_on_xy(K_R,renderer,x,y);break;
        case L:
            render_on_xy(L_R,renderer,x,y);break;
        case M:
            render_on_xy(M_R,renderer,x,y);break;
        case N:
            render_on_xy(N_R,renderer,x,y);break;
        case O:
            render_on_xy(O_R,renderer,x,y);break;
        case P:
            render_on_xy(P_R,renderer,x,y);break;
        case Q:
            render_on_xy(Q_R,renderer,x,y);break;
        case R:
            render_on_xy(R_R,renderer,x,y);break;
        case S:
            render_on_xy(S_R,renderer,x,y);break;
        case T:
            render_on_xy(T_R,renderer,x,y);break;
        case U:
            render_on_xy(U_R,renderer,x,y);break;
        case V:
            render_on_xy(V_R,renderer,x,y);break;
        case W:
            render_on_xy(W_R,renderer,x,y);break;
        case X:
            render_on_xy(X_R,renderer,x,y);break;
        case Y:
            render_on_xy(Y_R,renderer,x,y);break;
        case Z:
            render_on_xy(Z_R,renderer,x,y);break;

    }
}

// render linge ;

void render_linge6(SDL_Renderer *renderer,linge6_ linge,int h_pose){
            int x=266,y=160;
            render_box(renderer,linge.box[0],x,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[1],x+BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[2],x+2*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[3],x+3*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[4],x+4*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[5],x+5*BOX,y+(h_pose - 1)*BOX);}

void render_linge7(SDL_Renderer *renderer,linge7_ linge,int h_pose){
            int x=266-25,y=160;
            render_box(renderer,linge.box[0],x,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[1],x+BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[2],x+2*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[3],x+3*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[4],x+4*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[5],x+5*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[6],x+6*BOX,y+(h_pose - 1)*BOX);}

void render_linge8(SDL_Renderer *renderer,linge8_ linge,int h_pose){
            int x=266-50,y=160;
            render_box(renderer,linge.box[0],x,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[1],x+BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[2],x+2*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[3],x+3*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[4],x+4*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[5],x+5*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[6],x+6*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[7],x+7*BOX,y+(h_pose - 1)*BOX);}

void render_linge9(SDL_Renderer *renderer,linge9_ linge,int h_pose){
            int x=266-75,y=160;
            render_box(renderer,linge.box[0],x,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[1],x+BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[2],x+2*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[3],x+3*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[4],x+4*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[5],x+5*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[6],x+6*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[7],x+7*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[8],x+8*BOX,y+(h_pose - 1)*BOX);}

void render_linge10(SDL_Renderer *renderer,linge10_ linge,int h_pose){
            int x=266-100,y=160;
            render_box(renderer,linge.box[0],x,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[1],x+BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[2],x+2*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[3],x+3*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[4],x+4*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[5],x+5*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[6],x+6*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[7],x+7*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[8],x+8*BOX,y+(h_pose - 1)*BOX);
            render_box(renderer,linge.box[9],x+9*BOX,y+(h_pose - 1)*BOX);}
////////////////////////////////////////////////////////////////////////////////////
void player_input(SDL_Renderer* renderer ,char* text,int* chow,int* box, int h_pose){
SDL_Event event;  //SDL_Event event;
                 while(SDL_PollEvent(&event)){
                    switch (event.type){
                        case SDL_QUIT:
                               running = false; break;
                        case SDL_KEYDOWN: // Spesial keys cases
                            switch (event.key.keysym.scancode){ 
                                case SDL_SCANCODE_ESCAPE: // go back
                                    //menu.select=NOT_SELECTED;
                                    //reset_input();
                                    break;
                                case SDL_SCANCODE_BACKSPACE: // del last element :
                                    text[i-1]=0;chow[i-1]=0;box[i-1]=BOX_R_BLACK; i--; break;
                                 case SDL_SCANCODE_RETURN:
                                // enter case
                                    break;
                                case SDL_SCANCODE_Q:
                                    text[i]='A'; chow[i]=A;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_W:
                                    text[i]='Z'; chow[i]=Z;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_E:
                                    text[i]='E'; chow[i]=E;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_R:
                                    text[i]='R'; chow[i]=R;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_T:
                                    text[i]='T'; chow[i]=T;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_Y:
                                    text[i]='Y'; chow[i]=Y;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_U:
                                    text[i]='U'; chow[i]=U;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_I:
                                    text[i]='I'; chow[i]=I;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_O:
                                    text[i]='O'; chow[i]=O;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_P:
                                    text[i]='P'; chow[i]=P;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_A:
                                    text[i]='Q'; chow[i]=Q;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_S:
                                    text[i]='S'; chow[i]=S;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_D:
                                    text[i]='D'; chow[i]=D;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_F:
                                    text[i]='F'; chow[i]=F;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_G:
                                    text[i]='G'; chow[i]=G;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_H:
                                    text[i]='H'; chow[i]=H;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_J:
                                    text[i]='J'; chow[i]=J;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_K:
                                    text[i]='K'; chow[i]=K;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_L:
                                    text[i]='L'; chow[i]=L;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_SEMICOLON:
                                    text[i]='M'; chow[i]=M;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_Z:
                                    text[i]='W'; chow[i]=W;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_X:
                                    text[i]='X'; chow[i]=X;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_C:
                                    text[i]='C'; chow[i]=C;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_V:
                                    text[i]='V'; chow[i]=V;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_B:
                                    text[i]='B'; chow[i]=B;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_N:
                                    text[i]='N'; chow[i]=N;box[i]=BOX_R_BLEU; i++; break;
            }
        }
    }


}


// linge text data chow :
void render_linge_text6(SDL_Renderer *renderer,linge6_ linge,int h_pose){
    int x=266,y=160;
    render_box_text(renderer,linge.chow[0],x,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[1],x+BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[2],x+2*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[3],x+3*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[4],x+4*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[5],x+5*BOX,y+(h_pose - 1)*BOX);}

void render_linge_text7(SDL_Renderer *renderer,linge7_ linge,int h_pose){
    int x=266-25,y=160;
    render_box_text(renderer,linge.chow[0],x,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[1],x+BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[2],x+2*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[3],x+3*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[4],x+4*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[5],x+5*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[6],x+6*BOX,y+(h_pose - 1)*BOX);}

void render_linge_text8(SDL_Renderer *renderer,linge8_ linge,int h_pose){
    int x=266-50,y=160;
    render_box_text(renderer,linge.chow[0],x,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[1],x+BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[2],x+2*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[3],x+3*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[4],x+4*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[5],x+5*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[6],x+6*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[7],x+7*BOX,y+(h_pose - 1)*BOX);}

void render_linge_text9(SDL_Renderer *renderer,linge9_ linge,int h_pose){
    int x=266-75,y=160;
    render_box_text(renderer,linge.chow[0],x,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[1],x+BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[2],x+2*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[3],x+3*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[4],x+4*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[5],x+5*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[6],x+6*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[7],x+7*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[8],x+8*BOX,y+(h_pose - 1)*BOX);}

void render_linge_text10(SDL_Renderer *renderer,linge10_ linge,int h_pose){
    int x=266-100,y=160;
    render_box_text(renderer,linge.chow[0],x,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[1],x+BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[2],x+2*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[3],x+3*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[4],x+4*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[5],x+5*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[6],x+6*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[7],x+7*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[8],x+8*BOX,y+(h_pose - 1)*BOX);
    render_box_text(renderer,linge.chow[9],x+9*BOX,y+(h_pose - 1)*BOX);}



// empty  grids :
void render_empty_grid6(SDL_Renderer *renderer){
    render_linge6(renderer,empty_linge6,LN_1);render_linge6(renderer,empty_linge6,LN_2);
    render_linge6(renderer,empty_linge6,LN_3);render_linge6(renderer,empty_linge6,LN_4);
    render_linge6(renderer,empty_linge6,LN_5);render_linge6(renderer,empty_linge6,LN_6);
    render_linge6(renderer,empty_linge6,LN_7);}

void render_empty_grid7(SDL_Renderer *renderer){
    render_linge7(renderer,empty_linge7,LN_1);render_linge7(renderer,empty_linge7,LN_2);
    render_linge7(renderer,empty_linge7,LN_3);render_linge7(renderer,empty_linge7,LN_4);
    render_linge7(renderer,empty_linge7,LN_5);render_linge7(renderer,empty_linge7,LN_6);
    render_linge7(renderer,empty_linge7,LN_7);}

void render_empty_grid8(SDL_Renderer *renderer){
    render_linge8(renderer,empty_linge8,LN_1);render_linge8(renderer,empty_linge8,LN_2);
    render_linge8(renderer,empty_linge8,LN_3);render_linge8(renderer,empty_linge8,LN_4);
    render_linge8(renderer,empty_linge8,LN_5);render_linge8(renderer,empty_linge8,LN_6);
    render_linge8(renderer,empty_linge8,LN_7);}

void render_empty_grid9(SDL_Renderer *renderer){
    render_linge9(renderer,empty_linge9,LN_1);render_linge9(renderer,empty_linge9,LN_2);
    render_linge9(renderer,empty_linge9,LN_3);render_linge9(renderer,empty_linge9,LN_4);
    render_linge9(renderer,empty_linge9,LN_5);render_linge9(renderer,empty_linge9,LN_6);
    render_linge9(renderer,empty_linge9,LN_7);}

void render_empty_grid10(SDL_Renderer *renderer){
    render_linge10(renderer,empty_linge10,LN_1);render_linge10(renderer,empty_linge10,LN_2);
    render_linge10(renderer,empty_linge10,LN_3);render_linge10(renderer,empty_linge10,LN_4);
    render_linge10(renderer,empty_linge10,LN_5);render_linge10(renderer,empty_linge10,LN_6);
    render_linge10(renderer,empty_linge10,LN_7);}

///////////////////////////////////////////


void render_play_as_gest(SDL_Renderer *renderer){
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"WARNING","Your Progress wont be saved :(",NULL);
                game.state=PLAYING_STATE;
                menu.select=NOT_SELECTED;
                menu.hover=NOT_SELECTED;
                user.score=699;
}
                                                                /////////////////////////////:
                                            ////////////////////
////////////////////////////////////////////                            ////////////////////////////
int signup(singup_txt_ player){
    FILE* f=fopen("data/players.bin","ab");
    if(!f) return 0;
    fwrite(&player,sizeof(player),1,f);
    fclose(f);
    return 1;
}

int login(login_txt_ player){
    FILE* f= fopen("data/players.bin","rb");
    if(!f) {printf("Erreur ouverture fichier\n"); exit(0);}
    login_txt_ user;
    while(!feof(f)){
        fread(&user,sizeof(user),1,f);
        if(strcmp(user.id,player.id)==0 && strcmp(user.passwd,player.passwd)==0) return 1;
    }
    fclose(f);
    return 0;
}



char* generationMot(int nblettres,FILE* f, char*mot){
    int j,nblignes=0,i=0;
    char c;
    srand(time(NULL)*100);
    while((c = fgetc(f)) != EOF) {if(c == '\n') nblignes++;}
    fseek(f, 0L, SEEK_SET);
    j = rand() % nblignes + 1;
    do{
        fscanf(f,"%s",mot);
        i++;
    }while(i != j);
    return mot;
}
//saisi d'un mot/ la saisis n'est acceptée que si le mot saisi est de longueur nblettres
char* saisirMot(int nblettres,char* saisi){
    int i=0;
    char c;
    fflush(stdin);
    while(i < nblettres){
        if(isalpha(c=getchar())){
            saisi[i]=c; i++;
        }
    }
    saisi[i]='\0';
    for(int i=0;i<strlen(saisi);i++) saisi[i]=toupper(saisi[i]);
    return saisi;
}
//tester si le mot existe dans le dictionnaire
int motFrancais(char *mot, FILE* f,int nblettres){
    char c;
    int i;
    fseek(f,0L,SEEK_SET);
    while(f){
        char test[nblettres+1];
        i=0;
        while((c=fgetc(f) )!= '\n') {test[i]=c;i++;}
        test[i]='\0';
        if(strcmp(test,mot)==0) {printf("appartient au dictionnaire\n");return 1;}
    }
    printf("n'appartient pas\n");
    return -1;
}
//test sur les lettres: bien pacée, mal placée....
void verification(char *mot,char *saisi){
    for(int i=0; i<strlen( mot);i++){
        for(int j=0; j<strlen(mot);j++ ){
            if(mot[j]==saisi[i]){
                if(i==j) printf("%c lettre bien placée \n",saisi[i]); //carrérouge
                else printf(" %c lettre mal placée\n",saisi[i]);//cerclejaune
            } 
        }
    }
}
//choix du fichier selon la longueur du mot
FILE* ouvertureFichier(int nblettres){
    FILE* f=NULL;
    switch(nblettres){
        case NBR_L_6 : f=fopen("6letters.txt","r");break;
        case NBR_L_7 : f=fopen("7letters.txt","r");break;
        case NBR_L_8 : f=fopen("8letters.txt","r");break;
        case NBR_L_9 : f=fopen("9letters.txt","r");break;
        case NBR_L_10 : f=fopen("10letters.txt","r");break;
    }
    if(!f) {printf("erreur ouverture du fichier");exit(-1);}
    return f;
}
//déroulement de la partie
void PARTIE(int temps, int nblettres){
    game_options_ game_options;
    game_options.nbr_letters=nblettres;game_options.nbr_time=temps;game_options.score=0;
    char* motATrouver,*motSaisi;
    motATrouver=(char*)malloc(sizeof(char)*(nblettres+1));
    motSaisi=(char*)malloc(sizeof(char)*(nblettres+1));
    FILE* f=ouvertureFichier(nblettres);
    generationMot(nblettres,f,motATrouver);
    printf("%s\n", motATrouver);
    motSaisi=saisirMot(nblettres,motSaisi);
    if(motFrancais(motSaisi,f,nblettres)==1){ verification(motATrouver,motSaisi);}
}
//////////////////////////////













void play_game(SDL_Renderer *renderer,int letters,int time,user_ user){
    // temp :
    render_empty_grid9(renderer);
    player_input(renderer ,linge9_1.text,linge9_1.chow,linge9_1.box, 1);
    render_linge9(renderer,linge9_1,LN_1);
    render_linge_text9(renderer,linge9_1,LN_1);

}




////////////////////////////////////////////////////////////////////////////////////////////////:


void render_time(SDL_Renderer* renderer){
    

    int i = game_options.nbr_time;
    char str[10];
    sprintf(str, "%d", i);
    // Now str contains the integer as characters

    TTF_Init();
    TTF_Font * font = TTF_OpenFont(DEFAULT_FONT, 42);
    SDL_Rect dest;
    dest.x = 705; dest.y = 57;
    SDL_Surface * surface = TTF_RenderText_Blended(font, str, white);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();

}

void render_score(SDL_Renderer* renderer){
    

    int i = user.score;
    char str[10];
    sprintf(str, "%d", i);
    // Now str contains the integer as characters

    TTF_Init();
    TTF_Font * font = TTF_OpenFont(DEFAULT_FONT, 32);
    SDL_Rect dest;
    dest.x = 690; dest.y = 535;
    SDL_Surface * surface = TTF_RenderText_Blended(font, str, white);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();

}








void render_options(SDL_Renderer* renderer){
    switch(game_options.nbr_letters){
        case NBR_L_6 :
            render_empty_grid6(renderer);
            break;
        case NBR_L_7 :
            render_empty_grid7(renderer);
            break;
        case NBR_L_8 :
            render_empty_grid8(renderer);
            break;
        case NBR_L_9 :
            render_empty_grid9(renderer);
            break;
        case NBR_L_10 :
            render_empty_grid10(renderer);
            break;
    }

        render_time(renderer);
        render_score(renderer);

}

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

// menu_loop :
void menu_loop(SDL_Renderer *renderer){


     //loop
    SDL_Event event;
    while(running && game.state==MENU_STATE)
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
                render_play_as_gest(renderer);
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
////////////////////////////////////////////////////////////////////////////////////////////////////
void game_loop(SDL_Renderer *renderer){

     //loop
    SDL_Event event;
    while(running && game.state==PLAYING_STATE )
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
                        //game_options.select=NOT_SELECTED;
                        break;
                    }
        }

       

       
        SDL_RenderClear(renderer);
    switch(game_options.select) {
            case NOT_SELECTED:
               // render_game_menu(renderer);
                break;
            case START_SELECTED:
                    // start the game
                 break;
            case RESET_SELECTED :
                    // reset
                break;  
            case LOGOUT_SELECTED:
                game.state=MENU_STATE;
                game_options.select=NOT_SELECTED;
                game_options.hover=0;
                break;
            case NBR_6_SELECTED :
                game_options.nbr_letters=NBR_L_6;
                break;
            case NBR_7_SELECTED :
                game_options.nbr_letters=NBR_L_7;
                break;
            case NBR_8_SELECTED :
                game_options.nbr_letters=NBR_L_8;
                break;
            case NBR_9_SELECTED :
                game_options.nbr_letters=NBR_L_9;
                break;
            case NBR_10_SELECTED :
                game_options.nbr_letters=NBR_L_10;
                break;

            case TIME_10_SELECTED :
                game_options.nbr_time=TIME_L_10;
                break;
            case TIME_15_SELECTED :
                game_options.nbr_time=TIME_L_15;
                break;
            case TIME_20_SELECTED :
                game_options.nbr_time=TIME_L_20;
                break;


}
                 }

        
    render_game_menu(renderer);
    render_options(renderer);
    SDL_RenderPresent(renderer);



    }
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:
//////////////////////////////////////////////////////////////://////////////////////////////////////////////////////////////:
void main_loop(SDL_Renderer *renderer){
    
    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
         

        switch(event.type){
            case SDL_QUIT:
                running = false; break;
}
}



        SDL_RenderClear(renderer);
        switch (game.state){
            case MENU_STATE : 
                menu_loop(renderer);
                break;
            case PLAYING_STATE :
                game_loop(renderer);
                break;
        }  
        SDL_RenderPresent(renderer); 
}
}
