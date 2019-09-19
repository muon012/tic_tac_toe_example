// TicTacToe.cpp
#include <vector>
#include <iostream>

#include "ticTacToe.hpp"







/*******************************************************************************
** displayBoard - Displays the game board to standard output.  Each game board
**                cell is displayed in a field of spaces with the X, O or * in
**                the center space separated with a separator character.
*******************************************************************************/
void displayBoard(const GameBoardType & gameBoard)
{
  // Each player's mark on the board is displayed in the center of a 3x3 square.  Each square is separated by vertical
  // and horizontal lines.  Vertical lines require their own column, but horizontal lines don't

  const unsigned SQUARE_SIZE = 3;  // Each player's mark will be displayed in a 3x3 square with the mark in the center



  // Define a matrix to hold and build the display contents.  The display matrix will be constructed as
  //    1) Create the right size matrix.  The matrix will be wider than it is tall. The extra columns are used for the
  //       vertical separator.  Initialize each element to a space.
  //    2) Insert horizontal lines into the display matrix by replacing the blank row with a row of underscore
  //       characters.
  //    3) Insert the vertical lines into the display matrix by replacing the blank column with the pipe character.
  //    4) Insert the player's marks into the display matrix by replacing just the right space with the corresponding
  //       game board character. The mapping from game board matrix to display matrix is a stepping association.  See
  //       below.
  std::vector<std::vector<char>> display( gameBoard.size() * SQUARE_SIZE,                               // number of rows
                                          std::vector<char>(                                            // initial value of each row is itself a collection
                                                             gameBoard.size() * (SQUARE_SIZE + 1) - 1,  // number of columns
                                                             ' '                                        // initial value of each column
                                                            )
                                        );


  // 2) Insert the horizontal lines
  for (unsigned rowIndex = SQUARE_SIZE-1;  rowIndex < display.size()-1;  rowIndex += SQUARE_SIZE)
  {
    for (auto & col : display[rowIndex])  col = '_';
  }


  // 3) Insert the vertical lines
  for (auto & row : display) for (unsigned colIndex = SQUARE_SIZE;  colIndex < row.size();  colIndex += SQUARE_SIZE + 1)
  {
    row[colIndex] = '|';
  }


  // 4) Now insert the player's marks
  //    Walk the game board matrix by row and column and use the indexes to map into the display matrix. A mark in row r
  //    of the game board maps to row = (r * SQUARE_SIZE)+1 of the display matrix, and a mark in column c of the game
  //    board maps to column = c * (SQUARE_SIZE + 1) + 1 of the display matrix
  for (unsigned rowIndex = 0; rowIndex < gameBoard.size(); ++rowIndex)
  {
    for (unsigned colIndex = 0; colIndex < gameBoard[rowIndex].size(); ++colIndex)
    {
      display[rowIndex*SQUARE_SIZE + 1][colIndex*(SQUARE_SIZE + 1) + 1] = gameBoard[rowIndex][colIndex];
    }
  }



  // And finally, display the pretty formatted game board by printing a newline after each row.
  for (const auto & row : display)
  {
    for (const auto & col : row) std::cout << col;
    std::cout << '\n';
  }
}







/*******************************************************************************
** makeMove - Displays the game board to standard output.  Each game board cell
**            is displayed in a field of spaces with the X, O or * in the center
**            space separated with a separator character.
*******************************************************************************/
void makeMove(GameBoardType & gameBoard)
{
  static char playersMark = 'O';
  if (playersMark == 'X') playersMark = 'O';
  else                    playersMark = 'X';

  unsigned row, col;
  do
  {
    std::cout << "Player_" << playersMark << ", make your move (row[1.." << gameBoard.size() << "] then col[1.." << gameBoard.size() << "]): ";
    std::cin >> row >> col;


    // If row and column inputs are out of range, emit error message and prompt again
    if ((row - 1 >= gameBoard.size()) || (col - 1 >= gameBoard.size()))
    {
      std::cout << "Ooops, bad row or column value.\n"
                << "  Expected a row and column between 1 and " << gameBoard.size() << '\n'
                << "  Please try again\n";
    }

    // If input is within range but the cell is already occupied, emit error message and prompt again
    else if (gameBoard[row-1][col-1] != EMPTY_CELL)
    {
      std::cout << "That square is already taken.  You have to pick an empty square\n"
                << "  Please try again\n";
    }

    // Everything looks good.  Accept the input and exit the loop
    else break;

  } while (true);

  gameBoard[row-1][col-1] = playersMark;
}







