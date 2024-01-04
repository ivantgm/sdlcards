#ifndef __PACIENCIA_APP__
#define __PACIENCIA_APP__

#include "app.hpp"

class Paciencia: public App {
public:
    Paciencia();
    ~Paciencia();
    void poll_event(SDL_Event *e);
private:
    const int cw = 100;
    const int ch = 150;
    const int dist = 12;
    void pega_monte(void);
    void casa_ouros(void);
    void casa_espadas(void);
    void casa_copas(void);
    void casa_paus(void);
    int calc_col_x(int col) const;
    int calc_row_y(int row) const;
    CardGroup *create_col(int col);
};

#endif