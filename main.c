#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <time.h>
#include <math.h>

typedef struct{
    int x, y, w, h, framew, frameh, textw, texth, posx, posy, posw, posh, collx, colly, collw, collh, movex, movey, mousex, mousey;
    char life;
    char action;
    char r;
    char trigger;
    char hit;
    int tics;
} Man;

typedef struct{
    int x, y, w, h, framew, frameh, textw, texth, posx, posy, posw, posh, collx, colly, collw, collh, movex, movey, mousex, mousey, f;
    char life;
    char action;
    char r;
    char trigger;
    char hit;
    int tics, awarex, awarew, awareh, atac;
} Skeleton;

typedef struct{
    int x, y, w, h;
    char life;
    int tics;
} Dirt;

typedef struct{
    int x, y, w, h, th, collx, collw, treex, treey, tradius, local, tics, frame, offsetx, offsety;
    char life;
} Tree;

typedef struct{
    int x, y, w, h, collx, collw, posx, posy, posw, posh, type, local, offsetx, offsety;
    char life;
} Stone;

typedef struct{
    int x, y, w, h, collx, collw, posx, posy, posw, posh, type, local, offsetx, offsety;
    char life;
} Mine;

typedef struct{
    char *name;
    int selection, tic, tics;
} Menu;

typedef struct {
    Man man;
    Mine  mine[100];
    Menu menu[100];
    Tree tree[100];
    Stone stone[100000];
    Dirt dirt[100];
    Skeleton skeleton[100];
    SDL_Texture *stone_img;
    SDL_Texture *run;
    SDL_Texture *stand;
    SDL_Texture *sword;
    SDL_Texture *bow;
    SDL_Texture *skel_img;
    SDL_Texture *grass;
    SDL_Texture *treetop;
    SDL_Texture *treebottom;
    SDL_Texture *mine_img;
    SDL_Texture *dirt_img;
    TTF_Font *ttf;
    int height;
    int local;
    int width;
    int tics;
    float rot;
    int FPS;
    int frames;
    int offsetx;
    int offsety;
    int display;
} GameState;

