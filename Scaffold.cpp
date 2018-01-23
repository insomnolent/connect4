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
    int nCols = 0;
    int nRows = 0;
    // int actualSize = 0;
    vector<vector<char>> grid;

    struct Coord {
        int row;
        int col;
    };
    stack<Coord> moves;
    // include a stack of move actions

};

// Construct a Scaffold with the indicated number of columns and levels.
// If either is not positive, you may terminate the program after writing a message to cerr.
ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns < 1 || nLevels < 1) {
        cerr << "Error: columns and/or levels must be non-negative." << endl;
        exit(1);
    }
    nCols = nColumns;
    nRows = nLevels;
    int actualSize = 2*nColumns+1; // to account for dividers between cols - should it be a private var??
    grid.resize(nLevels+1);  // grid now has nLevels empty rows plus bottom row
    for (int i = 0; i < nRows+1; i++) {
        // if it's the first bottom row, initialize with + and - chars
        if (i == 0) {
                grid[i].resize(actualSize);
            for (int j = 0; j < actualSize; j++) {
                if (j % 2 == 0) {
                    grid[i][j] = '+';
                }
                else {
                    grid[i][j] = '-';
                }
            }
        }
            // for other rows, add dividers between cols
        else {
            grid[i].resize(actualSize);
            for (int j = 0; j < actualSize; j++) {
                if (j%2 == 0)
                    grid[i][j] = '|';
                else
                    grid[i][j] = ' ';
            }
            // int col = 0;
            // iterate through each row and insert dividers
            // iter = grid[i].begin();
//        while (iter != grid[i].end()){
//            grid[i].insert(iter,'|');
//            iter+=2;
//        }
        }
    }
}

// Return the number of columns in the scaffold.
int ScaffoldImpl::cols() const
{
    return nCols;
}
//Return the number of levels in the scaffold.
int ScaffoldImpl::levels() const
{
    return nRows;
}
//Return the number of positions in the scaffold not occupied by a checker.
int ScaffoldImpl::numberEmpty() const
{
    // or is it better to have a private member that keeps track of the num empty?
    int num = 0;
    for (int i = 0; i < nRows+1; i++)
        for (int j = 0; j < 2*nCols+1; j++)
            if (grid[i][j] == ' ')
               num++;

    return num;  //  This is not always correct; it's just here to compile
}
// If there is a red checker at the indicated column and level, return RED;
// if there's a black checker there, return BLACK; otherwise, return VACANT.
int ScaffoldImpl::checkerAt(int column, int level) const {
    // if (column > cols() || level > levels())
    if (grid[column][level] == 'R')
        return RED;
    if (grid[column][level] == 'B')
        return VACANT;
    return 1; // is this needed to catch exceptions?
}

//Display the scaffold to the screen in the following manner:
//Display the levels of the scaffold from highest to lowest.
//Display each red checker as an R.
//Display each black checker as a B.
//Display each vacant cell as a space character.
//Display a - (hyphen) character below level 1 of each column.
//Display the side of each column as a | character.
//Display the joints between the bottom of the column and the sides of the columns as + characters.
//Below is an example of the output where the scaffold has 4 columns and three rows:
//| | | | |
//| |R| | |
//|R|B|B|R|
//+-+-+-+-+
void ScaffoldImpl::display() const
{
    // iterate through each row
    for(int i = nRows; i >= 0; i--) {
        for (int j = 0; j < 2*nCols+1; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

//If the first parameter is a valid column number with at least one vacant position in that column,
// and if color is RED or BLACK, drop a checker of the appropriate color into that column and return true.
// Otherwise, do nothing and return false.
bool ScaffoldImpl::makeMove(int column, int color)
{
    char checker;
    if (color == RED)
        checker = 'R';
    else if (color == BLACK)
        checker = 'B';
    else
        return false;
    if (column > 0 && column <= cols()) {
        // checks for empty entries in that column
        for (int i = 1; i < nRows + 1; i++) {
            if (grid[i][2*column-1] == ' ') {
                grid[i][2*column-1] = checker;
                Coord action;
                action.row = i;
                action.col = 2*column-1;
                moves.push(action);
                return true;
            }
        }
        // if no empty slots ??
    }
    return false;  //  This is not always correct; it's just here to compile
}

//Undo the most recently made move that has not already been undone
// (i.e., remove the checker in the scaffold that was most recently added),
// and return the number of the column from which that checker was removed.
// If there are no checkers in the scaffold, do nothing and return 0.
int ScaffoldImpl::undoMove()
{
    // if no checkers in scaffold
    if (numberEmpty() == cols()*levels())
        return 0;
    Coord lastMove = moves.top();
    int lastRow = lastMove.row;
    int lastCol = lastMove.col;
    grid[lastRow][lastCol] = ' ';
    moves.pop();
    return 0;  //  This is not always correct; it's just here to compile
}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

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
