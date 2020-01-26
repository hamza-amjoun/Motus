#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <fmodex/fmod.h>
#include "game.h"
#include "menu-items.h"	
#include "rendering.h"
// variables needed :
int sco=0; // see if score added or not yet
login_txt_ login_data;  // login informations
singup_txt_ singup_data; // singup info 
bool running = true; // see if the X botton clicked or not
int i=0; // enumeration var
char hide[25]; // used to print a unvisible passwd
int input_state = 1; // see if there is input or not
int temps=20; // time initialisation 
int tempsActuel; // used in timer
int tempsPrecedent; // usef in timer
menu_ menu = {.select=0,.hover = 0,.input_state = 1};// struct menu initialisation
// data initialisation 
playing_data6_ playing_data6;
playing_data7_ playing_data7;
playing_data8_ playing_data8;
playing_data9_ playing_data9;
playing_data10_ playing_data10;
// game options initialisation :
game_options_ game_options = {.select=0,.hover = 0,.nbr_letters=0,.nbr_time=20,};
game_ game= {.state= MENU_STATE,};/// game state
singup_txt_ singup_player;// player data :
// empty linges data for rundring :
linge6_ empty_linge6 = {  .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,};
linge7_ empty_linge7 = {  .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,.box[6]=1};
linge8_ empty_linge8 = {  .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,.box[6]=1,.box[7]=1};
linge9_ empty_linge9 = {  .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,.box[6]=1,.box[7]=1,.box[8]=1};
linge10_ empty_linge10 ={ .box[0]=1,.box[1]=1,.box[2]=1,.box[3]=1,.box[4]=1,.box[5]=1,.box[6]=1,.box[7]=1,.box[8]=1,.box[9]=1,};
// colors used to runder colord text
const SDL_Color white = { .r = 255, .g = 255, .b = 255};
const SDL_Color black = { .r = 0, .g = 0, .b = 0};
// data initialisation :
data_grid6_ data_grid6;
data_grid6_ new6;
data_grid7_ data_grid7;
data_grid7_ new7;
data_grid8_ data_grid8;
data_grid8_ new8;
data_grid9_ data_grid9;
data_grid9_ new9;
data_grid10_ data_grid10;
data_grid10_ new10;
int pass=1; // linge of input
int prev=0; 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int isASCII(char* c){
    for(int i=0;*(c+i)!='\0';i++) {if(c[i]<0 || c[i]>127) return 0;}
    return 1;
}
char* tochar(int i,char* str){
  sprintf(str, "%d", i);
  return str;
}
void swap(topPlayer *a, topPlayer *b) 
{ 
    topPlayer temp;
    strcpy(temp.id,a->id); temp.score=a->score;
    strcpy(a->id,b->id); a->score=b->score;
    strcpy(b->id,temp.id); b->score=temp.score;
} 
int empty(char* filename, char* mode){
    FILE* f=fopen(filename,mode);
    fseek(f,0L,SEEK_END);
    int vide=(ftell(f)==0L);
    fclose(f);
    return vide;
}
int existe(login_txt_ player){
    FILE* f=fopen("data/players.bin","rb");
    login_txt_ user;
    while(1){
        fread(&user,sizeof(user),1,f);
        if(feof(f)) break;
        if(strcmp(user.id,player.id)==0) return 1;
    }
    fclose(f);
    return 0;
}
int signup(singup_txt_ player){
    int signup;
    player.score=0;
    FILE* f=fopen("data/players.bin","ab");
    if(!f) return 0;
    if(empty("data/players.bin","ab+")==1){
        fwrite(&player,sizeof(player),1,f);
        signup=1;
    }
    else{
        login_txt_ user;
        strcpy(user.id,player.id);strcpy(user.passwd,player.passwd);user.score=0;
        if(existe(user)==0) {fwrite(&player,sizeof(player),1,f); signup=1;}
        else { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Oops!!","alredy exists :( ",NULL);
        signup=0;}//notification ;
    }
    fclose(f);
    return signup;
}
int login(login_txt_ player){
    FILE* f= fopen("data/players.bin","rb");
    if(!f) {printf("Erreur ouverture fichier\n"); exit(0);}
    return existe(player);
}

void topPlayers(login_txt_ player,int score){
    FILE* f=fopen("data/topPlayers.txt","a+");
    if(empty("data/topPlayers.txt","a+")==1){
        fprintf(f,"%s %d\n",player.id,score);
    }else{
        fseek(f,0L,SEEK_SET);
        topPlayer *top=(topPlayer*)malloc(sizeof(topPlayer)*11); 
        int i=0,existe=0,k,j;
        while(1){
            fscanf(f,"%s%d",top[i].id,&top[i].score);
            if(feof(f)) break;
            i++;
        }
        fclose(f);
        remove("data/topPlayers.txt");
        for ( j = 0; j<i ;j++) if(strcmp(top[j].id,player.id)==0){top[j].score=score;existe=1;break;}
        if(existe==0){strcpy(top[i].id,player.id);top[i].score=score;}
        for (j=0;j<i-1;j++){
            for(k=j+1;k<i;k++){
                if(top[j].score>top[k].score) swap(&top[j],&top[k]);
            }
        }
        FILE* f=fopen("data/topPlayers.txt","a+");
        if(!f) printf("erreur\n");
        while(i>-1){
            if(strcmp(top[i].id,"0")!=0 && top[i].score!=0 && isASCII(top[i].id)) fprintf(f,"%s %d\n",top[i].id,top[i].score);
            i--;

        }
        fclose(f);
    }
}
void score(login_txt_ player,game_options_ opt){
    sco=1;
    int pourcentage,score;
    switch(opt.nbr_time){
        case 10: pourcentage=5;break;
        case 15: pourcentage=0;break;
        case 20: pourcentage=-5;break;
    }
    score=(10*opt.nbr_letters)-opt.nbr_time;
    score+=(score*pourcentage)/100;
    FILE* f=fopen("data/players.bin","ab+");
    FILE* n=fopen("data/newfile.bin","ab+");
    rewind(f);
    if(!f) printf("Erreur ouverture\n");
    login_data.score+=score;
    login_txt_ user;
    while(1){
        fread(&user,sizeof(user),1,f);
        if(feof(f)) break;
            if(strcmp(user.id,player.id)==0 && strcmp(user.passwd,player.passwd)==0){
                user.score+=score;
                fwrite(&user,sizeof(user),1,n);
                topPlayers(user,user.score);
            }else{
                fwrite(&user,sizeof(user),1,n);
            }   
    }
    rename("data/newfile.bin","data/players.bin");
    fclose(n);
    fclose(f);
}
affichageTop  affichage;
int top_seen=0;

void show_top_players(){
    top_seen=1;
    FILE* stat_file = fopen("data/topPlayers.txt", "r");
    
    char ligne1[40];char ligne11[40];
    char ligne2[40];char ligne21[40];
    char ligne3[40];char ligne31[40];
    char ligne4[40];char ligne41[40];
    char ligne5[40];char ligne51[40];
    char ligne6[40];char ligne61[40];
    char ligne7[40];char ligne71[40];
    char ligne8[40];char ligne81[40];
    char ligne9[40];char ligne91[40];
    char ligne10[40];char ligne101[40];   
    char espace[20]="         ";

    fscanf(stat_file,"%s",ligne1);fscanf(stat_file,"%s",ligne11); strcat(ligne1,espace);
    fscanf(stat_file,"%s",ligne2);fscanf(stat_file,"%s",ligne21);strcat(ligne2,espace);
    fscanf(stat_file,"%s",ligne3);fscanf(stat_file,"%s",ligne31);strcat(ligne3,espace);
    fscanf(stat_file,"%s",ligne4);fscanf(stat_file,"%s",ligne41);strcat(ligne4,espace);
    fscanf(stat_file,"%s",ligne5);fscanf(stat_file,"%s",ligne51);strcat(ligne5,espace);
    fscanf(stat_file,"%s",ligne6);fscanf(stat_file,"%s",ligne61);strcat(ligne6,espace);
    fscanf(stat_file,"%s",ligne7);fscanf(stat_file,"%s",ligne71);strcat(ligne7,espace);
    fscanf(stat_file,"%s",ligne8);fscanf(stat_file,"%s",ligne81);strcat(ligne8,espace);
    fscanf(stat_file,"%s",ligne9);fscanf(stat_file,"%s",ligne91);strcat(ligne9,espace);
    fscanf(stat_file,"%s",ligne10);fscanf(stat_file,"%s",ligne101);strcat(ligne10,espace);

    strcat(ligne1,ligne11); strcpy(affichage.ligne1,ligne1);
    strcat(ligne2,ligne21); strcpy(affichage.ligne2,ligne2);
    strcat(ligne3,ligne31); strcpy(affichage.ligne3,ligne3);
    strcat(ligne4,ligne41); strcpy(affichage.ligne4,ligne4);
    strcat(ligne5,ligne51); strcpy(affichage.ligne5,ligne5);
    strcat(ligne6,ligne61); strcpy(affichage.ligne6,ligne6);
    strcat(ligne7,ligne71); strcpy(affichage.ligne7,ligne7);
    strcat(ligne8,ligne81); strcpy(affichage.ligne8,ligne8);
    strcat(ligne9,ligne91); strcpy(affichage.ligne9,ligne9);
    strcat(ligne10,ligne101); strcpy(affichage.ligne10,ligne10);

    fclose(stat_file);
}
//génération aléatoire d'un mot
char* generationMot(FILE* f, char*mot){
    
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
//indice
int indice(int nbr_letters){
    srand(time(NULL)*100);
    return rand()%(nbr_letters-1)+1;
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


int correct(char *mot,char *saisi){
    if(strcmp(mot,saisi)==0) return 1;
    return 0;
}
//test sur les lettres: bien pacée, mal placée....
void verification(char *mot,char *saisi,int* box){
    int taille=strlen(mot),tab[taille];
    for(int i=0;i<taille;i++) tab[i]=-1;
    for(int i=0; i<taille;i++){
        for(int j=0; j<taille;j++ ){
            if(mot[i]==saisi[j]){
                if(i==j) tab[j]=1;
                else if(tab[j]!=1) tab[j]=0;
            } 
        }
    }
    for (int i = 0; i < taille; i++)
    {
        switch(tab[i]){
            case -1: box[i]=BOX_R_BLEU; printf("%c n'existe pas\n",saisi[i]);break;
            case 0: box[i]=BOX_R_YELLOW;printf("%c mal\n",saisi[i]);break;
            case 1: box[i]=BOX_R_RED; printf("%c bien\n",saisi[i]);break;
        }
    }
}

//choix du fichier selon la longueur du mot
FILE* ouvertureFichier(int nblettres){
    FILE* f=NULL;
    switch(nblettres){
        case NBR_L_6 : f=fopen("data/6letters.txt","r");break;
        case NBR_L_7 : f=fopen("data/7letters.txt","r");break;
        case NBR_L_8 : f=fopen("data/8letters.txt","r");break;
        case NBR_L_9 : f=fopen("data/9letters.txt","r");break;
        case NBR_L_10 : f=fopen("data/10letters.txt","r");break;
    }
    if(!f) {printf("erreur ouverture du fichier");exit(-1);}
    return f;
}
int motFrancais(char *mot,int nblettres){
    FILE* f=ouvertureFichier(nblettres);
    char c;
    int i;
    fseek(f,0L,SEEK_SET);
    while(!feof(f)){
        char test[nblettres+1];
        i=0;
        while((c=fgetc(f) )!= '\n' && !feof(f)) {test[i]=c;i++;}
        test[i]='\0';
        if(strcmp(test,mot)==0){ printf("appartient au dictionnaire\n"); return 1;}
    }
    printf("n'appartient pas\n");
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// reset user input in input and singup
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
// take user login text to verify it and print it on screen
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
                        SDL_StopTextInput();
                        break;

                }
        }
    }

        render_text_on_xy(renderer,text,340,315,black);
}
// takes usre passwd and show it as "*"
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
                        if (login(login_data)==1) { // if login data is correct
                            game.state=PLAYING_PARAMETERS_STATE; // move rendrer to playing sceen
                            menu.select=NOT_SELECTED;
                            menu.hover=NOT_SELECTED;
                            SDL_StopTextInput();
                        } else {
                            reset_input();
                            SDL_StopTextInput();
                        }
                        break;
                }
        }
    }  
        render_text_on_xy(renderer,login_data.id,340,315,black);
        i=0;
        while(i<strlen(text)){ // hide pass
            hide[i]='*';
            i++;
        }
        render_text_on_xy(renderer,hide,340,395,black);       
        i=0;
        while(i<25){ // if usr deleted a char from pass delet it from screen
            hide[i]=0; 
            i++;
        }
}
// render login BG  and take input
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
// take singup id
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
                        SDL_StopTextInput();
                        break;
                }
        }
    }
