#include "render.hpp"
#include "exception.hpp"
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

void inflate_rect(SDL_Rect &rect, int amount) {
    rect.x -= amount;
    rect.y -= amount;
    rect.w += (amount*2);
    rect.h += (amount*2);
}

//-----------------------------------------------------------------------------
//- Render --------------------------------------------------------------------
//-----------------------------------------------------------------------------
Render::Render(SDL_Renderer* window_renderer) {
    this->window_renderer = window_renderer;
}

//-----------------------------------------------------------------------------
Render::~Render() {

}

//-----------------------------------------------------------------------------
void Render::set_xy(int x, int y) {
    set_x(x);
    set_y(y);
}

//-----------------------------------------------------------------------------
void Render::get_inflate_rect(SDL_Rect &rect, int amount) const {
    get_rect(rect);
    inflate_rect(rect, amount);
}

//-----------------------------------------------------------------------------
const Renders& Render::get_renders(void) const {
    return renders;
}

//-----------------------------------------------------------------------------
bool Render::rect_contains(int x, int y) const {
    SDL_Rect rect;
    get_rect(rect);
    return (rect.x <= x) && 
           (rect.y <= y) && 
           ((rect.x+rect.w) >= x) &&
           ((rect.y+rect.h) >= y);
}



//-----------------------------------------------------------------------------
//- Texture -------------------------------------------------------------------
//-----------------------------------------------------------------------------
Texture::Texture(SDL_Renderer* window_renderer, const string& file_name, int x, int y) 
    : Render(window_renderer) {    
    SDL_Surface* temp_surface = IMG_Load(file_name.c_str());
    if(!temp_surface) {
        throw Exception("Não foi possível carregar a imagem " + file_name, IMG_GetError());
    }
    SDL_GetClipRect(temp_surface, &rect);
    rect.x = x;
    rect.y = y;
    texture = SDL_CreateTextureFromSurface(this->window_renderer, temp_surface);
    if(!texture) {
        throw Exception("Não foi possível criar a textura " + file_name, SDL_GetError());
    }
    SDL_FreeSurface(temp_surface);
}

//-----------------------------------------------------------------------------
Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

//-----------------------------------------------------------------------------
void Texture::render() {
    SDL_RenderCopy(window_renderer, texture, NULL, &rect);
}

//-----------------------------------------------------------------------------
void Texture::set_x(int x) {
    rect.x = x;
}

//-----------------------------------------------------------------------------
void Texture::set_y(int y) {
    rect.y = y;
}

//-----------------------------------------------------------------------------
void Texture::move(int x, int y) {
    rect.x += x;
    rect.y += y;
}

//-----------------------------------------------------------------------------
void Texture::get_rect(SDL_Rect &rect) const {
    rect.x = this->rect.x;
    rect.y = this->rect.y;
    rect.w = this->rect.w;
    rect.h = this->rect.h;
}

//-----------------------------------------------------------------------------
void Texture::set_blend(SDL_BlendMode mode) {
    SDL_SetTextureBlendMode(texture, mode);
}

//-----------------------------------------------------------------------------
void Texture::set_alpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

//-----------------------------------------------------------------------------
void Texture::set_color(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetTextureColorMod(texture, r, g, b);
}

//-----------------------------------------------------------------------------
//- Rectangle -----------------------------------------------------------------
//-----------------------------------------------------------------------------
Rectangle::Rectangle(SDL_Renderer* window_renderer, const SDL_Rect &rect, const SDL_Color &color, bool fill) 
    : Render(window_renderer) {        
    this->rect = rect;
    this->color = color;
    this->fill = fill;
}

//-----------------------------------------------------------------------------
Rectangle::~Rectangle() {
    
}

//-----------------------------------------------------------------------------
void Rectangle::render() {
    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, color.a);
    if(fill) {
        SDL_RenderFillRect(window_renderer, &rect);   
    } else {
        SDL_RenderDrawRect(window_renderer, &rect);   
    }
    
}

//-----------------------------------------------------------------------------
void Rectangle::set_x(int x) {
    rect.x = x;
}

//-----------------------------------------------------------------------------
void Rectangle::set_y(int y) {
    rect.y = y;
}

//-----------------------------------------------------------------------------
void Rectangle::move(int x, int y) {
    rect.x += x;
    rect.y += y;
}

