#include "app.hpp"
#include "exception.hpp"
#include <iostream>


//-----------------------------------------------------------------------------
App::App(const string& window_caption, int width, int heigth) {
    window = NULL;
    this->width = width;
    this->heigth = heigth;    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw Exception("SDL não inicializou", SDL_GetError());            
    } 
    window = SDL_CreateWindow(
        window_caption.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        width, 
        heigth, 
        SDL_WINDOW_SHOWN
    ); 
    if(!window) {
        throw Exception("SDL não criou a janela", SDL_GetError());
    }                        
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        throw Exception("SDL_Image não inicializou", IMG_GetError());
    }
    window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!window_renderer) {
        throw Exception("Não foi possível criar o renderizador da janela", SDL_GetError());
    }  
    SDL_RenderSetLogicalSize(window_renderer, width, heigth);  
}

//-----------------------------------------------------------------------------
App::~App() {
    delete_renders();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//-----------------------------------------------------------------------------
void App::loop(void) {
    SDL_Event e; 
    bool quit = false; 
    while(!quit) { 
        while(SDL_PollEvent(&e)) {
            poll_event(&e);
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
            }
            render();
        }
    }    
}

//-----------------------------------------------------------------------------
void App::poll_event(SDL_Event *e) {

}

//-----------------------------------------------------------------------------
void App::render(void) {
    SDL_SetRenderDrawColor(window_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(window_renderer);

    render_renders();

    SDL_RenderPresent(window_renderer);
}

//-----------------------------------------------------------------------------
void App::add_texture(const string& file_name, int x, int y) { 
    Texture *p = new Texture(window_renderer, file_name, x, y);
    renders.push_back(p);
}

//-----------------------------------------------------------------------------
void App::render_renders(void) {
    for(RendersI i = renders.begin(); i != renders.end(); i++) {
        (*i)->render();                
    }     
}

//-----------------------------------------------------------------------------
void App::delete_renders(void) {
    for(RendersI i = renders.begin(); i != renders.end(); i++) {
        delete (*i);                
    }     
}
//-----------------------------------------------------------------------------
void App::add_rectangle(const SDL_Rect &rect, const SDL_Color &color, bool fill) {
    Rectangle *p = new Rectangle(window_renderer, rect, color, fill);
    renders.push_back(p);
}
//-----------------------------------------------------------------------------
void App::add_rectangles(const vector<SDL_Rect> &rects, const SDL_Color &color, bool fill) {
    Rectangles *p = new Rectangles(window_renderer, rects, color, fill);
    renders.push_back(p);
}

//-----------------------------------------------------------------------------
void App::add_line(const SDL_Point &point1, const SDL_Point &point2, const SDL_Color &color) {
    Line *p = new Line(window_renderer, point1, point2, color);
    renders.push_back(p);
}

void App::add_lines(const vector<SDL_Point> &points, const SDL_Color &color) {
    Lines *p = new Lines(window_renderer, points, color);
    renders.push_back(p);    
}

//-----------------------------------------------------------------------------
void App::add_point(const SDL_Point &point, const SDL_Color &color) {
    Point *p = new Point(window_renderer, point, color);
    renders.push_back(p);
}

//-----------------------------------------------------------------------------
void App::add_points(const vector<SDL_Point> &points, const SDL_Color &color) {
    Points *p = new Points(window_renderer, points, color);
    renders.push_back(p);
}

//-----------------------------------------------------------------------------
Grid *App::add_grid(int cols, int rows, int col_size, 
                   int row_size, int vline_size, int hline_size, 
                   int vpad, int hpad, 
                   const SDL_Color &color) {
    Grid *p = new Grid(
        window_renderer, 
        cols, 
        rows, 
        col_size, 
        row_size, 
        vline_size, 
        hline_size,
        vpad,
        hpad, 
        color
    );
    renders.push_back(p);
    return p;

}

//-----------------------------------------------------------------------------
void App::screen_shot(void) {
    // https://stackoverflow.com/questions/22315980/sdl2-c-taking-a-screenshot
    SDL_Surface *ss = SDL_CreateRGBSurface(0, width, heigth, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(window_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, ss->pixels, ss->pitch);
    SDL_SaveBMP(ss, "screenshots/screenshot.bmp");
    SDL_FreeSurface(ss);
}

//-----------------------------------------------------------------------------
Render *App::get_render_at(int x, int y) {
    for(auto r : renders) {
        const Renders &rs = r->get_renders();
        for (RendersCRI i = rs.rbegin(); i != rs.rend(); i++) {
            if((*i)->rect_contains(x, y)) {
                return *i;
            }
        }
        if(r->rect_contains(x, y)) {
            return r;
        }        
    }
    return NULL;
}
