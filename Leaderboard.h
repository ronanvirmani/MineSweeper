#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cctype>
#include <sstream>
using namespace std;
using namespace sf;

struct Leaderboard{

    int num_cols;
    int num_rows;
    int current_player_time;
    string current_player_name;
    vector<string> times;
    vector<string> names;
    bool new_time;


    Leaderboard(int num_cols, int num_rows, int current_player_time, string current_player_name, bool new_time){
        this->num_cols = num_cols;
        this->num_rows = num_rows;
        this->current_player_time = current_player_time;
        this->current_player_name = current_player_name;
        this->new_time = new_time;

    }

    Leaderboard(int num_cols, int num_rows){
        this->num_cols = num_cols;
        this->num_rows = num_rows;
        current_player_name = "none";
    }

    bool CreateLeaderBoard(bool open) {

        int width = num_cols * 16;
        int height = (num_rows * 16) + 50;


        RenderWindow lbWindow(VideoMode(width, height), "Minesweeper", sf::Style::Close);

        Font font;
        font.loadFromFile("files/font.ttf");

        fstream file;
        file.open("files/leaderboard.txt");

        for (int i = 0; i < 5; i++) {
            string data;
            getline(file, data);
            stringstream ss(data);
            for (int i = 0; i < 2; i++) {
                string data;
                getline(ss, data, ',');
                if (i == 0) {
                    times.push_back(data);
                } else if (i == 1) {
                    names.push_back(data);
                }
            }
        }

        string cpt;
        int j = current_player_time / 60;
        if(j < 10){
            cpt += "0";
            stringstream ss;
            ss << j;
            cpt += ss.str();
        }
        else{
            stringstream ss;
            ss << j;
            cpt += ss.str();
        }
        cpt += ":";

        int k = current_player_time - (j * 60);



        stringstream jj;
        jj << k;
        if(k < 10){
            cpt += "0";
        }
        cpt += jj.str();

        int count = 6;


        if(current_player_name != "none" && new_time){

            for(int i = 0; i < 5; i++){
                string temp = "";
                temp += times[i][0];
                temp += times[i][1];
                string temp2 = "";
                temp2 += times[i][3];
                temp2 += times[i][4];
                int min = stoi(temp);
                int sec = stoi(temp);


                if(j <= min){
                    if( k < sec){
                        cout << "here" << endl;
                    }
                    if(k < sec && i > 0 && j != min){
                        i--;
                    }
                    if(j == min){
                        i++;
                    }

                    if(i == 0){
                        count = i;
                        times[5] = times[4];
                        times[4] = times[3];
                        times[3] = times[2];
                        times[2] = times[1];
                        times[1] = times[0];
                        times[0] = cpt;
                        names[5] = names[4];
                        names[4] = names[3];
                        names[3] = names[2];
                        names[2] = names[1];
                        names[1] = names[0];
                        names[0] = current_player_name;
                        i = 6;
                    }
                    else if(i == 1){
                        count = i;
                        times[5] = times[4];
                        times[4] = times[3];
                        times[3] = times[2];
                        times[2] = times[1];
                        times[1] = cpt;
                        names[5] = names[4];
                        names[4] = names[3];
                        names[3] = names[2];
                        names[2] = names[1];
                        names[1] = current_player_name;
                        i = 5;
                    }
                    else if(i == 2){
                        count = i;
                        times[5] = times[4];
                        times[4] = times[3];
                        times[3] = times[2];
                        times[2] = cpt;
                        names[5] = names[4];
                        names[4] = names[3];
                        names[3] = names[2];
                        names[2] = current_player_name;
                        i = 6;
                    }
                    else if(i == 3){
                        count = i;
                        times[5] = times[4];
                        times[4] = times[3];
                        times[3] = cpt;
                        names[5] = names[4];
                        names[4] = names[3];
                        names[3] = current_player_name;
                        i = 6;
                    }
                    else if(i == 4){
                        count = i;
                        times[5] = times[4];
                        times[4] = cpt;
                        names[5] = names[4];
                        names[4] = current_player_name;
                        i = 6;
                    }


                }
            }

            file.close();
            //creating new duplicate version of file
            ofstream newFile("files/leaderboard.txt");
            for(int i = 0; i < 5; i++){

                string temp = times[i] + "," + names[i] + "\n";
                newFile << temp;
            }
            newFile.close();


        }

        Text leaderboard;
        leaderboard.setFont(font);
        leaderboard.setString("LEADERBOARD");
        leaderboard.setCharacterSize(20);
        leaderboard.setStyle(Text::Bold | Text::Underlined);
        FloatRect floatrect = leaderboard.getGlobalBounds();
        float messageWidth = floatrect.width;
        float messageHeight = floatrect.height;
        leaderboard.setPosition(width/2.0f - messageWidth/2.0f, height/2.0f - 130 - messageHeight/2);

        Text players;
        players.setFont(font);
        string output = "1.\t";
        output += times[0];
        output += "\t";
        output += names[0];
        if(count == 0){
            output += "*";
        }
        output += "\n\n";
        output += "2.\t";
        output += times[1];
        output += "\t";
        output += names[1];
        if(count == 1){
            output += "*";
        }
        output += "\n\n";
        output += "3.\t";
        output += times[2];
        output += "\t";
        output += names[2];
        if(count == 2){
            output += "*";
        }
        output += "\n\n";
        output += "4.\t";
        output += times[3];
        output += "\t";
        output += names[3];
        if(count == 3){
            output += "*";
        }
        output += "\n\n";
        output += "5.\t";
        output += times[4];
        output += "\t";
        output += names[4];
        if(count == 4){
            output += "*";
        }
        players.setString(output);
        players.setStyle(Text::Bold);
        players.setCharacterSize(18);
        FloatRect floatrect7 = players.getGlobalBounds();
        float messageWidth7 = floatrect7.width;
        float messageHeight7 = floatrect7.height;
        players.setPosition(width/2.0f - messageWidth7/2.0f, height/2.0f + 20 - messageHeight7/2.0f);

        if(open){
            while (lbWindow.isOpen()) {

                Event event;
                while (lbWindow.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        lbWindow.close();
                        return false;
                    }
                }
                lbWindow.clear(Color(0,0,255));
                lbWindow.draw(leaderboard);
                lbWindow.draw(players);
                lbWindow.display();
            }
        }
    }

};

