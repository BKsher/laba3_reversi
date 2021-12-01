#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Point.h"
using namespace sf;
using namespace std;

class MyWindow : public RenderWindow {
private:
    Font font;

public:
    static const int SIZE = 64, line_width = 4;
    static const int height = 8 * SIZE + line_width, width = 8 * SIZE + line_width;

    vector <string> names = { "Player", "AI Greedy", "AI Random", "AI Dynamic" };
    int curName1 = 0, curName2 = 0;

    MyWindow(VideoMode mode, const String& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings()) : RenderWindow(mode, title, style, settings) {
        font.loadFromFile("F:\\VisualStudioProjects\\University\\sem1.2\\laba5_reversi\\laba5_reversi\\Raleway-Regular.ttf");
    }
    
    vector <string> getNames() {
        return { names[curName1], names[curName2] };
    }

    void drawField() {
        RectangleShape line(Vector2f(SIZE * 8 + line_width, line_width));
        line.setFillColor(Color(105,105,105));
        for (int i = 0; i < 9; i++) {
            line.setPosition(0, i * SIZE);
            this->draw(line);
            line.rotate(90);
            line.setPosition(i * SIZE + line_width, 0);
            this->draw(line);
            line.rotate(-90);
        }
    }

    void drawPoint(long long x, long long y, int type) {
        if (!type) return;
        CircleShape shape(0.4 * SIZE);
        shape.setFillColor(type == 1 ? Color::Black : Color::White);
        shape.setPosition(((2 * y + 1) * SIZE + line_width - 0.8 * SIZE) / 2, ((2 * x + 1) * SIZE + line_width - 0.8 * SIZE) / 2);
        this->draw(shape);
    }

    void drawHighlightedPoint(long long x, long long y) {
        CircleShape shape(0.4 * SIZE);
        shape.setOutlineThickness(line_width);
        shape.setFillColor(Color::Green);
        shape.setOutlineColor(Color(255, 140, 0));
        shape.setPosition(((2 * y + 1) * SIZE + line_width - 0.8 * SIZE) / 2, ((2 * x + 1) * SIZE + line_width - 0.8 * SIZE) / 2);
        this->draw(shape);
    }

    void drawPoints(int** board) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                drawPoint(i, j, board[i][j]);
    }

    void drawHighlightedPoints(vector<Point> legalMoves) {
        for (Point p : legalMoves) {
            drawHighlightedPoint(p.x, p.y);
        }
    }

    void drawText(string output, int x, int y, int size, Color color) {
        Text text(output, font);
        text.setPosition(x, y);
        text.setCharacterSize(size);
        text.setFillColor(color);
        FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
        this->draw(text);
    }

    void menuClicked(double posX, double posY, string &mode) {
        if (posX + 60 > width / 2 && posX - 60 < width / 2 && posY + 10 > height / 3 && posY - 40 < height / 3)
            mode = "game";
        int x = (int)((posY + (SIZE / 4)) / SIZE) - 4, y = (int)(posX * 2 / width);
        if (x < 0 || y < 0 || x >= names.size() || y > 1) return;
        y == 0 ? curName1 = x : curName2 = x;
    }

    void drawMenu() {
        drawText("Reversi", width/2, 0, 48, Color::Black);
        drawText("VS", width / 2, height / 6, 36, Color::Black);
        drawText("PLAY", width / 2, height / 3, 48, Color::Black);
        drawText(names[curName1], width / 4, height / 6, 36, Color::Black);
        drawText(names[curName2], width * 3 / 4, height / 6, 36, Color::Black);
        
        for (int i = 0; i < names.size(); i++) {
            drawText(names[i], width / 4, height/2 + SIZE * i, 36, Color::Black);
            drawText(names[i], width * 3 / 4, height/2 + SIZE * i, 36, Color::Black);
        }

    }

    void drawGame(int** board, vector<Point> legalMoves) {
        drawField();
        drawPoints(board);
        drawHighlightedPoints(legalMoves);
    }

    void drawAll(int** board, vector<Point> legalMoves, string mode) {
        if (mode == "menu")
            drawMenu();
        else
            drawGame(board, legalMoves);
    }
};