int processEvents(SDL_Window *window, SDL_Renderer *renderer, GameState *game) {
    SDL_Event event;
    int done = 0;
    game->man.movex = 0;
    game->man.movey = 0;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEMOTION:{
                game->man.mousex = event.button.x;
                game->man.mousey = event.button.y;
                int doe = 0;
                if (game->display == 1){
                    for (int i = 0; i < 100000; ++i) {
                        if (game->stone[i].life == 'p' && doe == 0 && game->menu->selection == 1) {
                            int x = event.button.x;
                            int y = event.button.y;
                            game->stone[i].life = 'p';
                            game->stone[i].posx = x - (game->stone[i].w / 2);
                            game->stone[i].posy = y - (game->stone[i].h / 2);
                            game->stone[i].x = game->stone[i].w * game->stone->type;
                            doe = 1;
                        }
                    }
                   for(int i = 0; i<100; i++){
                       if(game->tree[i].life == 'p' && doe == 0 && game->menu->selection == 0){
                           int x = event.button.x;
                           int y = event.button.y;
                           doe =1;
                           game->tree[i].life = 'p';
                           game->tree[i].tics = SDL_GetTicks();
                           game->tree[i].frame = 0;
                           game->tree[i].x = x - (192 / 2);
                           game->tree[i].y = y + 30;
                           game->tree[i].w = 192;
                           game->tree[i].collx = game->tree[i].x + 80;
                           game->tree[i].collw = game->tree[i].w - 150;
                           game->tree[i].h = 60;
                           game->tree[i].th = 147;
                           game->tree[i].treex = 0;
                           game->tree[i].treey = 0;
                           game->tree[i].tradius = 0;

                       }

                       else if (game->mine[i].life == 'p' && doe == 0 && game->menu->selection == 2){
                           int x = event.button.x;
                           int y = event.button.y;
                           game->mine[i].life = 'p';
                           game->mine[i].posx = x - (game->mine[i].w/2);
                           game->mine[i].posy = y - (game->mine[i].h/2);
                           game->mine[i].x = game->mine[i].w*game->stone->type;
                           doe = 1;
                       }
                   }
                } else{
                    for(int i = 0; i<100; i++){
                        if(game->tree[i].life == 'p' && game->tree[i].x != -100000) {
                            game->tree[i].x = -100000;
                        }
                        if(game->mine[i].life == 'p' && game->mine[i].x != -100000) {
                            game->mine[i].posx = -100000;
                        }
                    }
                    for (int i = 0; i < 100000; ++i) {
                        if(game->stone[i].life == 'p' && game->stone[i].x != -100000) {
                            game->stone[i].posx = -100000;
                        }
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                if (game->menu->selection == 0) {
                    if (event.button.button == 1) {
                        int x = event.button.x;
                        int y = event.button.y;
                        int doe = 0;
                        for (int i = 0; i < 100; i++) {
                            if (game->tree[i].life == 'n' && doe == 0) {
                                game->tree[i].life = 'y';
                                game->tree[i].tics = SDL_GetTicks();
                                game->tree[i].frame = 0;
                                game->tree[i].x = x - (192 / 2);
                                game->tree[i].y = y + 30;
                                game->tree[i].w = 192;
                                game->tree[i].collx = game->tree[i].x + 80;
                                game->tree[i].collw = game->tree[i].w - 150;
                                game->tree[i].h = 60;
                                game->tree[i].th = 147;
                                game->tree[i].treex = 0;
                                game->tree[i].treey = 0;
                                game->tree[i].tradius = 0;
                                doe = 1;
                            }
                        }
                    } else if (event.button.button == 3) {
                        int x = event.button.x;
                        int y = event.button.y;
                        for (int i = 0; i < 100; i++) {
                            if (!(game->tree[i].x + game->tree[i].w < x || game->tree[i].x > x ||
                                  game->tree[i].y > y || game->tree[i].y + game->tree[i].h < y) &&
                                game->tree[i].life == 'y') {
                                game->tree[i].tics = SDL_GetTicks();
                                game->tree[i].frame = 1;
                                game->tree[i].life = 'n';

                            }
                        }
                    }
                }else if (game->menu->selection == 1) {
                        if (event.button.button == 1) {
                            int x = event.button.x;
                            int y = event.button.y;
                            int doe = 0;
                            for (int i = 0; i < 100000; i++) {
                                if (game->stone[i].life == 'n' && doe == 0) {
                                    game->stone[i].life = 'y';
                                    game->stone[i].posx = x - (game->stone[i].w / 2);
                                    game->stone[i].posy = y - (game->stone[i].h / 2);
                                    game->stone[i].offsetx = game->offsetx;
                                    game->stone[i].offsety = game->offsety;
                                    game->stone[i].x = game->stone[i].w * game->stone->type;
                                    doe = 1;
                                }
                            }
                        } else if (event.button.button == 3) {
                            int x = event.button.x;
                            int y = event.button.y;
                            for (int i = 0; i < 100000; i++) {
                                if (!(game->stone[i].posx + game->stone[i].w < x || game->stone[i].posx > x ||
                                      game->stone[i].posy > y || game->stone[i].posy + game->stone[i].h < y) &&
                                    game->stone[i].life == 'y') {
                                    game->stone[i].life = 'n';
                                }
                            }
                        }
                    }else if (game->menu->selection == 2){
                        if (event.button.button == 1) {
                            int x = event.button.x;
                            int y = event.button.y;
                            int doe = 0;
                            for (int i = 0; i < 100; i++) {
                                if (game->mine[i].life == 'n' && doe == 0) {
                                    game->mine[i].life = 'y';
                                    game->mine[i].posx = x - (game->mine[i].w/2);
                                    game->mine[i].posy = y - (game->mine[i].h/2);
                                    game->mine[i].x = game->mine[i].w*game->stone->type;
                                    doe = 1;
                                }
                            }
                        } else if (event.button.button == 3) {
                            int x = event.button.x;
                            int y = event.button.y;
                            for (int i = 0; i < 100; i++) {
                                if (!(game->mine[i].posx + game->mine[i].w < x || game->mine[i].posx > x ||
                                      game->mine[i].posy > y || game->mine[i].posy + game->mine[i].h < y) &&
                                    game->mine[i].life == 'y') {
                                    game->mine[i].life = 'n';
                                }
                            }
                        }
                }

                break;
            }
            case SDL_WINDOWEVENT_CLOSE: {
                if (window) {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
                break;
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                }
            }
                break;
            case SDL_QUIT:
                done = 1;
                break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_TAB]){
        if (game->display == 0 && SDL_GetTicks()-game->menu->tics > 100){
            game->display = 1;
            game->menu->tics = SDL_GetTicks();
        }else if(game->display == 1 && SDL_GetTicks()-game->menu->tics > 100){
            game->display = 0;
            game->menu->tics = SDL_GetTicks();
        }
    }
    if (state[SDL_SCANCODE_UP]){
        if (game->display == 1){

            if (game->menu->selection-1 >= 0 && SDL_GetTicks()-game->menu->tic > 100){
                game->menu->selection -= 1;
                game->menu->tic = SDL_GetTicks();
            }

        }
    }
    if (state[SDL_SCANCODE_DOWN]){
        if (game->display == 1){
            if (SDL_GetTicks()-game->menu->tic > 100){
                game->menu->selection += 1;
                game->menu->tic = SDL_GetTicks();
            }

        }
    }
    if (state[SDL_SCANCODE_RIGHT]){
        if (game->display == 1){
            if (SDL_GetTicks()-game->menu->tic > 100){
                game->stone->type += 1;
                game->menu->tic = SDL_GetTicks();
            }

        }
    }
    if (state[SDL_SCANCODE_LEFT]){
        if (game->display == 1){
            if (SDL_GetTicks()-game->menu->tic > 100){
                game->stone->type -= 1;
                game->menu->tic = SDL_GetTicks();
            }

        }
    }

    if (state[SDL_SCANCODE_SPACE]) {
        if (game->man.action != 'r' & game->man.action != 'b' & game->man.action != 'p' & game->man.action != 'x') {
            if (game->man.action == 'r') {
                game->man.trigger = 'n';
            }
            game->man.action = 'm';
            if (game->man.trigger == 'n') {
                game->man.trigger = 'y';
                game->man.x = game->man.framew * 12;
            }
        }
    } else if (state[SDL_SCANCODE_LSHIFT]) {
        if (game->man.action != 'm' & game->man.action != 'r' & game->man.action != 'p' & game->man.action != 'x') {
            if (game->man.action == 'r') {
                game->man.trigger = 'n';
            }
            game->man.action = 'b';
            if (game->man.trigger == 'n') {
                game->man.trigger = 'y';
                game->man.x = game->man.framew * 16;
            }
        }
    } else if (state[SDL_SCANCODE_Q]) {
        if (game->man.action != 'm' & game->man.action != 'b' & game->man.action != 'r' & game->man.action != 'x') {
            if (game->man.action == 'r') {
                game->man.trigger = 'n';
            }
            game->man.action = 'p';
            if (game->man.trigger == 'n') {
                game->man.trigger = 'y';
                game->man.x = game->man.framew * 24;
            }
        }
    } else if (state[SDL_SCANCODE_E]) {
        if (game->man.action != 'm' & game->man.action != 'b' & game->man.action != 'p' & game->man.action != 'r') {
        if (game->man.action == 'r') {
            game->man.trigger = 'n';
        }
        game->man.action = 'x';
        if (game->man.trigger == 'n') {
            game->man.trigger = 'y';
            game->man.x = game->man.framew * 28;
        }
    }
}

    if (game->man.action != 'm' & game->man.action != 'b' & game->man.action != 'p' & game->man.action != 'x'){
        game->man.action = 's';
        if (state[SDL_SCANCODE_A]) {
            if (game->man.trigger == 'n'){
                game->man.trigger = 'y';
                game->man.x = game->man.framew*4;
            }
            game->man.movex = -10;
            game->man.y = 0;
            game->man.r = 'w';
            if (game->man.collx < -20){
                game->man.posx = 950;
            }
            game->man.action = 'r';
        }
        if (state[SDL_SCANCODE_D]) {
            game->man.movex = 10;
            game->man.y = game->man.frameh*4;
            game->man.action = 'r';
            game->man.r = 'e';
            if (game->man.collx > 1020){
                game->man.posx = -180;
            }
            if (game->man.trigger == 'n'){
                game->man.trigger = 'y';
                game->man.x = game->man.framew*4;
            }
        }
        if (state[SDL_SCANCODE_W]) {
            game->man.movey = -10;
            game->man.y = game->man.frameh*2;
            game->man.r = 'n';
            if (game->man.colly < -80) {
                game->man.posy = 630;
            }
            game->man.action = 'r';
            if (game->man.trigger == 'n'){
                game->man.trigger = 'y';
                game->man.x = game->man.framew*4;
            }
        }
        if (state[SDL_SCANCODE_S]) {
            game->man.movey = 10;
            game->man.y = game->man.frameh*6;
            game->man.action = 'r';
            game->man.r = 's';
            if (game->man.colly > 730) {
                game->man.posy = -180;
            }
            if (game->man.trigger == 'n'){
                game->man.trigger = 'y';
                game->man.x = game->man.framew*4;
            }
        }
        if (state[SDL_SCANCODE_S] & state[SDL_SCANCODE_A]) {
            game->man.y = game->man.frameh*7;
            game->man.action = 'r';
            game->man.r = 'z';
            if (game->man.trigger == 'n'){
                game->man.trigger = 'y';
                game->man.x = game->man.framew*4;
            }
        }
        if (state[SDL_SCANCODE_S] & state[SDL_SCANCODE_D]) {
            game->man.y = game->man.frameh*5;
            game->man.action = 'r';
            game->man.r = 'x';
        }
        if (state[SDL_SCANCODE_W] & state[SDL_SCANCODE_A]) {
            game->man.y = game->man.frameh;
            game->man.action = 'r';
            game->man.r = 'q';

        }
        if (state[SDL_SCANCODE_W] & state[SDL_SCANCODE_D]) {
            game->man.y = game->man.frameh*3;
            game->man.action = 'r';
            game->man.r = 'r';
        }
    }
    game->frames += 1;
    game->man.collx = game->man.posx + 110;
    game->man.colly = game->man.posy + 120;
    return done;
}

