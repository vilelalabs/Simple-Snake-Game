#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;


bool gameOver;
const int width = 20;                               // game table size W
const int height = 20;                              // game table size H
int x,y, fruitX, fruitY, score;                     // positions
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN}; // direction
eDirection dir;



void Setup()
{
    gameOver = false;
    dir = STOP;                 //start stopped
    x = width/2;                //start in the middle of screen
    y = height/2;               //start in the middle of screen
    fruitX = rand () % width;
    fruitY = rand () % height;
    score  = 0;
}
void Draw()
{
    system("cls");              // clear the screen

    // ---------- drawning wall ------------
    for( int i = 0;i< width+2; i++)
        cout << "#";
    cout << endl;


    for( int i = 0;i< height; i++)
    {
        for( int j = 0;j< width; j++)
        {
            if (j==0)
                cout << "#";
            if(i == y && j == x)
                cout << "O"; //drawnin snake's head

            else if (i == fruitY && j == fruitX)
                cout << "F"; // drawning fruit
            else
            {
                bool print = false;
                for(int k=0;k< nTail;k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        print = true;
                        cout << "o";
                    }
                }
                if(!print)
                    cout << " ";
            }
            /*else
                cout << " ";*/


            if (j==width-1)
                cout << "#";


        }
        cout << endl;
    }
    for( int i = 0;i< width+2; i++)
        cout << "#";
    cout << endl;
   // ---------- end drawning wall ------------

   cout << "Score: " << score << endl;

}
void Input()
{
    if(kbhit())
    {
        switch(getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }

}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i =1; i<nTail;i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
        case LEFT:
            x--;

            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    /*if(x > width || x< 0 || y > height || y< 0)
        gameOver = true;*/
    for(int i=0;i<nTail;i++)
    {
        if(tailX[i]==x && tailY[i]==y)
            gameOver = true;
    }

    if(x == fruitX && y == fruitY)
    {
        score+=10;
        fruitX = rand () % width;
        fruitY = rand () % height;
        nTail++;
    }
    
    if(x<0) x=width;
    else if(x>width) x=0;
    if(y<0) y=height;
    else if(y>height) y=0;
}


///////////////////////////////////////////////////////////////////////////////

int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        // Sleep(10); - slow the game for good view
    }


    return 0;
}

