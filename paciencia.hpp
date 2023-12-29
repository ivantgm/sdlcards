#ifndef __PACIENCIA_APP__
#define __PACIENCIA_APP__

#include "app.hpp"

class Paciencia: public App {
public:
    Paciencia();
    ~Paciencia();
    void poll_event(SDL_Event *e);
private:
    void pega_monte(void);
    void casa_ouros(void);
    void casa_espadas(void);
    void casa_copas(void);
    void casa_paus(void);
};

#endif