//-----------------------------------------------------------------------------
void Rectangle::get_rect(SDL_Rect &rect) const {
    rect.x = this->rect.x;
    rect.y = this->rect.y;
    rect.w = this->rect.w;
    rect.h = this->rect.h;
}


//-----------------------------------------------------------------------------
//- Line ----------------------------------------------------------------------
//-----------------------------------------------------------------------------
Line::Line(SDL_Renderer* window_renderer, const SDL_Point &point1, const SDL_Point &point2, const SDL_Color &color) 
    : Render(window_renderer) {
    this->point1 = point1;
    this->point2 = point2;
    this->color = color;
}

//-----------------------------------------------------------------------------
Line::~Line() {

}
//-----------------------------------------------------------------------------
void Line::render(void) {
    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, color.a);      
    SDL_RenderDrawLine(window_renderer, point1.x, point1.y, point2.x, point2.y); 
}
//-----------------------------------------------------------------------------
void Line::set_x(int x) {
    point2.x += (x - point1.x);
    point1.x = x;
}

//-----------------------------------------------------------------------------
void Line::set_y(int y) {
    point2.y += (y - point1.y);
    point1.y = y;
}

//-----------------------------------------------------------------------------
void Line::move(int x, int y) {
    point1.x += x;
    point1.y += y;
    point2.x += x;
    point2.y += y;
}

//-----------------------------------------------------------------------------
void Line::get_rect(SDL_Rect &rect) const {
    rect.x = this->point1.x;
    rect.y = this->point1.y;
    rect.w = this->point2.x - this->point1.x + 1;
    rect.h = this->point2.y - this->point1.y + 1;
}

//-----------------------------------------------------------------------------
//- Lines ---------------------------------------------------------------------
//-----------------------------------------------------------------------------
Lines::Lines(SDL_Renderer* window_renderer, const vector<SDL_Point> &points, const SDL_Color &color) 
    : Render(window_renderer) {
    this->points = points;
    this->color = color;
}

//-----------------------------------------------------------------------------
Lines::~Lines() {

}

//-----------------------------------------------------------------------------
void Lines::render(void) {
    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, color.a);      
    SDL_RenderDrawLines(window_renderer, points.data(), points.size()); 
}

//-----------------------------------------------------------------------------
void Lines::set_x(int x) {
    int m = numeric_limits<int>::max();
    for (auto& point : points) {
        m = min(m, point.x);
    }
    move(x-m, 0);
}

//-----------------------------------------------------------------------------
void Lines::set_y(int y) {
    int m = numeric_limits<int>::max();
    for (auto& point : points) {
        m = min(m, point.y);
    }
    move(0, y-m);
}

//-----------------------------------------------------------------------------
void Lines::move(int x, int y) {
    for (auto& point : points) {
        point.x += x;
        point.y += y;
    }
}

//-----------------------------------------------------------------------------
void Lines::get_rect(SDL_Rect &rect) const {

    int min_x = numeric_limits<int>::max();
    int min_y = numeric_limits<int>::max();
    int max_x = numeric_limits<int>::min();
    int max_y = numeric_limits<int>::min();

    for (auto& point : points) {
        min_x = min(min_x, point.x);
        min_y = min(min_y, point.y);
        max_x = max(max_x, point.x);
        max_y = max(max_y, point.y);
    }    

    rect.x = min_x;
    rect.y = min_y;
    rect.w = max_x - min_x + 1;
    rect.h = max_y - min_y + 1;
}


//-----------------------------------------------------------------------------
//- Point ---------------------------------------------------------------------
//-----------------------------------------------------------------------------
Point::Point(SDL_Renderer* window_renderer, const SDL_Point &point, const SDL_Color &color) 
    : Render(window_renderer) {
    this->point = point;
    this->color = color;
}

//-----------------------------------------------------------------------------
Point::~Point() {

}
//-----------------------------------------------------------------------------
void Point::render(void) {
    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, color.a);      
    SDL_RenderDrawPoint(window_renderer, point.x, point.y);  
}

//-----------------------------------------------------------------------------
void Point::set_x(int x) {
    point.x = x;
}

//-----------------------------------------------------------------------------
void Point::set_y(int y) {
    point.y = y;
}

//-----------------------------------------------------------------------------
void Point::move(int x, int y) {
    point.x += x;
    point.y += y;
}

//-----------------------------------------------------------------------------
void Point::get_rect(SDL_Rect &rect) const {
    rect.x = point.x;
    rect.y = point.y;
    rect.w = 1;
    rect.h = 1;
}

