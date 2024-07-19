#ifndef __PACIENCIA_APP__
#define __PACIENCIA_APP__

#include "app.hpp"

typedef vector<CardGroup*> Cols;
typedef vector<int> Baralho;

class Paciencia: public App {
public:
    Paciencia();
    ~Paciencia();
    void poll_event(SDL_Event *e);
public:
    Cols cols;
    int pop_baralho(void);
    void new_game(void);
private:
    const int cw = 100;
    const int ch = 150;
    const int dist = 12;
    const int ghost_alpha = 32;
    Baralho baralho;   
    CardGroup *casa_ouros;
    Card *casa_ouros_ghost;
    CardGroup *casa_espadas;
    Card *casa_espadas_ghost;
    CardGroup *casa_copas;
    Card *casa_copas_ghost;
    CardGroup *casa_paus;
    Card *casa_paus_ghost;
    void pega_monte(Render *r);
    void casa_ouros_click(void);
    void casa_espadas_click(void);
    void casa_copas_click(void);
    void casa_paus_click(void);
    void casa_click(Naipe naipe);
    int calc_col_x(int col) const;
    int calc_row_y(int row) const;
    CardGroup *create_col(int col);    
};

class PacienciaCard: public Card {
public:
    PacienciaCard(Paciencia *app, int card_id, int x, int y);
protected:
    void before_select(bool &can_select);
};

#endif