#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cctype>
#include "WelcomeWindow.h"
#include "Board.h"
#include "Leaderboard.h"
using namespace std;
using namespace sf;

int main()
{

    WelcomeWindow welcomewindow;
    welcomewindow.openWindow();
//    fstream file;
//    file.open("files/board_config.cfg");
//    int num_cols;
//    int num_rows;
//    int num_mine;
//    file >> num_cols;
//    file >> num_rows;
//    file >> num_mine;
//    Board board(num_cols, num_rows, 2, "name");
//    board.CreateBoard();
//    Leaderboard leaderboard(num_cols, num_rows, 3600, "Rayna");
//    leaderboard.CreateLeaderBoard(false);




    return 0;
}