render_text_on_xy(renderer,text,340,315,black);
}
// take singup passwd
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
                        SDL_StopTextInput();
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
// render singup and take input
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
    int ne=80; // diff between 2 linges
    if (top_seen == 0){show_top_players();}
    render_text_on_xy(renderer,affichage.ligne1,132,167,white);
    render_text_on_xy(renderer,affichage.ligne2,132,167+ne,white);
    render_text_on_xy(renderer,affichage.ligne3,132,167+2*ne,white);
    render_text_on_xy(renderer,affichage.ligne4,132,167+3*ne,white);
    render_text_on_xy(renderer,affichage.ligne5,132,167+4*ne,white);
    render_text_on_xy(renderer,affichage.ligne6,500,167,white);
    render_text_on_xy(renderer,affichage.ligne7,500,167+ne,white);
    render_text_on_xy(renderer,affichage.ligne8,500,167+2*ne,white);
    render_text_on_xy(renderer,affichage.ligne9,500,167+3*ne,white);
    render_text_on_xy(renderer,affichage.ligne10,500,167+4*ne,white);
}
// render  playing menu
void render_game_menu(SDL_Renderer *renderer){
    int x1=24,y1=242,nxt=54;  // x1,y1 pos of first botton, nxt : how far is next pos 
    render_on_xy(GAME_BG,renderer,0,0); // BG
    render_on_xy(NBR_6,renderer,x1,y1); // nbr 6 botton
    render_on_xy(NBR_7,renderer,x1,y1+nxt);
    render_on_xy(NBR_8,renderer,x1,y1+2*nxt);
    render_on_xy(NBR_9,renderer,x1,y1+3*nxt);
    render_on_xy(NBR_10,renderer,x1,y1+4*nxt);
    int x2=716,y2=250,nxt2=70; // x2,y2 pos of first botton, nxt : how far is next pos 
    render_on_xy(TIME_10,renderer,x2,y2);
    render_on_xy(TIME_15,renderer,x2,y2+nxt2);
    render_on_xy(TIME_20,renderer,x2,y2+2*nxt2);
    int y3=533;
    render_on_xy(START_BT,renderer,445,y3); // start botton
    render_on_xy(RESET_BT,renderer,445-BOTTON_H-30,y3); // reset // botton
    render_on_xy(LOGOUT_BT,renderer,445-2*BOTTON_H-60,y3); // logout botton
    int mouse_x, mouse_y; 
    SDL_GetMouseState(&mouse_x, &mouse_y); // takes mouse position
    // bottons hover effect : ///
    if (mouse_x > 445 && mouse_x < 445 + BOTTON_H && mouse_y > y3 && mouse_y < y3 + BOTTON_W){
         render_on_xy(START_BT,renderer,445+4,y3);
            game_options.hover=START_SELECTED;}
    if (mouse_x > 445-BOTTON_H-30 && mouse_x < 445-BOTTON_H-30 + BOTTON_H && mouse_y > y3 && mouse_y < y3 + BOTTON_W){
         render_on_xy(RESET_BT,renderer,445-BOTTON_H-30+4,y3);
            game_options.hover=RESET_SELECTED;}    
    if (mouse_x > 445-2*BOTTON_H-60 && mouse_x < 445-2*BOTTON_H-60 + BOTTON_H && mouse_y > y3 && mouse_y < y3 + BOTTON_W){
         render_on_xy(LOGOUT_BT,renderer,445-2*BOTTON_H-60+4,y3);
            game_options.hover=LOGOUT_SELECTED;}
    if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1 && mouse_y < y1 + ARROW_W){
        render_on_xy(NBR_6,renderer,x1+1,y1);
        game_options.hover=NBR_6_SELECTED;}
    if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1+nxt && mouse_y < y1+nxt + ARROW_W){
        render_on_xy(NBR_7,renderer,x1+1,y1+nxt);
        game_options.hover=NBR_7_SELECTED;}
    if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1+2*nxt && mouse_y < y1+2*nxt + ARROW_W){
        render_on_xy(NBR_8,renderer,x1+1,y1+2*nxt);
        game_options.hover=NBR_8_SELECTED;  }
    if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1+3*nxt && mouse_y < y1+3*nxt + ARROW_W){
        render_on_xy(NBR_9,renderer,x1+1,y1+3*nxt);
        game_options.hover=NBR_9_SELECTED;}
    if (mouse_x > x1 && mouse_x < x1 + ARROW_H && mouse_y > y1+4*nxt && mouse_y < y1+4*nxt + ARROW_W){
        render_on_xy(NBR_10,renderer,x1+1,y1+4*nxt);
        game_options.hover=NBR_10_SELECTED;}
    if (mouse_x > x2 && mouse_x < x2 + ARROW_H && mouse_y > y2 && mouse_y < y2 + ARROW_W){
        render_on_xy(TIME_10,renderer,x2-1,y2);
        game_options.hover=TIME_10_SELECTED;}
    if (mouse_x > x2 && mouse_x < x2 + ARROW_H && mouse_y > y2+nxt2 && mouse_y < y2+nxt2 + ARROW_W){
        render_on_xy(TIME_15,renderer,x2-1,y2+nxt2);
        game_options.hover=TIME_15_SELECTED;}
    if (mouse_x > x2 && mouse_x < x2 + ARROW_H && mouse_y > y2+2*nxt2 && mouse_y < y2+2*nxt2 + ARROW_W){
        render_on_xy(TIME_20,renderer,x2-1,y2+2*nxt2);
        game_options.hover=TIME_20_SELECTED;}
}
// render box BG ( red , yellow , black , bleu)
void render_box(SDL_Renderer *renderer,int boxBG,int x,int y){
    switch (boxBG){
        case BOX_R_BLACK:render_on_xy(BOX_BLACK_BG,renderer,x,y);break;
        case BOX_R_BLEU:render_on_xy(BOX_BLEU_BG,renderer,x,y); break;
        case BOX_R_RED:render_on_xy(BOX_RED_BG,renderer,x,y); break;
        case BOX_R_YELLOW:render_on_xy(BOX_YELLOW_BG,renderer,x,y); break;
    }
}
// takes player input in the game: takes only alphabet and enter to verify .. 
void player_input(SDL_Renderer* renderer ,char* text,int* chow,int* box,int nbr_letters){
                    tempsActuel = SDL_GetTicks(); // timer
                        if (tempsActuel - tempsPrecedent > 1000){ temps--; // every 1s time-1
                            if (temps == 0){  // if time =0 move to next linge
                                pass++; temps=game_options.nbr_time; i=0; prev=0;} 
                        tempsPrecedent = tempsActuel;} // timer 
                SDL_Event event;  //SDL_Event event;
                 while(SDL_PollEvent(&event)){
                    switch (event.type){
                        case SDL_QUIT:
                               running = false; break; // X botton case
                        case SDL_KEYDOWN: // Spesial keys cases
                            switch (event.key.keysym.scancode){ 
                                case SDL_SCANCODE_BACKSPACE: // delete last element :
                                    text[i-1]=0;chow[i-1]=0;box[i-1]=BOX_R_BLACK; i--; break;
                                 case SDL_SCANCODE_RETURN:
                                    if (i==nbr_letters){
                                        if(motFrancais(text,nbr_letters)==1){ // verify if the intred word is french
                                            if(correct(text,playing_data6.generated)==1){ 
                                                game.state=GAME_OVER_STATE;
                                                score(login_data,game_options); // add score
                                                game_over(renderer,1,text); // move to game_over state
                                            }
                                            verification(playing_data6.generated,text,box);
                                        }
                                    pass++;// move to next linge
                                    i=0; // rest typing cursur place
                                    prev=0;
                                    temps=game_options.nbr_time; // reset timer
                                    }
                                    break;
                                  /******************** TAKE INPUT FROM KEYBOARD***********************/
                                case SDL_SCANCODE_Q: text[i]='A'; chow[i]=A;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_W: text[i]='Z'; chow[i]=Z;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_E: text[i]='E'; chow[i]=E;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_R: text[i]='R'; chow[i]=R;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_T: text[i]='T'; chow[i]=T;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_Y: text[i]='Y'; chow[i]=Y;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_U: text[i]='U'; chow[i]=U;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_I: text[i]='I'; chow[i]=I;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_O: text[i]='O'; chow[i]=O;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_P: text[i]='P'; chow[i]=P;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_A: text[i]='Q'; chow[i]=Q;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_S: text[i]='S'; chow[i]=S;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_D: text[i]='D'; chow[i]=D;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_F: text[i]='F'; chow[i]=F;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_G: text[i]='G'; chow[i]=G;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_H: text[i]='H'; chow[i]=H;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_J: text[i]='J'; chow[i]=J;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_K: text[i]='K'; chow[i]=K;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_L: text[i]='L'; chow[i]=L;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_Z: text[i]='W'; chow[i]=W;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_X: text[i]='X'; chow[i]=X;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_C: text[i]='C'; chow[i]=C;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_V: text[i]='V'; chow[i]=V;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_B: text[i]='B'; chow[i]=B;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_N: text[i]='N'; chow[i]=N;box[i]=BOX_R_BLEU; i++; break;
                                case SDL_SCANCODE_SEMICOLON: text[i]='M'; chow[i]=M;box[i]=BOX_R_BLEU; i++; break;
            }
        }
    }
}
// empty  grids : /////// I didn't use loops in because of SDL time and rendring problems  ////////////
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

// render data of grids to screen : /////// I didn't use loops in because of SDL time and rendring problems  ////////////
void render_data6(SDL_Renderer* renderer){
    render_linge6(renderer,data_grid6.linge1,1);render_linge_text6(renderer,data_grid6.linge1,1);
    render_linge6(renderer,data_grid6.linge2,2);render_linge_text6(renderer,data_grid6.linge2,2);
    render_linge6(renderer,data_grid6.linge3,3);render_linge_text6(renderer,data_grid6.linge3,3);
    render_linge6(renderer,data_grid6.linge4,4);render_linge_text6(renderer,data_grid6.linge4,4);
    render_linge6(renderer,data_grid6.linge5,5);render_linge_text6(renderer,data_grid6.linge5,5);
    render_linge6(renderer,data_grid6.linge6,6);render_linge_text6(renderer,data_grid6.linge6,6);
    render_linge6(renderer,data_grid6.linge7,7);render_linge_text6(renderer,data_grid6.linge7,7);}

void render_data7(SDL_Renderer* renderer){
    render_linge7(renderer,data_grid7.linge1,1);render_linge_text7(renderer,data_grid7.linge1,1);
    render_linge7(renderer,data_grid7.linge2,2);render_linge_text7(renderer,data_grid7.linge2,2);
    render_linge7(renderer,data_grid7.linge3,3);render_linge_text7(renderer,data_grid7.linge3,3);
    render_linge7(renderer,data_grid7.linge4,4);render_linge_text7(renderer,data_grid7.linge4,4);
    render_linge7(renderer,data_grid7.linge5,5);render_linge_text7(renderer,data_grid7.linge5,5);
    render_linge7(renderer,data_grid7.linge6,6);render_linge_text7(renderer,data_grid7.linge6,6);
    render_linge7(renderer,data_grid7.linge7,7);render_linge_text7(renderer,data_grid7.linge7,7);}

void render_data8(SDL_Renderer* renderer){
    render_linge8(renderer,data_grid8.linge1,1);render_linge_text8(renderer,data_grid8.linge1,1);
    render_linge8(renderer,data_grid8.linge2,2);render_linge_text8(renderer,data_grid8.linge2,2);
    render_linge8(renderer,data_grid8.linge3,3);render_linge_text8(renderer,data_grid8.linge3,3);
    render_linge8(renderer,data_grid8.linge4,4);render_linge_text8(renderer,data_grid8.linge4,4);
    render_linge8(renderer,data_grid8.linge5,5);render_linge_text8(renderer,data_grid8.linge5,5);
    render_linge8(renderer,data_grid8.linge6,6);render_linge_text8(renderer,data_grid8.linge6,6);
    render_linge8(renderer,data_grid8.linge7,7);render_linge_text8(renderer,data_grid8.linge7,7);}

void render_data9(SDL_Renderer* renderer){
    render_linge9(renderer,data_grid9.linge1,1);render_linge_text9(renderer,data_grid9.linge1,1);
    render_linge9(renderer,data_grid9.linge2,2);render_linge_text9(renderer,data_grid9.linge2,2);
    render_linge9(renderer,data_grid9.linge3,3);render_linge_text9(renderer,data_grid9.linge3,3);
    render_linge9(renderer,data_grid9.linge4,4);render_linge_text9(renderer,data_grid9.linge4,4);
    render_linge9(renderer,data_grid9.linge5,5);render_linge_text9(renderer,data_grid9.linge5,5);
    render_linge9(renderer,data_grid9.linge6,6);render_linge_text9(renderer,data_grid9.linge6,6);
    render_linge9(renderer,data_grid9.linge7,7);render_linge_text9(renderer,data_grid9.linge7,7);}

