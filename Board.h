#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cctype>
#include "Textures.h"
#include "Cell.h"
#include <vector>
#include "Leaderboard.h"
using namespace std;
using namespace sf;


vector<int> getNeighbors(vector<Cell> cells, int position, int num_cols, int tile_count) {

    vector<int> returnCells;

    if (position < num_cols){

        if (position == 0){

            returnCells.push_back(position + 1); // right
            returnCells.push_back(position + num_cols); // down
            returnCells.push_back(position + num_cols + 1); // downright

        }
        else if(position == num_cols - 1){

            returnCells.push_back(position - 1); // left
            returnCells.push_back(position + num_cols); // down
            returnCells.push_back(position + num_cols -1); // downleft

        }
        else{

            returnCells.push_back(position + 1); // right
            returnCells.push_back(position + num_cols); // down
            returnCells.push_back(position + num_cols + 1); // downright
            returnCells.push_back(position - 1); // left
            returnCells.push_back(position + num_cols -1); // downleft

        }
    } //first row

    else if(position >= tile_count - num_cols) {

        if (position == tile_count - num_cols){ //375 bottom left

            returnCells.push_back(position + 1); // right
            returnCells.push_back(position - num_cols); // up
            returnCells.push_back(position - num_cols + 1); // upright

        }
        else if (position == tile_count - 1){

            returnCells.push_back(position - num_cols); // up
            returnCells.push_back(position - 1); // left
            returnCells.push_back(position - num_cols - 1); // upleft

        }
        else{

            returnCells.push_back(position - num_cols); // up
            returnCells.push_back(position - 1); // left
            returnCells.push_back(position - num_cols - 1); // upleft
            returnCells.push_back(position - num_cols + 1); // upright
            returnCells.push_back(position + 1); // right

        }
    } // bottom row

    else if(position % num_cols == 0 && position != 0 && position != tile_count - num_cols) {

        returnCells.push_back(position + 1); // right
        returnCells.push_back(position - num_cols); // up
        returnCells.push_back(position + num_cols); // down
        returnCells.push_back(position - num_cols + 1); // upright
        returnCells.push_back(position + num_cols + 1); // downright

    } // first col


    else if((position + 1) % num_cols == 0 && position != num_cols - 1 && position != tile_count - 1){

        returnCells.push_back(position - num_cols); // up
        returnCells.push_back(position + num_cols); // down
        returnCells.push_back(position - num_cols - 1); // upleft
        returnCells.push_back(position - 1); // left
        returnCells.push_back(position + num_cols -1); // downleft

    } //last col

    else{
        returnCells.push_back(position - num_cols); // up
        returnCells.push_back(position + num_cols); // down
        returnCells.push_back(position - num_cols - 1); // upleft
        returnCells.push_back(position - 1); // left
        returnCells.push_back(position + num_cols -1); // downleft
        returnCells.push_back(position - num_cols + 1); // upright
        returnCells.push_back(position + num_cols + 1); // downright
        returnCells.push_back(position + 1); // right

    }

    return returnCells;
}

void RevealTiles(vector<Cell> &cells, int position, int num_cols, int tile_count){


    vector<int> returnCells = getNeighbors(cells, position, num_cols, tile_count);
    cells[position].revealed = true;
    for(int i = 0; i < returnCells.size(); i++){
        int location = returnCells[i];

        // if it is a blank cell and needs to get re-revealed
        if(!cells[location].revealed && cells[location].num_mines_around == 0 && !cells[location].is_mine && !cells[location].has_flag){
            RevealTiles(cells, location, num_cols, tile_count);
        }
        // one of the neighbors is a number
        else if(cells[location].num_mines_around > 0 && !cells[location].is_mine && !cells[location].has_flag){
            cells[location].revealed = true;
        }
    }

}

void AddMines(vector<Cell> &cells, int tile_count, int num_mine){
    int count = 0;
    srand((unsigned) time(NULL));
    while(count < num_mine){
        int random_num = rand() % tile_count;
        if (!cells.at(random_num).is_mine){
            cells.at(random_num).is_mine = true;
            count++;
        }
    }
}