void collision(SDL_Renderer *renderer, GameState *game){
    //block man from all angles
    //calculate collisons aftrer getting key pressses
    //add a varible for both x and y movement so if collideing or no moving == 0 and if key pressed movement = 10
    //add man w and man h in boundary
    int ax =0;
    int ay=0;
    int aw=0;
    int ah=0;
    int doe = 0;
    int x = 0;
    int y = 0;
    if (game->man.r == 'w'){
        ax = game->man.posx+60;
        ay = game->man.posy+150;
        aw = game->man.posw-230;
        ah = game->man.posh-235;

    } else if (game->man.r == 'e'){
        ax = game->man.posx+180;
        ay = game->man.posy+150;
        aw = game->man.posw-230;
        ah = game->man.posh-235;

//            if (game->dirt[i].life == 'n' && doe == 0 && game->man.hit == 'y'){
//                if ((game->man.collx + game->offsetx)%30 == 0 ){
//                    x = game->man.collx;
//                }else if ((game->man.collx+ game->offsetx)%30 >= 15 ){
//                    x =  game->man.collx + (30-game->man.collx%30);
//                } else if ((game->man.collx+ game->offsetx)%30 < 15){
//                    x = game->man.collx - game->man.collx%30;
//                }
//                if (game->man.colly + game->offsety%30 == 0 ){
//                    y = game->man.colly;
//                }else if ((game->man.colly+ game->offsety)%30 >= 15 ){
//                    y =  (game->man.colly + (30-game->man.colly%30));
//                } else if ((game->man.colly + game->offsety)%30 < 15){
//                    y = (game->man.colly - (game->man.colly%30));
//                }
//                for (int j = 0; j < 100; ++j) {
//                    if (game->dirt[j].life == 'y' && game->dirt[j].x == x && game->dirt[j].y == y){
//                        doe = 1;
//                    }
//                }
//
//                if (doe == 0){
//                    game->dirt[i].life = 'y';
//                    game->dirt[i].x = x;
//                    game->dirt[i].y = y;
//                    doe = 1;
//                }
//            }

    } else if (game->man.r == 's'){
        ax = game->man.posx+120;
        ay = game->man.posy+230;
        aw = game->man.posw-230;
        ah = game->man.posh-235;

    }else if (game->man.r == 'n'){
        ax = game->man.posx+120;
        ay = game->man.posy+100;
        aw = game->man.posw-230;
        ah = game->man.posh-235;

    }else if (game->man.r == 'z'){
        ax = game->man.posx+70;
        ay = game->man.posy+210;
        aw = game->man.posw-230;
        ah = game->man.posh-235;

    }else if (game->man.r == 'x'){
        ax = game->man.posx+170;
        ay = game->man.posy+210;
        aw = game->man.posw-230;
        ah = game->man.posh-235;

    }else if (game->man.r == 'q'){
        ax = game->man.posx+70;
        ay = game->man.posy+100;
        aw = game->man.posw-230;
        ah = game->man.posh-235;

    }else if (game->man.r == 'r'){
        ax = game->man.posx+170;
        ay = game->man.posy+120;
        aw = game->man.posw-230;
        ah = game->man.posh-235;

    }
    for (int i = 0; i < 100; i++){
        if (!(game->tree[i].collx + game->tree[i].collw < ax|| game->tree[i].collx > ax + aw || game->tree[i].y > ay + ah || game->tree[i].y + game->tree[i].h < ay) && game->tree[i].life == 'y' && game->man.life == 'y'){
            if (game->man.hit == 'y'){
                game->tree[i].tics = SDL_GetTicks();
                game->tree[i].frame = 1;
                game->tree[i].life = 'n';
            }
        }
    }
    for (int i = 0; i < 100; i++){
        if (!(game->tree[i].collx+game->tree[i].collw < game->man.collx + game->man.movex|| game->tree[i].collx > game->man.collx+game->man.movex + game->man.collw || game->tree[i].y > game->man.colly+game->man.movey + game->man.collh || game->tree[i].y + game->tree[i].h < game->man.colly+game->man.movey) && game->tree[i].life == 'y' && game->man.life == 'y'){
            game->man.movey = 0;
            game->man.movex = 0;
        }
//        if (!(game->skeleton[i].collx+game->skeleton[i].collw < game->man.collx + game->man.movex|| game->skeleton[i].collx > game->man.collx+game->man.movex + game->man.collw || game->skeleton[i].colly > game->man.colly+game->man.movey + game->man.collh || game->skeleton[i].colly + game->skeleton[i].collh < game->man.colly+game->man.movey) && game->skeleton[i].life == 'y' && game->man.life == 'y'){
//            game->man.movey = 0;
//            game->man.movex = 0;
//        }
    }
}

