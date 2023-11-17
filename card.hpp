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
    bool get_selected(void);
private:
    bool selected;
    static string determine_file_name(int card_id);
};

class CardGroup: public Grid {
public:
    CardGroup(App *app, CardGroupDirection direction);
public:
    Card *add_card(int card_id);
    Card *add_card(Card *card);
private:
    CardGroupDirection direction; 
    void inc_col_row(int &col, int &row, SDL_Rect &rect);
    Card *add(Card *card, int col, int row);
};

#endif