void render_data10(SDL_Renderer* renderer){
    render_linge10(renderer,data_grid10.linge1,1);render_linge_text10(renderer,data_grid10.linge1,1);
    render_linge10(renderer,data_grid10.linge2,2);render_linge_text10(renderer,data_grid10.linge2,2);
    render_linge10(renderer,data_grid10.linge3,3);render_linge_text10(renderer,data_grid10.linge3,3);
    render_linge10(renderer,data_grid10.linge4,4);render_linge_text10(renderer,data_grid10.linge4,4);
    render_linge10(renderer,data_grid10.linge5,5);render_linge_text10(renderer,data_grid10.linge5,5);
    render_linge10(renderer,data_grid10.linge6,6);render_linge_text10(renderer,data_grid10.linge6,6);
    render_linge10(renderer,data_grid10.linge7,7);render_linge_text10(renderer,data_grid10.linge7,7);
}

// in case playing 6 letters word /////// I didn't use loops in because of SDL time and rendring problems  ////////////
void input_data6(SDL_Renderer* renderer){
    switch(pass){ // pass is the linge of the grid6 we are typing in
        case 1 :
                if(prev==0){ // prev see if this part have been rendred or not
                data_grid6.linge1.box[1]=BOX_R_RED;
                data_grid6.linge1.chow[1]=txt_to_chow(playing_data6.generated,1);
                data_grid6.linge1.box[NBR_L_6-2]=BOX_R_RED;
                data_grid6.linge1.chow[NBR_L_6-2]=txt_to_chow(playing_data6.generated,NBR_L_6-2);
               prev=1;}
            player_input(renderer ,data_grid6.linge1.text,data_grid6.linge1.chow,data_grid6.linge1.box,6); // take input to linge1
            break;
        case 2 :
            if(prev==0){ // prev see if this part have been rendred or not
                data_grid6.linge2.box[1]=BOX_R_RED; // show indicateurs again
                data_grid6.linge2.chow[1]=txt_to_chow(playing_data6.generated,1);
                data_grid6.linge2.box[NBR_L_6-2]=BOX_R_RED;
                data_grid6.linge2.chow[NBR_L_6-2]=txt_to_chow(playing_data6.generated,NBR_L_6-2);
                // show reviled letters in the next linge : 
                if(data_grid6.linge1.box[0]==BOX_R_RED){
                    data_grid6.linge2.box[0]=BOX_R_RED;data_grid6.linge2.chow[0]=data_grid6.linge1.chow[0];}
                if(data_grid6.linge1.box[1]==BOX_R_RED){
                    data_grid6.linge2.box[1]=BOX_R_RED;data_grid6.linge2.chow[1]=data_grid6.linge1.chow[1];}
                if(data_grid6.linge1.box[2]==BOX_R_RED){
                    data_grid6.linge2.box[2]=BOX_R_RED;data_grid6.linge2.chow[2]=data_grid6.linge1.chow[2];}
                if(data_grid6.linge1.box[3]==BOX_R_RED){
                    data_grid6.linge2.box[3]=BOX_R_RED;data_grid6.linge2.chow[3]=data_grid6.linge1.chow[3];}
                if(data_grid6.linge1.box[4]==BOX_R_RED){
                    data_grid6.linge2.box[4]=BOX_R_RED;data_grid6.linge2.chow[4]=data_grid6.linge1.chow[4];}
                if(data_grid6.linge1.box[5]==BOX_R_RED){
                    data_grid6.linge2.box[5]=BOX_R_RED;data_grid6.linge2.chow[5]=data_grid6.linge1.chow[5];}
                prev=1;
            }
            player_input(renderer ,data_grid6.linge2.text,data_grid6.linge2.chow,data_grid6.linge2.box,6);
            break;
        case 3 :
            if(prev==0){
                data_grid6.linge3.box[1]=BOX_R_RED;
                data_grid6.linge3.chow[1]=txt_to_chow(playing_data6.generated,1);
                data_grid6.linge3.box[NBR_L_6-2]=BOX_R_RED;
                data_grid6.linge3.chow[NBR_L_6-2]=txt_to_chow(playing_data6.generated,NBR_L_6-2);
                if(data_grid6.linge2.box[0]==BOX_R_RED){
                    data_grid6.linge3.box[0]=BOX_R_RED;data_grid6.linge3.chow[0]=data_grid6.linge2.chow[0];}
                if(data_grid6.linge2.box[1]==BOX_R_RED){
                    data_grid6.linge3.box[1]=BOX_R_RED;data_grid6.linge3.chow[1]=data_grid6.linge2.chow[1];}
                if(data_grid6.linge2.box[2]==BOX_R_RED){
                    data_grid6.linge3.box[2]=BOX_R_RED;data_grid6.linge3.chow[2]=data_grid6.linge2.chow[2];}
                if(data_grid6.linge2.box[3]==BOX_R_RED){
                    data_grid6.linge3.box[3]=BOX_R_RED;data_grid6.linge3.chow[3]=data_grid6.linge2.chow[3];}
                if(data_grid6.linge2.box[4]==BOX_R_RED){
                    data_grid6.linge3.box[4]=BOX_R_RED;data_grid6.linge3.chow[4]=data_grid6.linge2.chow[4];}
                if(data_grid6.linge2.box[5]==BOX_R_RED){
                    data_grid6.linge3.box[5]=BOX_R_RED;data_grid6.linge3.chow[5]=data_grid6.linge2.chow[5];}
                prev=1;
            }
            player_input(renderer ,data_grid6.linge3.text,data_grid6.linge3.chow,data_grid6.linge3.box,6);
            break;
        case 4 :
            if(prev==0){
                data_grid6.linge4.box[1]=BOX_R_RED;
                data_grid6.linge4.chow[1]=txt_to_chow(playing_data6.generated,1);
                data_grid6.linge4.box[NBR_L_6-2]=BOX_R_RED;
                data_grid6.linge4.chow[NBR_L_6-2]=txt_to_chow(playing_data6.generated,NBR_L_6-2);
                if(data_grid6.linge3.box[0]==BOX_R_RED){
                    data_grid6.linge4.box[0]=BOX_R_RED;data_grid6.linge4.chow[0]=data_grid6.linge3.chow[0];}
                if(data_grid6.linge3.box[1]==BOX_R_RED){
                    data_grid6.linge4.box[1]=BOX_R_RED;data_grid6.linge4.chow[1]=data_grid6.linge3.chow[1];}
                if(data_grid6.linge3.box[2]==BOX_R_RED){
                    data_grid6.linge4.box[2]=BOX_R_RED;data_grid6.linge4.chow[2]=data_grid6.linge3.chow[2];}
                if(data_grid6.linge3.box[3]==BOX_R_RED){
                    data_grid6.linge4.box[3]=BOX_R_RED;data_grid6.linge4.chow[3]=data_grid6.linge3.chow[3];}
                if(data_grid6.linge3.box[4]==BOX_R_RED){
                    data_grid6.linge4.box[4]=BOX_R_RED;data_grid6.linge4.chow[4]=data_grid6.linge3.chow[4];}
                if(data_grid6.linge3.box[5]==BOX_R_RED){
                    data_grid6.linge4.box[5]=BOX_R_RED;data_grid6.linge4.chow[5]=data_grid6.linge3.chow[5];}
                prev=1;
            }
            player_input(renderer ,data_grid6.linge4.text,data_grid6.linge4.chow,data_grid6.linge4.box,6);
            break;
        case 5 :
            if(prev==0){
                data_grid6.linge5.box[1]=BOX_R_RED;
                data_grid6.linge5.chow[1]=txt_to_chow(playing_data6.generated,1);
                data_grid6.linge5.box[NBR_L_6-2]=BOX_R_RED;
                data_grid6.linge5.chow[NBR_L_6-2]=txt_to_chow(playing_data6.generated,NBR_L_6-2);
                if(data_grid6.linge4.box[0]==BOX_R_RED){
                    data_grid6.linge5.box[0]=BOX_R_RED;data_grid6.linge5.chow[0]=data_grid6.linge4.chow[0];}
                if(data_grid6.linge4.box[1]==BOX_R_RED){
                    data_grid6.linge5.box[1]=BOX_R_RED;data_grid6.linge5.chow[1]=data_grid6.linge4.chow[1];}
                if(data_grid6.linge4.box[2]==BOX_R_RED){
                    data_grid6.linge5.box[2]=BOX_R_RED;data_grid6.linge5.chow[2]=data_grid6.linge4.chow[2];}
                if(data_grid6.linge4.box[3]==BOX_R_RED){
                    data_grid6.linge5.box[3]=BOX_R_RED;data_grid6.linge5.chow[3]=data_grid6.linge4.chow[3];}
                if(data_grid6.linge4.box[4]==BOX_R_RED){
                    data_grid6.linge5.box[4]=BOX_R_RED;data_grid6.linge5.chow[4]=data_grid6.linge4.chow[4];}
                if(data_grid6.linge4.box[5]==BOX_R_RED){
                    data_grid6.linge5.box[5]=BOX_R_RED;data_grid6.linge5.chow[5]=data_grid6.linge4.chow[5];}
                prev=1;
            }
            player_input(renderer ,data_grid6.linge5.text,data_grid6.linge5.chow,data_grid6.linge5.box,6);
            break;
        case 6 :
            if(prev==0){
                data_grid6.linge6.box[1]=BOX_R_RED;
                data_grid6.linge6.chow[1]=txt_to_chow(playing_data6.generated,1);
                data_grid6.linge6.box[NBR_L_6-2]=BOX_R_RED;
                data_grid6.linge6.chow[NBR_L_6-2]=txt_to_chow(playing_data6.generated,NBR_L_6-2);
                if(data_grid6.linge5.box[0]==BOX_R_RED){
                    data_grid6.linge6.box[0]=BOX_R_RED;data_grid6.linge6.chow[0]=data_grid6.linge5.chow[0];}
                if(data_grid6.linge5.box[1]==BOX_R_RED){
                    data_grid6.linge6.box[1]=BOX_R_RED;data_grid6.linge6.chow[1]=data_grid6.linge5.chow[1];}
                if(data_grid6.linge5.box[2]==BOX_R_RED){
                    data_grid6.linge6.box[2]=BOX_R_RED;data_grid6.linge6.chow[2]=data_grid6.linge5.chow[2];}
                if(data_grid6.linge5.box[3]==BOX_R_RED){
                    data_grid6.linge6.box[3]=BOX_R_RED;data_grid6.linge6.chow[3]=data_grid6.linge5.chow[3];}
                if(data_grid6.linge5.box[4]==BOX_R_RED){
                    data_grid6.linge6.box[4]=BOX_R_RED;data_grid6.linge6.chow[4]=data_grid6.linge5.chow[4];}
                if(data_grid6.linge5.box[5]==BOX_R_RED){
                    data_grid6.linge6.box[5]=BOX_R_RED;data_grid6.linge6.chow[5]=data_grid6.linge5.chow[5];}
                prev=1;
            }
            player_input(renderer ,data_grid6.linge6.text,data_grid6.linge6.chow,data_grid6.linge6.box,6);
            break;
        case 7 :
            if(prev==0){
                data_grid6.linge7.box[1]=BOX_R_RED;
                data_grid6.linge7.chow[1]=txt_to_chow(playing_data6.generated,1);
                data_grid6.linge7.box[NBR_L_6-2]=BOX_R_RED;
                data_grid6.linge7.chow[NBR_L_6-2]=txt_to_chow(playing_data6.generated,NBR_L_6-2);
                if(data_grid6.linge6.box[0]==BOX_R_RED){
                    data_grid6.linge7.box[0]=BOX_R_RED;data_grid6.linge7.chow[0]=data_grid6.linge6.chow[0];}
                if(data_grid6.linge6.box[1]==BOX_R_RED){
                    data_grid6.linge7.box[1]=BOX_R_RED;data_grid6.linge7.chow[1]=data_grid6.linge6.chow[1];}
                if(data_grid6.linge6.box[2]==BOX_R_RED){
                    data_grid6.linge7.box[2]=BOX_R_RED;data_grid6.linge7.chow[2]=data_grid6.linge6.chow[2];}
                if(data_grid6.linge6.box[3]==BOX_R_RED){
                    data_grid6.linge7.box[3]=BOX_R_RED;data_grid6.linge7.chow[3]=data_grid6.linge6.chow[3];}
                if(data_grid6.linge6.box[4]==BOX_R_RED){
                    data_grid6.linge7.box[4]=BOX_R_RED;data_grid6.linge7.chow[4]=data_grid6.linge6.chow[4];}
                if(data_grid6.linge6.box[5]==BOX_R_RED){
                    data_grid6.linge7.box[5]=BOX_R_RED;data_grid6.linge7.chow[5]=data_grid6.linge6.chow[5];}
                prev=1;
            }
            player_input(renderer ,data_grid6.linge7.text,data_grid6.linge7.chow,data_grid6.linge7.box,6);
            break;
        case 8 :
                game.state=GAME_OVER_STATE;
                game_over(renderer,0,playing_data6.generated);
            break;    
    }
}