struct Board{

    map<string, Sprite> sprites;

    int num_cols;
    int num_rows;
    int num_mine;
    string user_name;


    Board(int num_cols, int num_rows, int num_mine, string user_name){
        this->num_cols = num_cols;
        this->num_rows = num_rows;
        this->num_mine = num_mine;
        this->user_name = user_name;

    }


    void CreateBoard() {

        vector<Cell> cells;
        vector<int> flags;
        vector<int> mines;
        vector<int> numbers;
        vector<int> blank_cells;
        bool first_time = true;


        int clicked_on = 0;

        int width = num_cols * 32;
        int height = num_rows * 32 + 100;
        int tile_count = num_cols * num_rows;


        RenderWindow gameWindow(VideoMode(width, height), "Minesweeper", sf::Style::Close);

        Font font;
        font.loadFromFile("files/font.ttf");

        Texture_ textures;
        textures.loadSprite();
        Sprite mine = textures.sprites["mine"];
        Sprite tile_hidden = textures.sprites["tile_hidden"];
        Sprite tile_revealed = textures.sprites["tile_revealed"];
        Sprite debug = textures.sprites["debug"];
        Sprite digits = textures.sprites["digits"];
        Sprite face_happy = textures.sprites["face_happy"];
        Sprite face_lose = textures.sprites["face_lose"];
        Sprite face_win = textures.sprites["face_win"];
        Sprite flag = textures.sprites["flag"];
        Sprite leaderboard = textures.sprites["leaderboard"];
        Sprite play = textures.sprites["play"];
        Sprite pause = textures.sprites["pause"];
        Sprite number_1 = textures.sprites["number_1"];
        Sprite number_2 = textures.sprites["number_2"];
        Sprite number_3 = textures.sprites["number_3"];
        Sprite number_4 = textures.sprites["number_4"];
        Sprite number_5 = textures.sprites["number_5"];
        Sprite number_6 = textures.sprites["number_6"];
        Sprite number_7 = textures.sprites["number_7"];
        Sprite number_8 = textures.sprites["number_8"];

        int w = 32;

        for (int i = 0; i < tile_count; i++){
            Cell newCell(false);
            cells.push_back(newCell);
        }

        AddMines(cells, tile_count, num_mine);


        for(int i = 0; i < tile_count; i++){

            int number_of_mines = 0;


            if (i < num_cols){

                if (i == 0){
                    if(cells[i].is_mine){
                        continue;
                    }
                    if(cells[i + 1].is_mine){ //right

                        number_of_mines++;
                    }
                    if(cells[i + num_cols].is_mine){ //down
                        number_of_mines++;
                    }
                    if(cells[i + num_cols + 1].is_mine){ //downright
                        number_of_mines++;
                    }
                }
                else if(i == num_cols - 1){
                    if(cells[i].is_mine){
                        continue;
                    }
                    if(cells[i - 1].is_mine){ //left
                        number_of_mines++;
                    }
                    if(cells[i + num_cols].is_mine){ //down
                        number_of_mines++;
                    }
                    if(cells[i + num_cols - 1].is_mine){ //downleft
                        number_of_mines++;
                    }

                }
                else{
                    if(cells[i].is_mine){
                        continue;
                    }
                    if(cells[i + 1].is_mine){ //right
                        number_of_mines++;
                    }
                    if(cells[i + num_cols].is_mine){ //down
                        number_of_mines++;
                    }
                    if(cells[i + num_cols + 1].is_mine){ //downright
                        number_of_mines++;
                    }
                    if(cells[i - 1].is_mine){ //left
                        number_of_mines++;
                    }
                    if(cells[i + num_cols - 1].is_mine){ //downleft
                        number_of_mines++;
                    }
                }
            } //first row

            else if(i >= tile_count - num_cols) {

                if (i == tile_count - num_cols){ //375 bottom left

                    if(cells[i].is_mine){
                        continue;
                    }
                    if(cells[i + 1].is_mine){ //right
                        number_of_mines++;
                    }
                    if(cells[i - num_cols].is_mine){ //up
                        number_of_mines++;
                    }
                    if(cells[i - num_cols + 1].is_mine){ //upright
                        number_of_mines++;
                    }
                }
                else if (i == tile_count - 1){
                    if(cells[i].is_mine){
                        continue;
                    }
                    if(cells[i - num_cols].is_mine){ //up
                        number_of_mines++;
                    }
                    if(cells[i - 1].is_mine){ //left
                        number_of_mines++;
                    }
                    if(cells[i - num_cols - 1].is_mine){ //upleft
                        number_of_mines++;
                    }
                }
                else{

                    if(cells[i].is_mine){
                        continue;
                    }
                    if(cells[i - num_cols].is_mine){ //up
                        number_of_mines++;
                    }
                    if(cells[i - 1].is_mine){ //left
                        number_of_mines++;
                    }
                    if(cells[i - num_cols - 1].is_mine){ //upleft
                        number_of_mines++;
                    }
                    if(cells[i + 1].is_mine){ //right
                        number_of_mines++;
                    }
                    if(cells[i - num_cols + 1].is_mine){ //upright
                        number_of_mines++;
                    }
                }
            } // bottom row

            else if(i % num_cols == 0 && i != 0 && i != tile_count - num_cols) {

                if(cells[i].is_mine){
                    continue;
                }
                if(cells[i + 1].is_mine){ //right
                    number_of_mines++;
                }
                if(cells[i - num_cols].is_mine){ //up
                    number_of_mines++;
                }
                if(cells[i + num_cols].is_mine){ //down
                    number_of_mines++;
                }
                if(cells[i - num_cols + 1].is_mine){ //upright
                    number_of_mines++;
                }
                if(cells[i + num_cols + 1].is_mine){ //downright
                    number_of_mines++;
                }

            } // first col


            else if( (i + 1) % num_cols == 0 && i != num_cols - 1 && i != tile_count - 1){
                if(i == tile_count - num_cols - 1){
                }
                if(cells[i].is_mine){
                    continue;
                }
                if(cells[i - num_cols].is_mine){ //up
                    number_of_mines++;
                }
                if(cells[i + num_cols].is_mine){ //down
                    number_of_mines++;
                }
                if(cells[i - num_cols - 1].is_mine){ //upleft
                    number_of_mines++;
                }
                if(cells[i - 1].is_mine){ //left
                    number_of_mines++;
                }
                if(cells[i + num_cols - 1].is_mine){ //downleft
                    number_of_mines++;
                }
            } //last col

            else{
                if(i == tile_count - num_cols - 1){
                    cout <<"here" << endl;

                }
                if(cells[i].is_mine){
                    continue;
                }
                if(cells[i - 1].is_mine){ //left
                    number_of_mines++;
                }
                if(cells[i + 1].is_mine){ //right
                    number_of_mines++;
                }
                if(cells[i - num_cols].is_mine){ //up
                    number_of_mines++;
                }
                if(cells[i + num_cols].is_mine){ //down
                    number_of_mines++;
                }
                if(cells[i - num_cols - 1].is_mine){ //upleft
                    number_of_mines++;
                }
                if(cells[i - num_cols + 1].is_mine){ //upright
                    number_of_mines++;
                }
                if(cells[i + num_cols - 1].is_mine){ //downleft
                    number_of_mines++;
                }
                if(cells[i + num_cols + 1].is_mine){ //downright
                    number_of_mines++;
                }
            }


            cells[i].num_mines_around = number_of_mines;
        }
        bool printmines = false;
        bool paused = false;
        int curr_flags_out = 0;

        int seconds_1 = 0;
        int seconds_2 = 0;
        int seconds_3 = 0;
        int seconds_4 = 0;

        bool game_won = false;
        bool game_lose = false;
        bool interaction = true;
        int time = 0;
        int final_time;
        bool pause_button_clicked = false;

        Clock clock1;
        Clock pausedClock;
        int sec_paused;
        bool leaderboard_open = false;

        while (gameWindow.isOpen()) {

            int curr_mine_count;

            Time elapsed_time_clock1 = clock1.getElapsedTime();
            Time t2 = pausedClock.getElapsedTime();

            final_time = (int)elapsed_time_clock1.asSeconds();

            gameWindow.clear(Color(255, 255, 255));

            for (int i = 0; i < tile_count; i++) {

                int col = i % num_cols;
                int row = i / num_cols;
                tile_hidden.setPosition(col * w, row * w);
                gameWindow.draw(tile_hidden);
                if(printmines){
                    if(cells[i].is_mine){
                        mine.setPosition(col * w, row * w);
                        gameWindow.draw(mine);
                    }
                }
                else if(paused){
                    tile_revealed.setPosition(col * w, row * w);
                    gameWindow.draw(tile_revealed);
                }
                if(leaderboard_open){

                    Leaderboard leaderboard(num_cols, num_rows);
                    bool con = leaderboard.CreateLeaderBoard(true);
                    if(!con){
                        leaderboard_open = false;
                        sec_paused = (int)pausedClock.getElapsedTime().asSeconds();
                        time += sec_paused;
                    }
                }
                if(game_won && cells[i].is_mine){
                    curr_flags_out = num_mine;
                    flag.setPosition(col * w, row * w);
                    gameWindow.draw(flag);
                }
            }

            face_happy.setPosition(((num_cols / 2.0) * 32) - 32, 32 *(num_rows +0.5f));
            debug.setPosition((num_cols * 32) - 304, 32 * (num_rows+0.5f));
            pause.setPosition((num_cols * 32) - 240, 32 * (num_rows+0.5f));
            leaderboard.setPosition((num_cols * 32) - 176, 32 * (num_rows+0.5f));
            gameWindow.draw(face_happy);
            gameWindow.draw(leaderboard);
            gameWindow.draw(pause);
            gameWindow.draw(debug);

            Event event;
            while (gameWindow.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    gameWindow.close();
                }

                if(event.type == Event::MouseButtonPressed){

                    Vector2i position = Mouse::getPosition(gameWindow);
                    int x = position.x / w;
                    int y = position.y / w;
                    int tile_clicked = (y * num_cols) + x;
                    bool inBoard;
                    if(position.y <= num_rows * w){
                        inBoard = true;
                    }
                    else{
                        inBoard = false;
                    }

                    if (inBoard && interaction) {
                        if (event.key.code == Mouse::Left && !paused) {
                            if(!cells[tile_clicked].has_flag){
                                if (cells[tile_clicked].is_mine) {
                                    mines.push_back(tile_clicked);
                                }
                                else if(cells[tile_clicked].num_mines_around > 0){
                                    if(!cells[tile_clicked].been_pushed){
                                        numbers.push_back(tile_clicked);
                                        clicked_on++;
                                        cells[tile_clicked].been_pushed = true;
                                    }

                                }
                                else{
                                    RevealTiles(cells, tile_clicked, num_cols, tile_count);

                                    for(int i = 0; i < tile_count; i++){

                                        if(cells[i].revealed){
                                            if(cells[i].num_mines_around > 0 && !cells[i].been_pushed){
                                                clicked_on++;
                                                numbers.push_back(i);
                                                cells[i].been_pushed = true;
                                            }
                                            else if(!cells[i].been_pushed){
                                                clicked_on++;
                                                blank_cells.push_back(i);
                                                cells[i].been_pushed = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else if (event.key.code == Mouse::Right && !paused) {
                            cells[tile_clicked].has_flag = !cells[tile_clicked].has_flag;
                            if(cells[tile_clicked].has_flag){
                                curr_flags_out ++;
                            }
                            else{
                                curr_flags_out --;
                            }
                            flags.push_back(tile_clicked);
                        }
                    }

                    else{
                        if (event.key.code == Mouse::Left) {
                            if(position.y > 32 * (num_rows+0.5f) && position.y < 32 * (num_rows+0.5f) + 60){
                                //debug button
                                if(position.x > (num_cols * 32) - 304 && position.x < (num_cols * 32) - 304 + 60 && interaction){
                                    printmines = !printmines;
                                }
                                //leaderboard button
                                if(position.x > (num_cols * 32) - 176 && position.x < (num_cols * 32) - 176 + 60){

                                    if(!game_won){
                                        for (int i = 0; i < tile_count; i++) {

                                            int col = i % num_cols;
                                            int row = i / num_cols;
                                            tile_revealed.setPosition(col * w, row * w);
                                            gameWindow.draw(tile_revealed);
                                        }
                                    }

                                    pausedClock.restart();
                                    leaderboard_open = !leaderboard_open;

                                }

                                //face button
                                else if(position.x > (((num_cols) / 2.0) * 32) - 32 && position.x < ((num_cols / 2.0) * 32) - 32 + 60){
                                    gameWindow.close();
                                    Board board(num_cols, num_rows, num_mine, user_name);
                                    board.CreateBoard();
                                }

                                //pause/play button
                                if(position.x > (num_cols * 32) - 240 && position.x < (num_cols * 32) - 240 + 60 && interaction) {
                                    paused = !paused;
                                    pause_button_clicked = !pause_button_clicked;
                                    if(pause_button_clicked){
                                        pausedClock.restart();
                                    }
                                    else{
                                        sec_paused = (int)pausedClock.getElapsedTime().asSeconds();
                                        time += sec_paused;
                                    }

                                }

                            }
                        }
                    }
                }
            }

            if(!paused){
                pause.setPosition((num_cols * 32) - 240, 32 * (num_rows+0.5f));
                gameWindow.draw(pause);
            }
            else{
                play.setPosition((num_cols * 32) - 240, 32 * (num_rows+0.5f));
                gameWindow.draw(play);
            }



            for(int i = 0; i < mines.size(); i++){

                int curr_tile = mines[i];
                int col = curr_tile % num_cols;
                int row = curr_tile / num_cols;

                if (cells[curr_tile].is_mine){

                    face_lose.setPosition(((num_cols / 2.0) * 32) - 32, 32 *(num_rows +0.5f));
                    mine.setPosition(col * w, row * w);
                    gameWindow.draw(mine);
                    gameWindow.draw(face_lose);
                    printmines = true;
                    interaction = false;
                    game_lose = true;
                }

            }

            for (int i = 0; i < flags.size(); i++){

                if(!paused){
                    int curr_tile = flags[i];
                    int col = curr_tile % num_cols;
                    int row = curr_tile / num_cols;

                    if(cells[curr_tile].has_flag){
                        flag.setPosition(col * w, row * w);
                        gameWindow.draw(flag);
                    }
                    else{
                        if(!cells[curr_tile].revealed){
                            tile_hidden.setPosition(col * w, row * w);
                            gameWindow.draw(tile_hidden);
                        }
                    }
                }

            }

            for(int i = 0; i < numbers.size(); i++){

                if(!paused){
                    int curr_tile = numbers[i];
                    int col = curr_tile % num_cols;
                    int row = curr_tile / num_cols;

                    if (cells[curr_tile].num_mines_around == 1) {
                        tile_revealed.setPosition(col * w, row * w);
                        number_1.setPosition(col * w , row * w);
                        gameWindow.draw(tile_revealed);
                        gameWindow.draw(number_1);
                    } else if (cells[curr_tile].num_mines_around == 2) {
                        tile_revealed.setPosition(col * w, row * w);
                        number_2.setPosition(col * w , row * w);
                        gameWindow.draw(tile_revealed);
                        gameWindow.draw(number_2);
                    } else if (cells[curr_tile].num_mines_around == 3) {
                        tile_revealed.setPosition(col * w, row * w);
                        number_3.setPosition(col * w , row * w);
                        gameWindow.draw(tile_revealed);
                        gameWindow.draw(number_3);
                    } else if (cells[curr_tile].num_mines_around == 4) {
                        tile_revealed.setPosition(col * w, row * w);
                        number_4.setPosition(col * w , row * w);
                        gameWindow.draw(tile_revealed);
                        gameWindow.draw(number_4);
                    } else if (cells[curr_tile].num_mines_around == 5) {
                        tile_revealed.setPosition(col * w, row * w);
                        number_5.setPosition(col * w , row * w);
                        gameWindow.draw(tile_revealed);
                        gameWindow.draw(number_5);
                    } else if (cells[curr_tile].num_mines_around == 6) {
                        tile_revealed.setPosition(col * w, row * w);
                        number_6.setPosition(col * w , row * w);
                        gameWindow.draw(tile_revealed);
                        gameWindow.draw(number_6);
                    } else if (cells[curr_tile].num_mines_around == 7) {
                        tile_revealed.setPosition(col * w, row * w);
                        number_7.setPosition(col * w , row * w);
                        gameWindow.draw(tile_revealed);
                        gameWindow.draw(number_7);
                    } else if (cells[curr_tile].num_mines_around == 8) {
                        tile_revealed.setPosition(col * w, row * w);
                        number_8.setPosition(col * w , row * w);
                        gameWindow.draw(tile_revealed);
                        gameWindow.draw(number_8);
                    }
                }



            }

            for(int i = 0; i < blank_cells.size(); i++){
                if(!paused) {
                    int curr_tile = blank_cells[i];
                    int col = curr_tile % num_cols;
                    int row = curr_tile / num_cols;
                    tile_revealed.setPosition(col * w, row * w);
                    gameWindow.draw(tile_revealed);
                }
            }

            curr_mine_count = num_mine - curr_flags_out;

            int num_digit;
            int tens_digit;
            if (curr_mine_count < 0){
                num_digit = -curr_mine_count % 10;
                tens_digit = -curr_mine_count / 10;

            }
            else{
                num_digit = curr_mine_count % 10;
                tens_digit = curr_mine_count / 10;
            }
            int hund_digit = curr_mine_count / 100;


            for(int i = 0; i <= hund_digit; i++){
                if(curr_mine_count < 0){
                    digits.setTextureRect(IntRect(10 *  21,0,21,32));
                    digits.setPosition(33, 32 * ((num_rows)+0.5f)+16);
                    gameWindow.draw(digits);
                }
                else{
                    digits.setTextureRect(IntRect(i *  21,0,21,32));
                    digits.setPosition(33, 32 * ((num_rows)+0.5f)+16);
                    gameWindow.draw(digits);
                }


            }
            for(int i = 0; i <= tens_digit; i++){
                digits.setTextureRect(IntRect(i * 21,0,21,32));
                digits.setPosition(33 + 21, 32 * ((num_rows)+0.5f)+16);
                gameWindow.draw(digits);
            }
            for(int i = 0; i <= num_digit; i++){
                digits.setTextureRect(IntRect(i * 21,0,21,32));
                digits.setPosition(33 + 21 + 21, 32 * ((num_rows)+0.5f)+16);
                gameWindow.draw(digits);
            }

            if((!paused  || leaderboard_open) && !game_lose){
                seconds_1 = (final_time - time) % 10;
                seconds_2 = ((final_time - time) % 60) / 10;
                seconds_3 = (final_time - time)/ 60;
                seconds_4 = (final_time - time) / 600;
            }


            for(int i = 0; i <= seconds_4; i++){
                digits.setTextureRect(IntRect(i *  21,0,21,32));
                digits.setPosition(((num_cols) * 32) - 97, 32 * ((num_rows)+0.5f)+16 );
                gameWindow.draw(digits);
            }
            for(int i = 0; i <= seconds_3; i++){
                digits.setTextureRect(IntRect(i *  21,0,21,32));
                digits.setPosition(((num_cols) * 32) - 97 + 21, 32 * ((num_rows)+0.5f)+16 );
                gameWindow.draw(digits);
            }
            for(int i = 0; i <= seconds_2; i++){
                digits.setTextureRect(IntRect(i *  21,0,21,32));
                digits.setPosition(((num_cols) * 32) - 54, 32 * ((num_rows)+0.5f)+16 );
                gameWindow.draw(digits);
            }
            for(int i = 0; i <= seconds_1; i++){
                digits.setTextureRect(IntRect(i *  21,0,21,32));
                digits.setPosition(((num_cols) * 32) - 54 + 21, 32 * ((num_rows)+0.5f)  + 16 );
                gameWindow.draw(digits);
            }

//            if(reset){
//                for(int i = 0; i < tile_count; i++){
//                    cells[i].is_mine = false;
//                    cells[i].has_flag = false;
//
//                    int col = i % num_cols;
//                    int row = i / num_cols;
//                    tile_hidden.setPosition(col * w, row * w);
//                    gameWindow.draw(tile_hidden);
//
//                    int count = 0;
//                    srand((unsigned) time(NULL));
//                    while(count < num_mine){
//                        int random_num = rand() % tile_count;
//                        if (!cells.at(random_num).is_mine){
//                            cells.at(random_num).is_mine = true;
//                            count++;
//                        }
//                    }
//
//                    for(int i = 0; i < tile_count; i++){
//
//                        int number_of_mines = 0;
//
//
//                        if (i < num_cols){
//
//                            if (i == 0){
//                                if(cells[i].is_mine){
//                                    continue;
//                                }
//                                if(cells[i + 1].is_mine){ //right
//
//                                    number_of_mines++;
//                                }
//                                if(cells[i + num_cols].is_mine){ //down
//                                    number_of_mines++;
//                                }
//                                if(cells[i + num_cols + 1].is_mine){ //downright
//                                    number_of_mines++;
//                                }
//                            }
//                            else if(i == num_cols - 1){
//                                if(cells[i].is_mine){
//                                    continue;
//                                }
//                                if(cells[i - 1].is_mine){ //left
//                                    number_of_mines++;
//                                }
//                                if(cells[i + num_cols].is_mine){ //down
//                                    number_of_mines++;
//                                }
//                                if(cells[i + num_cols - 1].is_mine){ //downleft
//                                    number_of_mines++;
//                                }
//
//                            }
//                            else{
//                                if(cells[i].is_mine){
//                                    continue;
//                                }
//                                if(cells[i + 1].is_mine){ //right
//                                    number_of_mines++;
//                                }
//                                if(cells[i + num_cols].is_mine){ //down
//                                    number_of_mines++;
//                                }
//                                if(cells[i + num_cols + 1].is_mine){ //downright
//                                    number_of_mines++;
//                                }
//                                if(cells[i - 1].is_mine){ //left
//                                    number_of_mines++;
//                                }
//                                if(cells[i + num_cols - 1].is_mine){ //downleft
//                                    number_of_mines++;
//                                }
//                            }
//                        } //first row
//
//                        else if(i >= tile_count - num_cols) {
//
//                            if (i == tile_count - num_cols){ //375 bottom left
//
//                                if(cells[i].is_mine){
//                                    continue;
//                                }
//                                if(cells[i + 1].is_mine){ //right
//                                    number_of_mines++;
//                                }
//                                if(cells[i - num_cols].is_mine){ //up
//                                    number_of_mines++;
//                                }
//                                if(cells[i - num_cols + 1].is_mine){ //upright
//                                    number_of_mines++;
//                                }
//                            }
//                            else if (i == tile_count - 1){
//                                if(cells[i].is_mine){
//                                    continue;
//                                }
//                                if(cells[i - num_cols].is_mine){ //up
//                                    number_of_mines++;
//                                }
//                                if(cells[i - 1].is_mine){ //left
//                                    number_of_mines++;
//                                }
//                                if(cells[i - num_cols - 1].is_mine){ //upleft
//                                    number_of_mines++;
//                                }
//                            }
//                            else{
//
//                                if(cells[i].is_mine){
//                                    continue;
//                                }
//                                if(cells[i - num_cols].is_mine){ //up
//                                    number_of_mines++;
//                                }
//                                if(cells[i - 1].is_mine){ //left
//                                    number_of_mines++;
//                                }
//                                if(cells[i - num_cols - 1].is_mine){ //upleft
//                                    number_of_mines++;
//                                }
//                                if(cells[i + 1].is_mine){ //right
//                                    number_of_mines++;
//                                }
//                                if(cells[i - num_cols + 1].is_mine){ //upright
//                                    number_of_mines++;
//                                }
//                            }
//                        } // bottom row
//
//                        else if(i % num_cols == 0 && i != 0 && i != tile_count - num_cols) {
//
//                            if(cells[i].is_mine){
//                                continue;
//                            }
//                            if(cells[i + 1].is_mine){ //right
//                                number_of_mines++;
//                            }
//                            if(cells[i - num_cols].is_mine){ //up
//                                number_of_mines++;
//                            }
//                            if(cells[i + num_cols].is_mine){ //down
//                                number_of_mines++;
//                            }
//                            if(cells[i - num_cols + 1].is_mine){ //upright
//                                number_of_mines++;
//                            }
//                            if(cells[i + num_cols + 1].is_mine){ //downright
//                                number_of_mines++;
//                            }
//
//                        } // first col
//
//
//                        else if( (i + 1) % num_cols == 0 && i != num_cols - 1 && i != tile_count - 1){
//                            if(i == tile_count - num_cols - 1){
//                            }
//                            if(cells[i].is_mine){
//                                continue;
//                            }
//                            if(cells[i - num_cols].is_mine){ //up
//                                number_of_mines++;
//                            }
//                            if(cells[i + num_cols].is_mine){ //down
//                                number_of_mines++;
//                            }
//                            if(cells[i - num_cols - 1].is_mine){ //upleft
//                                number_of_mines++;
//                            }
//                            if(cells[i - 1].is_mine){ //left
//                                number_of_mines++;
//                            }
//                            if(cells[i + num_cols - 1].is_mine){ //downleft
//                                number_of_mines++;
//                            }
//                        } //last col
//
//                        else{
//                            if(i == tile_count - num_cols - 1){
//                                cout <<"here" << endl;
//
//                            }
//                            if(cells[i].is_mine){
//                                continue;
//                            }
//                            if(cells[i - 1].is_mine){ //left
//                                number_of_mines++;
//                            }
//                            if(cells[i + 1].is_mine){ //right
//                                number_of_mines++;
//                            }
//                            if(cells[i - num_cols].is_mine){ //up
//                                number_of_mines++;
//                            }
//                            if(cells[i + num_cols].is_mine){ //down
//                                number_of_mines++;
//                            }
//                            if(cells[i - num_cols - 1].is_mine){ //upleft
//                                number_of_mines++;
//                            }
//                            if(cells[i - num_cols + 1].is_mine){ //upright
//                                number_of_mines++;
//                            }
//                            if(cells[i + num_cols - 1].is_mine){ //downleft
//                                number_of_mines++;
//                            }
//                            if(cells[i + num_cols + 1].is_mine){ //downright
//                                number_of_mines++;
//                            }
//                        }
//
//
//                        cells[i].num_mines_around = number_of_mines;
//                    }
//
//                }
//            }
            if(clicked_on == tile_count - num_mine){

                face_win.setPosition(((num_cols / 2.0) * 32) - 32, 32 *(num_rows +0.5f));
                gameWindow.draw(face_win);
                game_won = true;
                interaction = false;
                game_lose = true;

            }

            if(game_won && first_time){
                Leaderboard leaderboard1(num_cols, num_rows, final_time - time,user_name, first_time);
                leaderboard1.CreateLeaderBoard(false);
                first_time = false;
            }
            else if(game_won && !first_time){
                Leaderboard leaderboard1(num_cols, num_rows, final_time - time,user_name, first_time);
                leaderboard1.CreateLeaderBoard(false);
            }
            gameWindow.display();

        }
    }

};