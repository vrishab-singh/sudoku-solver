#include <iostream>
#include<bits/stdc++.h>
#define N 9
using namespace std;
int grid[N][N] = {
   {8, 0, 5, 0, 4, 0, 2, 0, 3},
   {4, 0, 9, 0, 2, 0, 6, 0, 5},
   {2, 3, 1, 0, 0, 5, 0, 0, 0},
   {0, 0, 2, 5, 0, 3, 0, 4, 0},
   {7, 8, 0, 1, 0, 0, 5, 0, 0},
   {3, 5, 0, 4, 7, 2, 1, 0, 0},
   {6, 0, 3, 0, 5, 0, 0, 0, 8},
   {9, 4, 0, 0, 0, 0, 0, 5, 7},
   {5, 2, 0, 0, 0, 0, 9, 0, 0}
};
bool isPresentInCol(int col, int num){ //check whether num is present in col or not
   for (int row = 0; row < N; row++)
      if (grid[row][col] == num)
         return true;
   return false;
}
bool isPresentInRow(int row, int num){ //check whether num is present in row or not
   for (int col = 0; col < N; col++)
      if (grid[row][col] == num)
         return true;
   return false;
}
bool isPresentInBox(int boxStartRow, int boxStartCol, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (grid[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}
void printGrid(){ //print the sudoku grid after solve
	cout << "  --------------------------------------------" << endl;
   for (int row = 0; row < N; row++){
    cout<<" | ";
      for (int col = 0; col < N; col++){
         cout << grid[row][col] <<" ";
         cout<<" | ";
      }
      cout << endl;
    }
    cout << "  -------------------------------------------" << endl;
}
bool findEmptyPlace(int &row, int &col){ //get empty location and update row and column
   for (row = 0; row < N; row++)
      for (col = 0; col < N; col++)
         if (grid[row][col] == 0) //marked with 0 is empty
            return true;
   return false;
}
bool isValidPlace(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
col - col%3, num);
}
bool solveSudoku(){
   int row, col;
   if (!findEmptyPlace(row, col))
      return true; //when all places are filled
   for (int num = 1; num <= 9; num++){ // 1 to 9
      if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the grid
         grid[row][col] = num;
         bool smallsolveSudoku = solveSudoku();
         if (smallsolveSudoku == true) //recursively go for other cell in the grid
            return true;
         else{
            grid[row][col] = 0; //backtrack when conditions are not satisfied
         }
      }
   }
   return false;
}
int main(){
   if (solveSudoku() == true)
      printGrid();
   else
      cout << "No solution exists";
}