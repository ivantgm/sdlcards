#include "cacheta.hpp"

//-----------------------------------------------------------------------------
Cacheta::Cacheta() : App("Cacheta 1.0", 800, 600) {

    int w, h;
    SDL_RenderGetLogicalSize(window_renderer, &w, &h);

    //====================================================
    Grid *grid = 
    add_grid(
        8,     /* cols */
        8,     /* rows */
        64,     /* col size */
        32,     /* row size */
        4,      /* vertical line size */
        3,      /* horizontal line size */
        3,      /* vertical padding */
        4,      /* horizontal padding */
        {
            0xFF, /* red */
            0xFF, /* green */
            0xFF, /* blue */
            0x00  /* alpha */
        }
    );

    grid->add_retangle(
        3, // col coord
        3, // row coord
        {255, 0, 255, 0}, // color
        true
    );

    grid->add_retangle(
        3, // col coord
        1, // row coord
        {255, 0, 0, 0}, // color
        true
    );

    grid->add_retangle(
        2, // col coord
        3, // row coord
        {255, 255, 0, 0}, // color
        true
    );

    //====================================================  

    

}

//-----------------------------------------------------------------------------
Cacheta::~Cacheta() {

}

//-----------------------------------------------------------------------------
void Cacheta::poll_event(SDL_Event *e) {    
    switch(e->type) {
        case SDL_KEYDOWN: {
            if(e->key.keysym.sym == SDLK_ESCAPE) {
               e->type = SDL_QUIT; 
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {

            RendersI i = renders.begin();                
            Grid *grid = dynamic_cast<Grid*>(*i);            
            SDL_Rect rect;
            grid->get_cell_rect(0, 0, rect);    
            add_rectangle(rect, {0, 255, 255, 0}, true);
            grid->get_cell_rect(1, 1, rect);    
            add_rectangle(rect, {255, 0, 0, 0}, true);
            grid->get_cell_rect(2, 2, rect);
            add_rectangle(rect, {255, 255, 0, 0}, true);
            grid->get_cell_rect(3, 3, rect);
            add_rectangle(rect, {255, 0, 255, 0}, true);

            break;
        }
        case SDL_MOUSEWHEEL: {
            if(!renders.empty()) {
                RendersRI i = renders.rbegin();
                (*i)->move(0, e->wheel.y*2);
            }
            break;
        }
        case SDL_MOUSEMOTION: {
            if(!renders.empty()) {
                RendersI i = renders.begin();                
                (*i)->set_xy(e->motion.x, e->motion.y);
            }
            break;
        }
    }
    App::poll_event(e);
}

