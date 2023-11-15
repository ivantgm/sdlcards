#include "cacheta.hpp"

//-----------------------------------------------------------------------------
Cacheta::Cacheta() : App("Cacheta 1.0", 800, 600) {

    int um_id_qualquer_ainda_nao_programado = 0;

    CardGroup *group_vertical = add_card_group(Vertical);    
    for(int i = 0; i < 5; i++) {
      group_vertical->add_card(um_id_qualquer_ainda_nao_programado);
    }

    CardGroup *group_horizontal = add_card_group(Horizontal);    
    group_horizontal->set_xy(200, 200);
    for(int i = 0; i < 5; i++) {
      group_horizontal->add_card(um_id_qualquer_ainda_nao_programado);
    } 

    add_texture_text(
        "28 Days Later.ttf", 
        "ABCDEFGHIJKLMNOPKRSTUVWXYZ", 
        100, 10, {0xFF, 0xFF, 0xFF, 0xFF}, 48
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

