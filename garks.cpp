//
//  main.cpp
//  proj7
//
//  Created by Margaret Capetz on 11/23/21.
//

// garks.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Mesa::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the mesa
const int MAXCOLS = 25;             // max number of columns in the mesa
const int MAXGARKS = 150;           // max number of garks allowed
const int INITIAL_GARK_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Mesa;  // This is needed to let the compiler know that Mesa is a
             // type name, since it's mentioned in the Gark declaration.

class Gark
{
  public:
        // Constructor
    Gark(Mesa* mp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool getAttacked(int dir);

  private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_health;
};

class Player
{
  public:
        // Constructor
    Player(Mesa *mp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

        // Mutators
    void   stand();
    void   moveOrAttack(int dir);
    void   setDead();

  private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

class Mesa
{
  public:
        // Constructor/destructor
    Mesa(int nRows, int nCols);
    ~Mesa();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     garkCount() const;
    int     numGarksAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

        // Mutators
    bool   addGark(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackGarkAt(int r, int c, int dir);
    bool   moveGarks();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Gark*   m_garks[MAXGARKS];
    int     m_nGarks;
};

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

        // Mutators
    void play();

  private:
    Mesa* m_mesa;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Gark implementation
///////////////////////////////////////////////////////////////////////////

Gark::Gark(Mesa* mp, int r, int c)
{
    if (mp == nullptr)
    {
        cout << "***** A gark must be created in some Mesa!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > mp->rows()  ||  c < 1  ||  c > mp->cols())
    {
        cout << "***** Gark created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_mesa = mp;
    m_row = r;
    m_col = c;
    m_health = INITIAL_GARK_HEALTH;
}

int Gark::row() const
{
    return 0;
}

int Gark::col() const
{
    return 0;
}

void Gark::move()
{
      // Attempt to move in a random direction; if it can't move, don't move
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
    
    
    //MAYBE THIS IS WRONG AND YOU NEED TO USE THE MESA FUNCTION
    //check if gark is going to fall off the mesa
    if((this->row() == 1 && dir == 0) || (this->row() == m_mesa->rows() && dir == 1) || (this->col() == 1 && dir == 2) || (this->col() == m_mesa->cols() && dir == 3)) {
        return;
    }
    
    //move the gark
    else {
        switch(dir) {
            case 0:
                m_col++;
                break;
            case 1:
                m_col--;
                break;
            case 2:
                m_row--;
                break;
            case 3:
                m_row++;
                break;
        }
    }
    
}

bool Gark::getAttacked(int dir)  // return true if dies
{

    if(m_health == INITIAL_GARK_HEALTH) {
        //gark has not been attacked before
        m_health--; //m_health is now 1
        
        //check if gark is going to fall off the mesa
        if((m_row == 1 && dir == 0) || (m_row == m_mesa->rows() && dir == 1) || (m_col == 1 && dir == 2) || (m_col == m_mesa->cols() && dir == 3)) {
            return true;
        }
        
        //move the gark
        switch(dir) {
            case 0:
                m_col++;
                break;
            case 1:
                m_col--;
                break;
            case 2:
                m_row--;
                break;
            case 3:
                m_row++;
                break;
        }
        return false;
    }
    else {
        //gark has been attacked before
        m_health--; //m_health is now 0
        return true;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Mesa* mp, int r, int c)
{
    if (mp == nullptr)
    {
        cout << "***** The player must be created in some Mesa!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > mp->rows()  ||  c < 1  ||  c > mp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_mesa = mp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::moveOrAttack(int dir)
{
    m_age++;
    
    //if gark is adjacent, attack it
    switch (dir)
    {
      case UP:
            if(!(m_mesa->attackGarkAt(m_row - 1, m_col, dir))) {
                //no gark at pos or gark didn't die
                if(m_row != 1 && m_mesa->numGarksAt(m_row - 1, m_col) == 0) {
                    //no gark at pos
                    m_row--;
                }
            }
            break;
      case DOWN:
            if(!(m_mesa->attackGarkAt(m_row + 1, m_col, dir))) {
                //no gark at pos or gark didn't die
                if(m_row != m_mesa->rows() && m_mesa->numGarksAt(m_row + 1, m_col) == 0) {
                    //no gark at pos
                    m_row++;
                }
            }
            break;
      case LEFT:
            if(!(m_mesa->attackGarkAt(m_row, m_col - 1, dir))) {
                //no gark at pos or gark didn't die
                if(m_col != 1 && m_mesa->numGarksAt(m_row, m_col - 1) == 0) {
                    //no gark at pos
                    m_col--;
                }
            }
            break;
      case RIGHT:
            if(!(m_mesa->attackGarkAt(m_row, m_col + 1, dir))) {
                //no gark at pos or gark didn't die
                if(m_col != m_mesa->cols() && m_mesa->numGarksAt(m_row, m_col + 1) == 0) {
                    //no gark at pos
                    m_col++;
                }
            }
            break;
            
    }
    
        // If there is a gark adjacent to the player in the direction
      // dir, attack it.  Otherwise, move the player to that position if
      // possible (i.e., if the move would not be off the edge of the mesa).
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Mesa implementations
///////////////////////////////////////////////////////////////////////////

Mesa::Mesa(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Mesa created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nGarks = 0;

}

Mesa::~Mesa()
{
    delete m_player;
    for(int i = 0; i < m_nGarks; i++) {
        delete m_garks[i];
    }
}

int Mesa::rows() const
{
    return m_rows;
}

int Mesa::cols() const
{
    return m_cols;
}

Player* Mesa::player() const
{
    return m_player;
}

int Mesa::garkCount() const
{
    return m_nGarks;
}

int Mesa::numGarksAt(int r, int c) const
{
    int count = 0;
    
    for(int i = 0; i < m_nGarks; i++) {
        if(m_garks[i]->row() == r && m_garks[i]->col() == c) {
            count++;
        }
    }
    return count;
}

bool Mesa::determineNewPosition(int& r, int& c, int dir) const
{
      // If a move from row r, column c, one step in direction dir
      // would go off the edge of the mesa, leave r and c unchanged and
      // return false.  Otherwise, set r or c so that row r, column c, is
      // now the new position resulting from the proposed move, and
      // return true.
    
    switch (dir)
    {
      case UP:
            if(r == 1) {
                return false;
            }
            else {
                r--;
            }
            break;
      case DOWN:
            if(r == this->rows()) {
                return false;
            }
            else {
                r++;
            }
            break;
      case LEFT:
            if(c == 1) {
                return false;
            }
            else {
                c--;
            }
            break;
      case RIGHT:
            if(c == this->cols()) {
                return false;
            }
            else {
                c++;
            }
            break;
      default:
        return false;
    }
    return true;
}

void Mesa::display() const
{
      // Position (row,col) in the mesa coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each gark's position
    for (r = 0; r < rows(); r++) {
        for (c = 0; c < cols(); c++) {
            if(numGarksAt(r,c) == 1) {
                grid[r][c] = 'G';
            }
            else if(numGarksAt(r,c) >= 2 && numGarksAt(r,c) <=8) {
                int n = numGarksAt(r,c);
                switch(n) {
                    case 2:
                        grid[r][c] = '2';
                        break;
                    case 3:
                        grid[r][c] = '3';
                        break;
                    case 4:
                        grid[r][c] = '4';
                        break;
                    case 5:
                        grid[r][c] = '5';
                        break;
                    case 6:
                        grid[r][c] = '6';
                        break;
                    case 7:
                        grid[r][c] = '7';
                        break;
                    case 8:
                        grid[r][c] = '8';
                        break;
                }
            }
            else if(numGarksAt(r,c) >= 9) {
                grid[r][c] = '9';
            }
        }
    }

        // Indicate player's position
    if (m_player != nullptr)
    {
          // Set the char to '@', unless there's also a gark there,
          // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, gark, and player info
    cout << endl;
    cout << "There are " << garkCount() << " garks remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Mesa::addGark(int r, int c)
{
      // If there are MAXGARKS garks, return false.  Otherwise,
      // dynamically allocate a new Gark at coordinates (r,c).  Save the
      // pointer to the newly allocated Gark and return true.

      // Your function must work as specified in the preceding paragraph even
      // in this scenario (which won't occur in this game):  MAXGARKS
      // are added, then some are destroyed, then more are added.
    
    if(m_nGarks == MAXGARKS) {
        return false;
    }
    else {
        m_nGarks++;
        m_garks[m_nGarks] = new Gark(this, r, c);
        return true;
    }

}

bool Mesa::addPlayer(int r, int c)
{
      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Dynamically allocate a new Player and add it to the mesa
    m_player = new Player(this, r, c);
    return true;
}

bool Mesa::attackGarkAt(int r, int c, int dir)
{
      // Attack one gark at row r, column c if at least one is at
      // that position.  If the gark does not survive the attack, destroy the
      // gark object, removing it from the mesa, and return true.  Otherwise,
      // return false (no gark at (r,c), or gark didn't die).
    
    for(int i = 0; i < m_nGarks; i++) {
        if(m_garks[i]->row() == r && m_garks[i]->col() == c) {
            if(m_garks[i]->getAttacked(dir)) {
                //gark died
                delete m_garks[i];
                return true;
            }
            else {
                return false; //gark didn't die
            }
        }
    }
    return false; //no gark at (r,c)
    
}

bool Mesa::moveGarks()
{
    for (int k = 0; k < m_nGarks; k++)
    {
      // Have the k-th gark on the mesa make one move.
      //        If that move results in that gark being in the same
      //        position as the player, the player dies.
        m_garks[k]->move();
        if(m_garks[k]->row() == m_player->row() && m_garks[k]->col() == m_player->col()) {
            m_player->setDead(); //player dies
        }
    }

      // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nGarks)
{
    if (nGarks < 0)
    {
        cout << "***** Cannot create Game with negative number of garks!" << endl;
        exit(1);
    }
    if (nGarks > MAXGARKS)
    {
        cout << "***** Trying to create Game with " << nGarks
             << " garks; only " << MAXGARKS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nGarks > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the garks!" << endl;
        exit(1);
    }

        // Create mesa
    m_mesa = new Mesa(rows, cols);

        // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_mesa->addPlayer(rPlayer, cPlayer);

      // Populate with garks
    while (nGarks > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
          // Don't put a gark where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_mesa->addGark(r, c);
        nGarks--;
    }
}

Game::~Game()
{
    delete m_mesa;
}

void Game::play()
{
    m_mesa->display();
    Player* player = m_mesa->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_mesa->garkCount() > 0)
    {
        cout << endl;
        cout << "Move (u/d/l/r/q or nothing): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player stands
            player->stand();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                player->moveOrAttack(decodeDirection(action[0]));
                break;
            }
        }
        m_mesa->moveGarks();
        m_mesa->display();
    }
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

  // Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

