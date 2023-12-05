#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cctype>
#include "Board.h"
using namespace std;
using namespace sf;



struct WelcomeWindow{

    void openWindow(){
        fstream file;
        file.open("files/board_config.cfg");
        int num_cols;
        int num_rows;
        int num_mine;
        file >> num_cols;
        file >> num_rows;
        file >> num_mine;
        int width = num_cols * 32;
        int height = num_rows * 32 + 100;



        RenderWindow welcomeWindow(VideoMode(width, height), "Minesweeper", sf::Style::Close);

        Font font;
        font.loadFromFile("files/font.ttf");


        Text welcomeMessage;
        welcomeMessage.setFont(font);
        welcomeMessage.setString("WELCOME TO MINESWEEPER!");
        welcomeMessage.setCharacterSize(24);
        welcomeMessage.setStyle(Text::Bold | Text::Underlined);
        FloatRect floatrect = welcomeMessage.getGlobalBounds();
        float messageWidth = floatrect.width;
        float messageHeight = floatrect.height;
        welcomeMessage.setPosition(width/2.0f - messageWidth/2.0f, height/2.0f - 150 - messageHeight/2);

        Text inputPrompt;
        inputPrompt.setFont(font);
        inputPrompt.setString("Enter your name:");
        inputPrompt.setCharacterSize(20);
        inputPrompt.setStyle(Text::Bold);
        FloatRect floatrect2 = inputPrompt.getGlobalBounds();
        float inputWidth = floatrect2.width;
        float inputHeight = floatrect2.height;
        inputPrompt.setPosition(width/2.0f - inputWidth/2.0f, height/2.0f - 75 - inputHeight/2);

        string name = "";
        Text inputText;
        inputText.setString(name);
        inputText.setFont(font);
        inputText.setCharacterSize(18);
        inputText.setFillColor(Color::Yellow);
        FloatRect floatrect3 = inputText.getGlobalBounds();
        float inputWidth2 = floatrect3.width;
        float inputHeight2 = floatrect3.height;
        inputText.setPosition(width/2.0f - inputWidth2/2.0f, height/2.0f - 45 - inputHeight2/2);

        Text cursor;
        cursor.setString("|");
        cursor.setFont(font);
        cursor.setCharacterSize(20);
        cursor.setFillColor(Color::Yellow);
        cursor.setPosition(width/2.0f, height/2.0f - 52);


        while (welcomeWindow.isOpen())
        {

            Event event;
            while (welcomeWindow.pollEvent(event))
            {
                if (event.type == Event::Closed){
                    welcomeWindow.close();
                }

                if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && name.length() > 0){
                    welcomeWindow.close();
                    Board board(num_cols, num_rows, num_mine, name);
                    board.CreateBoard();
                }


                if (event.type == Event::TextEntered){

                    if(name.length() < 10){

                        if(isalpha(static_cast<char>(event.text.unicode))){

                            if(name.length() == 0){

                                name += toupper(static_cast<char>(event.text.unicode));
                                inputText.setString(name);
                                inputText.setFillColor(Color::Yellow);
                                FloatRect floatrect3 = inputText.getGlobalBounds();
                                float inputWidth2 = floatrect3.width;
                                float inputHeight2 = floatrect3.height;
                                inputText.setPosition(width/2.0f - inputWidth2/2.0f, height/2.0f - 45 - inputHeight2/2);
                            }

                            else{

                                name += tolower(static_cast<char>(event.text.unicode));
                                inputText.setString(name);
                                inputText.setFillColor(Color::Yellow);
                                FloatRect floatrect3 = inputText.getGlobalBounds();
                                float inputWidth2 = floatrect3.width;
                                float inputHeight2 = floatrect3.height;
                                inputText.setPosition(width/2.0f - inputWidth2/2.0f, height/2.0f - 45 - inputHeight2/2);

                            }

                            cursor.setPosition(width/2.0f + name.length() * 5, height/2.0f - 52);

                        }
                    }
                }

                else if(event.type == Event::KeyPressed && event.key.code == Keyboard::Backspace){
                    if(name.length() > 0){
                        string temp;
                        for (int i = 0; i < name.length() - 1; i++){
                            temp += name[i];
                        }
                        name = temp;
                        inputText.setString(name);
                        inputText.setFillColor(Color::Yellow);
                        FloatRect floatrect3 = inputText.getGlobalBounds();
                        float inputWidth2 = floatrect3.width;
                        float inputHeight2 = floatrect3.height;
                        inputText.setPosition(width/2.0f - inputWidth2/2.0f, height/2.0f - 45 - inputHeight2/2);
                    }

                    cursor.setPosition(width/2.0f + (name.length() - 1) * 5, height/2.0f - 52);
                    if(name.length() == 0){
                        cursor.setPosition(width/2.0f, height/2.0f - 52);
                    }

                }
            }

            welcomeWindow.clear(Color(0,0,255));
            welcomeWindow.draw(inputText);
            welcomeWindow.draw(welcomeMessage);
            welcomeWindow.draw(inputPrompt);
            welcomeWindow.draw(cursor);
            welcomeWindow.display();
        }
    }
};