//-----------------------------------------------------------------------------
//- Rectangles ----------------------------------------------------------------
//-----------------------------------------------------------------------------
Rectangles::Rectangles(SDL_Renderer* window_renderer, const vector<SDL_Rect>&rects, const SDL_Color &color, bool fill) 
    : Render(window_renderer) {
    this->rects = rects;
    this->color = color;
    this->fill = fill;
}
//-----------------------------------------------------------------------------
Rectangles::~Rectangles() {

}
//-----------------------------------------------------------------------------
void Rectangles::render(void) {
    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, color.a);      
    if(fill) {
        SDL_RenderFillRects(window_renderer, rects.data(), rects.size());   
    } else {
        SDL_RenderDrawRects(window_renderer, rects.data(), rects.size());   
    }
}

//-----------------------------------------------------------------------------
void Rectangles::set_x(int x) {
    int m = numeric_limits<int>::max();
    for (auto& rect : rects) {
        m = min(m, rect.x);
    }
    move(x-m, 0);
}

//-----------------------------------------------------------------------------
void Rectangles::set_y(int y) {
    int m = numeric_limits<int>::max();
    for (auto& rect : rects) {
        m = min(m, rect.y);
    }
    move(0, y-m);
}

//-----------------------------------------------------------------------------
void Rectangles::move(int x, int y) {
    for (auto& rect : rects) {
        rect.x += x;
        rect.y += y;
    }
}

//-----------------------------------------------------------------------------
void Rectangles::get_xy(int &x, int &y) {
    x = numeric_limits<int>::max();
    y = numeric_limits<int>::max();
    for (auto& rect : rects) {
        x = min(x, rect.x);
        y = min(y, rect.y);    
    } 
}

//-----------------------------------------------------------------------------
void Rectangles::get_rect(SDL_Rect &rect) const {

    int min_x = numeric_limits<int>::max();
    int min_y = numeric_limits<int>::max();
    int max_x = numeric_limits<int>::min();
    int max_y = numeric_limits<int>::min();

    for (auto& rect : rects) {
        min_x = min(min_x, rect.x);
        min_y = min(min_y, rect.y);  
        max_x = max(max_x, rect.x + rect.w);
        max_y = max(max_y, rect.y + rect.y);
    } 

    rect.x = min_x;
    rect.y = min_y;
    rect.w = max_x - min_x;
    rect.h = max_y - min_y;
}

//-----------------------------------------------------------------------------
//- Points --------------------------------------------------------------------
//-----------------------------------------------------------------------------
Points::Points(SDL_Renderer* window_renderer, const vector<SDL_Point>&points, const SDL_Color &color) 
    : Render(window_renderer) {
    this->points = points;
    this->color = color;
}

//-----------------------------------------------------------------------------
Points::~Points() {
    
}

//-----------------------------------------------------------------------------
void Points::render(void) {
    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, color.a);      
    SDL_RenderDrawPoints(window_renderer, points.data(), points.size());  
}

//-----------------------------------------------------------------------------
void Points::set_x(int x) {
    int m = numeric_limits<int>::max();
    for (auto& point : points) {
        m = min(m, point.x);
    }
    move(x-m, 0);    
}

//-----------------------------------------------------------------------------
void Points::set_y(int y) {
    int m = numeric_limits<int>::max();
    for (auto& point : points) {
        m = min(m, point.y);
    }
    move(0, y-m);    
}

//-----------------------------------------------------------------------------
void Points::move(int x, int y) {
    for (auto& point : points) {
        point.x += x;
        point.y += y;
    }
}

//-----------------------------------------------------------------------------
void Points::get_rect(SDL_Rect &rect) const {

    int min_x = numeric_limits<int>::max();
    int min_y = numeric_limits<int>::max();
    int max_x = numeric_limits<int>::min();
    int max_y = numeric_limits<int>::min();    

    for (auto& point : points) {
        min_x = min(min_x, point.x);
        min_y = min(min_y, point.y);
        max_x = max(max_x, point.x);
        max_y = max(max_y, point.y);
    }

    rect.x = min_x;
    rect.y = min_y;
    rect.w = max_x - min_x + 1;
    rect.h = max_y - min_y + 1;
}

