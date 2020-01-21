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

// temp lings for testing:
linge6_ linge6_1 = { .box[0]=1,.box[1]=2,.box[2]=3,.box[3]=4,.box[4]=1,.box[5]=3,};
linge9_ linge9_1 = { .box[0]=1,.box[1]=2,.box[2]=3,.box[3]=4,.box[4]=1,.box[5]=3,};

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






    //render_empty_grid6(renderer);
    render_empty_grid9(renderer);
    player_input(renderer ,linge9_1.text,linge9_1.chow,linge9_1.box, 1);
    render_linge9(renderer,linge9_1,LN_1);
    render_linge_text9(renderer,linge9_1,LN_1);






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
    render_linge6(renderer,empty_linge6,LN_1);
    render_linge6(renderer,empty_linge6,LN_2);
    render_linge6(renderer,empty_linge6,LN_3);
    render_linge6(renderer,empty_linge6,LN_4);
    render_linge6(renderer,empty_linge6,LN_5);
    render_linge6(renderer,empty_linge6,LN_6);
    render_linge6(renderer,empty_linge6,LN_7);}

void render_empty_grid7(SDL_Renderer *renderer){
    render_linge7(renderer,empty_linge7,LN_1);
    render_linge7(renderer,empty_linge7,LN_2);
    render_linge7(renderer,empty_linge7,LN_3);
    render_linge7(renderer,empty_linge7,LN_4);
    render_linge7(renderer,empty_linge7,LN_5);
    render_linge7(renderer,empty_linge7,LN_6);
    render_linge7(renderer,empty_linge7,LN_7);}

void render_empty_grid8(SDL_Renderer *renderer){
    render_linge8(renderer,empty_linge8,LN_1);
    render_linge8(renderer,empty_linge8,LN_2);
    render_linge8(renderer,empty_linge8,LN_3);
    render_linge8(renderer,empty_linge8,LN_4);
    render_linge8(renderer,empty_linge8,LN_5);
    render_linge8(renderer,empty_linge8,LN_6);
    render_linge8(renderer,empty_linge8,LN_7);}

void render_empty_grid9(SDL_Renderer *renderer){
    render_linge9(renderer,empty_linge9,LN_1);
    render_linge9(renderer,empty_linge9,LN_2);
    render_linge9(renderer,empty_linge9,LN_3);
    render_linge9(renderer,empty_linge9,LN_4);
    render_linge9(renderer,empty_linge9,LN_5);
    render_linge9(renderer,empty_linge9,LN_6);
    render_linge9(renderer,empty_linge9,LN_7);}

void render_empty_grid10(SDL_Renderer *renderer){
    render_linge10(renderer,empty_linge10,LN_1);
    render_linge10(renderer,empty_linge10,LN_2);
    render_linge10(renderer,empty_linge10,LN_3);
    render_linge10(renderer,empty_linge10,LN_4);
    render_linge10(renderer,empty_linge10,LN_5);
    render_linge10(renderer,empty_linge10,LN_6);
    render_linge10(renderer,empty_linge10,LN_7);}




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
                        //game_options.select=NOT_SELECTED;
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