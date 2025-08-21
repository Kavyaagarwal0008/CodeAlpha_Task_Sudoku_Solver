/*
Extra Feature
1-Manual Input Mode → User can enter their own Sudoku.
2-Generator Mode → Program generates a random valid puzzle.
3-Validation → Detects invalid input before solving.
4-Backtracking Solver → Finds solution step by step.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define N 9  // Sudoku grid size

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "---------------------\n"; // Separate 3x3 blocks
        }
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0)
                cout << " | ";  // Separate subgrids
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to find an empty cell
bool findEmptyLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

// Backtracking solver
bool solveSudoku(int grid[N][N]) {
    int row, col;
    if (!findEmptyLocation(grid, row, col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

// Validate the Sudoku
bool isValidSudoku(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        bool rowCheck[N + 1] = {false};
        bool colCheck[N + 1] = {false};
        for (int j = 0;j < N; j++) {
            if (grid[i][j] != 0) {
                if (rowCheck[grid[i][j]]) return false;
                rowCheck[grid[i][j]] = true;
            }
            if (grid[j][i] != 0) {
                if (colCheck[grid[j][i]]) return false;
                colCheck[grid[j][i]] = true;
            }
        }
    }

    for (int boxRow = 0; boxRow < N; boxRow += 3) {
        for (int boxCol = 0; boxCol < N; boxCol += 3) {
            bool boxCheck[N + 1] = {false};
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int val = grid[boxRow + i][boxCol + j];
                    if (val != 0) {
                        if (boxCheck[val]) return false;
                        boxCheck[val] = true;
                    }
                }
            }
        }
    }
    return true;
}

// Fill diagonal 3x3 boxes randomly
void fillDiagonal(int grid[N][N]) {
    for (int box = 0; box < N; box += 3) {
        bool used[10] = {false};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int num;
                do {
                    num = rand() % 9 + 1;
                } while (used[num]);
                used[num] = true;
                grid[box + i][box + j] = num;
            }
        }
    }
}

// Remove random cells to create puzzle
void removeNumbers(int grid[N][N], int count) {
    while (count > 0) {
        int i = rand() % N;
        int j = rand() % N;
        if (grid[i][j] != 0) {
            grid[i][j] = 0;
            count--;
        }
    }
}

// Generate a Sudoku puzzle
void generateSudoku(int grid[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;

    fillDiagonal(grid);
    solveSudoku(grid);   // Solve completely
    removeNumbers(grid, 40); // Remove 40 cells to make puzzle
}

int main() {
    srand(time(0)); // Seed random generator
    int grid[N][N];
    int choice;

    cout << "Sudoku Solver\n";
    cout << "1. Enter your own Sudoku\n";
    cout << "2. Generate a random Sudoku puzzle\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the Sudoku puzzle (9x9 grid, use 0 for empty cells):\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> grid[i][j];
            }
        }

        cout << "\nOriginal Sudoku Puzzle:\n";
        printGrid(grid);

        if (!isValidSudoku(grid)) {
            cout << "\nInvalid Sudoku input! Please check your puzzle.\n";
            return 0;
        }
    } 
    else if (choice == 2) {
        generateSudoku(grid);
        cout << "\nGenerated Sudoku Puzzle:\n";
        printGrid(grid);
    } 
    else {
        cout << "Invalid choice!\n";
        return 0;
    }

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku Puzzle:\n";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for the given Sudoku.\n";
    }

    return 0;
}
