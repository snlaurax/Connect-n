// Scaffold.cpp

#include "provided.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();

private:
    int totalcols;
    int totallevels;
    stack <int> moves;
    vector<vector<char>> grid; //create a vector
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    //end the program if the numbers are negative
    if (nColumns <= 0 || nLevels <= 0 )
    {
        cerr << "These numbers do not work. End program. " << endl;
        exit (1);
    }
    
    //create a scaffold with that size
    else
    {
        totalcols = nColumns;
        totallevels = nLevels;
        
        grid.resize(totallevels); //resize it to have that many rows
        
        for (int i = 0; i < totallevels; i++)
            grid[i].resize(totalcols);

        //now we have to fill the columns
        for (int x = 0; x< totallevels; x++)
        {
            for (int i = 0; i < totalcols; i++)
            {
                grid [x][i] = ' ';
            }
        }
        
    }
}

int ScaffoldImpl::cols() const
{
    return totalcols;
}

int ScaffoldImpl::levels() const
{
    return totallevels;
}

int ScaffoldImpl::numberEmpty() const
{
    //run a for loop through the scaffold to find the number of ' '
    int total = 0;
    for (int i = 0; i<totallevels ; i++)
    {
        for (int x = 0; x <totalcols ; x++)
        {
            if (grid [i][x] == ' ')
            {
                total++;
            }
        }
        
    }
    return total;
}

int ScaffoldImpl::checkerAt(int column, int level) const //column and level NOT THE INDEX
{
    if (column <= 0 || level <= 0) //column and level all need to be minimum 1 
    {
        return VACANT;
    }
    
   else if (column <= totalcols && level <= totallevels)
    {
        //subtract 1 to get to the index
        if (grid [level-1][column-1] == 'R')
            return RED;
        
        else if (grid [level-1][column-1] == 'B')
            return BLACK;
        
        else
            return VACANT;
    }
    
    else
    {
        return VACANT;
    }

}


void ScaffoldImpl::display() const
{
    int cols;
    char hold;
    
    for (int i = totallevels-1; i >= 0; i--)
    {
        cols = 0;
        
        for (int x = 0; x <(totalcols*2+1); x++)
        {
                if (x%2 ==0)
                    cout << '|';
                
                else
                {
                    hold = grid [i][cols];
                    cout << hold;
                    cols = cols+1;
                }
        }
        cout << endl;
    }
    
    //safe guards
    
    for (int x = 0; x <(totalcols*2+1); x++)
    {
        if (x%2 ==0)
            cout << '+';
        
        else
            cout << '-';
    }
    
    cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    //find the row number that it can go
    int go = -1;

    if (column <= 0 || column > totalcols)
    {
   //     cerr << "wrong column"<<endl;
        return false;
    }
    
    if (color != RED && color != BLACK)
    {
     //   cerr << "wrong color" <<endl;
        return false; 
    }
    
    for (int i = 0; i < totallevels; i++)
    {
        if (grid [i][column-1] == ' ')
        {
            go = i; //this marks the spot of where the piece would land
            break;
        }
    }
    
    if (go ==-1) //all the columns are full
    {
      //  cerr << "beyond" << endl;
        return false;
    }
    

    moves.push (column-1); //push the index of the column
    
    if (color == 0)
    {
        grid [go][column-1] = 'R';
        return true;
    }
   
    else
    {
        grid [go][column-1] = 'B';
        return true;
    }

    return false;
}

int ScaffoldImpl::undoMove()
{
    //find the row number that it can go
    int go = -1;
    int lastcol = 0;
    
    if (moves.empty ()) //if the stack is empty
    {
        return false;
    }
    
    lastcol= moves.top (); //don't need to subtract one because moves is storing the index of the columns
    
    for (int i = 0; i < totallevels; i++)
    {
        if (grid [i][lastcol] == ' ')
        {
            go = i; //this marks the row of where the piece would land in the column if we added another one
            //so we know we have to delete the one underneath to undo the move
            
            grid [go-1][lastcol] = ' ';
            moves.pop (); //pop off the stack to get rid of that move
            break;
        }
    }
    
    if (go == -1) // this means that all the columns are filled
    {
        grid [totallevels-1][lastcol] = ' '; //change the top one
        moves.pop (); //pop off the stack to get rid of that move
    }
    
    return lastcol+1; //have to add one to adjust that their first column is actually index 0 

}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}

Scaffold::~Scaffold()
{
    delete m_impl;
}


Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}

Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}

int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}

void Scaffold::display() const
{
    m_impl->display();
}

bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}

int Scaffold::undoMove()
{
    return m_impl->undoMove();
}


