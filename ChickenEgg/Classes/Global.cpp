#include "Global.h"

#include <regex>
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;

string Global::username = "";
int Global::score = 0;

Global::Global() {}


Global::~Global() {}

string Global::toString(vector<char> *buffer) {
    string rst;
    for (char ch : *buffer) {
        rst.push_back(ch);
    }
    return rst;
}