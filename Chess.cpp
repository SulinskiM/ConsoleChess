#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

//Szachy w trybie konsolowym

struct Move
{
    int x;
    int y;
};

class Figure
{
public:
    virtual void move() = 0;
    virtual void print() = 0;
    Figure(int, int, bool);
    int getPositionX() { return positionX; };
    int getPositionY() { return positionY; };
    bool getColor() { return color; };

private:
    bool color;
    int positionX;
    int positionY;
    int directMove; //1 - ruch w rosnącym kierunku, -1 - ruch w przeciwną stronę
};

Figure::Figure(int x, int y, bool playerColor) : color(playerColor)
{
    positionX = x;
    positionY = y;
}

class Pawn 
    : public Figure
{
public:
    virtual void move();
    virtual void print();
    Pawn(int x, int y, bool color) : Figure(x, y, color) { moveState = false; };

private:
    bool moveState; //Czy nastąpił pierwszy ruch

};
void Pawn::move()
{

}
void Pawn::print()
{
    cout << "P";
}

class King 
    : public Figure
{
public:
    virtual void move();
    virtual void print();
    King(int x, int y, bool color) : Figure(x, y, color) {};

private:

};
void King::move()
{

}
void King::print()
{
    cout << "K";
}

class Rock 
    : public Figure
{
public:
    virtual void move();
    virtual void print();
    Rock(int x, int y, bool color) : Figure(x, y, color) {};

private:

};
void Rock::move()
{

}
void Rock::print()
{
    cout << "R";
}

class Bishop 
    : public Figure
{
public:
    virtual void move();
    virtual void print();
    Bishop(int x, int y, bool color) : Figure(x, y, color) {};

private:

};
void Bishop::move()
{

}
void Bishop::print()
{
    cout << "B";
}

class Queen 
    : public Figure
{
public:
    virtual void move();
    virtual void print();
    Queen(int x, int y, bool color) : Figure(x, y, color) {};

private:

};
void Queen::move()
{

}
void Queen::print()
{
    cout << "Q";
}

class Knight 
    : public Figure
{
public:
    virtual void move();
    virtual void print();
    Knight(int x, int y, bool color) : Figure(x, y, color) {};

private:

};
void Knight::move()
{

}
void Knight::print()
{
    cout << "N";
}

class Player
{
public:
    Player(int, bool);
    ~Player();
    auto getFiguresBegin();
    auto getFiguresEnd();

private:
    bool playerColor;
    vector<Figure*> figures;
};

auto Player::getFiguresBegin()
{
    return figures.begin();
}

auto Player::getFiguresEnd()
{
    return figures.end();
}

Player::Player(int positionHeight, bool color) : playerColor(color)
{
    Pawn* figure;
    for (int i = 0; i < 8; i++)
    {
        figure = new Pawn(i, positionHeight, playerColor);
        figures.push_back(figure);
    }
    if (positionHeight == 1)
        positionHeight--;
    else
        positionHeight++;
    
    Queen* queen;
    queen = new Queen(4, positionHeight, playerColor);
    figures.push_back(queen);

    King* king;
    king = new King(3, positionHeight, playerColor);
    figures.push_back(king);

    Rock* rock;
    rock = new Rock(0, positionHeight, playerColor);
    figures.push_back(rock);
    rock = new Rock(7, positionHeight, playerColor);
    figures.push_back(rock);

    Knight* knight;
    knight = new Knight(1, positionHeight, playerColor);
    figures.push_back(knight);
    knight = new Knight(6, positionHeight, playerColor);
    figures.push_back(knight);

    Bishop* bishop;
    bishop = new Bishop(2, positionHeight, playerColor);
    figures.push_back(bishop);
    bishop = new Bishop(5, positionHeight, playerColor);
    figures.push_back(bishop);
}

Player::~Player()
{

}

class Chess
{
public:
    void printBoard(vector<pair<int, int>>);
    void takeMove();
    Chess();
    ~Chess();

private:
    Player* WhitePlayer;
    Player* BlackPlayer;
    Figure* board[8][8];
    const int boardWidth = 8;
    const int boardHeight = 8;
};

void Chess::takeMove()
{
    unsigned char moveInt = 0;
    unsigned char moveChar = 0;
    unsigned char znak;

    vector<pair<int, int>> checked;

    do
    {
        znak = _getch();
        system("cls");
        this->printBoard(checked);

        if (znak > '0' && znak <= '8')
            moveInt = znak;

        if (znak >= 'a' && znak <= 'h')
            znak += 'A' - 'a';

        if (znak >= 'A' && znak <= 'H')
            moveChar = znak;

        cout << "Pozycja: " << moveChar << moveInt << endl;

        if (znak == 13) //NACIŚNIETO ENTER
        {
            if (moveInt > 0 && moveChar > 0)
            {
                pair<int, int> field(moveChar - 'A' + 1, moveInt - '1' + 1);
                checked.push_back(field);
                cout << "ENTER";
            }
        }
    } while (znak != 27); //ESC
}

Chess::~Chess()
{
    delete WhitePlayer;
    delete BlackPlayer;
}

Chess::Chess()
{
    for (int y = 0; y < boardHeight; y++)
        for (int x = 0; x < boardWidth; x++)
            board[y][x] = NULL;

    WhitePlayer = new Player(1, false);
    BlackPlayer = new Player(6, true);
    
    {//Ustawianie bialych
        auto begin = WhitePlayer->getFiguresBegin();
        auto end = WhitePlayer->getFiguresEnd();
        while (begin != end)
        {
            board[begin[0]->getPositionY()][begin[0]->getPositionX()] = begin[0];
            begin++;
        }
    }

    {//Ustawianie czarnych
        auto begin = BlackPlayer->getFiguresBegin();
        auto end = BlackPlayer->getFiguresEnd();
        while (begin != end)
        {
            board[begin[0]->getPositionY()][begin[0]->getPositionX()] = begin[0];
            begin++;
        }
    }
}

void Chess::printBoard(vector<pair<int, int>> checked)
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    auto printLine = [this]() { cout << "  ";
    for (int i = 0; i < boardWidth; i++)
        cout << " " << (char)(i + 'A') << " ";
    cout << endl; };

    printLine();

    for (int y = 0; y < boardHeight; y++)
    {
        cout << 8 - y << "|";
        for (int x = 0; x < boardWidth; x++)
        {
            auto printSetting = 0x0000;

            //Ustawienie koloru tła
            bool special = false;
            for (auto field : checked)
            {
                if (x + 1 == field.first && 8 - y == field.second)
                {
                    special = true;
                    printSetting |= BACKGROUND_RED;
                }
            }
            if( !special )
                if (!((x + y) % 2))
                    printSetting |= BACKGROUND_INTENSITY;
                else
                    printSetting |= BACKGROUND_GREEN;

            //Ustawienie koloru tekstu
            if(board[y][x])
            if (board[y][x]->getColor())
            {
                printSetting |= FOREGROUND_RED;
            }
            else
            {
                printSetting |= FOREGROUND_BLUE;
            }
            SetConsoleTextAttribute(hOut, printSetting);

            if (board[y][x])
            {
                cout << " ";
                board[y][x]->print();
                cout << " ";
            }
            else
            {
                cout << "   ";
            }
        }
        SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
        cout << "|" << 8 - y;
        cout << endl;
    }

    printLine();
}

int main()
{
    Chess* game = new Chess();

    while (1)
    {
        game->takeMove();
    }
}