//-----------------------------------------------------------------------------
//- Grid ----------------------------------------------------------------------
//-----------------------------------------------------------------------------
Grid::Grid(SDL_Renderer* window_renderer, 
           int cols, int rows, int col_size, 
           int row_size, int vline_size, int hline_size,
           int vpad, int hpad,
           const SDL_Color &color)
    : Rectangles(window_renderer, vector<SDL_Rect>(), color, true) {

    this->cols = cols;
    this->rows = rows;
    this->col_size = col_size;
    this->row_size = row_size;    
    this->vline_size = vline_size;
    this->hline_size = hline_size;
    this->vpad = vpad;
    this->hpad = hpad;

    for(int i = 0; i <= cols; i++) {
        rects.push_back({i*col_size, 0, vline_size, rows*row_size+hline_size});            
    }
    
    for(int i = 0; i <= rows; i++) {
        rects.push_back({0, i*row_size, cols*col_size+vline_size, hline_size});            
    }
          
}  

//-----------------------------------------------------------------------------        
Grid::~Grid() {
    for(RendersI i = renders.begin(); i != renders.end(); i++) {
        delete (*i);                
    }   
}

//-----------------------------------------------------------------------------
void Grid::get_cell_rect(int col, int row, SDL_Rect &rect) { 
    int x, y;
    get_xy(x, y);
    rect.x = ((col_size * col) + vpad + vline_size) + x;
    rect.y = ((row_size * row) + hpad + hline_size) + y;
    rect.w = col_size - (vpad*2) - vline_size;
    rect.h = row_size - (hpad*2) - hline_size;
}

//-----------------------------------------------------------------------------
void Grid::add_retangle(int col, int row, const SDL_Color &color, bool fill) {
    SDL_Rect rect;
    get_cell_rect(col, row, rect);
    Rectangle *p = new Rectangle(window_renderer, rect, color, fill);
    renders.push_back(p);
    map_renders[col][row] = p;
}

//-----------------------------------------------------------------------------
void Grid::add_texture(int col, int row, const string& file_name) { 
    SDL_Rect rect;
    get_cell_rect(col, row, rect);    
    Texture *p = new Texture(window_renderer, file_name, rect.x, rect.y);
    renders.push_back(p);
    map_renders[col][row] = p;
}    


//-----------------------------------------------------------------------------
void Grid::render(void) {

    Rectangles::render();

    for (auto i : renders) {
        i->render();    
    }
}

//-----------------------------------------------------------------------------
void Grid::set_x(int x) {

    Rectangles::set_x(x); 

    int m = numeric_limits<int>::max();
    for (auto& rect : rects) {
        m = min(m, rect.x);
    }     

    for (auto i : renders) {
        i->move(x-m, 0);
    }
}

//-----------------------------------------------------------------------------
void Grid::set_y(int y) {

    Rectangles::set_y(y); 

    int m = numeric_limits<int>::max();
    for (auto& rect : rects) {
        m = min(m, rect.y);
    }     

    for (auto i : renders) {
        i->move(0, y-m);
    }    
}

//-----------------------------------------------------------------------------
void Grid::move(int x, int y) {

    Rectangles::move(x, y);

    for (auto i : renders) {
        Rectangle *r = dynamic_cast<Rectangle*>(i);
        if(r) {
            r->rect.x += x;
            r->rect.y += y;
        } else {
            Texture *t = dynamic_cast<Texture*>(i);
            if(t) {
                t->rect.x += x;
                t->rect.y += y;
            }
        }
    }
}

//-----------------------------------------------------------------------------
void Grid::get_rect(SDL_Rect &rect) const {

    int min_x = numeric_limits<int>::max();
    int min_y = numeric_limits<int>::max();
    int max_x = numeric_limits<int>::min();
    int max_y = numeric_limits<int>::min();    
    
    for (auto& rect : rects) {
        min_x = min(min_x, rect.x);
        min_y = min(min_y, rect.y);
        max_x = max(max_x, rect.x + rect.w);
        max_y = max(max_y, rect.y + rect.h);
    }   

    rect.x = min_x;
    rect.y = min_y;
    rect.w = max_x - min_x;
    rect.h = max_y - min_y;
}

//-----------------------------------------------------------------------------
Render *Grid::get_render(int col, int row) {
    Render *result = map_renders[col][row];
    return result;
}

//-----------------------------------------------------------------------------
Render *Grid::remove_render(int col, int row) {
    Render *result = get_render(col, row);
    map_renders[col][row] = NULL;
    RendersI position = find(renders.begin(), renders.end(), result);
    if(position != renders.end())  {
        renders.erase(position);
    }
    return result;
}

