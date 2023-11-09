#ifndef __GAME_CARD__
#define __GAME_CARD__

#include "render.hpp"

enum CardGroupDirection {
    Vertical,
    Horizontal
};

class Card: public Texture {
public:
    Card(SDL_Renderer* window_renderer, int card_id, int x, int y);
public:
    void set_selected(bool selected);
    bool get_selected(void);
private:
    bool selected;
    static string determine_file_name(int card_id);
};

class CardGroup: public Grid {
public:
    CardGroup(SDL_Renderer* window_renderer, CardGroupDirection direction);
public:
    Card *add_card(int card_id);    
private:
    CardGroupDirection direction;        
};

#endif