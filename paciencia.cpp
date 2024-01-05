#include "paciencia.hpp"

//-----------------------------------------------------------------------------
Paciencia::Paciencia() : App("Paciência 1.0", 800, 600) {    

    for (int i = 1; i <= 7; i++) {
        create_col(i);
    }

    //====================
    void (*monte_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->pega_monte();
    };
    Card *monte = add_card(0, calc_col_x(1), calc_row_y(1));
    monte->set_enabled(false);
    monte->on_mouse_click = monte_click;
    
    //====================
    void (*casa_ouros_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->casa_ouros_click();
    };
    
    casa_ouros = add_card_group();
    casa_ouros->set_xy(calc_col_x(2), calc_row_y(1));    
    casa_ouros_ghost = casa_ouros->add_card(11);
    casa_ouros_ghost->set_alpha(32);
    casa_ouros_ghost->set_enabled(false);
    casa_ouros_ghost->on_mouse_click = casa_ouros_click;

    //====================
    void (*casa_espadas_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->casa_espadas_click();
    };
    Card *casa_espadas = add_card(12, calc_col_x(3), calc_row_y(1));
    casa_espadas->set_alpha(32);
    casa_espadas->set_enabled(false);
    casa_espadas->on_mouse_click = casa_espadas_click;

    //====================
    void (*casa_copas_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->casa_copas_click();
    };
    Card *casa_copas = add_card(13, calc_col_x(4), calc_row_y(1));
    casa_copas->set_alpha(32);
    casa_copas->set_enabled(false);
    casa_copas->on_mouse_click = casa_copas_click;

    //====================
    void (*casa_paus_click)(Render*) = [](Render *r) {
        Paciencia *paciencia = dynamic_cast<Paciencia*>(r->app);
        paciencia->casa_paus_click();
    };
    Card *casa_paus = add_card(14, calc_col_x(5), calc_row_y(1));
    casa_paus->set_alpha(32);
    casa_paus->set_enabled(false);
    casa_paus->on_mouse_click = casa_paus_click;





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
void Paciencia::casa_ouros_click(void) {    
    for(auto col : cols) {
        Cards selecteds = col->get_selecteds();
        for(auto card : selecteds) {
            card->set_selected(false);
            card->on_mouse_click = casa_ouros_ghost->on_mouse_click;
        }
        col->move_cards(selecteds, casa_ouros, casa_ouros->get_cards().size());
        
        if(!selecteds.empty()) {
            Cards cards = col->get_cards();
            if(!cards.empty()) {
                (*cards.rbegin())->set_card_id(Card::rand_card_id());
            }
        }
    }
}

//-----------------------------------------------------------------------------
void Paciencia::casa_espadas_click(void) {

}

//-----------------------------------------------------------------------------
void Paciencia::casa_copas_click(void) {

}

//-----------------------------------------------------------------------------
void Paciencia::casa_paus_click(void) {    

}

//-----------------------------------------------------------------------------
int Paciencia::calc_col_x(int col) const {
    return (dist*col) + (cw*(col-1));
}

//-----------------------------------------------------------------------------
int Paciencia::calc_row_y(int row) const {
    return (dist*row) + (ch*(row-1));
}

//-----------------------------------------------------------------------------
CardGroup *Paciencia::create_col(int col) {
    CardGroup *group = add_card_group(Vertical);    
    group->set_xy(calc_col_x(col), calc_row_y(2)); 
    for (int i = 1; i <= col; i++) {
        group->add_card(0);
    }    
    group->add_card(Card::rand_card_id()); 
    cols.push_back(group);
    return group;   
}