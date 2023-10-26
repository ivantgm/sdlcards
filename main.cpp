#define SDL_MAIN_HANDLED
#include "cacheta.hpp"
#include "exception.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main() {
    try {
        Cacheta cacheta = Cacheta();
        cacheta.loop();        
    } catch(const Exception& e) {
        e.show();
        return -1;
    }	
    return 0;
}
