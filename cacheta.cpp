#include "cacheta.hpp"

//-----------------------------------------------------------------------------
Cacheta::Cacheta() : App("Cacheta 1.0", 800, 600) {

    int w, h;
    SDL_RenderGetLogicalSize(window_renderer, &w, &h);

    //====================================================
    Grid *grid = 
    add_grid(
        24,     /* cols */
        8,     /* rows */
        16,     /* col size */
        32,     /* row size */
        4,      /* vertical line size */
        3,      /* horizontal line size */
        3,      /* vertical padding */
        4,      /* horizontal padding */
        {
            0x44, /* red */
            0x44, /* green */
            0x44, /* blue */
            0x00  /* alpha */
        }
    );
    
    // posiciona um grupo de cartas na vertical
    grid->add_texture(0, 4, "image_teste.png");
    grid->add_texture(0, 5, "image_teste.png");
    grid->add_texture(0, 6, "image_teste.png");
    grid->add_texture(0, 7, "image_teste.png");

    // posiciona um grupo de cartas numa mesma linha
    grid->add_texture(12, 6, "image_teste.png");
    grid->add_texture(13, 6, "image_teste.png");
    grid->add_texture(14, 6, "image_teste.png");
    grid->add_texture(15, 6, "image_teste.png");

    // posiciona um grupo de cartas na diagonal
    grid->add_texture(22, 0, "image_teste.png");
    grid->add_texture(23, 1, "image_teste.png");
    grid->add_texture(24, 2, "image_teste.png");
    grid->add_texture(25, 3, "image_teste.png"); 

    // adiciona alguns retangulos coloridos
    grid->add_retangle( 8, 1, {0xFF, 0x00, 0x00, 0x00}, true);
    grid->add_retangle( 9, 1, {0xFF, 0xFF, 0x00, 0x00}, true);
    grid->add_retangle(10, 1, {0xFF, 0x00, 0xFF, 0x00}, true);
    grid->add_retangle( 9, 2, {0x00, 0xFF, 0xFF, 0x00}, false); 

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

            break;
        }
        case SDL_MOUSEWHEEL: {

            break;
        }
        case SDL_MOUSEMOTION: {
            if(!renders.empty()) {
                
                // movimenta o Grid
                // ele é o primeiro elemento neste exemplo

                RendersI i = renders.begin();                
                (*i)->set_xy(e->motion.x, e->motion.y);

            }
            break;
        }
    }
    App::poll_event(e);
}

