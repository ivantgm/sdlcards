#include "cacheta.hpp"

//-----------------------------------------------------------------------------
Cacheta::Cacheta() : App("Cacheta 1.0", 800, 600) {

    void (*event_click)(Render*) = [](Render *r) {
        Texture *t = dynamic_cast<Texture*>(r);
        if(t) {
            t->set_color(0x77, 0x77, 0xFF);    
        }
    };

    for(int i = 0; i < 10; i++) {
        Texture *texture = add_texture("image_teste.png", 100+(i*16), 150);
        texture->on_mouse_click = event_click;  
    }

    Grid *grid = 
    add_grid(
        24,     /* cols */
        8,     /* rows */
        16,     /* col size */
        32,     /* row size */
        1,      /* vertical line size */
        1,      /* horizontal line size */
        3,      /* vertical padding */
        3,      /* horizontal padding */
        {
            0x44, /* red */
            0x44, /* green */
            0x44, /* blue */
            0x00  /* alpha */
        }
    );
    
    for(int i = 0; i < 10; i++) {
      grid->add_texture(20, 4+i, "image_teste.png")->on_mouse_click = event_click;
    }
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
            if(e->key.keysym.sym == SDLK_p) {
               screen_shot(); 
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
            break;
        }
    }
    App::poll_event(e);
}

