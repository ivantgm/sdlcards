#include "cacheta.hpp"

//-----------------------------------------------------------------------------
Cacheta::Cacheta() : App("Cacheta 1.0", 800, 600) {

    CardGroup *group_1 = add_card_group(Horizontal);    
    group_1->set_xy(0, 100);
    for(int i = 1; i <= 7; i++) {
        for(int j = 1; j <=4; j++) {
            group_1->add_card(i*10+j);
        }
    }

    CardGroup *group_2 = add_card_group(Horizontal);    
    group_2->set_xy(0, 300);
    for(int i = 8; i <= 13; i++) {
        for(int j = 1; j <=4; j++) {
            group_2->add_card(i*10+j);
        }
    }     

    add_texture_text(
        "28 Days Later.ttf", 
        "CACHETA", 
        100, 10, {0xFF, 0xFF, 0xFF, 0xFF}, 96
    );   
}

//-----------------------------------------------------------------------------
Cacheta::~Cacheta() {

}

//-----------------------------------------------------------------------------
void Cacheta::poll_event(SDL_Event *e) {    
    switch(e->type) {
        case SDL_KEYDOWN: {
            if(e->key.keysym.sym == SDLK_ESCAPE) {
               e->type = SDL_QUIT; 
            }
            if(e->key.keysym.sym == SDLK_p) {
               screen_shot(); 
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            break;
        }
        case SDL_MOUSEWHEEL: {
            break;
        }
        case SDL_MOUSEMOTION: {
            break;
        }
    }
    App::poll_event(e);
}

