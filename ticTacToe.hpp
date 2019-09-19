//TicTacToe.hpp
#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP


#include <vector>
// Note: Avoid the namespace-scope using statement in header files



// Global constants used or provided by the functions declared below
const char EMPTY_CELL = '*',     // Connotes a space in the game board is empty and can be claimed by either player
           NO_WINNER  = '\0';    // Returned by isaWinner indicating neither play has yet won the game






// Type alias defining the underlying game board type.  GameBoardType
// must be defined as an NxN matrix
using GameBoardType = std::vector<std::vector<char>>;






/*******************************************************************************
** Displays the game board to standard output.  Each game board cell is
** displayed in a field of spaces with the X, O or * in the center space
** separated with a separator character.
*******************************************************************************/
void displayBoard( const GameBoardType & gameBoard );



/*******************************************************************************
** Displays whose turn it is, prompts the player for their move, validates the
** player's response, and re-prompts if necessary.  The game board is updated
** with the player's X or O inserted into the selected location. This function
** remembers whose turn it is and toggles the player each time this function is
** called.
*******************************************************************************/
void makeMove( GameBoardType & gameBoard );



/*******************************************************************************
** Boolean function indicating all spaces on the game board have been played. A
** true value returned indicates the game board has been fully consumed and no
** more moves are possible.
*******************************************************************************/
bool isBoardFull (const GameBoardType & gameBoard);


/*******************************************************************************
** Determines and returns an O if player O has won, an X if player X has won, or
** the NO_WINNER character (defined above) if neither has won.  A player has won
** if they occupy an entire row, and entire column, or an entire diagonal.
*******************************************************************************/
char isaWinner   (const GameBoardType & gameBoard);



#endif
