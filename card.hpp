#ifndef __GAME_CARD__
#define __GAME_CARD__

#include "render.hpp"

enum CardGroupDirection {
    Vertical,
    Horizontal
};

class Card: public Texture {
public:
    Card(App *app, int card_id, int x, int y);
public:
    void set_selected(bool selected);
    bool get_selected(void) const;
    int get_card_id(void) const;
private:
    int card_id;
    bool selected;
    static string determine_file_name(int card_id);
};

typedef vector<Card*> Cards;

class CardGroup: public Grid {
public:
    CardGroup(App *app, CardGroupDirection direction);
public:
    Card *add_card(int card_id);
    Card *add_card(Card *card);
    Card *remove_card(int card_id);
    Card *remove_card(Card *card);
    Card *insert_card(int card_id, int index);
    Card *insert_card(Card *card, int index);
    Cards get_cards(void) const;
    Cards get_selecteds(bool selecteds = true) const;
    void select_all(bool select = true);
private:
    CardGroupDirection direction; 
    void inc_col_row(int &col, int &row, SDL_Rect &rect);
    Card *add(Card *card, int col, int row);
};

#endif