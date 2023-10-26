#ifndef __GAME_RENDER__
#define __GAME_RENDER__

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Render;

typedef vector<Render*> Renders;
typedef Renders::iterator RendersI;
typedef Renders::reverse_iterator RendersRI;

class Render {
protected:
    SDL_Renderer* window_renderer;
public:
    Render(SDL_Renderer* window_renderer);
    virtual ~Render();
public:
    SDL_Color color;
    virtual void render(void) = 0;
    virtual void set_x(int x) = 0;
    virtual void set_y(int y) = 0;
    virtual void move(int x, int y) = 0;
    void set_xy(int x, int y);
};

class Texture : public Render {
public:
    Texture(SDL_Renderer* window_renderer, const string& file_name, int x, int y);
    ~Texture();
public:      
    SDL_Rect rect;
    void render(void);      
    void set_x(int x);
    void set_y(int y);
    void move(int x, int y);
private:
    SDL_Texture* texture;    
};

class Rectangle : public Render {
public:
    Rectangle(SDL_Renderer* window_renderer, const SDL_Rect &rect, const SDL_Color &color, bool fill);
    ~Rectangle();
public:
    SDL_Rect rect;
    void render(void);
    void set_x(int x);
    void set_y(int y);
    void move(int x, int y);    
private:
    bool fill;    
};

class Rectangles : public Render {
public:
    Rectangles(SDL_Renderer* window_renderer, const vector<SDL_Rect>&rects, const SDL_Color &color, bool fill);
    ~Rectangles();
public:
    void render(void);
    void set_x(int x);
    void set_y(int y);
    void move(int x, int y);
    void get_xy(int &x, int &y);
protected:
    vector<SDL_Rect>rects;
private:
    bool fill;    
};

class Line : public Render {
public:
    Line(SDL_Renderer* window_renderer, const SDL_Point &point1, const SDL_Point &point2, const SDL_Color &color);
    ~Line();
public:
    SDL_Point point1, point2;
    void render(void);
    void set_x(int x);
    void set_y(int y);
    void move(int x, int y);        
};

class Lines : public Render {
public:
    Lines(SDL_Renderer* window_renderer, const vector<SDL_Point> &points, const SDL_Color &color);
    ~Lines();
public:
    void render(void);
    void set_x(int x);
    void set_y(int y);
    void move(int x, int y);       
private:
    vector<SDL_Point> points;
};

class Point : public Render {
public:
    Point(SDL_Renderer* window_renderer, const SDL_Point &point, const SDL_Color &color);
    ~Point();
public:
    SDL_Point point;
    void render(void); 
    void set_x(int x);
    void set_y(int y);
    void move(int x, int y);         
};

class Points : public Render {
public:
    Points(SDL_Renderer* window_renderer, const vector<SDL_Point>&points, const SDL_Color &color);
    ~Points();
public:
    void render(void);
    void set_x(int x);
    void set_y(int y);
    void move(int x, int y);       
private:
    vector<SDL_Point>points;    
};

class Grid : public Rectangles {
public:
    Grid(SDL_Renderer* window_renderer, 
         int cols, int rows, int col_size, 
         int row_size, int vline_size, int hline_size,
         int vpad, int hpad,
         const SDL_Color &color);
    ~Grid();
public:
    void get_cell_rect(int col, int row, SDL_Rect &rect);
    void add_retangle(int col, int row, const SDL_Color &color, bool fill);
    void add_texture(int col, int row, const string& file_name);

public:
    void render(void);    
    void set_x(int x);
    void set_y(int y);
    void move(int x, int y);    
private:
    int cols;
    int rows;
    int col_size;
    int row_size;    
    int vline_size;
    int hline_size;
    int vpad;
    int hpad;
    Renders renders;
};

#endif