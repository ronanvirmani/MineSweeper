#include <fstream>
#include <SFML/Graphics.hpp>
#include <cctype>
#include "Textures.h"
#include "Cell.h"
using namespace std;
using namespace sf;

Cell::Cell(bool is_mine) {
    this->is_mine = is_mine;
    num_mines_around = 0;
    has_flag = false;
    revealed = false;

}


