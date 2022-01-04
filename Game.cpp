// Game.cpp

#include "provided.h"
#include <iostream>
using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    
private:
    int cols;
    int levels;
    int goal;
    Scaffold s;
    Player* current;
    Player* red_p;
    Player* black_p;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black): cols (nColumns), levels (nLevels),  goal (N), s (nColumns,nLevels), red_p (red), black_p (black)
{
    if (cols <=0 || levels <= 0 || goal <=0) //no point in creating a board with no columns levels or a negative goal
    {
        exit (0);
    }
  
    //get the red player to move first by setting it to be black (changes it once we're in taketurn function)
    current = black_p;
}

bool GameImpl::completed(int& winner) const
{
    //limit is to s.cols-goal-1 because we know that if we were to get connect goal, there's no point in starting to count at the very edge
    //this same logic applies to every single kind of check that we do
    
    int r_countcons, b_countcons, curr_l, curr_c;
    
    //*************************************************************************
    // *****************************horizontalCheck****************************
    //*************************************************************************
   
    // [ ] [R] [R]
    // [R] [R] [R] checking in  ->>>> this direction
    r_countcons = 0;
    b_countcons = 0;
    
    if (goal<=s.cols()) // goal can't be greater than the total amount of columns
    {
        for (int i = 1; i<=s.levels(); i++)
        {
            for (int j = 1; j<= s.cols()-goal+1; j++ )
            {
                //count how many of reds are in a row if we wncounter a red
                if (s.checkerAt (j, i) == RED)
                {
                    curr_c =j+1;
                    r_countcons = 1;

                    for (int x =1; x<goal; x++)
                    {
                        if (s.checkerAt(curr_c, i) != RED) //if its not in a row
                            break;

                        r_countcons++;
                        curr_c++; //increment so we know that we're checking consecutively
                    }
                }
                
                if (r_countcons==goal)
                {
                    winner = RED;
                    return true;
                }
                
                //count how many of blacks are in a row
                if (s.checkerAt (j, i) == BLACK)
                {
                    b_countcons = 1;
                    curr_c = j+1; //reset it to count the number of black in a row

                    for (int x =1; x<goal; x++)
                    {
                        if (s.checkerAt(curr_c, i)  != BLACK)
                        {
                            break;
                        }
                        b_countcons++;
                        curr_c++;
                    }
                }

                if (b_countcons == goal)
                {
                    winner = BLACK;
                    return true;
                }
                
            }
        }
    }

    //*************************************************************************
    // *******************************verticalCheck***************************
    //*************************************************************************

    // [R]
    // [R]
    // [R]
    // [R]
    
    //start both counters at 1 because s.checker at takes in the  NUMBER and not the iNDEX
    
    if (goal<=s.levels()) // goal can't be greater than the total amount of levels
    {
        for (int i = 1; i<=s.cols(); i++)
        {
            for (int j = 1; j<= s.levels()-goal+1; j++ )
            {
                
                //count how many of reds are in a column (column stays the same but levels increment)
                if (s.checkerAt (i, j) == RED)
                {
                    r_countcons = 1;
                    curr_l =j+1;
                    for (int x =1; x<goal; x++)
                    {
                        if (s.checkerAt(i, curr_l) != RED)
                            break;
                        
                        r_countcons++;
                        curr_l++; //increment so we know that we're checking consecutively
                    }
                }
                
                if (r_countcons==goal)
                {
                    winner = RED;
                    return true;
                }
                
                if (s.checkerAt (i,j) == BLACK) //count how many of blacks are in a column
                {
                    b_countcons = 1;
                    curr_l = j+1; //reset it
                    for (int x =1; x<goal; x++)
                    {
                        if (s.checkerAt(i, curr_l) != BLACK)
                            break;
                        
                        b_countcons++;
                        curr_l++;
                    }
                    
                }
                
                if (b_countcons == goal)
                {
                    winner = BLACK;
                    return true;
                }
                
            }
        }
    }
    
    //*************************************************************************
    // ***********************ascendingdiagonalCheck***************************
    //*************************************************************************
    
    /*
     [ ][ ][x][ ]
     [ ][x][ ][ ]
     [x][ ][ ][ ]
    */
    
    if (goal <= s.levels() && goal <= s.cols())
    {
        for (int i=1; i<=s.levels(); i++)
        {
            for (int j = 1; j<= s.cols()-goal+1; j++ )
            {
                //count how many of reds are in an ascending diagnoal
                if (s.checkerAt (j,i) == RED)
                {
                    r_countcons = 1;
                    curr_l=i+1;
                    curr_c = j+1;
                    
                    for (int x =1; x<goal; x++)
                    {
                        if (s.checkerAt(curr_c, curr_l) != RED)
                        {
                            break;
                        }
                        r_countcons++;
                        curr_c++;
                        curr_l++; //increment so we know that we're checking consecutively
                    }
                    
                }
               
                if (r_countcons==goal)
                {
                    winner = RED;
                    return true;
                }
                
                if (s.checkerAt (j,i) == BLACK)
                {
                     b_countcons = 1;
                    curr_l=i+1;
                    curr_c = j+1;
                    
                    for (int x =1; x<goal; x++)
                    {
                        if (s.checkerAt(curr_c, curr_l)  != BLACK)
                        {
                            break;
                        }
                        b_countcons++;
                        curr_c++;
                        curr_l++; //increment so we know that we're checking consecutively
                    }
                }
                
                
                if (b_countcons == goal)
                {
                    winner = BLACK;
                    return true;
                }
                
            }
        }
    }

    //*************************************************************************
    // ***********************descendingdiagonalCheck***************************
    //*************************************************************************
    
    /*
     [x][ ][ ][ ]
     [ ][x][ ][ ]
     [ ][ ][x][ ]
     -------^------ start and go from right to left
     */
    
    if (goal <= s.levels() && goal <= s.cols())
    {
        for (int i=1; i<=s.levels(); i++)
        {
            for (int j = goal; j<= s.cols(); j++ ) //we can't start at the first column since its physically impossible to get a connect N there
            {
                r_countcons = 0;
                b_countcons = 0;
                curr_l=i;
                curr_c = j;
                
                //count how many of reds are in an descending diagnoal
                for (int x =0; x<goal; x++)
                {
                    if (s.checkerAt(curr_c, curr_l) != RED)
                    {
                        break;
                    }
                    r_countcons++;
                    curr_c--;
                    curr_l++; //increment so we know that we're checking consecutively
                }
                
                curr_l=i;
                curr_c = j;
                
                //count how many of blacks are in a descending diagonal
                for (int x =0; x<goal; x++)
                {
                    if (s.checkerAt(curr_c, curr_l)  != BLACK)
                    {
                        break;
                    }
                    b_countcons++;
                    curr_c--;
                    curr_l++; //increment so we know that we're checking consecutively
                }
                
                if (b_countcons == goal)
                {
                    
                    winner = BLACK;
                    return true;
                }
                
                else if (r_countcons==goal)
                {
                    winner = RED;
                    return true;
                }
            }
        }
    }
    
    if (s.numberEmpty () == 0) //tied game: no more places to go
    {
       // cerr << "there's no more spots to go";
        winner = TIE_GAME;
        return true;
    }
    
    return false;
}

