#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"
#include "rendering.h"
#include "logic.h"


// (x,y) of players :
int login_x=487, login_y=361;
int singup_x=331,singup_y=361;
int play_gest_x=171,play_gest_y=361;
int top_players_x=394,top_players_y=413;
int how_to_x=234,how_to_y=413;

//login_txt_ login_data;


// file to texture
SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

// render texture on (x,y):
void render_on_xy(const char* file_name,SDL_Renderer *renderer,int x,int y){
    SDL_Texture * texture = initialize_texture_from_file(file_name, renderer);
    int height;int width;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.w = width;
    destination.h = height;
    SDL_RenderCopy(renderer,texture, NULL, &destination);
    SDL_DestroyTexture(texture);
}




// render text to screen : 
void render_text_on_xy(SDL_Renderer* renderer,const char* text, int x,int y,SDL_Color color){
    TTF_Init();
    TTF_Font * font = TTF_OpenFont(DEFAULT_FONT, 17);
    SDL_Rect dest;
    dest.x = x; dest.y = y;
    SDL_Surface * surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
}


// render all menu to screen
int render_menu(SDL_Renderer *renderer){

    render_on_xy(MENU_BG,renderer,0,0);
    render_on_xy(LOG_IN,renderer,login_x,login_y);
    render_on_xy(SING_UP,renderer,singup_x,singup_y);
    render_on_xy(PLAY_GEST,renderer,play_gest_x,play_gest_y);
    render_on_xy(TOP_PLAYERS,renderer,top_players_x,top_players_y);
    render_on_xy(HOW_TO,renderer,how_to_x,how_to_y);

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if (mouse_x > login_x && mouse_x < login_x + BOTTON_H && mouse_y > login_y && mouse_y < login_y + BOTTON_W)
    { render_on_xy(LOG_IN,renderer,login_x+4,login_y);return LOGIN_SELECTED;}
    if (mouse_x > singup_x && mouse_x < singup_x + BOTTON_H && mouse_y > singup_y && mouse_y < singup_y + BOTTON_W)
    { render_on_xy(SING_UP,renderer,singup_x+4,singup_y);return SINGUP_SELECTED;}
    if (mouse_x > play_gest_x && mouse_x < play_gest_x + BOTTON_H && mouse_y > play_gest_y && mouse_y < play_gest_y + BOTTON_W)
    { render_on_xy(PLAY_GEST,renderer,play_gest_x+4,play_gest_y);return PLAY_AS_GUEST_SELECTED;}
    if (mouse_x > top_players_x && mouse_x < top_players_x + BOTTON_H && mouse_y > top_players_y && mouse_y < top_players_y + BOTTON_W)
    { render_on_xy(TOP_PLAYERS,renderer,top_players_x+4,top_players_y);return TOP_PLAYERS_SELECTED;}
    if (mouse_x > how_to_x && mouse_x < how_to_x + BOTTON_H && mouse_y > how_to_y && mouse_y < how_to_y + BOTTON_W)
    { render_on_xy(HOW_TO,renderer,how_to_x+4,how_to_y);return HOW_TO_PLAY_SELECTED;}

return 0;
}


void render_text_on_box(SDL_Renderer* renderer,const char* text, int x,int y,SDL_Color color){
    TTF_Init();
    TTF_Font * font = TTF_OpenFont(DEFAULT_FONT, 40);
    SDL_Rect dest;
    dest.x = x; dest.y = y;
    SDL_Surface * surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
}




// linge text data chow :
void render_linge_text6(SDL_Renderer *renderer,linge6_ linge,int h_pose){
    int x=266,y=160;
    render_box_text(renderer,linge.chow[0],x,y+(h_pose-1)*BOX);
    render_box_text(renderer,linge.chow[1],x+BOX,y+(h_pose-1)*BOX);
    render_box_text(renderer,linge.chow[2],x+2*BOX,y+(h_pose-1)*BOX);
    render_box_text(renderer,linge.chow[3],x+3*BOX,y+(h_pose-1)*BOX);
    render_box_text(renderer,linge.chow[4],x+4*BOX,y+(h_pose-1)*BOX);
    render_box_text(renderer,linge.chow[5],x+5*BOX,y+(h_pose-1)*BOX);}

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





int txt_to_chow(char* text,int indice){
    switch(text[indice]){
        case 'A': return A; break;
        case 'Z': return Z; break;
        case 'E': return E; break;
        case 'R': return R; break;
        case 'T': return T; break;
        case 'Y': return Y; break;
        case 'U': return U; break;
        case 'I': return I; break;
        case 'O': return O; break;
        case 'P': return P; break;
        case 'Q': return Q; break;
        case 'S': return S; break;
        case 'D': return D; break;
        case 'F': return F; break;
        case 'G': return G; break;
        case 'H': return H; break;
        case 'J': return J; break;
        case 'K': return K; break;
        case 'L': return L; break;
        case 'M': return M; break;
        case 'W': return W; break;
        case 'X': return X; break;
        case 'C': return C; break;
        case 'V': return V; break;
        case 'B': return B; break;
        case 'N': return N; break;
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