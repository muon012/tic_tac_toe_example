/*******************************************************************************
**                          T I C   T A C   T O E
** This is a program that allows two players to play a game of tic-tac-toe.
**    o - Player X selects a location in an NxN square board for placing an X by
**        entering a row and column number.
**    o - If there is no winner yet and the board is not yet full, Player O
**        selects a location in an NxN square board for placing an O by entering
**        a row and column number.
**
** The game continues until a player has won or a tie has occurred.
**    o - Player X wins when there are N Xs in a row, a column, or a diagonal on
**        the game board.
**    o - Player O wins when there are N Os in a row, a column, or a diagonal on
**        the game board.
**    o - A tie occurs when all of the locations on the board are full, but
**        there is no winner.
*******************************************************************************/


#include <iostream>
#include <vector>
#include "ticTacToe.hpp"






int main()
{
  // Create the game board and initialize it to be empty
  unsigned BOARD_SIZE = 3U; // Could ask the user for this value ...

  GameBoardType theBoard(BOARD_SIZE, std::vector<char>(BOARD_SIZE, EMPTY_CELL)); // define the NxN matrix and initialize
                                                                                 // every cell to the empty cell

  // Have each player take alternating turns.  Each iteration through the loop
  // is one player's turn. A turn will
  //   1) display the current state of the game board, and
  //   2) allow the player to make a valid move
  // Alternating turns continue until someone has won the game, or until the
  // game board has been fully consumed and no more moves are possible.
  char winningPlayer;
  do
  {
    displayBoard(theBoard);
    makeMove(theBoard);

    winningPlayer = isaWinner(theBoard);
  } while (winningPlayer == NO_WINNER  &&  !isBoardFull(theBoard));

  // Display the final state of the game board so the players can see the winning configuration
  displayBoard(theBoard);



  // Report the outcome of the game by stating who, if anyone, won the game
  if (winningPlayer == NO_WINNER)  std::cout << "Tie game, no winner";
  else                             std::cout << "The Winner is Player_" << winningPlayer << "!\n";

  return 0;
}