void enemyMovement(GameState *game){
    int ax;
    int ay;
    int aw;
    int ah;
    int dis;
    double dev;
    double angle;
    for (int i=0; i<100;i++){
        //agame->skeleton[i].action = 's';
        ax = game->man.posx+60;
        ay = game->man.posy+150;
        aw = game->man.posw-230;
        ah = game->man.posh-235;
        dev = ((game->skeleton[i].posx+game->skeleton[i].posw/2)) - ((game->man.posx+game->man.posw/2));
        if(dev == 0){
            dev = .01;
        }
        angle = atan(((game->skeleton[i].posy+game->skeleton[i].posh/2) - (game->man.posy+game->man.posh/2)) / dev);
        angle = angle * (180 / 3.14);
        if (game->man.posx+game->man.posw/2 > game->skeleton[i].posx+game->skeleton[i].posw/2) {
            angle -= 90;
        } else if (game->man.posx+game->man.posw/2 < game->skeleton[i].posx+game->skeleton[i].posw/2) {
            angle += 90;
        }
        printf("%f\n", angle);
        if (!(game->skeleton[i].awarex + game->skeleton[i].awarew < ax|| game->skeleton[i].awarex > ax + aw || game->skeleton[i].posy > ay + ah || game->skeleton[i].posy + game->skeleton[i].awareh < ay) && game->skeleton[i].life == 'y' && game->man.life == 'y'){
//                printf("collion\n");
//            //game->man.movex = 10;

            if (22.5 > angle && angle > -22.5){
                game->skeleton[i].y = game->skeleton[i].frameh*6;

            }else if (67.5 > angle && angle > 22.5){
                game->skeleton[i].y = game->skeleton[i].frameh*7;
            } else if (-67.5 < angle && angle < -22.5){
                game->skeleton[i].y = game->skeleton[i].frameh*5;
            }else if (-112.5 < angle && angle < -67.5){
                game->skeleton[i].y = game->skeleton[i].frameh*4;
            }else if (-157.5 < angle && angle < -112.5){
                game->skeleton[i].y = game->skeleton[i].frameh*3;
            }else if (112.5 > angle && angle > 67.5){
                game->skeleton[i].y = game->skeleton[i].frameh*0;
            }else if (157.5 > angle && angle > 112.5){
                game->skeleton[i].y = game->skeleton[i].frameh*1;
            }else if (202.5 > angle && angle > 157.5){
                game->skeleton[i].y = game->skeleton[i].frameh*2;
            }else if (-202.5 < angle && angle < -157.5){
                game->skeleton[i].y = game->skeleton[i].frameh*2;
            }

                game->skeleton[i].action = 'r';
                game->skeleton[i].r = 'e';
                if (game->skeleton[i].trigger == 'n'){
                    game->skeleton[i].trigger = 'y';
                    game->skeleton[i].x = game->skeleton[i].framew*4;
                }
            dis = sqrt((pow((game->man.x - game->skeleton[i].x), 2.0)) + pow((game->man.y - game->skeleton[i].y), 2.0));
            if (dis > 0) {
                game->skeleton[i].posx += (game->man.posx - game->skeleton[i].posx) * .01;
                game->skeleton[i].posy += (game->man.posy - game->skeleton[i].posy) * .01;
            }
//                game->skeleton[i].movey = 3;
//                game->skeleton[i].movex = 0;
//            if (SDL_GetTicks()-game->skeleton[i].atac > ((random()%9)+1)*3000) {
//                if (game->skeleton[i].action == 'r') {
//                    game->skeleton[i].trigger = 'n';
//                }
//                game->skeleton[i].action = 'm';
//                if (game->skeleton[i].trigger == 'n') {
//                    game->skeleton[i].trigger = 'y';
//                    game->skeleton[i].x = game->skeleton[i].framew * 12;
//                }
//                game->skeleton[i].atac = SDL_GetTicks();
//            }

        }
    }


}

