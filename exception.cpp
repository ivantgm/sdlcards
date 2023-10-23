#include "exception.hpp"
#include <iostream>

//-----------------------------------------------------------------------------
Exception::Exception(const string& msg, const string& error) {
    this->msg = msg;
    this->error = error;
}

//-----------------------------------------------------------------------------
void Exception::show(void) const {
    cout << msg << ": " << error << endl;
}
