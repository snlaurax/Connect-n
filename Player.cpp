//
//  Player.cpp
//  Project3
//
//  Created by Laura Lu on 2021-05-12.
//  Copyright © 2021 Laura Lu. All rights reserved.
//
// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;
int minimax (const Scaffold& s, int depth, bool isMaximizing, AlarmClock& a);
bool gameover(int& winner, Scaffold s, int goal);

class HumanPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
private:
    int alarmhelper (AlarmClock& ac);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int number;
    do
    {
        cout << "Enter a positive number: " << endl;
        cin >> number;
    }
    while (number <= 0 || number > s.cols () || s.checkerAt (number, s.levels()) != VACANT); //if the column is full it needs to be somewhere else
    
    return number;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    for (int i =1; i<= s.levels(); i++)
    {
        for (int x = 1; x<= s.cols(); x++) //START AT 1 TO GET THE NUMBER not the index
        {
            //put it in the first vacant spot and make sure that the top row is also empty (this allows us to place it in the top row without going over since both will return VACANT

            if (s.checkerAt (x,i) == VACANT && s.checkerAt (x, s.levels()) ==VACANT)
            {
                return x; //returning column number
            }
        }
    }
    return 0;
}

bool gameover(int& winner, Scaffold s, int goal) //checks whether the game is over
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
                
                //count how many of blacks are in a row
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

//find the scores for each of the potential moves
int minimax (Scaffold& a, int depth, bool isMaximizing, int goal, int color, AlarmClock &ac)
{
    int winner, opp_color = -1;
    int bestScore = 0;
    int bignumber = a.levels()*a.cols ();

    bool result = gameover (winner, a, goal); //check whether the game is over
    
    if (color == RED)
        opp_color = BLACK;
    
    if (color == BLACK)
        opp_color = RED;
    
    if (result) //if the game is over
    {
        if (winner == TIE_GAME)
            return 0;
        
        else if ((isMaximizing && color == winner) || (!isMaximizing && opp_color == winner))
            return bignumber - depth; //when maximizing, we want to choose the biggest number ex. 9997 (depth 3) vs 9996 (depth 4) -> we favor the win at the earlier depth
        
        else if ((!isMaximizing && color == winner) || (isMaximizing && opp_color == winner)) //human win: wants to minimize
        {
            bignumber = -bignumber;
            return bignumber + depth; //when minimizing, we want to choose the smallest number ex. -9997 (winning with depth 3) vs -9996 (depth 4) -> favoring the depth at the earlier one
        }
    }
    
    //maximizing
    if (isMaximizing) //it's the computers turn
    {
        bestScore = -a.levels()*a.cols(); //-s.levels() * s.cols() -1;
        
        for (int i = 1; i<=a.cols(); i++)
        {
                //check if the spot is available
                if (a.checkerAt (i, a.levels()) == VACANT)
                {
                    a.makeMove (i, color); //try going there and placing something
                    
                    if (ac.timedOut())
                    {
                        return bestScore;
                    }
                    int score = minimax (a, depth+1, false, goal, opp_color, ac); //, ac
                    a.undoMove(); //undo it so it won't be changed
                    
                    if (score > bestScore)
                        bestScore = score;
                }
        }
        return bestScore;
    }
    
    else //minimizing player
    {
        bestScore = a.levels()*a.cols();
        
        for (int i = 1; i<=a.cols(); i++)
        {
            //check if the spot is available
            if (a.checkerAt (i, a.levels()) == VACANT)
            {
                a.makeMove (i, color); //try going there and placing something

                if (ac.timedOut())
                {
                    return bestScore;
                }
                
                int score = minimax (a, depth+1, true, goal, opp_color, ac); //, ac
                a.undoMove(); //undo it so it won't be changed
                
                if (score < bestScore)
                    bestScore = score;
            }
         }
        return bestScore;
    }
    return -1;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    AlarmClock ac(9900);
    Scaffold a = s;
    int score = -1;
    int bestScore = -a.levels()*a.cols ();
    int bestMove = 0;
    int opp_color;
    
    if (color == RED)
    {
        opp_color = BLACK;
    }
    
    else
    {
        opp_color = RED;
    }
    
    for (int i = 1; i<=s.cols(); i++)
    {
        if (s.checkerAt (i, s.levels())== VACANT) //if i can go in this column
        {
            a.makeMove (i, color);
            score = minimax (a, 0, false, N, opp_color, ac); //call the minimax algorithm , ac
            a.undoMove ();
         //   cerr << "column" << i <<  "score: " << score << endl;
            if (score > bestScore) //compare the scores between the diff columns
            {
                bestScore = score;
                bestMove = i;
              //  cerr << "bestScore " << bestScore << endl;
            }
        }
    }
//    cerr<< "best move" << bestMove<<endl;
    return bestMove;
}

//moveonto another column since we don't want to check all the empty spots since this game is gravity based
// [don't check this one]
// [ ]
// [just check this one]



//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
: Player(nm)
{
    m_impl = new HumanPlayerImpl;
}

HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
: Player(nm)
{
    m_impl = new BadPlayerImpl;
}

BadPlayer::~BadPlayer()
{
    delete m_impl;
}

int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
: Player(nm)
{
    m_impl = new SmartPlayerImpl;
}

SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
