#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Entry {
    string name;
    int value;
    int cost;
    string label;
    string kind;
    string target;
    string cell;
};

int main() {