#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>

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
    Figure(int, int);
    int getPositionX() { return positionX; };
    int getPositionY() { return positionY; };

private:
    int positionX;
    int positionY;
};

Figure::Figure(int x, int y)
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
    Pawn(int x, int y) : Figure(x, y) {};

private:

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
    King(int x, int y) : Figure(x, y) {};

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
    Rock(int x, int y) : Figure(x, y) {};

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
    Bishop(int x, int y) : Figure(x, y) {};

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
    Queen(int x, int y) : Figure(x, y) {};

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
    Knight(int x, int y) : Figure(x, y) {};

private:

};
void Knight::move()
{

}
void Knight::print()
{
    cout << "J";
}

class Player
{
public:
    Player(int);
    ~Player();
    auto getFiguresBegin();
    auto getFiguresEnd();

private:
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

Player::Player(int positionHeight)
{
    Pawn* figure;
    for (int i = 0; i < 8; i++)
    {
        figure = new Pawn(i, positionHeight);
        figures.push_back(figure);
    }
    if (positionHeight == 1)
        positionHeight--;
    else
        positionHeight++;
    
    Queen* queen;
    queen = new Queen(4, positionHeight);
    figures.push_back(queen);

    King* king;
    king = new King(3, positionHeight);
    figures.push_back(king);

    Rock* rock;
    rock = new Rock(0, positionHeight);
    figures.push_back(rock);
    rock = new Rock(7, positionHeight);
    figures.push_back(rock);

    Knight* knight;
    knight = new Knight(1, positionHeight);
    figures.push_back(knight);
    knight = new Knight(6, positionHeight);
    figures.push_back(knight);

    Bishop* bishop;
    bishop = new Bishop(2, positionHeight);
    figures.push_back(bishop);
    bishop = new Bishop(5, positionHeight);
    figures.push_back(bishop);
}

Player::~Player()
{

}

class Chess
{
public:
    void printBoard();
    Chess();
    ~Chess();

private:
    Player* WhitePlayer;
    Player* BlackPlayer;
    Figure* board[8][8];
    const int boardWidth = 8;
    const int boardHeight = 8;
};

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

    WhitePlayer = new Player(1);
    BlackPlayer = new Player(6);
    
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

void Chess::printBoard()
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
            if ( !((x + y) % 2) )
                SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY);
            else
                SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);

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
    game->printBoard();
}
