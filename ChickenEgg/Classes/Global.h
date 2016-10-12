#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Global {
    public:
        Global();
        ~Global();
        static string username;
        static int score;
        static string toString(vector<char> *buffer);
};

#endif

