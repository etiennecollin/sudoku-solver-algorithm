//
//  main.cpp
//  Sudoku
//
//  Created by Etienne Collin on 2019-12-06.
//
#include <math.h>

#include <iostream>
#include <vector>

double x = 0;
double y = 0;
int nb = 0;
bool again = true;
bool kill = false;

struct Box {
    int value;
    bool initialized;
};
std::vector<std::vector<Box> > sudoku(9, std::vector<Box>(9));
void initialize();
void initializeTest();
bool calculate(double x, double y);
void print();
void space() {
    for (int i = 0; i < 100; i++) {
        std::cout << "\n";
    }
}
void error() {
    space();
    std::cout << "Value has to be between 1 and 9 inclusively.";

    int c;
    std::cout << "\n"
              << "Do you wish to continue ?"
              << "\n"
              << "1 to continue and 0 to stop : ";
    std::cin >> c;
    if (c == 1) {
    } else {
        kill = true;
        again = false;
    }
}

bool zeros() {
    for (int f = 0; f < 9; f++) {
        for (int g = 0; g < 9; g++) {
            if (sudoku[f][g].value == 0) {
                return true;
            }
        }
    }
    return false;
}

bool isValidXY(double x, double y, int v) {
    // Check if value 'v' is found in same row/column.

    //'i' is used to go through all the boxes.
    for (int i = 0; i < 9; i++) {
        // Verification for x and y axes.
        if ((sudoku[i][y].value == v) || (sudoku[x][i].value == v)) return false;
    }
    return true;
}

bool isValid3x3(double x, double y, int v) {
    int count = 0;  // Counts the number of times a box with a value 'v' is found in the same 3x3 box.
    double ax = (ceil((x + 1) / 3) * 3);
    double ay = (ceil((y + 1) / 3) * 3);
    //'x' coordinate of the 3x3 box.
    for (double i = 0; i < 3; i++) {
        //'y' coordinate of the 3x3 box.
        for (double j = 0; j < 3; j++) {
            // Verification of the values of the 3x3 box.
            if (sudoku[(ax - 1 - i)][(ay - 1 - j)].value == v) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    initialize();
    if (kill) {
        return 0;
    } else {
        calculate(x, y);
        space();
        std::cout << "\n"
                  << "Using " << nb << " base number(s)."
                  << "\n\n";
        print();
        if (zeros()) {
            std::cout << "\n"
                      << "This sudoku has no valid solution."
                      << "\n";
        }
    }
}

// Function used to input the base numbers in the sudoku.
void initialize() {
    while (again) {
        int x, y, v;

        space();
        std::cout << "You currently have : " << nb << " base number(s)."
                  << "\n";
        std::cout << "Input 0 as 'x' and 'y' when you are done."
                  << "\n\n";
        print();
        std::cout << "Which box do you want to set a value to ?"
                  << "\n"
                  << "Insert 'x' then 'y' : ";
        std::cin >> x >> y;

        if ((x == 0) && (y == 0)) {
            again = false;
        } else if ((x == -1) && (y == -1)) {
            initializeTest();
        } else if (((x <= 9) && (y <= 9)) && ((x > 0) && (y > 0))) {
            std::cout << "\n"
                      << "What should be the value of this box : ";
            std::cin >> v;
            if ((v <= 9) && (v > 0)) {
                sudoku[(x - 1)][(y - 1)].value = v;
                sudoku[(x - 1)][(y - 1)].initialized = true;
                nb++;
            } else if ((v == 0) && (sudoku[(x - 1)][(y - 1)].initialized == true)) {
                sudoku[(x - 1)][(y - 1)].value = v;
                sudoku[(x - 1)][(y - 1)].initialized = false;
                nb--;
            } else {
                error();
            }
        } else {
            error();
        }
    }
}

// Function used to input the missing numbers in the sudoku.
bool calculate(double x, double y) {
    if (x == 9) {
        x = 0;
        y++;
        if (y == 9) {
            return true;
        }
    }
    if ((sudoku[x][y].initialized != false) || (sudoku[x][y].value != 0)) {
        return calculate(++x, y);
    }
    for (int v = 1; v <= 9; v++) {
        if (isValidXY(x, y, v) && isValid3x3(x, y, v)) {
            sudoku[x][y].value = v;
            sudoku[x][y].initialized = true;

            if (calculate(x + 1, y)) {
                return true;
            } else {
                sudoku[x][y].value = 0;
                sudoku[x][y].initialized = false;
            }
        }
    }
    return false;
}

// Function used to print the sudoku.
void print() {
    std::cout << "|-|-|-|-|-|-|-|-|-|"
              << "\n";
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (sudoku[x][y].value == 0) {
                std::cout << "|•";
            } else {
                std::cout << "|" << sudoku[x][y].value;
            }
        }
        std::cout << "|"
                  << "\n";
    }
    std::cout << "|-|-|-|-|-|-|-|-|-|"
              << "\n\n";
}

// Function used to input the base number(s) of a pre-made sudoku for testing.
void initializeTest() {
    sudoku[0][0].value = 3;
    sudoku[3][0].value = 7;
    sudoku[6][0].value = 9;

    sudoku[0][1].value = 2;
    sudoku[1][1].value = 4;
    sudoku[5][1].value = 1;
    sudoku[6][1].value = 5;

    sudoku[4][2].value = 4;
    sudoku[5][2].value = 3;
    sudoku[6][2].value = 1;

    sudoku[0][4].value = 5;
    sudoku[1][4].value = 7;
    sudoku[2][4].value = 6;
    sudoku[8][4].value = 2;

    sudoku[8][5].value = 4;

    sudoku[3][6].value = 9;
    sudoku[5][6].value = 4;
    sudoku[7][6].value = 3;
    sudoku[8][6].value = 7;

    sudoku[2][7].value = 7;
    sudoku[3][7].value = 5;
    sudoku[6][7].value = 6;
    sudoku[8][7].value = 9;

    sudoku[2][8].value = 3;
    sudoku[4][8].value = 6;

    nb += 25;

    print();
}
