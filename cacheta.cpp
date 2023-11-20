#include "cacheta.hpp"

//-----------------------------------------------------------------------------
Cacheta::Cacheta() : App("Cacheta 1.0", 800, 600) {

    CardGroup *group_1 = add_card_group(Horizontal);    
    group_1->set_xy(0, 100);
    for(int i = 1; i <= 13; i++) {
        for(int j = 1; j <=1; j++) {
            group_1->add_card(i*10+j);
        }
    }  

    Texture *btn1 = add_texture_text(
        "28 Days Later.ttf", 
        "SELECIONE ALGUMAS CARTAS PARA O GIRO 360", 
        10, 10, {0x00, 0x00, 0xFF, 0xFF}, 36
    );
    void (*btn1_click)(Render*) = [](Render *r) {

        auto thread_function = [](void *r) {
            Card *card = (Card*)r;
            double rotate = 0;
            while(rotate<360) {            
                card->rotate(rotate += 0.000001f);            
            }
            return 0;
        };

        App *app = r->app;
        CardGroup *group = dynamic_cast<CardGroup*>(app->renders[0]);
        Cards cards = group->get_selecteds();
        for(int i = 0; i < cards.size(); i++) {
            SDL_Thread* thread;
            thread = SDL_CreateThread( thread_function, "LoopThread", (void*)cards[i]);
        }
    };
    btn1->on_mouse_click = btn1_click;

    
    auto thread_function = [](void *r) {
        Card *card = (Card*)r;
        while(true) {            
            card->inc_rotate(0.000001f);            
        }
        return 0;
    };

    Cards cards = group_1->get_cards();
    SDL_Thread* thread;
    thread = SDL_CreateThread( thread_function, "CachetaThread", (void*)cards[12]);

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

