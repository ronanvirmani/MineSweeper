#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cctype>
#include "Textures.h"
using namespace std;
using namespace sf;

struct Cell{

    bool is_mine;
    int num_mines_around = 0;
    bool has_flag;
    bool revealed;
    bool been_pushed = false;
    Cell(bool is_mine);

};