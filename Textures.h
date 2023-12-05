#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cctype>
using namespace std;
using namespace sf;

struct Texture_ {

    map<string, Sprite> sprites;
    Texture mine;
    Texture tile_hidden;
    Texture tile_revealed;
    Texture number_1;
    Texture number_2;
    Texture number_3;
    Texture number_4;
    Texture number_5;
    Texture number_6;
    Texture number_7;
    Texture number_8;
    Texture number_9;
    Texture debug;
    Texture digits;
    Texture face_happy;
    Texture face_lose;
    Texture face_win;
    Texture flag;
    Texture leaderboard;
    Texture pause;
    Texture play;

    void loadSprite() {

        mine.loadFromFile("files/images/mine.png");
//        if(!mine.loadFromFile("files/images/mine.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite mine_;
        mine_.setTexture(mine);
        sprites.emplace("mine", mine_);


        tile_hidden.loadFromFile("files/images/tile_hidden.png");
//        if(!tile_hidden.loadFromFile("files/images/tile_hidden.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite tile_hidden_;
        tile_hidden_.setTexture(tile_hidden);
        sprites.emplace("tile_hidden", tile_hidden_);


        tile_revealed.loadFromFile("files/images/tile_revealed.png");
//        if(!tile_revealed.loadFromFile("files/images/tile_revealed.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite tile_revealed_;
        tile_revealed_.setTexture(tile_revealed);
        sprites.emplace("tile_revealed", tile_revealed_);


        number_1.loadFromFile("files/images/number_1.png");
//        if(!number_1.loadFromFile("files/images/number_1.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite number_1_;
        number_1_.setTexture(number_1);
        sprites.emplace("number_1", number_1_);


        number_2.loadFromFile("files/images/number_2.png");
//        if(!number_2.loadFromFile("files/images/number_2.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite number_2_;
        number_2_.setTexture(number_2);
        sprites.emplace("number_2", number_2_);


        number_3.loadFromFile("files/images/number_3.png");
//        if(!number_3.loadFromFile("files/images/number_3.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite number_3_;
        number_3_.setTexture(number_3);
        sprites.emplace("number_3", number_3_);


        number_4.loadFromFile("files/images/number_4.png");
//        if(!number_4.loadFromFile("files/images/number_4.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite number_4_;
        number_4_.setTexture(number_4);
        sprites.emplace("number_4", number_4_);


        number_5.loadFromFile("files/images/number_5.png");
//        if(!number_5.loadFromFile("files/images/number_5.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite number_5_;
        number_5_.setTexture(number_5);
        sprites.emplace("number_5", number_5_);


        number_6.loadFromFile("files/images/number_6.png");
//        if(!number_6.loadFromFile("files/images/number_6.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite number_6_;
        number_6_.setTexture(number_6);
        sprites.emplace("number_6", number_6_);


        number_7.loadFromFile("files/images/number_7.png");
//        if(!number_7.loadFromFile("files/images/number_7.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite number_7_;
        number_7_.setTexture(number_7);
        sprites.emplace("number_7", number_7_);


        number_8.loadFromFile("files/images/number_8.png");
//        if(!number_8.loadFromFile("files/images/number_8.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite number_8_;
        number_8_.setTexture(number_8);
        sprites.emplace("number_8", number_8_);


        debug.loadFromFile("files/images/debug.png");
//        if(!debug.loadFromFile("files/images/debug.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite debug_;
        debug_.setTexture(debug);
        sprites.emplace("debug", debug_);

        digits.loadFromFile("files/images/digits.png");
//        if(!digits.loadFromFile("files/images/digits.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite digits_;
        digits_.setTexture(digits);
        sprites.emplace("digits", digits_);

        face_happy.loadFromFile("files/images/face_happy.png");
//        if(!face_happy.loadFromFile("files/images/face_happy.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite face_happy_;
        face_happy_.setTexture(face_happy);
        sprites.emplace("face_happy", face_happy_);

        face_lose.loadFromFile("files/images/face_lose.png");
//        if(!face_lose.loadFromFile("files/images/face_lose.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite face_lose_;
        face_lose_.setTexture(face_lose);
        sprites.emplace("face_lose", face_lose_);


        flag.loadFromFile("files/images/flag.png");
//        if(!flag.loadFromFile("files/images/flag.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite flag_;
        flag_.setTexture(flag);
        sprites.emplace("flag", flag_);


        leaderboard.loadFromFile("files/images/leaderboard.png");
//        if(!leaderboard.loadFromFile("files/images/leaderboard.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite leaderboard_;
        leaderboard_.setTexture(leaderboard);
        sprites.emplace("leaderboard", leaderboard_);


        pause.loadFromFile("files/images/pause.png");
//        if(!pause.loadFromFile("files/images/pause.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite pause_;
        pause_.setTexture(pause);
        sprites.emplace("pause", pause_);


        play.loadFromFile("files/images/play.png");
//        if(!play.loadFromFile("files/images/play.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite play_;
        play_.setTexture(play);
        sprites.emplace("play", play_);

        face_win.loadFromFile("files/images/face_win.png");
//        if(!face_win.loadFromFile("files/images/face_win.png")){
//            cout << "not loaded" << endl;
//        }
        Sprite face_win_;
        face_win_.setTexture(face_win);
        sprites.emplace("face_win", face_win_);





    }
};
