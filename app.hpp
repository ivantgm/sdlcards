#ifndef __GAME_APP__
#define __GAME_APP__

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "render.hpp"

using namespace std;

typedef vector<Render*> Renders;
typedef Renders::iterator RendersI;
typedef Renders::reverse_iterator RendersRI;

class App {
public:
    App(const string& window_caption, int width, int heigth);
    ~App();
public:    
    void loop(void);
    virtual void poll_event(SDL_Event *e);
protected:
    SDL_Renderer* window_renderer;
    Renders renders;    
    void add_texture(const string& file_name, int x, int y);
    void add_rectangle(const SDL_Rect &rect, const SDL_Color &color, bool fill);
    void add_rectangles(const vector<SDL_Rect> &rects, const SDL_Color &color, bool fill);
    void add_line(const SDL_Point &point1, const SDL_Point &point2, const SDL_Color &color);
    void add_lines(const vector<SDL_Point> &points, const SDL_Color &color);
    void add_point(const SDL_Point &point, const SDL_Color &color);
    void add_points(const vector<SDL_Point> &points, const SDL_Color &color);
    Grid *add_grid(
            int cols, int rows, 
            int col_size, int row_size, 
            int vline_size, int hline_size, 
            int vpad, int hpad, 
            const SDL_Color &color
        );
private:
    SDL_Window* window;    
private:
    void render_renders(void);
    void delete_renders(void);
    void render(void);
};

#endif
