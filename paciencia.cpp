#include "paciencia.hpp"

//-----------------------------------------------------------------------------
Paciencia::Paciencia() : App("Paciência 1.0", 800, 600) {    
    
    //====================
    void (*monte_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->pega_monte();
    };
    Card *monte = add_card(0, 16 + 136*0, 16);
    monte->set_enabled(false);
    monte->on_mouse_click = monte_click;
    
    //====================
    void (*casa_ouros_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->casa_ouros();
    };
    Card *casa_ouros = add_card(11, 16 + 136*1, 16);
    casa_ouros->set_alpha(32);
    casa_ouros->set_enabled(false);
    casa_ouros->on_mouse_click = casa_ouros_click;

    //====================
    void (*casa_espadas_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->casa_espadas();
    };
    Card *casa_espadas = add_card(12, 16 + 136*2, 16);
    casa_espadas->set_alpha(32);
    casa_espadas->set_enabled(false);
    casa_espadas->on_mouse_click = casa_espadas_click;

    //====================
    void (*casa_copas_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->casa_copas();
    };
    Card *casa_copas = add_card(13, 16 + 136*3, 16);
    casa_copas->set_alpha(32);
    casa_copas->set_enabled(false);
    casa_copas->on_mouse_click = casa_copas_click;

    //====================
    void (*casa_paus_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->casa_paus();
    };
    Card *casa_paus = add_card(14, 16 + 136*4, 16);
    casa_paus->set_alpha(32);
    casa_paus->set_enabled(false);
    casa_paus->on_mouse_click = casa_paus_click;

    //====================
    CardGroup *coluna_1 = add_card_group(Vertical);    
    coluna_1->set_xy(16 + 136*0, 210); 
    coluna_1->add_card(0);
    coluna_1->add_card(Card::rand_card_id());

    //====================
    CardGroup *coluna_2 = add_card_group(Vertical);    
    coluna_2->set_xy(16 + 136*1, 210); 
    coluna_2->add_card(0);
    coluna_2->add_card(0);
    coluna_2->add_card(Card::rand_card_id());
    coluna_2->add_card(Card::rand_card_id());

    //====================
    CardGroup *coluna_3 = add_card_group(Vertical);    
    coluna_3->set_xy(16 + 136*2, 210); 
    coluna_3->add_card(0);
    coluna_3->add_card(0);
    coluna_3->add_card(0);
    coluna_3->add_card(Card::rand_card_id());
    coluna_3->add_card(Card::rand_card_id());
    coluna_3->add_card(Card::rand_card_id());
    
    //====================
    CardGroup *coluna_4 = add_card_group(Vertical);    
    coluna_4->set_xy(16 + 136*3, 210); 
    coluna_4->add_card(0);
    coluna_4->add_card(0);
    coluna_4->add_card(0);
    coluna_4->add_card(0);
    coluna_4->add_card(Card::rand_card_id());
    coluna_4->add_card(Card::rand_card_id());
    coluna_4->add_card(Card::rand_card_id());
    coluna_4->add_card(Card::rand_card_id());

    //====================
    CardGroup *coluna_5 = add_card_group(Vertical);    
    coluna_5->set_xy(16 + 136*4, 210); 
    coluna_5->add_card(0);
    coluna_5->add_card(0);
    coluna_5->add_card(0);
    coluna_5->add_card(0);
    coluna_5->add_card(0);
    coluna_5->add_card(Card::rand_card_id());
    coluna_5->add_card(Card::rand_card_id());
    coluna_5->add_card(Card::rand_card_id());
    coluna_5->add_card(Card::rand_card_id());
    coluna_5->add_card(Card::rand_card_id());



}

//-----------------------------------------------------------------------------
Paciencia::~Paciencia() {

}

//-----------------------------------------------------------------------------
void Paciencia::poll_event(SDL_Event *e) {    
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
    }
    App::poll_event(e);
}

//-----------------------------------------------------------------------------
void Paciencia::pega_monte(void) {    

}

//-----------------------------------------------------------------------------
void Paciencia::casa_ouros(void) {    

}

//-----------------------------------------------------------------------------
void Paciencia::casa_espadas(void) {

}

//-----------------------------------------------------------------------------
void Paciencia::casa_copas(void) {

}

//-----------------------------------------------------------------------------
void Paciencia::casa_paus(void) {    

}


