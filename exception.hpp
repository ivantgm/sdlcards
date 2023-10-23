#ifndef __GAME_EXCEPTION__
#define __GAME_EXCEPTION__

#include <string>

using namespace std;

class Exception {    
public:
    Exception(const string& msg, const string& error);
    void show(void) const;
private:
    string msg;
    string error;
};

#endif
