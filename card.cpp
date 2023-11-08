#include "card.hpp"

//-----------------------------------------------------------------------------
Card::Card(SDL_Renderer* window_renderer, int card_id, int x, int y) 
     :Texture(window_renderer, determine_file_name(card_id), x, y) {
    
    void (*event_click)(Render*) = [](Render *r) {
        Card *c = dynamic_cast<Card*>(r);
        if(c) {            
            c->set_selected(!c->get_selected());
        }
    };
    on_mouse_click = event_click;
    set_selected(false);
}

//-----------------------------------------------------------------------------
string Card::determine_file_name(int card_id) {
    // essa função vai gerar o nome do arquivo com base no card_id ;-)
    // mais ainda falta o pack de imagens :-(
    return "image_teste.png";
}

//-----------------------------------------------------------------------------
void Card::set_selected(bool selected) {
    this->selected = selected;
    if(selected) {
        set_color(0xFF, 0xFF, 0x77);
    } else {
        set_color(0xFF, 0xFF, 0xFF);
    }
}

//-----------------------------------------------------------------------------
bool Card::get_selected(void) {
    return selected;
}


//-----------------------------------------------------------------------------
//- CardGroup -----------------------------------------------------------------
//-----------------------------------------------------------------------------
CardGroup::CardGroup(SDL_Renderer* window_renderer, CardGroupDirection direction) 
    : Grid(window_renderer, 0, 0, 18, 24, 0, 0, 0, 0, SDL_Color()) {
    this->direction = direction;
}

//-----------------------------------------------------------------------------
Card *CardGroup::add_card(int card_id) {
    int col, row;
    switch(direction) {
        case Vertical: {
            col = 0;
            row = get_renders().size();
            break;
        }
        case Horizontal: {
            row = 0;
            col = get_renders().size();
            break;
        }
    }
    SDL_Rect rect;
    get_cell_rect(col, row, rect);    
    Card *p = new Card(window_renderer, card_id, rect.x, rect.y);
    renders.push_back(p);
    map_renders[col][row] = p;
    p->owner = this;
    return p;    
}