void input_data7(SDL_Renderer* renderer){
    switch(pass){
        case 1 :
                if(prev==0){
                data_grid7.linge1.box[1]=BOX_R_RED;
                data_grid7.linge1.chow[1]=txt_to_chow(playing_data7.generated,1);
                data_grid7.linge1.box[NBR_L_7-2]=BOX_R_RED;
                data_grid7.linge1.chow[NBR_L_7-2]=txt_to_chow(playing_data7.generated,NBR_L_7-2);
               prev=1;
           }
            player_input(renderer ,data_grid7.linge1.text,data_grid7.linge1.chow,data_grid7.linge1.box,7);
            break;
        case 2 :
            if(prev==0){
                data_grid7.linge2.box[1]=BOX_R_RED;
                data_grid7.linge2.chow[1]=txt_to_chow(playing_data7.generated,1);
                data_grid7.linge2.box[NBR_L_7-2]=BOX_R_RED;
                data_grid7.linge2.chow[NBR_L_7-2]=txt_to_chow(playing_data7.generated,NBR_L_7-2);
                if(data_grid7.linge1.box[0]==BOX_R_RED){
                    data_grid7.linge2.box[0]=BOX_R_RED;data_grid7.linge2.chow[0]=data_grid7.linge1.chow[0];}
                if(data_grid7.linge1.box[1]==BOX_R_RED){
                    data_grid7.linge2.box[1]=BOX_R_RED;data_grid7.linge2.chow[1]=data_grid7.linge1.chow[1];}
                if(data_grid7.linge1.box[2]==BOX_R_RED){
                    data_grid7.linge2.box[2]=BOX_R_RED;data_grid7.linge2.chow[2]=data_grid7.linge1.chow[2];}
                if(data_grid7.linge1.box[3]==BOX_R_RED){
                    data_grid7.linge2.box[3]=BOX_R_RED;data_grid7.linge2.chow[3]=data_grid7.linge1.chow[3];}
                if(data_grid7.linge1.box[4]==BOX_R_RED){
                    data_grid7.linge2.box[4]=BOX_R_RED;data_grid7.linge2.chow[4]=data_grid7.linge1.chow[4];}
                if(data_grid7.linge1.box[5]==BOX_R_RED){
                    data_grid7.linge2.box[5]=BOX_R_RED;data_grid7.linge2.chow[5]=data_grid7.linge1.chow[5];}
                if(data_grid7.linge1.box[6]==BOX_R_RED){
                    data_grid7.linge2.box[6]=BOX_R_RED;data_grid7.linge2.chow[6]=data_grid7.linge1.chow[6];}
                prev=1;
            }
            player_input(renderer ,data_grid7.linge2.text,data_grid7.linge2.chow,data_grid7.linge2.box,7);
            break;
        case 3 :
            if(prev==0){
                data_grid7.linge3.box[1]=BOX_R_RED;
                data_grid7.linge3.chow[1]=txt_to_chow(playing_data7.generated,1);
                data_grid7.linge3.box[NBR_L_7-2]=BOX_R_RED;
                data_grid7.linge3.chow[NBR_L_7-2]=txt_to_chow(playing_data7.generated,NBR_L_7-2);
                if(data_grid7.linge2.box[0]==BOX_R_RED){
                    data_grid7.linge3.box[0]=BOX_R_RED;data_grid7.linge3.chow[0]=data_grid7.linge2.chow[0];}
                if(data_grid7.linge2.box[1]==BOX_R_RED){
                    data_grid7.linge3.box[1]=BOX_R_RED;data_grid7.linge3.chow[1]=data_grid7.linge2.chow[1];}
                if(data_grid7.linge2.box[2]==BOX_R_RED){
                    data_grid7.linge3.box[2]=BOX_R_RED;data_grid7.linge3.chow[2]=data_grid7.linge2.chow[2];}
                if(data_grid7.linge2.box[3]==BOX_R_RED){
                    data_grid7.linge3.box[3]=BOX_R_RED;data_grid7.linge3.chow[3]=data_grid7.linge2.chow[3];}
                if(data_grid7.linge2.box[4]==BOX_R_RED){
                    data_grid7.linge3.box[4]=BOX_R_RED;data_grid7.linge3.chow[4]=data_grid7.linge2.chow[4];}
                if(data_grid7.linge2.box[5]==BOX_R_RED){
                    data_grid7.linge3.box[5]=BOX_R_RED;data_grid7.linge3.chow[5]=data_grid7.linge2.chow[5];}
                if(data_grid7.linge2.box[6]==BOX_R_RED){
                    data_grid7.linge3.box[6]=BOX_R_RED;data_grid7.linge3.chow[6]=data_grid7.linge2.chow[6];}
                prev=1;
            }
            player_input(renderer ,data_grid7.linge3.text,data_grid7.linge3.chow,data_grid7.linge3.box,7);
            break;
        case 4 :
            if(prev==0){
                data_grid7.linge4.box[1]=BOX_R_RED;
                data_grid7.linge4.chow[1]=txt_to_chow(playing_data7.generated,1);
                data_grid7.linge4.box[NBR_L_7-2]=BOX_R_RED;
                data_grid7.linge4.chow[NBR_L_7-2]=txt_to_chow(playing_data7.generated,NBR_L_7-2);
                if(data_grid7.linge3.box[0]==BOX_R_RED){
                    data_grid7.linge4.box[0]=BOX_R_RED;data_grid7.linge4.chow[0]=data_grid7.linge3.chow[0];}
                if(data_grid7.linge3.box[1]==BOX_R_RED){
                    data_grid7.linge4.box[1]=BOX_R_RED;data_grid7.linge4.chow[1]=data_grid7.linge3.chow[1];}
                if(data_grid7.linge3.box[2]==BOX_R_RED){
                    data_grid7.linge4.box[2]=BOX_R_RED;data_grid7.linge4.chow[2]=data_grid7.linge3.chow[2];}
                if(data_grid7.linge3.box[3]==BOX_R_RED){
                    data_grid7.linge4.box[3]=BOX_R_RED;data_grid7.linge4.chow[3]=data_grid7.linge3.chow[3];}
                if(data_grid7.linge3.box[4]==BOX_R_RED){
                    data_grid7.linge4.box[4]=BOX_R_RED;data_grid7.linge4.chow[4]=data_grid7.linge3.chow[4];}
                if(data_grid7.linge3.box[5]==BOX_R_RED){
                    data_grid7.linge4.box[5]=BOX_R_RED;data_grid7.linge4.chow[5]=data_grid7.linge3.chow[5];}
                if(data_grid7.linge3.box[6]==BOX_R_RED){
                    data_grid7.linge4.box[6]=BOX_R_RED;data_grid7.linge4.chow[6]=data_grid7.linge3.chow[6];}
                prev=1;
            }
            player_input(renderer ,data_grid7.linge4.text,data_grid7.linge4.chow,data_grid7.linge4.box,7);
            break;
        case 5 :
            if(prev==0){
                data_grid7.linge5.box[1]=BOX_R_RED;
                data_grid7.linge5.chow[1]=txt_to_chow(playing_data7.generated,1);
                data_grid7.linge5.box[NBR_L_7-2]=BOX_R_RED;
                data_grid7.linge5.chow[NBR_L_7-2]=txt_to_chow(playing_data7.generated,NBR_L_7-2);
                if(data_grid7.linge4.box[0]==BOX_R_RED){
                    data_grid7.linge5.box[0]=BOX_R_RED;data_grid7.linge5.chow[0]=data_grid7.linge4.chow[0];}
                if(data_grid7.linge4.box[1]==BOX_R_RED){
                    data_grid7.linge5.box[1]=BOX_R_RED;data_grid7.linge5.chow[1]=data_grid7.linge4.chow[1];}
                if(data_grid7.linge4.box[2]==BOX_R_RED){
                    data_grid7.linge5.box[2]=BOX_R_RED;data_grid7.linge5.chow[2]=data_grid7.linge4.chow[2];}
                if(data_grid7.linge4.box[3]==BOX_R_RED){
                    data_grid7.linge5.box[3]=BOX_R_RED;data_grid7.linge5.chow[3]=data_grid7.linge4.chow[3];}
                if(data_grid7.linge4.box[4]==BOX_R_RED){
                    data_grid7.linge5.box[4]=BOX_R_RED;data_grid7.linge5.chow[4]=data_grid7.linge4.chow[4];}
                if(data_grid7.linge4.box[5]==BOX_R_RED){
                    data_grid7.linge5.box[5]=BOX_R_RED;data_grid7.linge5.chow[5]=data_grid7.linge4.chow[5];}
                if(data_grid7.linge4.box[6]==BOX_R_RED){
                    data_grid7.linge5.box[6]=BOX_R_RED;data_grid7.linge5.chow[6]=data_grid7.linge4.chow[6];}
                prev=1;
            }
            player_input(renderer ,data_grid7.linge5.text,data_grid7.linge5.chow,data_grid7.linge5.box,7);
            break;
        case 6 :
            if(prev==0){
                data_grid7.linge6.box[1]=BOX_R_RED;
                data_grid7.linge6.chow[1]=txt_to_chow(playing_data7.generated,1);
                data_grid7.linge6.box[NBR_L_7-2]=BOX_R_RED;
                data_grid7.linge6.chow[NBR_L_7-2]=txt_to_chow(playing_data7.generated,NBR_L_7-2);
                if(data_grid7.linge5.box[0]==BOX_R_RED){
                    data_grid7.linge6.box[0]=BOX_R_RED;data_grid7.linge6.chow[0]=data_grid7.linge5.chow[0];}
                if(data_grid7.linge5.box[1]==BOX_R_RED){
                    data_grid7.linge6.box[1]=BOX_R_RED;data_grid7.linge6.chow[1]=data_grid7.linge5.chow[1];}
                if(data_grid7.linge5.box[2]==BOX_R_RED){
                    data_grid7.linge6.box[2]=BOX_R_RED;data_grid7.linge6.chow[2]=data_grid7.linge5.chow[2];}
                if(data_grid7.linge5.box[3]==BOX_R_RED){
                    data_grid7.linge6.box[3]=BOX_R_RED;data_grid7.linge6.chow[3]=data_grid7.linge5.chow[3];}
                if(data_grid7.linge5.box[4]==BOX_R_RED){
                    data_grid7.linge6.box[4]=BOX_R_RED;data_grid7.linge6.chow[4]=data_grid7.linge5.chow[4];}
                if(data_grid7.linge5.box[5]==BOX_R_RED){
                    data_grid7.linge6.box[5]=BOX_R_RED;data_grid7.linge6.chow[5]=data_grid7.linge5.chow[5];}
                if(data_grid7.linge5.box[6]==BOX_R_RED){
                    data_grid7.linge6.box[6]=BOX_R_RED;data_grid7.linge6.chow[6]=data_grid7.linge5.chow[6];}
                prev=1;
            }
            player_input(renderer ,data_grid7.linge6.text,data_grid7.linge6.chow,data_grid7.linge6.box,7);
            break;
        case 7 :
            if(prev==0){
                data_grid7.linge7.box[1]=BOX_R_RED;
                data_grid7.linge7.chow[1]=txt_to_chow(playing_data7.generated,1);
                data_grid7.linge7.box[NBR_L_7-2]=BOX_R_RED;
                data_grid7.linge7.chow[NBR_L_7-2]=txt_to_chow(playing_data7.generated,NBR_L_7-2);
                if(data_grid7.linge6.box[0]==BOX_R_RED){
                    data_grid7.linge7.box[0]=BOX_R_RED;data_grid7.linge7.chow[0]=data_grid7.linge6.chow[0];}
                if(data_grid7.linge6.box[1]==BOX_R_RED){
                    data_grid7.linge7.box[1]=BOX_R_RED;data_grid7.linge7.chow[1]=data_grid7.linge6.chow[1];}
                if(data_grid7.linge6.box[2]==BOX_R_RED){
                    data_grid7.linge7.box[2]=BOX_R_RED;data_grid7.linge7.chow[2]=data_grid7.linge6.chow[2];}
                if(data_grid7.linge6.box[3]==BOX_R_RED){
                    data_grid7.linge7.box[3]=BOX_R_RED;data_grid7.linge7.chow[3]=data_grid7.linge6.chow[3];}
                if(data_grid7.linge6.box[4]==BOX_R_RED){
                    data_grid7.linge7.box[4]=BOX_R_RED;data_grid7.linge7.chow[4]=data_grid7.linge6.chow[4];}
                if(data_grid7.linge6.box[5]==BOX_R_RED){
                    data_grid7.linge7.box[5]=BOX_R_RED;data_grid7.linge7.chow[5]=data_grid7.linge6.chow[5];}
                if(data_grid7.linge6.box[6]==BOX_R_RED){
                    data_grid7.linge7.box[6]=BOX_R_RED;data_grid7.linge7.chow[6]=data_grid7.linge6.chow[6];}
                prev=1;
            }
            player_input(renderer ,data_grid7.linge7.text,data_grid7.linge7.chow,data_grid7.linge7.box,7);
            break;
        case 8 :
                game.state=GAME_OVER_STATE;
                game_over(renderer,0,playing_data7.generated);
            break;
    }
}
// take input for case 8:
void input_data8(SDL_Renderer* renderer){
    switch(pass){
        case 1 :
                if(prev==0){
                data_grid8.linge1.box[1]=BOX_R_RED;
                data_grid8.linge1.chow[1]=txt_to_chow(playing_data8.generated,1);
                data_grid8.linge1.box[NBR_L_8-2]=BOX_R_RED;
                data_grid8.linge1.chow[NBR_L_8-2]=txt_to_chow(playing_data8.generated,NBR_L_8-2);
               prev=1;
           }
            player_input(renderer ,data_grid8.linge1.text,data_grid8.linge1.chow,data_grid8.linge1.box,8);
            break;
        case 2 :
            if(prev==0){
                data_grid8.linge2.box[1]=BOX_R_RED;
                data_grid8.linge2.chow[1]=txt_to_chow(playing_data8.generated,1);
                data_grid8.linge2.box[NBR_L_8-2]=BOX_R_RED;
                data_grid8.linge2.chow[NBR_L_8-2]=txt_to_chow(playing_data8.generated,NBR_L_8-2);
                if(data_grid8.linge1.box[0]==BOX_R_RED){
                    data_grid8.linge2.box[0]=BOX_R_RED;data_grid8.linge2.chow[0]=data_grid8.linge1.chow[0];}
                if(data_grid8.linge1.box[1]==BOX_R_RED){
                    data_grid8.linge2.box[1]=BOX_R_RED;data_grid8.linge2.chow[1]=data_grid8.linge1.chow[1];}
                if(data_grid8.linge1.box[2]==BOX_R_RED){
                    data_grid8.linge2.box[2]=BOX_R_RED;data_grid8.linge2.chow[2]=data_grid8.linge1.chow[2];}
                if(data_grid8.linge1.box[3]==BOX_R_RED){
                    data_grid8.linge2.box[3]=BOX_R_RED;data_grid8.linge2.chow[3]=data_grid8.linge1.chow[3];}
                if(data_grid8.linge1.box[4]==BOX_R_RED){
                    data_grid8.linge2.box[4]=BOX_R_RED;data_grid8.linge2.chow[4]=data_grid8.linge1.chow[4];}
                if(data_grid8.linge1.box[5]==BOX_R_RED){
                    data_grid8.linge2.box[5]=BOX_R_RED;data_grid8.linge2.chow[5]=data_grid8.linge1.chow[5];}
                if(data_grid8.linge1.box[6]==BOX_R_RED){
                    data_grid8.linge2.box[6]=BOX_R_RED;data_grid8.linge2.chow[6]=data_grid8.linge1.chow[6];}
                if(data_grid8.linge1.box[7]==BOX_R_RED){
                    data_grid8.linge2.box[7]=BOX_R_RED;data_grid8.linge2.chow[7]=data_grid8.linge1.chow[7];}
                prev=1;
            }
            player_input(renderer ,data_grid8.linge2.text,data_grid8.linge2.chow,data_grid8.linge2.box,8);
            break;
        case 3 :
            if(prev==0){
                data_grid8.linge3.box[1]=BOX_R_RED;
                data_grid8.linge3.chow[1]=txt_to_chow(playing_data8.generated,1);
                data_grid8.linge3.box[NBR_L_8-2]=BOX_R_RED;
                data_grid8.linge3.chow[NBR_L_8-2]=txt_to_chow(playing_data8.generated,NBR_L_8-2);
                if(data_grid8.linge2.box[0]==BOX_R_RED){
                    data_grid8.linge3.box[0]=BOX_R_RED;data_grid8.linge3.chow[0]=data_grid8.linge2.chow[0];}
                if(data_grid8.linge2.box[1]==BOX_R_RED){
                    data_grid8.linge3.box[1]=BOX_R_RED;data_grid8.linge3.chow[1]=data_grid8.linge2.chow[1];}
                if(data_grid8.linge2.box[2]==BOX_R_RED){
                    data_grid8.linge3.box[2]=BOX_R_RED;data_grid8.linge3.chow[2]=data_grid8.linge2.chow[2];}
                if(data_grid8.linge2.box[3]==BOX_R_RED){
                    data_grid8.linge3.box[3]=BOX_R_RED;data_grid8.linge3.chow[3]=data_grid8.linge2.chow[3];}
                if(data_grid8.linge2.box[4]==BOX_R_RED){
                    data_grid8.linge3.box[4]=BOX_R_RED;data_grid8.linge3.chow[4]=data_grid8.linge2.chow[4];}
                if(data_grid8.linge2.box[5]==BOX_R_RED){
                    data_grid8.linge3.box[5]=BOX_R_RED;data_grid8.linge3.chow[5]=data_grid8.linge2.chow[5];}
                if(data_grid8.linge2.box[6]==BOX_R_RED){
                    data_grid8.linge3.box[6]=BOX_R_RED;data_grid8.linge3.chow[6]=data_grid8.linge2.chow[6];}
                if(data_grid8.linge2.box[7]==BOX_R_RED){
                    data_grid8.linge3.box[7]=BOX_R_RED;data_grid8.linge3.chow[7]=data_grid8.linge2.chow[7];}
                prev=1;
            }
            player_input(renderer ,data_grid8.linge3.text,data_grid8.linge3.chow,data_grid8.linge3.box,8);
            break;
        case 4 :
            if(prev==0){
                data_grid8.linge4.box[1]=BOX_R_RED;
                data_grid8.linge4.chow[1]=txt_to_chow(playing_data8.generated,1);
                data_grid8.linge4.box[NBR_L_8-2]=BOX_R_RED;
                data_grid8.linge4.chow[NBR_L_8-2]=txt_to_chow(playing_data8.generated,NBR_L_8-2);
                if(data_grid8.linge3.box[0]==BOX_R_RED){
                    data_grid8.linge4.box[0]=BOX_R_RED;data_grid8.linge4.chow[0]=data_grid8.linge3.chow[0];}
                if(data_grid8.linge3.box[1]==BOX_R_RED){
                    data_grid8.linge4.box[1]=BOX_R_RED;data_grid8.linge4.chow[1]=data_grid8.linge3.chow[1];}
                if(data_grid8.linge3.box[2]==BOX_R_RED){
                    data_grid8.linge4.box[2]=BOX_R_RED;data_grid8.linge4.chow[2]=data_grid8.linge3.chow[2];}
                if(data_grid8.linge3.box[3]==BOX_R_RED){
                    data_grid8.linge4.box[3]=BOX_R_RED;data_grid8.linge4.chow[3]=data_grid8.linge3.chow[3];}
                if(data_grid8.linge3.box[4]==BOX_R_RED){
                    data_grid8.linge4.box[4]=BOX_R_RED;data_grid8.linge4.chow[4]=data_grid8.linge3.chow[4];}
                if(data_grid8.linge3.box[5]==BOX_R_RED){
                    data_grid8.linge4.box[5]=BOX_R_RED;data_grid8.linge4.chow[5]=data_grid8.linge3.chow[5];}
                if(data_grid8.linge3.box[6]==BOX_R_RED){
                    data_grid8.linge4.box[6]=BOX_R_RED;data_grid8.linge4.chow[6]=data_grid8.linge3.chow[6];}
                if(data_grid8.linge3.box[7]==BOX_R_RED){
                    data_grid8.linge4.box[7]=BOX_R_RED;data_grid8.linge4.chow[7]=data_grid8.linge3.chow[7];}
                prev=1;
            }
            player_input(renderer ,data_grid8.linge4.text,data_grid8.linge4.chow,data_grid8.linge4.box,8);
            break;
        case 5 :
            if(prev==0){
                data_grid8.linge5.box[1]=BOX_R_RED;
                data_grid8.linge5.chow[1]=txt_to_chow(playing_data8.generated,1);
                data_grid8.linge5.box[NBR_L_8-2]=BOX_R_RED;
                data_grid8.linge5.chow[NBR_L_8-2]=txt_to_chow(playing_data8.generated,NBR_L_8-2);
                if(data_grid8.linge4.box[0]==BOX_R_RED){
                    data_grid8.linge5.box[0]=BOX_R_RED;data_grid8.linge5.chow[0]=data_grid8.linge4.chow[0];}
                if(data_grid8.linge4.box[1]==BOX_R_RED){
                    data_grid8.linge5.box[1]=BOX_R_RED;data_grid8.linge5.chow[1]=data_grid8.linge4.chow[1];}
                if(data_grid8.linge4.box[2]==BOX_R_RED){
                    data_grid8.linge5.box[2]=BOX_R_RED;data_grid8.linge5.chow[2]=data_grid8.linge4.chow[2];}
                if(data_grid8.linge4.box[3]==BOX_R_RED){
                    data_grid8.linge5.box[3]=BOX_R_RED;data_grid8.linge5.chow[3]=data_grid8.linge4.chow[3];}
                if(data_grid8.linge4.box[4]==BOX_R_RED){
                    data_grid8.linge5.box[4]=BOX_R_RED;data_grid8.linge5.chow[4]=data_grid8.linge4.chow[4];}
                if(data_grid8.linge4.box[5]==BOX_R_RED){
                    data_grid8.linge5.box[5]=BOX_R_RED;data_grid8.linge5.chow[5]=data_grid8.linge4.chow[5];}
                if(data_grid8.linge4.box[6]==BOX_R_RED){
                    data_grid8.linge5.box[6]=BOX_R_RED;data_grid8.linge5.chow[6]=data_grid8.linge4.chow[6];}
                if(data_grid8.linge4.box[7]==BOX_R_RED){
                    data_grid8.linge5.box[7]=BOX_R_RED;data_grid8.linge5.chow[7]=data_grid8.linge4.chow[7];}
                prev=1;
            }
            player_input(renderer ,data_grid8.linge5.text,data_grid8.linge5.chow,data_grid8.linge5.box,8);
            break;
        case 6 :
            if(prev==0){
                data_grid8.linge6.box[1]=BOX_R_RED;
                data_grid8.linge6.chow[1]=txt_to_chow(playing_data8.generated,1);
                data_grid8.linge6.box[NBR_L_8-2]=BOX_R_RED;
                data_grid8.linge6.chow[NBR_L_8-2]=txt_to_chow(playing_data8.generated,NBR_L_8-2);
                if(data_grid8.linge5.box[0]==BOX_R_RED){
                    data_grid8.linge6.box[0]=BOX_R_RED;data_grid8.linge6.chow[0]=data_grid8.linge5.chow[0];}
                if(data_grid8.linge5.box[1]==BOX_R_RED){
                    data_grid8.linge6.box[1]=BOX_R_RED;data_grid8.linge6.chow[1]=data_grid8.linge5.chow[1];}
                if(data_grid8.linge5.box[2]==BOX_R_RED){
                    data_grid8.linge6.box[2]=BOX_R_RED;data_grid8.linge6.chow[2]=data_grid8.linge5.chow[2];}
                if(data_grid8.linge5.box[3]==BOX_R_RED){
                    data_grid8.linge6.box[3]=BOX_R_RED;data_grid8.linge6.chow[3]=data_grid8.linge5.chow[3];}
                if(data_grid8.linge5.box[4]==BOX_R_RED){
                    data_grid8.linge6.box[4]=BOX_R_RED;data_grid8.linge6.chow[4]=data_grid8.linge5.chow[4];}
                if(data_grid8.linge5.box[5]==BOX_R_RED){
                    data_grid8.linge6.box[5]=BOX_R_RED;data_grid8.linge6.chow[5]=data_grid8.linge5.chow[5];}
                if(data_grid8.linge5.box[6]==BOX_R_RED){
                    data_grid8.linge6.box[6]=BOX_R_RED;data_grid8.linge6.chow[6]=data_grid8.linge5.chow[6];}
                if(data_grid8.linge5.box[7]==BOX_R_RED){
                    data_grid8.linge6.box[7]=BOX_R_RED;data_grid8.linge6.chow[7]=data_grid8.linge5.chow[7];}
                prev=1;
            }
            player_input(renderer ,data_grid8.linge6.text,data_grid8.linge6.chow,data_grid8.linge6.box,8);
            break;
        case 7 :
            if(prev==0){
                data_grid8.linge7.box[1]=BOX_R_RED;
                data_grid8.linge7.chow[1]=txt_to_chow(playing_data8.generated,1);
                data_grid8.linge7.box[NBR_L_8-2]=BOX_R_RED;
                data_grid8.linge7.chow[NBR_L_8-2]=txt_to_chow(playing_data8.generated,NBR_L_8-2);
                if(data_grid8.linge6.box[0]==BOX_R_RED){
                    data_grid8.linge7.box[0]=BOX_R_RED;data_grid8.linge7.chow[0]=data_grid8.linge6.chow[0];}
                if(data_grid8.linge6.box[1]==BOX_R_RED){
                    data_grid8.linge7.box[1]=BOX_R_RED;data_grid8.linge7.chow[1]=data_grid8.linge6.chow[1];}
                if(data_grid8.linge6.box[2]==BOX_R_RED){
                    data_grid8.linge7.box[2]=BOX_R_RED;data_grid8.linge7.chow[2]=data_grid8.linge6.chow[2];}
                if(data_grid8.linge6.box[3]==BOX_R_RED){
                    data_grid8.linge7.box[3]=BOX_R_RED;data_grid8.linge7.chow[3]=data_grid8.linge6.chow[3];}
                if(data_grid8.linge6.box[4]==BOX_R_RED){
                    data_grid8.linge7.box[4]=BOX_R_RED;data_grid8.linge7.chow[4]=data_grid8.linge6.chow[4];}
                if(data_grid8.linge6.box[5]==BOX_R_RED){
                    data_grid8.linge7.box[5]=BOX_R_RED;data_grid8.linge7.chow[5]=data_grid8.linge6.chow[5];}
                if(data_grid8.linge6.box[7]==BOX_R_RED){
                    data_grid8.linge7.box[7]=BOX_R_RED;data_grid8.linge7.chow[7]=data_grid8.linge6.chow[7];}
                prev=1;
            }
            player_input(renderer ,data_grid8.linge7.text,data_grid8.linge7.chow,data_grid8.linge7.box,8);
            break;
        case 8 :
                game.state=GAME_OVER_STATE;
                game_over(renderer,0,playing_data8.generated);
            break;
    }
}
void input_data9(SDL_Renderer* renderer){
    switch(pass){
        case 1 :
                if(prev==0){
                data_grid9.linge1.box[1]=BOX_R_RED;
                data_grid9.linge1.chow[1]=txt_to_chow(playing_data9.generated,1);
                data_grid9.linge1.box[NBR_L_9-2]=BOX_R_RED;
                data_grid9.linge1.chow[NBR_L_9-2]=txt_to_chow(playing_data9.generated,NBR_L_9-2);
               prev=1;}
            player_input(renderer ,data_grid9.linge1.text,data_grid9.linge1.chow,data_grid9.linge1.box,9);
            break;
        case 2 :
            if(prev==0){
                data_grid9.linge2.box[1]=BOX_R_RED;
                data_grid9.linge2.chow[1]=txt_to_chow(playing_data9.generated,1);
                data_grid9.linge2.box[NBR_L_9-2]=BOX_R_RED;
                data_grid9.linge2.chow[NBR_L_9-2]=txt_to_chow(playing_data9.generated,NBR_L_9-2);
                if(data_grid9.linge1.box[0]==BOX_R_RED){
                    data_grid9.linge2.box[0]=BOX_R_RED;data_grid9.linge2.chow[0]=data_grid9.linge1.chow[0];}
                if(data_grid9.linge1.box[1]==BOX_R_RED){
                    data_grid9.linge2.box[1]=BOX_R_RED;data_grid9.linge2.chow[1]=data_grid9.linge1.chow[1];}
                if(data_grid9.linge1.box[2]==BOX_R_RED){
                    data_grid9.linge2.box[2]=BOX_R_RED;data_grid9.linge2.chow[2]=data_grid9.linge1.chow[2];}
                if(data_grid9.linge1.box[3]==BOX_R_RED){
                    data_grid9.linge2.box[3]=BOX_R_RED;data_grid9.linge2.chow[3]=data_grid9.linge1.chow[3];}
                if(data_grid9.linge1.box[4]==BOX_R_RED){
                    data_grid9.linge2.box[4]=BOX_R_RED;data_grid9.linge2.chow[4]=data_grid9.linge1.chow[4];}
                if(data_grid9.linge1.box[5]==BOX_R_RED){
                    data_grid9.linge2.box[5]=BOX_R_RED;data_grid9.linge2.chow[5]=data_grid9.linge1.chow[5];}
                if(data_grid9.linge1.box[6]==BOX_R_RED){
                    data_grid9.linge2.box[6]=BOX_R_RED;data_grid9.linge2.chow[6]=data_grid9.linge1.chow[6];}
                if(data_grid9.linge1.box[7]==BOX_R_RED){
                    data_grid9.linge2.box[7]=BOX_R_RED;data_grid9.linge2.chow[7]=data_grid9.linge1.chow[7];}
                if(data_grid9.linge1.box[8]==BOX_R_RED){
                    data_grid9.linge2.box[8]=BOX_R_RED;data_grid9.linge2.chow[8]=data_grid9.linge1.chow[8];}
                prev=1;}
            player_input(renderer ,data_grid9.linge2.text,data_grid9.linge2.chow,data_grid9.linge2.box,9);
            break;
        case 3 :
            if(prev==0){
                data_grid9.linge3.box[1]=BOX_R_RED;
                data_grid9.linge3.chow[1]=txt_to_chow(playing_data9.generated,1);
                data_grid9.linge3.box[NBR_L_9-2]=BOX_R_RED;
                data_grid9.linge3.chow[NBR_L_9-2]=txt_to_chow(playing_data9.generated,NBR_L_9-2);
                if(data_grid9.linge2.box[0]==BOX_R_RED){
                    data_grid9.linge3.box[0]=BOX_R_RED;data_grid9.linge3.chow[0]=data_grid9.linge2.chow[0];}
                if(data_grid9.linge2.box[1]==BOX_R_RED){
                    data_grid9.linge3.box[1]=BOX_R_RED;data_grid9.linge3.chow[1]=data_grid9.linge2.chow[1];}
                if(data_grid9.linge2.box[2]==BOX_R_RED){
                    data_grid9.linge3.box[2]=BOX_R_RED;data_grid9.linge3.chow[2]=data_grid9.linge2.chow[2];}
                if(data_grid9.linge2.box[3]==BOX_R_RED){
                    data_grid9.linge3.box[3]=BOX_R_RED;data_grid9.linge3.chow[3]=data_grid9.linge2.chow[3];}
                if(data_grid9.linge2.box[4]==BOX_R_RED){
                    data_grid9.linge3.box[4]=BOX_R_RED;data_grid9.linge3.chow[4]=data_grid9.linge2.chow[4];}
                if(data_grid9.linge2.box[5]==BOX_R_RED){
                    data_grid9.linge3.box[5]=BOX_R_RED;data_grid9.linge3.chow[5]=data_grid9.linge2.chow[5];}
                if(data_grid9.linge2.box[6]==BOX_R_RED){
                    data_grid9.linge3.box[6]=BOX_R_RED;data_grid9.linge3.chow[6]=data_grid9.linge2.chow[6];}
                if(data_grid9.linge2.box[7]==BOX_R_RED){
                    data_grid9.linge3.box[7]=BOX_R_RED;data_grid9.linge3.chow[7]=data_grid9.linge2.chow[7];}
                if(data_grid9.linge2.box[8]==BOX_R_RED){
                    data_grid9.linge3.box[8]=BOX_R_RED;data_grid9.linge3.chow[8]=data_grid9.linge3.chow[8];}
                prev=1;
            }
            player_input(renderer ,data_grid9.linge3.text,data_grid9.linge3.chow,data_grid9.linge3.box,9);
            break;
        case 4 :
            if(prev==0){
                data_grid9.linge4.box[1]=BOX_R_RED;
                data_grid9.linge4.chow[1]=txt_to_chow(playing_data9.generated,1);
                data_grid9.linge4.box[NBR_L_9-2]=BOX_R_RED;
                data_grid9.linge4.chow[NBR_L_9-2]=txt_to_chow(playing_data9.generated,NBR_L_9-2);
                if(data_grid9.linge3.box[0]==BOX_R_RED){
                    data_grid9.linge4.box[0]=BOX_R_RED;data_grid9.linge4.chow[0]=data_grid9.linge3.chow[0];}
                if(data_grid9.linge3.box[1]==BOX_R_RED){
                    data_grid9.linge4.box[1]=BOX_R_RED;data_grid9.linge4.chow[1]=data_grid9.linge3.chow[1];}
                if(data_grid9.linge3.box[2]==BOX_R_RED){
                    data_grid9.linge4.box[2]=BOX_R_RED;data_grid9.linge4.chow[2]=data_grid9.linge3.chow[2];}
                if(data_grid9.linge3.box[3]==BOX_R_RED){
                    data_grid9.linge4.box[3]=BOX_R_RED;data_grid9.linge4.chow[3]=data_grid9.linge3.chow[3];}
                if(data_grid9.linge3.box[4]==BOX_R_RED){
                    data_grid9.linge4.box[4]=BOX_R_RED;data_grid9.linge4.chow[4]=data_grid9.linge3.chow[4];}
                if(data_grid9.linge3.box[5]==BOX_R_RED){
                    data_grid9.linge4.box[5]=BOX_R_RED;data_grid9.linge4.chow[5]=data_grid9.linge3.chow[5];}
                if(data_grid9.linge3.box[6]==BOX_R_RED){
                    data_grid9.linge4.box[6]=BOX_R_RED;data_grid9.linge4.chow[6]=data_grid9.linge3.chow[6];}
                if(data_grid9.linge3.box[7]==BOX_R_RED){
                    data_grid9.linge4.box[7]=BOX_R_RED;data_grid9.linge4.chow[7]=data_grid9.linge3.chow[7];}
                if(data_grid9.linge1.box[8]==BOX_R_RED){
                    data_grid9.linge4.box[8]=BOX_R_RED;data_grid9.linge4.chow[8]=data_grid9.linge1.chow[8];}
                prev=1;
            }
            player_input(renderer ,data_grid9.linge4.text,data_grid9.linge4.chow,data_grid9.linge4.box,8);
            break;
        case 5 :
            if(prev==0){
                data_grid9.linge5.box[1]=BOX_R_RED;
                data_grid9.linge5.chow[1]=txt_to_chow(playing_data9.generated,1);
                data_grid9.linge5.box[NBR_L_9-2]=BOX_R_RED;
                data_grid9.linge5.chow[NBR_L_9-2]=txt_to_chow(playing_data9.generated,NBR_L_9-2);
                if(data_grid9.linge4.box[0]==BOX_R_RED){
                    data_grid9.linge5.box[0]=BOX_R_RED;data_grid9.linge5.chow[0]=data_grid9.linge4.chow[0];}
                if(data_grid9.linge4.box[1]==BOX_R_RED){
                    data_grid9.linge5.box[1]=BOX_R_RED;data_grid9.linge5.chow[1]=data_grid9.linge4.chow[1];}
                if(data_grid9.linge4.box[2]==BOX_R_RED){
                    data_grid9.linge5.box[2]=BOX_R_RED;data_grid9.linge5.chow[2]=data_grid9.linge4.chow[2];}
                if(data_grid9.linge4.box[3]==BOX_R_RED){
                    data_grid9.linge5.box[3]=BOX_R_RED;data_grid9.linge5.chow[3]=data_grid9.linge4.chow[3];}
                if(data_grid9.linge4.box[4]==BOX_R_RED){
                    data_grid9.linge5.box[4]=BOX_R_RED;data_grid9.linge5.chow[4]=data_grid9.linge4.chow[4];}
                if(data_grid9.linge4.box[5]==BOX_R_RED){
                    data_grid9.linge5.box[5]=BOX_R_RED;data_grid9.linge5.chow[5]=data_grid9.linge4.chow[5];}
                if(data_grid9.linge4.box[6]==BOX_R_RED){
                    data_grid9.linge5.box[6]=BOX_R_RED;data_grid9.linge5.chow[6]=data_grid9.linge4.chow[6];}
                if(data_grid9.linge4.box[7]==BOX_R_RED){
                    data_grid9.linge5.box[7]=BOX_R_RED;data_grid9.linge5.chow[7]=data_grid9.linge4.chow[7];}
                if(data_grid9.linge4.box[8]==BOX_R_RED){
                    data_grid9.linge5.box[8]=BOX_R_RED;data_grid9.linge5.chow[8]=data_grid9.linge4.chow[8];}
                prev=1;
            }
            player_input(renderer ,data_grid9.linge5.text,data_grid9.linge5.chow,data_grid9.linge5.box,9);
            break;
        case 6 :
            if(prev==0){
                data_grid9.linge6.box[1]=BOX_R_RED;
                data_grid9.linge6.chow[1]=txt_to_chow(playing_data9.generated,1);
                data_grid9.linge6.box[NBR_L_9-2]=BOX_R_RED;
                data_grid9.linge6.chow[NBR_L_9-2]=txt_to_chow(playing_data9.generated,NBR_L_9-2);
                if(data_grid9.linge5.box[0]==BOX_R_RED){
                    data_grid9.linge6.box[0]=BOX_R_RED;data_grid9.linge6.chow[0]=data_grid9.linge5.chow[0];}
                if(data_grid9.linge5.box[1]==BOX_R_RED){
                    data_grid9.linge6.box[1]=BOX_R_RED;data_grid9.linge6.chow[1]=data_grid9.linge5.chow[1];}
                if(data_grid9.linge5.box[2]==BOX_R_RED){
                    data_grid9.linge6.box[2]=BOX_R_RED;data_grid9.linge6.chow[2]=data_grid9.linge5.chow[2];}
                if(data_grid9.linge5.box[3]==BOX_R_RED){
                    data_grid9.linge6.box[3]=BOX_R_RED;data_grid9.linge6.chow[3]=data_grid9.linge5.chow[3];}
                if(data_grid9.linge5.box[4]==BOX_R_RED){
                    data_grid9.linge6.box[4]=BOX_R_RED;data_grid9.linge6.chow[4]=data_grid9.linge5.chow[4];}
                if(data_grid9.linge5.box[5]==BOX_R_RED){
                    data_grid9.linge6.box[5]=BOX_R_RED;data_grid9.linge6.chow[5]=data_grid9.linge5.chow[5];}
                if(data_grid9.linge5.box[6]==BOX_R_RED){
                    data_grid9.linge6.box[6]=BOX_R_RED;data_grid9.linge6.chow[6]=data_grid9.linge5.chow[6];}
                if(data_grid9.linge5.box[7]==BOX_R_RED){
                    data_grid9.linge6.box[7]=BOX_R_RED;data_grid9.linge6.chow[7]=data_grid9.linge5.chow[7];}
                if(data_grid9.linge5.box[8]==BOX_R_RED){
                    data_grid9.linge6.box[8]=BOX_R_RED;data_grid9.linge6.chow[8]=data_grid9.linge5.chow[8];}
                prev=1;
            }
            player_input(renderer ,data_grid9.linge6.text,data_grid9.linge6.chow,data_grid9.linge6.box,9);
            break;
        case 7 :
            if(prev==0){
                data_grid9.linge7.box[1]=BOX_R_RED;
                data_grid9.linge7.chow[1]=txt_to_chow(playing_data9.generated,1);
                data_grid9.linge7.box[NBR_L_9-2]=BOX_R_RED;
                data_grid9.linge7.chow[NBR_L_9-2]=txt_to_chow(playing_data9.generated,NBR_L_9-2);
                if(data_grid9.linge6.box[0]==BOX_R_RED){
                    data_grid9.linge7.box[0]=BOX_R_RED;data_grid9.linge7.chow[0]=data_grid9.linge6.chow[0];}
                if(data_grid9.linge6.box[1]==BOX_R_RED){
                    data_grid9.linge7.box[1]=BOX_R_RED;data_grid9.linge7.chow[1]=data_grid9.linge6.chow[1];}
                if(data_grid9.linge6.box[2]==BOX_R_RED){
                    data_grid9.linge7.box[2]=BOX_R_RED;data_grid9.linge7.chow[2]=data_grid9.linge6.chow[2];}
                if(data_grid9.linge6.box[3]==BOX_R_RED){
                    data_grid9.linge7.box[3]=BOX_R_RED;data_grid9.linge7.chow[3]=data_grid9.linge6.chow[3];}
                if(data_grid9.linge6.box[4]==BOX_R_RED){
                    data_grid9.linge7.box[4]=BOX_R_RED;data_grid9.linge7.chow[4]=data_grid9.linge6.chow[4];}
                if(data_grid9.linge6.box[5]==BOX_R_RED){
                    data_grid9.linge7.box[5]=BOX_R_RED;data_grid9.linge7.chow[5]=data_grid9.linge6.chow[5];}
                if(data_grid9.linge6.box[7]==BOX_R_RED){
                    data_grid9.linge7.box[7]=BOX_R_RED;data_grid9.linge7.chow[7]=data_grid9.linge6.chow[7];}
                if(data_grid9.linge6.box[8]==BOX_R_RED){
                    data_grid9.linge7.box[8]=BOX_R_RED;data_grid9.linge7.chow[8]=data_grid9.linge6.chow[8];}
                prev=1;
            }
            player_input(renderer ,data_grid9.linge7.text,data_grid9.linge7.chow,data_grid9.linge7.box,9);
            break;
        case 8 :
                game.state=GAME_OVER_STATE;
                game_over(renderer,0,playing_data9.generated);
            break;
    }
}