/*******************************************************************************
** isBoardFull - Boolean function indicating all spaces on the game board have
**               been played. A true value returned indicates the game board has
**               been fully consumed and no more moves are possible.
*******************************************************************************/
bool isBoardFull(const GameBoardType & gameBoard)
{
  for (const auto & row : gameBoard) for (const auto & col : row)
  {
    if (col == EMPTY_CELL)  return false;
  }

  return true;
}








/*******************************************************************************
** isaWinner - Determines and returns an O if player O has won, an X if player X
**             has won, or the NO_WINNER character (defined above) if neither
**             has won.  A player has won if they occupy an entire row, and
**             entire column, or an entire diagonal.
*******************************************************************************/
char isaWinner(const GameBoardType & gameBoard)
{
  // A little defensive programming - if row size or column size is 0 there can't be a winner, and accessing the first element will
  // not over index the container
  // Note:  Short-circuit boolean expression required here
  if (gameBoard.size() == 0 || gameBoard[0].size() == 0)  return NO_WINNER;

  const auto ROW_SIZE = gameBoard.size();
  const auto COL_SIZE = gameBoard[0].size();


  /****************************************************************************
  **                        Horizontal Winner?
  ** First, are all the (non-empty) marks in any given row the same?  If so, we have a winner!
  *****************************************************************************/
  for (unsigned row = 0; row < ROW_SIZE; ++row)
  {
    // If at least one empty space, no winner yet - move on to the next row
    if (gameBoard[row][0] == EMPTY_CELL) continue;

    // Look for and count matching marks in all the columns of the row
    unsigned col = 1;
    while ( (col < COL_SIZE)  &&  (gameBoard[row][0] == gameBoard[row][col]) )   ++col;

    // If all the marks in the row are the same = Winner!
    if (col == COL_SIZE) return gameBoard[row][0];
  }



  // Okay, no winners across (rows), let's look up and down (columns)

  /****************************************************************************
  **                        Vertical Winner?
  ** Next, are all the (non-empty) marks in any given column the same?  If so, we have a winner!
  *****************************************************************************/
  for (unsigned col = 0; col < COL_SIZE; ++col)
  {
    // If at least one empty space, no winner yet - move on to the next column
    if (gameBoard[0][col] == EMPTY_CELL) continue;

    // Look for and count matching marks in all the rows of the column
    unsigned row = 1;
    while ((row < ROW_SIZE) && (gameBoard[0][col] == gameBoard[row][col]))   ++row;

    // If all the marks in the column are the same = Winner!
    if (row == ROW_SIZE) return gameBoard[0][col];
  }



  // Okay, no winners up and down (columns) either, let's look at the diagonals

  /****************************************************************************
  **                        Diagonal Winner?
  ** Finally, are all the (non-empty) marks in top-left to bottom-right, or
  ** top-right to bottom-left the same?
  *****************************************************************************/
  if (gameBoard[0][0] != EMPTY_CELL)  // Top-Left
  {
    // Look for and count matching marks along the top-left to bottom-right diagonal
    unsigned cell = 1;
    while ((cell < ROW_SIZE) && (gameBoard[0][0] == gameBoard[cell][cell]))   ++cell;

    // If all the marks along the top-left to bottom-right diagonal are the same = Winner!
    if (cell == ROW_SIZE) return gameBoard[0][0];  // Winner!
  }

  if (gameBoard[0][COL_SIZE-1] != EMPTY_CELL)  // Top-Right
  {
    // Look for and count matching marks along the top-right to bottom-left diagonal
    unsigned cell = 1;
    while ((cell < ROW_SIZE) && (gameBoard[0][COL_SIZE-1] == gameBoard[cell][COL_SIZE-1 - cell]))   ++cell;

    // If all the marks along the top-right to bottom-left diagonal are the same = Winner!
    if (cell == ROW_SIZE) return gameBoard[0][COL_SIZE-1];  // Winner!
  }

  // Looked across all rows, and all columns, and both diagonals and still no winners found ...
  return NO_WINNER;
}