void doRender(SDL_Renderer *renderer, GameState *game) {
//    game->man.posx += game->man.movex;
//    game->man.posy += game->man.movey;
    game->offsety += game->man.movey;
    game->offsetx += game->man.movex;
    for (int i = 0; i < 100; i++){

        game->skeleton[i].f += 1;

        game->tree[i].x -= game->man.movex;
        game->tree[i].y -= game->man.movey;
        game->tree[i].collx = game->tree[i].x + 80;
        game->tree[i].collw = game->tree[i].w - 150;
        game->mine[i].posx -= game->man.movex;
        game->mine[i].posy -= game->man.movey;
        game->dirt[i].x -= game->man.movex;
        game->dirt[i].y -= game->man.movey;
        game->skeleton[i].posx -= game->man.movex + game->skeleton[i].movex;
        game->skeleton[i].posy -= game->man.movey + game->skeleton[i].movey;
        game->skeleton[i].collx = game->skeleton[i].posx+100;
        game->skeleton[i].colly = game->skeleton[i].posy+110;
        game->skeleton[i].collw = game->skeleton[i].posw-220;
        game->skeleton[i].collh = game->skeleton[i].posh-170;
        game->skeleton[i].awarex = game->skeleton[i].posx-50;
        game->skeleton[i].awarew = game->skeleton[i].posw+100;
        game->skeleton[i].awareh = game->skeleton[i].posh+100;
        game->skeleton[i].movey = 0;
        game->skeleton[i].movex = 0;
    }
    for (int i = 0; i < 100000; ++i) {
        game->stone[i].posx -= game->man.movex;
        game->stone[i].posy -= game->man.movey;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (game->man.life == 'n') {
        if (game->frames == 20) {
            game->frames = 1;
            game->man.x += game->man.framew;
            if (game->man.x > game->man.framew * 23) {
                game->man.x = game->man.framew * 18;
            }
        }
    }
    if (game->man.action == 'r') {
        game->man.hit = 'n';
        if (game->frames >= 9) {
            game->frames = 1;
            game->man.x += game->man.framew;
            if (game->man.x > game->man.framew * 11) {
                game->man.x = game->man.framew * 4;
            }
        }
    }
    if (game->man.action == 's') {
        game->man.trigger = 'n';
        game->man.hit = 'n';
        if (game->frames >= 10) {
            game->frames = 1;
            game->man.x += game->man.framew;
            if (game->man.x > game->man.framew * 3) {
                game->man.x = 0;
            }
        }
    }
    if (game->man.action == 'p') {
        if (game->frames >= 10) {
            game->frames = 1;
            game->man.x += game->man.framew;
            if (game->man.x > game->man.framew * 27) {
                game->man.x = game->man.framew * 24;
                game->man.action = 's';
            }
        }
    }
    if (game->man.action == 'm') {
        if (game->frames >= 9) {
            game->frames = 1;
            game->man.x += game->man.framew;
            if (game->man.x > game->man.framew * 15) {
                game->man.x = game->man.framew * 12;
                game->man.action = 's';
                game->man.hit = 'y';
                game->man.trigger = 'n';
            }
        }
    }
    if (game->man.action == 'b') {
        if (game->frames >= 15) {
            game->frames = 1;
            game->man.x += game->man.framew;
            if (game->man.x > game->man.framew * 17) {
                game->man.x = game->man.framew * 16;
                game->man.action = 's';
            }
        }
    }
    if (game->man.action == 'x') {
        if (game->frames >= 10) {
            game->frames = 1;
            game->man.x += game->man.framew;
            if (game->man.x > game->man.framew * 31) {
                game->man.x = game->man.framew * 28;
                game->man.action = 's';
            }
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            SDL_Rect rect_grass = {0, 0, 100, 100};
            SDL_Rect rect_grasses = {i * 70, j * 70, 70, 70};
            SDL_RenderCopy(renderer, game->grass, &rect_grass, &rect_grasses);
        }
    }
    for (int i = -70; i < 100; i++) {
        for (int j = -70; j < 100; j++) {
            SDL_Rect rect_grass = {0, 0, 100, 100};
            SDL_Rect rect_grasses = {i * 35, j * 35, 70, 70};
            SDL_RenderCopy(renderer, game->grass, &rect_grass, &rect_grasses);
        }
    }

    for (int i = 0; i < 100; ++i) {
        if (game->dirt[i].life == 'y'){
            SDL_Rect rect_grass = {0, 0, 100, 100};
            SDL_Rect rect_grasses = {game->dirt[i].x, game->dirt[i].y, game->dirt[i].w, game->dirt[i].h};
            SDL_RenderCopy(renderer, game->dirt_img, &rect_grass, &rect_grasses);
        }
    }


//    for (int i = 0; i < game->width/30; i++) {
//        for (int j = 0; j < game->height/30; ++j) {
//            if (!((i*30)+30 < game->man.mousex || (i*30) > game->man.mousex || (j*30) > game->man.mousey || (j*30)+30 < game->man.mousey) && game->man.life == 'y') {
//                SDL_SetRenderDrawColor(renderer, 232, 234, 43, 255);
//                SDL_Rect arect = {i*30, j*30, 30, 30};
//                SDL_RenderFillRect(renderer, &arect);
//            }
//        }
//    }
    //game->tree[i].treex = 0;
    //game->tree[i].treey = 0;
    //game->tree[i].tradius = 0;
    for (int i = 0; i < 100000; ++i) {
        if (game->stone[i].life == 'y' && game->local == game->stone[i].local) {
            SDL_Rect rect_play = {game->stone[i].x, game->stone[i].y, game->stone[i].w, game->stone[i].h};
            SDL_Rect rect_pos = {game->stone[i].posx, game->stone[i].posy, game->stone[i].posw, game->stone[i].posh};
            SDL_RenderCopy(renderer, game->stone_img, &rect_play, &rect_pos);
        }
    }

    for (int i = 0; i < 100; i++) {
        if (game->mine[i].life == 'y' && game->local == game->mine[i].local) {
            SDL_Rect rect_play = {game->mine[i].x, game->mine[i].y, game->mine[i].w, game->mine[i].h};
            SDL_Rect rect_pos = {game->mine[i].posx, game->mine[i].posy, game->mine[i].posw, game->mine[i].posh};
            SDL_RenderCopy(renderer, game->mine_img, &rect_play, &rect_pos);
        }



        if (game->tree[i].life == 'n'  && game->local == game->tree[i].local) {
            if (game->tics > game->tree[i].tics + 100 && game->tree[i].frame < 9) {
                game->tree[i].frame++;
                game->tree[i].tics = SDL_GetTicks();
            }
            if (game->tree[i].frame == 1) {
                game->tree[i].treex = 20;
                game->tree[i].treey = 2;
                game->tree[i].tradius = 10;
            }
            if (game->tree[i].frame == 2) {
                game->tree[i].treex = 40;
                game->tree[i].treey = 10;
                game->tree[i].tradius = 20;
            }
            if (game->tree[i].frame == 3) {
                game->tree[i].treex = 60;
                game->tree[i].treey = 19;
                game->tree[i].tradius = 30;
            }
            if (game->tree[i].frame == 4) {
                game->tree[i].treex = 80;
                game->tree[i].treey = 36;
                game->tree[i].tradius = 40;
            }
            if (game->tree[i].frame == 5) {
                game->tree[i].treex = 80;
                game->tree[i].treey = 46;
                game->tree[i].tradius = 50;
            }
            if (game->tree[i].frame == 6) {
                game->tree[i].treex = 89;
                game->tree[i].treey = 50;
                game->tree[i].tradius = 60;
            }
            if (game->tree[i].frame == 7) {
                game->tree[i].treex = 95;
                game->tree[i].treey = 62;
                game->tree[i].tradius = 70;
            }
            if (game->tree[i].frame == 8) {
                game->tree[i].treex = 103;
                game->tree[i].treey = 91;
                game->tree[i].tradius = 80;
            }
            if (game->tree[i].frame == 9) {
                game->tree[i].treex = 104;
                game->tree[i].treey = 100;
                game->tree[i].tradius = 90;
            }
    }
//        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//        SDL_Rect trect = {game->skeleton[i].awarex, game->skeleton[i].posy, game->skeleton[i].awarew, game->skeleton[i].awareh};
//        SDL_RenderFillRect(renderer, &trect);

        if ((game->tree[i].life == 'n' || game->tree[i].life == 'y')  && game->local == game->tree[i].local){
            SDL_Rect rect_grasses = {game->tree[i].x, game->tree[i].y, game->tree[i].w, game->tree[i].h};
            SDL_RenderCopyEx(renderer, game->treebottom, NULL, &rect_grasses, game->tree[i].tradius, NULL, flip);
        }
    }

//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//    SDL_Rect rect = {game->man.collx, game->man.colly, game->man.collw, game->man.collh};
//    SDL_RenderFillRect(renderer, &rect);

    if (game->man.life == 'y') {
        SDL_Rect rect_play = {game->man.x, game->man.y, game->man.w, game->man.h};
        SDL_Rect rect_pos = {game->man.posx, game->man.posy, game->man.posw, game->man.posh};
        SDL_RenderCopy(renderer, game->run, &rect_play, &rect_pos);
        SDL_RenderCopy(renderer, game->stand, &rect_play, &rect_pos);
        SDL_RenderCopy(renderer, game->sword, &rect_play, &rect_pos);
        SDL_RenderCopy(renderer, game->bow, &rect_play, &rect_pos);
    } else if (game->man.life == 'n') {
        SDL_Rect rect_play = {game->man.x, game->man.y, game->man.w, game->man.h};
        SDL_Rect rect_pos = {game->man.posx, game->man.posy, game->man.posw, game->man.posh};
        SDL_RenderCopy(renderer, game->run, &rect_play, &rect_pos);
    }



    for (int i = 0; i < 100; ++i) {
        if (game->skeleton[i].action == 'r' && game->skeleton[i].life == 'y') {
            if (game->skeleton[i].f >= 9) {
                game->skeleton[i].f = 1;
                game->skeleton[i].x += game->skeleton[i].framew;
                if (game->skeleton[i].x > game->skeleton[i].framew * 11) {
                    game->skeleton[i].x = game->skeleton[i].framew * 4;
                }
            }
        }
        if (game->skeleton[i].action == 's' && game->skeleton[i].life == 'y') {
            game->skeleton[i].trigger = 'n';
            game->skeleton[i].hit = 'n';
            if (game->skeleton[i].f >= 10) {
                game->skeleton[i].f = 1;
                game->skeleton[i].x += game->skeleton[i].framew;
                if (game->skeleton[i].x > game->skeleton[i].framew * 3) {
                    game->skeleton[i].x = 0;
                }
            }
        }
        if (game->skeleton[i].action == 'm') {
            if (game->skeleton[i].f >= 9) {
                game->skeleton[i].f = 1;
                game->skeleton[i].x += game->skeleton[i].framew;
                if (game->skeleton[i].x > game->skeleton[i].framew * 15) {
                    game->skeleton[i].x = game->skeleton[i].framew * 12;
                    game->skeleton[i].action = 's';
                    game->skeleton[i].hit = 'y';
                    game->skeleton[i].trigger = 'n';
                }
            }
        }
        if (game->skeleton[i].life == 'y'){
            SDL_Rect rect_skelp = {game->skeleton[i].posx, game->skeleton[i].posy, game->skeleton[i].posw, game->skeleton[i].posh};
            SDL_Rect rect_skel = {game->skeleton[i].x, game->skeleton[i].y, game->skeleton[i].w, game->skeleton[i].h};
            SDL_RenderCopy(renderer, game->skel_img, &rect_skel, &rect_skelp);
            game->skeleton[i].tics = SDL_GetTicks();
        }
    }

    //tree top always 120 higher than tree bottom
    for (int i = 0; i < 100000; ++i) {
        if(game->stone[i].life == 'p'){
            SDL_Rect rect_play = {game->stone[i].x, game->stone[i].y, game->stone[i].w, game->stone[i].h};
            SDL_Rect rect_pos = {game->stone[i].posx, game->stone[i].posy, game->stone[i].posw, game->stone[i].posh};
            SDL_RenderCopy(renderer, game->stone_img, &rect_play, &rect_pos);
        }
    }
    for (int i = 0; i<100; i++){
        if ((game->tree[i].life == 'n' || game->tree[i].life == 'y')  && game->local == game->tree[i].local){
            SDL_Rect rect_treeses = {game->tree[i].x+game->tree[i].treex, (game->tree[i].y-game->tree[i].th)+game->tree[i].treey, game->tree[i].w, game->tree[i].th};
            SDL_RenderCopyEx(renderer, game->treetop, NULL, &rect_treeses, game->tree[i].tradius, NULL, flip);
        }
        if (game->tree[i].life == 'p'){
            SDL_Rect rect_grasses = {game->tree[i].x, game->tree[i].y, game->tree[i].w, game->tree[i].h};
            SDL_RenderCopyEx(renderer, game->treebottom, NULL, &rect_grasses, game->tree[i].tradius, NULL, flip);
            SDL_Rect rect_trees = {game->tree[i].x+game->tree[i].treex, (game->tree[i].y-game->tree[i].th)+game->tree[i].treey, game->tree[i].w, game->tree[i].th};
            SDL_RenderCopyEx(renderer, game->treetop, NULL, &rect_trees, game->tree[i].tradius, NULL, flip);
        }
        if(game->mine[i].life == 'p'){
            SDL_Rect rect_play = {game->mine[i].x, game->mine[i].y, game->mine[i].w, game->mine[i].h};
            SDL_Rect rect_pos = {game->mine[i].posx, game->mine[i].posy, game->mine[i].posw, game->mine[i].posh};
            SDL_RenderCopy(renderer, game->mine_img, &rect_play, &rect_pos);
        }


    }


    //tree falling right
    //SDL_Rect rect_treeses = {155, 40, 192, 147};10 20, 2
    //SDL_Rect rect_treeses = {175, 48, 192, 147};20 40, 10
    //SDL_Rect rect_treeses = {195, 57, 192, 147};30 60, 19
    //SDL_Rect rect_treeses = {215, 74, 192, 147};40 80, 36
    //SDL_Rect rect_treeses = {215, 84, 192, 147};50 80, 46
    //SDL_Rect rect_treeses = {224, 88, 192, 147};60 89, 50
    //SDL_Rect rect_treeses = {230, 100, 192, 147};70 95, 62
    //SDL_Rect rect_treeses = {238, 129, 192, 147};80 103, 91
    //SDL_Rect rect_treeses = {239, 138, 192, 147};90 104, 100



    if (game->display == 1){
        SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(game->ttf, "Debugger Menu", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
        SDL_Rect Message_rect = {90, 0, 200, 50}; //create a rect
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
        for (int i = 0; i<100; i++){
            if (strncmp(game->menu[i].name, "stone", 5) == 0){
                char r[10] = "";
                char d[30] = "stone: ";
                sprintf(r, "%d", game->stone->type);
                strcat(d,r);
                SDL_Surface* s = TTF_RenderText_Solid(game->ttf, d, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
                SDL_Texture* M = SDL_CreateTextureFromSurface(renderer, s); //now you can convert it into a texture
                SDL_Rect M_rect = {90, (i+1)*50, 70, 30}; //create a rect
                SDL_RenderCopy(renderer, M, NULL, &M_rect);
            } else{
                SDL_Surface* s = TTF_RenderText_Solid(game->ttf, game->menu[i].name, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
                SDL_Texture* M = SDL_CreateTextureFromSurface(renderer, s); //now you can convert it into a texture
                SDL_Rect M_rect = {90, (i+1)*50, 70, 30}; //create a rect
                SDL_RenderCopy(renderer, M, NULL, &M_rect);
            }

            if (i == game->menu->selection){
                SDL_Surface* s1 = TTF_RenderText_Solid(game->ttf, ">", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
                SDL_Texture* M1 = SDL_CreateTextureFromSurface(renderer, s1); //now you can convert it into a texture
                SDL_Rect M_rect1 = {30, (i+1)*50, 30, 30}; //create a rect
                SDL_RenderCopy(renderer, M1, NULL, &M_rect1);
            }
        }
    }


    SDL_RenderPresent(renderer);
    game->tics =SDL_GetTicks();
}

void load(GameState *game, SDL_Renderer *renderer, char* path){
    SDL_Surface *surface = NULL;
    SDL_Surface *head = NULL;
    SDL_Surface *sword = NULL;
    SDL_Surface *bow = NULL;
    SDL_Surface *grass = NULL;
    SDL_Surface *tree = NULL;
    SDL_Surface *stone = NULL;
    SDL_Surface *dirt = NULL;
    SDL_Surface *mine = NULL;
    SDL_Surface *skel = NULL;
    game->tics = SDL_GetTicks();
    //game->FPS = 60;
    game->frames = 1;
    game->rot = 0;
    game->man.r = ' ';
    game->local = 0;
    game->man.x = 0;
    game->man.y = 0;
    game->man.life = 'y';
    game->man.posx = 400;
    game->man.posy = 96;
    game->man.posw = game->man.posh = 300;
    game->man.movex = 0;
    game->man.movey = 0;
    game->offsetx = 0;
    game->offsety = 0;
    int frame_height;
    int frame_width;
    int texturewidth;
    int texturehieght;
    char *p = path;
    surface = IMG_Load(strcat(p,"/hero//leather_armor.png"));
    p[strlen(p)-24] = 0;
    head = IMG_Load(strcat(p,"/hero//male_head1.png"));
    p[strlen(p)-21] = 0;
    sword = IMG_Load(strcat(p,"/hero//ax.png"));
    p[strlen(p)-13] = 0;
    bow = IMG_Load(strcat(p,"/hero//longbow.png"));
    p[strlen(p)-18] = 0;
    grass = IMG_Load(strcat(p,"/tile//grass.png"));
    p[strlen(p)-16] = 0;
    tree = IMG_Load(strcat(p,"/tile//treetop.png"));
    p[strlen(p)-18] = 0;
    game->treetop = SDL_CreateTextureFromSurface(renderer, tree);
    tree = IMG_Load(strcat(p,"/tile//treebottom.png"));
    p[strlen(p)-21] = 0;
    game->treebottom = SDL_CreateTextureFromSurface(renderer, tree);
    game->ttf = TTF_OpenFont(strcat(p,"/fonts//mon.ttf"), 70);
    p[strlen(p)-15] = 0;
    stone = IMG_Load(strcat(p,"/tile//stone.png"));
    p[strlen(p)-16] = 0;
    mine = IMG_Load(strcat(p,"/tile//mines.png"));
    p[strlen(p)-16] = 0;
    dirt = IMG_Load(strcat(p,"/tile//dirt.jpg"));
    p[strlen(p)-15] = 0;
    skel = IMG_Load(strcat(p,"/hero//skeleton.png"));
    p[strlen(p)-19] = 0;
    game->mine_img = SDL_CreateTextureFromSurface(renderer, mine);
    game->stone_img = SDL_CreateTextureFromSurface(renderer, stone);
    game->run = SDL_CreateTextureFromSurface(renderer, surface);
    game->stand = SDL_CreateTextureFromSurface(renderer, head);
    game->sword = SDL_CreateTextureFromSurface(renderer, sword);
    game->bow = SDL_CreateTextureFromSurface(renderer, bow);
    game->grass = SDL_CreateTextureFromSurface(renderer, grass);
    game->dirt_img = SDL_CreateTextureFromSurface(renderer, dirt);
    game->skel_img = SDL_CreateTextureFromSurface(renderer, skel);
    SDL_QueryTexture(game->run, NULL, NULL, &texturewidth, &texturehieght);
    frame_height = texturehieght/8;
    frame_width = texturewidth/32;
    game->man.w = frame_width;
    game->man.h = frame_height;
    game->man.framew = frame_width;
    game->man.frameh = frame_height;
    game->man.textw = texturewidth;
    game->man.texth = texturehieght;

    SDL_QueryTexture(game->skel_img, NULL, NULL, &texturewidth, &texturehieght);
    frame_height = texturehieght/8;
    frame_width = texturewidth/32;
    for (int i = 0; i<100; i++){
        game->skeleton[i].atac = ((random()%9)+1)*3000;
        game->skeleton[i].tics = SDL_GetTicks();
        game->skeleton[i].trigger = 'n';
        game->skeleton[i].hit = 'n';
        game->skeleton[i].action = 's';
        game->skeleton[i].w = frame_width;
        game->skeleton[i].h = frame_height;
        game->skeleton[i].framew = frame_width;
        game->skeleton[i].frameh = frame_height;
        game->skeleton[i].textw = texturewidth;
        game->skeleton[i].texth = texturehieght;
        game->skeleton[i].r = ' ';
        game->skeleton[i].x = 0;
        game->skeleton[i].y = 0;
        game->skeleton[i].f = 1;
        game->skeleton[i].life = 'n';
        game->skeleton[i].posx = 100;
        game->skeleton[i].posy = 96;
        game->skeleton[i].posw = game->skeleton[i].posh = 300;
        game->skeleton[i].movex = 0;
        game->skeleton[i].movey = 0;
        game->skeleton[i].collx = game->skeleton[i].posx+100;
        game->skeleton[i].colly = game->skeleton[i].posy+110;
        game->skeleton[i].collw = game->skeleton[i].posw-220;
        game->skeleton[i].collh = game->skeleton[i].posh-170;
        game->skeleton[i].awarex = game->skeleton[i].posx-50;
        game->skeleton[i].awarew = game->skeleton[i].posw+100;
        game->skeleton[i].awareh = game->skeleton[i].posh+100;
        if (i == 99){
            game->skeleton[i].life = 'y';
        }
    }

    SDL_QueryTexture(game->mine_img, NULL, NULL, &texturewidth, &texturehieght);
    frame_width = texturewidth/4;
    game->stone->type = 0;
//    for (int i =0; i<100; i++){
//        if (i == 99){
//            game->mine[i].w = frame_width;
//            game->mine[i].h = texturehieght;
//            game->mine[i].posx = -100000;
//            game->mine[i].posy = -1000000;
//            game->mine[i].x = frame_width*0;
//            game->mine[i].y = 0;
//            game->mine[i].life = 'p';
//            game->mine[i].posw = 188;
//            game->mine[i].posh = 188;
//            game->mine[i].offsetx = 0;
//            game->mine[i].offsety = 0;
//        }else{
//            game->mine[i].w = frame_width;
//            game->mine[i].h = texturehieght;
//            game->mine[i].posx = -100000;
//            game->mine[i].posy = -1000000;
//            game->mine[i].x = frame_width*8;
//            game->mine[i].y = 0;
//            game->mine[i].life = 'n';
//            game->mine[i].posw = 188;
//            game->mine[i].posh = 188;
//            game->mine[i].offsetx = 0;
//            game->mine[i].offsety = 0;
//        }
//    }
    SDL_QueryTexture(game->stone_img, NULL, NULL, &texturewidth, &texturehieght);
    frame_width = texturewidth/24;
//    for (int i =0; i<100000; i++){
//        if (i == 99){
//            game->stone[i].w = frame_width;
//            game->stone[i].h = texturehieght;
//            game->stone[i].posx = -100000;
//            game->stone[i].posy = -1000000;
//            game->stone[i].x = frame_width*0;
//            game->stone[i].y = 0;
//            game->stone[i].life = 'p';
//            game->stone[i].posw = 188;
//            game->stone[i].posh = 188;
//            game->stone[i].offsetx = 0;
//            game->stone[i].offsety = 0;
//        }else{
//            game->stone[i].w = frame_width;
//            game->stone[i].h = texturehieght;
//            game->stone[i].posx = -100000;
//            game->stone[i].posy = -1000000;
//            game->stone[i].x = frame_width*8;
//            game->stone[i].y = 0;
//            game->stone[i].life = 'n';
//            game->stone[i].posw = 188;
//            game->stone[i].posh = 188;
//            game->stone[i].offsetx = 0;
//            game->stone[i].offsety = 0;
//        }
//    }
    for (int i = 0; i < 100000; ++i) {
        if (i != 99){
            game->stone[i].posx = game->stone[i].posx + game->stone[i].offsetx;
            game->stone[i].posy = game->stone[i].posy + game->stone[i].offsety;
        }

    }
    for (int i = 0; i < 100; ++i) {
        if (i != 99){
            game->tree[i].x = game->tree[i].x + game->tree[i].offsetx;
            game->tree[i].y = game->tree[i].y + game->tree[i].offsety;
            game->tree[i].collx = game->tree[i].x+80;
            game->mine[i].x = game->mine[i].x + game->mine[i].offsetx;
            game->mine[i].y = game->mine[i].y + game->mine[i].offsety;

        }
    }
    for (int i = 0; i < 100;i ++) {
        printf("%d  %d\n",game->tree[i].x, game->tree[i].offsetx);
    }
//    for(int i = 0; i < 100; i++){
//        if (i == 99){
//            game->tree[i].life = 'p';
//            game->tree[i].tics = SDL_GetTicks();
//            game->tree[i].frame = 0;
//            game->tree[i].x = -900335;
//            game->tree[i].y = 185*(i+1);
//            game->tree[i].w = 192;
//            game->tree[i].collx = game->tree[i].x+80;
//            game->tree[i].collw = game->tree[i].w-150;
//            game->tree[i].h = 60;
//            game->tree[i].th = 147;
//            game->tree[i].treex = 0;
//            game->tree[i].treey = 0;
//            game->tree[i].tradius = 0;
//            game->tree[i].offsetx = 0;
//            game->tree[i].offsety = 0;
//        }
//        else{
//            game->tree[i].life = 'n';
//            game->tree[i].tics = SDL_GetTicks();
//            game->tree[i].frame = 0;
//            game->tree[i].x = -11335;
//            game->tree[i].y = 185;
//            game->tree[i].w = 192;
//            game->tree[i].collx = game->tree[i].x+80;
//            game->tree[i].collw = game->tree[i].w-150;
//            game->tree[i].h = 60;
//            game->tree[i].th = 147;
//            game->tree[i].treex = 0;
//            game->tree[i].treey = 0;
//            game->tree[i].tradius = 0;
//            game->tree[i].offsetx = 0;
//            game->tree[i].offsety = 0;
//        }
//    }
    game->man.action = 's';
    game->man.trigger = 'n';
    game->menu->tic = SDL_GetTicks();
    game->man.collx = game->man.posx +110;
    game->man.colly = game->man.posy + 120;
    game->man.collw = game->man.framew-45;
    game->man.collh = game->man.frameh-15;
    game->man.hit = 'n';
    game->display = 0;
    game->menu->selection = 0;
    game->menu->tics = SDL_GetTicks();
    for (int i =0; i< 100; i++){
        if (i == 0){
            game->menu[i].name = "tree";
        } else if (i ==1){
            game->menu[i].name = "stone";
        } else if (i == 2){
            game->menu[i].name = "mine";
        }
        else{
            game->menu[i].name = "";
        }

    }
    for (int i = 0; i < 100; ++i) {
        game->dirt[i].x = -1000;
        game->dirt[i].y = 0;
        game->dirt[i].w = 30;
        game->dirt[i].h = 30;
        game->dirt[i].life = 'n';
        game->dirt[i].tics = SDL_GetTicks();
    }


    SDL_FreeSurface(grass);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(head);
    SDL_FreeSurface(sword);
    SDL_FreeSurface(bow);
    SDL_FreeSurface(tree);
    SDL_FreeSurface(stone);
    SDL_FreeSurface(mine);
    SDL_FreeSurface(dirt);
    SDL_FreeSurface(skel);
}

void save(GameState *game){
    for (int i = 0; i < 100; ++i) {
        game->tree[i].offsetx = game->offsetx;
        game->tree[i].offsety = game->offsety;
    }
    FILE *fptr;
    fptr = fopen("map1.dat","wb");
    fwrite(&game->tree, sizeof(game->tree), 1, fptr);
    fwrite(&game->stone, sizeof(game->stone), 1, fptr);
    fwrite(&game->mine, sizeof(game->stone), 1, fptr);
    fclose(fptr);

}

int main(int argc, char *argv[]){
    char *path = argv[0];
    //change to 10 so it can excute in the same dictorary as the image

    path[strlen(path)-23] = 0;

//    char str[10000];

      //path[strlen(path)-21] = 0;
//    fread(&str, 100000, sizeof(char*), fptr);
//    printf("%s\n", str);
//    fclose(fptr);

    GameState gameSate;
    FILE *fptr;
    fptr = fopen("map1.dat","rb");
    if (fptr != NULL){
        fread(&gameSate.tree,sizeof(gameSate.tree),1,fptr);
        fread(&gameSate.stone,sizeof(gameSate.stone),1,fptr);
        fread(&gameSate.mine, sizeof(gameSate.mine), 1, fptr);
    }
    fclose(fptr);
    for (int i = 0; i < 100;i ++) {
        printf("%d  %d\n",gameSate.stone[i].x, gameSate.stone[i].y);
    }
    gameSate.height = 720;
    gameSate.width = 1080;
    srandom((int)time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    SDL_Window *window= NULL;
    SDL_Renderer *renderer = NULL;
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSate.width, gameSate.height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    load(&gameSate, renderer, path);
    int done = 0;
    while (!done){
        done = processEvents(window, renderer, &gameSate);
        enemyMovement(&gameSate);
        collision(renderer, &gameSate);
        doRender(renderer, &gameSate);
    }
    save(&gameSate);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
    return 0;
}