void input_data10(SDL_Renderer* renderer){
    switch(pass){
        case 1 :
                if(prev==0){
                data_grid10.linge1.box[1]=BOX_R_RED;
                data_grid10.linge1.chow[1]=txt_to_chow(playing_data10.generated,1);
                data_grid10.linge1.box[NBR_L_10-2]=BOX_R_RED;
                data_grid10.linge1.chow[NBR_L_10-2]=txt_to_chow(playing_data10.generated,NBR_L_10-2);
               prev=1;
           }
            player_input(renderer ,data_grid10.linge1.text,data_grid10.linge1.chow,data_grid10.linge1.box,10);
            break;
        case 2 :
            if(prev==0){
                data_grid10.linge2.box[1]=BOX_R_RED;
                data_grid10.linge2.chow[1]=txt_to_chow(playing_data10.generated,1);
                data_grid10.linge2.box[NBR_L_10-2]=BOX_R_RED;
                data_grid10.linge2.chow[NBR_L_10-2]=txt_to_chow(playing_data10.generated,NBR_L_10-2);
                if(data_grid10.linge1.box[0]==BOX_R_RED){
                    data_grid10.linge2.box[0]=BOX_R_RED;data_grid10.linge2.chow[0]=data_grid10.linge1.chow[0];}
                if(data_grid10.linge1.box[1]==BOX_R_RED){
                    data_grid10.linge2.box[1]=BOX_R_RED;data_grid10.linge2.chow[1]=data_grid10.linge1.chow[1];}
                if(data_grid10.linge1.box[2]==BOX_R_RED){
                    data_grid10.linge2.box[2]=BOX_R_RED;data_grid10.linge2.chow[2]=data_grid10.linge1.chow[2];}
                if(data_grid10.linge1.box[3]==BOX_R_RED){
                    data_grid10.linge2.box[3]=BOX_R_RED;data_grid10.linge2.chow[3]=data_grid10.linge1.chow[3];}
                if(data_grid10.linge1.box[4]==BOX_R_RED){
                    data_grid10.linge2.box[4]=BOX_R_RED;data_grid10.linge2.chow[4]=data_grid10.linge1.chow[4];}
                if(data_grid10.linge1.box[5]==BOX_R_RED){
                    data_grid10.linge2.box[5]=BOX_R_RED;data_grid10.linge2.chow[5]=data_grid10.linge1.chow[5];}
                if(data_grid10.linge1.box[6]==BOX_R_RED){
                    data_grid10.linge2.box[6]=BOX_R_RED;data_grid10.linge2.chow[6]=data_grid10.linge1.chow[6];}
                if(data_grid10.linge1.box[7]==BOX_R_RED){
                    data_grid10.linge2.box[7]=BOX_R_RED;data_grid10.linge2.chow[7]=data_grid10.linge1.chow[7];}
                if(data_grid10.linge1.box[8]==BOX_R_RED){
                    data_grid10.linge2.box[8]=BOX_R_RED;data_grid10.linge2.chow[8]=data_grid10.linge1.chow[8];}
            }
                prev=1;
            player_input(renderer ,data_grid10.linge2.text,data_grid10.linge2.chow,data_grid10.linge2.box,10);
            break;
        case 3 :
            if(prev==0){
                data_grid10.linge3.box[1]=BOX_R_RED;
                data_grid10.linge3.chow[1]=txt_to_chow(playing_data10.generated,1);
                data_grid10.linge3.box[NBR_L_10-2]=BOX_R_RED;
                data_grid10.linge3.chow[NBR_L_10-2]=txt_to_chow(playing_data10.generated,NBR_L_10-2);
                if(data_grid10.linge2.box[0]==BOX_R_RED){
                    data_grid10.linge3.box[0]=BOX_R_RED;data_grid10.linge3.chow[0]=data_grid10.linge2.chow[0];}
                if(data_grid10.linge2.box[1]==BOX_R_RED){
                    data_grid10.linge3.box[1]=BOX_R_RED;data_grid10.linge3.chow[1]=data_grid10.linge2.chow[1];}
                if(data_grid10.linge2.box[2]==BOX_R_RED){
                    data_grid10.linge3.box[2]=BOX_R_RED;data_grid10.linge3.chow[2]=data_grid10.linge2.chow[2];}
                if(data_grid10.linge2.box[3]==BOX_R_RED){
                    data_grid10.linge3.box[3]=BOX_R_RED;data_grid10.linge3.chow[3]=data_grid10.linge2.chow[3];}
                if(data_grid10.linge2.box[4]==BOX_R_RED){
                    data_grid10.linge3.box[4]=BOX_R_RED;data_grid10.linge3.chow[4]=data_grid10.linge2.chow[4];}
                if(data_grid10.linge2.box[5]==BOX_R_RED){
                    data_grid10.linge3.box[5]=BOX_R_RED;data_grid10.linge3.chow[5]=data_grid10.linge2.chow[5];}
                if(data_grid10.linge2.box[6]==BOX_R_RED){
                    data_grid10.linge3.box[6]=BOX_R_RED;data_grid10.linge3.chow[6]=data_grid10.linge2.chow[6];}
                if(data_grid10.linge2.box[7]==BOX_R_RED){
                    data_grid10.linge3.box[7]=BOX_R_RED;data_grid10.linge3.chow[7]=data_grid10.linge2.chow[7];}
                if(data_grid10.linge2.box[8]==BOX_R_RED){
                    data_grid10.linge3.box[8]=BOX_R_RED;data_grid10.linge3.chow[8]=data_grid10.linge3.chow[8];}
            }
                prev=1;
            player_input(renderer ,data_grid10.linge3.text,data_grid10.linge3.chow,data_grid10.linge3.box,10);
            break;
        case 4 :
            if(prev==0){
                data_grid10.linge4.box[1]=BOX_R_RED;
                data_grid10.linge4.chow[1]=txt_to_chow(playing_data10.generated,1);
                data_grid10.linge4.box[NBR_L_10-2]=BOX_R_RED;
                data_grid10.linge4.chow[NBR_L_10-2]=txt_to_chow(playing_data10.generated,NBR_L_10-2);
                if(data_grid10.linge3.box[0]==BOX_R_RED){
                    data_grid10.linge4.box[0]=BOX_R_RED;data_grid10.linge4.chow[0]=data_grid10.linge3.chow[0];}
                if(data_grid10.linge3.box[1]==BOX_R_RED){
                    data_grid10.linge4.box[1]=BOX_R_RED;data_grid10.linge4.chow[1]=data_grid10.linge3.chow[1];}
                if(data_grid10.linge3.box[2]==BOX_R_RED){
                    data_grid10.linge4.box[2]=BOX_R_RED;data_grid10.linge4.chow[2]=data_grid10.linge3.chow[2];}
                if(data_grid10.linge3.box[3]==BOX_R_RED){
                    data_grid10.linge4.box[3]=BOX_R_RED;data_grid10.linge4.chow[3]=data_grid10.linge3.chow[3];}
                if(data_grid10.linge3.box[4]==BOX_R_RED){
                    data_grid10.linge4.box[4]=BOX_R_RED;data_grid10.linge4.chow[4]=data_grid10.linge3.chow[4];}
                if(data_grid10.linge3.box[5]==BOX_R_RED){
                    data_grid10.linge4.box[5]=BOX_R_RED;data_grid10.linge4.chow[5]=data_grid10.linge3.chow[5];}
                if(data_grid10.linge3.box[6]==BOX_R_RED){
                    data_grid10.linge4.box[6]=BOX_R_RED;data_grid10.linge4.chow[6]=data_grid10.linge3.chow[6];}
                if(data_grid10.linge3.box[7]==BOX_R_RED){
                    data_grid10.linge4.box[7]=BOX_R_RED;data_grid10.linge4.chow[7]=data_grid10.linge3.chow[7];}
                if(data_grid10.linge1.box[8]==BOX_R_RED){
                    data_grid10.linge4.box[8]=BOX_R_RED;data_grid10.linge4.chow[8]=data_grid10.linge1.chow[8];}
            }
                prev=1;
            player_input(renderer ,data_grid10.linge4.text,data_grid10.linge4.chow,data_grid10.linge4.box,10);
            break;
        case 5 :
            if(prev==0){
                data_grid10.linge5.box[1]=BOX_R_RED;
                data_grid10.linge5.chow[1]=txt_to_chow(playing_data10.generated,1);
                data_grid10.linge5.box[NBR_L_10-2]=BOX_R_RED;
                data_grid10.linge5.chow[NBR_L_10-2]=txt_to_chow(playing_data10.generated,NBR_L_10-2);
                if(data_grid10.linge4.box[0]==BOX_R_RED){
                    data_grid10.linge5.box[0]=BOX_R_RED;data_grid10.linge5.chow[0]=data_grid10.linge4.chow[0];}
                if(data_grid10.linge4.box[1]==BOX_R_RED){
                    data_grid10.linge5.box[1]=BOX_R_RED;data_grid10.linge5.chow[1]=data_grid10.linge4.chow[1];}
                if(data_grid10.linge4.box[2]==BOX_R_RED){
                    data_grid10.linge5.box[2]=BOX_R_RED;data_grid10.linge5.chow[2]=data_grid10.linge4.chow[2];}
                if(data_grid10.linge4.box[3]==BOX_R_RED){
                    data_grid10.linge5.box[3]=BOX_R_RED;data_grid10.linge5.chow[3]=data_grid10.linge4.chow[3];}
                if(data_grid10.linge4.box[4]==BOX_R_RED){
                    data_grid10.linge5.box[4]=BOX_R_RED;data_grid10.linge5.chow[4]=data_grid10.linge4.chow[4];}
                if(data_grid10.linge4.box[5]==BOX_R_RED){
                    data_grid10.linge5.box[5]=BOX_R_RED;data_grid10.linge5.chow[5]=data_grid10.linge4.chow[5];}
                if(data_grid10.linge4.box[6]==BOX_R_RED){
                    data_grid10.linge5.box[6]=BOX_R_RED;data_grid10.linge5.chow[6]=data_grid10.linge4.chow[6];}
                if(data_grid10.linge4.box[7]==BOX_R_RED){
                    data_grid10.linge5.box[7]=BOX_R_RED;data_grid10.linge5.chow[7]=data_grid10.linge4.chow[7];}
                if(data_grid10.linge4.box[8]==BOX_R_RED){
                    data_grid10.linge5.box[8]=BOX_R_RED;data_grid10.linge5.chow[8]=data_grid10.linge4.chow[8];}
            }
                prev=1;
            player_input(renderer ,data_grid10.linge5.text,data_grid10.linge5.chow,data_grid10.linge5.box,10);
            break;
        case 6 :
            if(prev==0){
                data_grid10.linge6.box[1]=BOX_R_RED;
                data_grid10.linge6.chow[1]=txt_to_chow(playing_data10.generated,1);
                data_grid10.linge6.box[NBR_L_10-2]=BOX_R_RED;
                data_grid10.linge6.chow[NBR_L_10-2]=txt_to_chow(playing_data10.generated,NBR_L_10-2);
                if(data_grid10.linge5.box[0]==BOX_R_RED){
                    data_grid10.linge6.box[0]=BOX_R_RED;data_grid10.linge6.chow[0]=data_grid10.linge5.chow[0];}
                if(data_grid10.linge5.box[1]==BOX_R_RED){
                    data_grid10.linge6.box[1]=BOX_R_RED;data_grid10.linge6.chow[1]=data_grid10.linge5.chow[1];}
                if(data_grid10.linge5.box[2]==BOX_R_RED){
                    data_grid10.linge6.box[2]=BOX_R_RED;data_grid10.linge6.chow[2]=data_grid10.linge5.chow[2];}
                if(data_grid10.linge5.box[3]==BOX_R_RED){
                    data_grid10.linge6.box[3]=BOX_R_RED;data_grid10.linge6.chow[3]=data_grid10.linge5.chow[3];}
                if(data_grid10.linge5.box[4]==BOX_R_RED){
                    data_grid10.linge6.box[4]=BOX_R_RED;data_grid10.linge6.chow[4]=data_grid10.linge5.chow[4];}
                if(data_grid10.linge5.box[5]==BOX_R_RED){
                    data_grid10.linge6.box[5]=BOX_R_RED;data_grid10.linge6.chow[5]=data_grid10.linge5.chow[5];}
                if(data_grid10.linge5.box[6]==BOX_R_RED){
                    data_grid10.linge6.box[6]=BOX_R_RED;data_grid10.linge6.chow[6]=data_grid10.linge5.chow[6];}
                if(data_grid10.linge5.box[7]==BOX_R_RED){
                    data_grid10.linge6.box[7]=BOX_R_RED;data_grid10.linge6.chow[7]=data_grid10.linge5.chow[7];}
                if(data_grid10.linge5.box[8]==BOX_R_RED){
                    data_grid10.linge6.box[8]=BOX_R_RED;data_grid10.linge6.chow[8]=data_grid10.linge5.chow[8];}
            }
                prev=1;
            player_input(renderer ,data_grid10.linge6.text,data_grid10.linge6.chow,data_grid10.linge6.box,10);
            break;
        case 7 :
            if(prev==0){
                data_grid10.linge7.box[1]=BOX_R_RED;
                data_grid10.linge7.chow[1]=txt_to_chow(playing_data10.generated,1);
                data_grid10.linge7.box[NBR_L_10-2]=BOX_R_RED;
                data_grid10.linge7.chow[NBR_L_10-2]=txt_to_chow(playing_data10.generated,NBR_L_10-2);
                if(data_grid10.linge6.box[0]==BOX_R_RED){
                    data_grid10.linge7.box[0]=BOX_R_RED;data_grid10.linge7.chow[0]=data_grid10.linge6.chow[0];}
                if(data_grid10.linge6.box[1]==BOX_R_RED){
                    data_grid10.linge7.box[1]=BOX_R_RED;data_grid10.linge7.chow[1]=data_grid10.linge6.chow[1];}
                if(data_grid10.linge6.box[2]==BOX_R_RED){
                    data_grid10.linge7.box[2]=BOX_R_RED;data_grid10.linge7.chow[2]=data_grid10.linge6.chow[2];}
                if(data_grid10.linge6.box[3]==BOX_R_RED){
                    data_grid10.linge7.box[3]=BOX_R_RED;data_grid10.linge7.chow[3]=data_grid10.linge6.chow[3];}
                if(data_grid10.linge6.box[4]==BOX_R_RED){
                    data_grid10.linge7.box[4]=BOX_R_RED;data_grid10.linge7.chow[4]=data_grid10.linge6.chow[4];}
                if(data_grid10.linge6.box[5]==BOX_R_RED){
                    data_grid10.linge7.box[5]=BOX_R_RED;data_grid10.linge7.chow[5]=data_grid10.linge6.chow[5];}
                if(data_grid10.linge6.box[7]==BOX_R_RED){
                    data_grid10.linge7.box[7]=BOX_R_RED;data_grid10.linge7.chow[7]=data_grid10.linge6.chow[7];}
                if(data_grid10.linge6.box[8]==BOX_R_RED){
                    data_grid10.linge7.box[8]=BOX_R_RED;data_grid10.linge7.chow[8]=data_grid10.linge6.chow[8];}
            }
                prev=1;
            player_input(renderer ,data_grid10.linge7.text,data_grid10.linge7.chow,data_grid10.linge7.box,10);
            break;
        case 8 :
                game.state=GAME_OVER_STATE;
                game_over(renderer,0,playing_data10.generated);
            break;
    }
}
/// render play as gest////////////////////////////////////////
void render_play_as_gest(SDL_Renderer *renderer){
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"WARNING","Your Progress wont be saved :(",NULL);
                game.state=PLAYING_PARAMETERS_STATE;
                menu.select=NOT_SELECTED;
                menu.hover=NOT_SELECTED;
                login_data.score=0;}
