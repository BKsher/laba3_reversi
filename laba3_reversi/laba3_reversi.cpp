#include <iostream>
#include <SFML/Graphics.hpp>
#include "MyWindow.h"
#include "BoardController.h"
using namespace std;
using namespace sf;

const int size_squre = MyWindow::SIZE;
const int line_width = MyWindow::line_width;

int main()
{
    MyWindow window(VideoMode(size_squre * 8 + line_width, size_squre * 8 + line_width), "SFML works!");
    BoardController controller;
    string mode = "menu";

    while (window.isOpen())
    {
        if(mode == "game") controller.manageTurn();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (Mouse::isButtonPressed(Mouse::Left) && controller.awaitForClick) {
                Vector2i pos = Mouse::getPosition(window);
                int x = (int)(pos.y / size_squre), y = (int)(pos.x / size_squre);
                controller.move(x, y);
            }

            if (Mouse::isButtonPressed(Mouse::Left) && mode == "menu") {
                Vector2i pos = Mouse::getPosition(window);
                window.menuClicked(pos.x, pos.y, mode);
                controller.player1Name = window.getNames()[0];
                controller.player2Name = window.getNames()[1];
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                controller.resetBoard();
                mode = "menu";
            }
        }
        window.clear(Color::Green);

        window.drawAll(controller.board, controller.legalMoves, mode);

        window.display();

    }
}
