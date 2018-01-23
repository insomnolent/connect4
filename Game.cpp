// Game.cpp

#include "provided.h"

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black); 
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
};

// Construct a Game to be played with the indicated players on a scaffold of the indicated size.
// The red player always moves first. The goal of the game is for a player to get N of their checkers in a row.
GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
}

// If the game isn't over (i.e., more moves are possible),
// return false and do not change winner. Otherwise, set
// winner to RED, BLACK, or TIE_GAME, reflecting the outcome
// of the game, and return true.
bool GameImpl::completed(int& winner) const
{
    return true;  //  This is not always correct; it's just here to compile
}

//If the game is over, return false. Otherwise, make a move
// for the player whose turn it is (so that it becomes the
// other player's turn) and return true.
bool GameImpl::takeTurn()
{
    return false;  //  This is not always correct; it's just here to compile
}
// Play the game. Display the progress of the game in a manner of your choosing,
// provided that someone looking at the screen can follow what's happening.
// If neither player is interactive, then to keep the display from quickly
// scrolling through the whole game, it would be reasonable periodically to
// prompt the viewer to press ENTER to continue and not proceed until ENTER
// is pressed. (The ignore member function for input streams is useful here.)
// Announce the winner at the end of the game.
void GameImpl::play()
{
}
// In the Game's scaffold, if there is a red checker
// at the indicated column and level, return RED;
// if there's a black checker there, return BLACK;
// otherwise, return VACANT. This function exists so that we and you can more easily test your program; a real client would never use it.
int GameImpl::checkerAt(int c, int r) const
{
    return VACANT;  //  This is not always correct; it's just here to compile
} 

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

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
