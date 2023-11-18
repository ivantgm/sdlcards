#include "card.hpp"

//-----------------------------------------------------------------------------
Card::Card(App *app, int card_id, int x, int y) 
     :Texture(app, determine_file_name(card_id), x, y) {
    
    void (*event_click)(Render*) = [](Render *r) {
        Card *c = dynamic_cast<Card*>(r);
        if(c) {            
            c->set_selected(!c->get_selected());
        }
    };
    this->card_id = card_id;
    on_mouse_click = event_click;
    set_selected(false);
}

//-----------------------------------------------------------------------------
string Card::determine_file_name(int card_id) {
    char s[32];
    sprintf(s, "%03d", card_id);
    return "./img/120x180/" + string(s) + ".png";
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
bool Card::get_selected(void) const {
    return selected;
}

//-----------------------------------------------------------------------------
int Card::get_card_id(void) const {
    return card_id;
}



//-----------------------------------------------------------------------------
//- CardGroup -----------------------------------------------------------------
//-----------------------------------------------------------------------------
CardGroup::CardGroup(App *app, CardGroupDirection direction) 
    : Grid(app, 0, 0, 18, 24, 0, 0, 0, 0, SDL_Color()) {
    this->direction = direction;
}

//-----------------------------------------------------------------------------
void CardGroup::inc_col_row(int &col, int &row, SDL_Rect &rect) {
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
    get_cell_rect(col, row, rect);
}

//-----------------------------------------------------------------------------
Card *CardGroup::add_card(int card_id) {
    int col, row;
    SDL_Rect rect;
    inc_col_row(col, row, rect);
    Card *card = new Card(app, card_id, rect.x, rect.y);
    return add(card, col, row);    
}

//-----------------------------------------------------------------------------
Card *CardGroup::add_card(Card *card) {
    int col, row;
    SDL_Rect rect;
    inc_col_row(col, row, rect);    
    card->set_xy(rect.x, rect.y);    
    return add(card, col, row);
}

//-----------------------------------------------------------------------------
Card *CardGroup::add(Card *card, int col, int row) {
    renders.push_back(card);
    map_renders[col][row] = card;
    card->owner = this; 
    return card;   
}

//-----------------------------------------------------------------------------
Card *CardGroup::remove_card(int card_id)  {
    Card *result = nullptr;
    for (auto &i : renders) {
        Card *c = dynamic_cast<Card*>(i);
        if(c) {
            if(c->get_card_id() == card_id) {
                result = c;
                break;
            }
        }
    }
    return remove_card(result);   
}

//-----------------------------------------------------------------------------
Card *CardGroup::remove_card(Card *card) {
    if(!card) {
        return nullptr;
    }
    int col, row;
    get_render_cell(card, col, row);
    remove_render(card);
    
    Cards cards = get_cards();

    switch(direction) {
        case Vertical: {
            for(int i = row; i < cards.size(); i++) {
                SDL_Rect rect;
                get_cell_rect(col, i, rect);
                Card *c = cards[i];
                if(c) {
                    c->set_xy(rect.x, rect.y);
                    map_renders[col][i] = c;
                    map_renders[col][i+1] = nullptr;
                }
            }
            break;
        }
        case Horizontal: {
            for(int i = col; i < cards.size(); i++) {
                SDL_Rect rect;
                get_cell_rect(i, row, rect);
                Card *c = cards[i];
                if(c) {
                    c->set_xy(rect.x, rect.y);
                    map_renders[i][row] = c;
                    map_renders[i+1][row] = nullptr;
                }
            }
            break;
        }
    }
    return card;
}

//-----------------------------------------------------------------------------
Cards CardGroup::get_cards(void) const {
    Cards cards;
    for (auto &i : renders) {
        Card *c = dynamic_cast<Card*>(i);
        if(c) {
            cards.push_back(c);
        }
    }
    return cards;
}

//-----------------------------------------------------------------------------
Cards CardGroup::get_selecteds(bool selecteds) const {
    Cards cards;
    for (auto &i : renders) {
        Card *c = dynamic_cast<Card*>(i);
        if(c) {
            if(c->get_selected() == selecteds) {
                cards.push_back(c);
            }            
        }
    }
    return cards;
}