// reset evry thing :
void  reset_data(){
data_grid6 = new6; data_grid7 = new7; data_grid8 = new8; data_grid9 = new9;  // empty all grids
game_options.select=0; game_options.nbr_letters=0; game_options.nbr_time=20; // empty game options 
}
///// render game over state //////////////////////////////////////////////////////
void game_over(SDL_Renderer* renderer,int win_or_lose,char* word){
    SDL_Event event;
    while(running && game.state==GAME_OVER_STATE){
        while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                running = false; break;// X botton XD
             
            case SDL_MOUSEBUTTONDOWN:
                 // if mouse inside botton borders + botton click => SELECTED
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode){
                    case SDL_SCANCODE_ESCAPE:
                        reset_data(); // Escape + return keys => return to menu
                        game.state=PLAYING_PARAMETERS_STATE;
                        break;
                    }
        }       
        }
        SDL_RenderClear(renderer);
        switch(win_or_lose){
                case 1 : // win
                    render_on_xy(WON_BG,renderer,0,0);
                    render_text_on_xy(renderer,word,370,500,white);
                    break;
                case 0 : // lose
                    render_on_xy(LOSE_BG,renderer,0,0);
                    render_text_on_xy(renderer,word,370,500,white); 
                    break;
        }
    SDL_RenderPresent(renderer);
                }
}
//////////playing case /////////////////////////////////////////////////////////////////////////////////////////////////////////
void playing_loop(SDL_Renderer *renderer){

        SDL_Event event;
    while(running && game.state==PLAYING_STATE){
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
                        //
                        break;
                    }
}       
        }
        SDL_RenderClear(renderer);
        render_game_menu(renderer);
                switch(game_options.select) {
            case RESET_SELECTED :
                    game_options.select=0;
                    game_options.nbr_letters=6;
                    game_options.nbr_time=0;
                    game.state=PLAYING_PARAMETERS_STATE;
                    game_options.hover=0;
                    prev=0;
                    sco=0;
                    reset_data();
                break;  
            case LOGOUT_SELECTED:
                game_options.select=0;
                game_options.nbr_letters=6;
                game.state=MENU_STATE;
                game_options.select=NOT_SELECTED;
                game_options.hover=0;
                prev=0;
                sco=0;
                reset_data();
                break;
            }
        switch(game_options.nbr_letters){ // playing the nbr of letters that player wanted ...
                case NBR_L_6 : render_empty_grid6(renderer); input_data6(renderer); render_data6(renderer); break;
                case NBR_L_7 : render_empty_grid7(renderer); input_data7(renderer); render_data7(renderer); break;
                case NBR_L_8 : render_empty_grid8(renderer); input_data8(renderer); render_data8(renderer); break;
                case NBR_L_9 : render_empty_grid9(renderer); input_data9(renderer); render_data9(renderer); break;
                case NBR_L_10 : render_empty_grid10(renderer); input_data10(renderer); render_data10(renderer); break;
    }         
    render_time(renderer); // aficher le temps
    render_score(renderer); // aficher score
    SDL_RenderPresent(renderer);
    }
} ////////////////////////////////////////////////////////////////////:
// afichage time
void render_time(SDL_Renderer* renderer){
    char str[10];
    sprintf(str, "%d", temps);    // Now str contains the integer as characters
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
}//////////////////////////////////////////////
// afichage score
void render_score(SDL_Renderer* renderer){
    int i = login_data.score;
    char str[10];
    sprintf(str, "%d", i);// Now str contains the integer as characters
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
}///////////////////////////////////////////////
// aficher empty grid : 
void render_options(SDL_Renderer* renderer){
    switch(game_options.nbr_letters){
        case NBR_L_6 : render_empty_grid6(renderer); break;
        case NBR_L_7 :render_empty_grid7(renderer); break;
        case NBR_L_8 : render_empty_grid8(renderer); break;
        case NBR_L_9 : render_empty_grid9(renderer); break;
        case NBR_L_10 :render_empty_grid10(renderer); break;
    }
        render_time(renderer);
        render_score(renderer);
}///////////////////////////////////////////////////////////////////
// main_menu_loop :
void menu_loop(SDL_Renderer *renderer){
     //loop
    SDL_Event event;
    while(running && game.state==MENU_STATE){
        while(SDL_PollEvent(&event)){// Process events
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
                top_seen=0; 
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
    
}//////////////////////////////////////////////////////////////////////////////////////////////////
// game state loop ; 
void game_loop(SDL_Renderer *renderer){
     //loop
    SDL_Event event;
    while(running && game.state==PLAYING_PARAMETERS_STATE ){
        // Process events
        while(SDL_PollEvent(&event)){
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
                    game_options.select=NOT_SELECTED;
                    game.state=PLAYING_STATE;
                    pass=1;
                    i=0;
                 break;
            case RESET_SELECTED :
                    game_options.select=0;
                    game_options.nbr_letters=6;
                    game_options.nbr_time=20;
                    prev=0;
                    reset_data();
                break;  
            case LOGOUT_SELECTED:
                game.state=MENU_STATE;
                game_options.select=NOT_SELECTED;
                game_options.hover=0;
                prev=0;
                reset_data();
                break;
            case NBR_6_SELECTED :
                game_options.nbr_letters=NBR_L_6; 
                FILE* f6=ouvertureFichier(NBR_L_6);
                generationMot(f6,playing_data6.generated);
                printf("%s\n", playing_data6.generated);
                fclose(f6);
                break;
            case NBR_7_SELECTED :
                game_options.nbr_letters=NBR_L_7;
                FILE* f7=ouvertureFichier(NBR_L_7);
                generationMot(f7,playing_data7.generated);
                fclose(f7);
                break;
            case NBR_8_SELECTED :
                game_options.nbr_letters=NBR_L_8;
                FILE* f8=ouvertureFichier(NBR_L_8);
                generationMot(f8,playing_data8.generated);
                fclose(f8);
                break;
            case NBR_9_SELECTED :
                game_options.nbr_letters=NBR_L_9;
                FILE* f9=ouvertureFichier(NBR_L_9);
                generationMot(f9,playing_data9.generated);
                fclose(f9);
                break;
            case NBR_10_SELECTED :
                game_options.nbr_letters=NBR_L_10;
                FILE* f10=ouvertureFichier(NBR_L_10);
                generationMot(f10,playing_data10.generated);
                fclose(f10);
                break;

            case TIME_10_SELECTED :
                game_options.nbr_time=TIME_L_10;
                temps=10;
                break;
            case TIME_15_SELECTED :
                game_options.nbr_time=TIME_L_15;
                temps=15;
                break;
            case TIME_20_SELECTED :
                game_options.nbr_time=TIME_L_20;
                temps=20;
                break;
}
                 }
    render_game_menu(renderer);
    render_options(renderer);
    SDL_RenderPresent(renderer);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main_main_loop ::

void main_loop(SDL_Renderer *renderer){
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
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
            case PLAYING_PARAMETERS_STATE :
                game_loop(renderer);
                break;
            case PLAYING_STATE:
                playing_loop(renderer);
        }  
        SDL_RenderPresent(renderer); 
    }
}