bool GameImpl::takeTurn()
{
    int hold;
   //check if game over
    if (completed (hold)) //send a random number in to check if its true
    {
        return false;
    }

    else
    {
        //make a move for the player whose turn it is so it beceoms the other players turn
        if (current == black_p)
        {
            current = red_p;
            hold = current->chooseMove (s, goal, RED);
            s.makeMove (hold, RED);
            return true;

        }
        
        if (current == red_p)
        {
            current = black_p; //change the players
            hold = current->chooseMove (s,goal,BLACK);
            s.makeMove (hold, BLACK);
            return true;

        }
    }
    
    return false;
}

void GameImpl::play()
{
    bool game = true;     //taketurn returns false if the game is over
    int winner;

    cout << "Red will start. Please press ENTER to confirm you agree.";
    cin.ignore(100000, '\n');

    while (game) //keep taking turns while game isn't over
    {
        s.display(); //display the move
        cerr << endl;
        
        game = takeTurn(); //switches color and makes the move
        if (game) //if its true
        {
            if (!(red_p->isInteractive()||black_p->isInteractive())) //if neither player is interactive
            {
                cout << "Press ENTER to play" << endl;
                cin.ignore(100000, '\n');
            }
        }
        
        else
            break;
    }
    
    //now that it's over, find the winner
    completed (winner);
    
    if (winner == RED)
    {
        cout << "Congratulations Red!" <<endl;
    }
    
    else if (winner == BLACK)
    {
        cout <<"Congratulations Black!"<<endl;
    }
    
    else
    {
        cout << "Tied Game!"<<endl;
    }
    
}

int GameImpl::checkerAt(int c, int r) const
{
    if (c <= 0 || r <= 0) //column and level all need to be minimum 1
    {
        return VACANT;
    }
    
    else if (c <= s.cols() && r <= s.levels())
    {
        //subtract 1 to get to the index
        if (s.checkerAt (c,r) == RED)
            return RED;
        
        else if (s.checkerAt (c,r) == BLACK)
            return BLACK;
        
        else
            return VACANT;
    }
    
    else
    {
        return VACANT;
    }
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}

Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}

int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}

/*
 red = red_p->chooseMove (s, goal, RED);
 s.makeMove (red, RED);
 s.display();
 
 test = completed (winner);
 
 if (test) //do a check after red to make sure that we aren't checking after each round but each turn
 {
 break;
 }
 
 black = black_p->chooseMove (s,goal,BLACK);
 s.makeMove (black, BLACK);
 s.display();
 */
