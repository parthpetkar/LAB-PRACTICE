#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class Main {
private:
    vector<int> board = vector<int>(9, 0);
    vector<int> magicSquare = { 2, 7, 6, 9, 5, 1, 4, 3, 8 };
    default_random_engine random;

public:
    Main() : random(random_device()()) {}

    void playGame() {
        for (int i = 0; i < 9; i++) {
            if (i % 2 == 0) {
                computerMove();
            } else {
                humanMove();
            }
            cout << endl;
            printBoard();
            if (checkWin()) {
                cout << "Game Over. Winner: " << (i % 2 == 0 ? "Computer" : "Human") << endl;
                return;
            }
        }
        cout << "Game Over. It's a draw." << endl;
    }

private:
    void computerMove() {
        if (count(board.begin(), board.end(), 0) < 4) {
            int move;
            do {
                move = random() % 9;
            } while (board[move] != 0);
            board[move] = 1;
        } else {
            int move = findBestMove(1);
            if (move == -1) {
                move = findBestMove(-1);
                if (move == -1) {
                    do {
                        move = random() % 9;
                    } while (board[move] != 0);
                }
            }
            board[move] = 1;
        }
    }

    int findBestMove(int player) {
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                int sum = 0;
                for (int j = 0; j < 9; j++) {
                    if (board[j] == player)
                        sum += magicSquare[j];
                }
                if (15 - sum == magicSquare[i])
                    return i;
            }
        }
        return -1;
    }

    void humanMove() {
        int move;
        do {
            cout << "Enter your move (1-9): ";
            cin >> move;
            move -= 1;
        } while (move < 0 || move >= 9 || board[move] != 0);
        board[move] = -1;
    }

    bool checkWin() {
        vector<vector<int>> lines = {
                { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, 
                { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, 
                { 0, 4, 8 }, { 2, 4, 6 } 
        };

        for (const auto& line : lines) {
            if (board[line[0]] != 0 &&
                board[line[0]] == board[line[1]] &&
                board[line[0]] == board[line[2]]) {
                return true;
            }
        }
        return false;
    }

    void printBoard() {
        for (int i = 0; i < 9; i++) {
            cout << (board[i] == 1 ? "X " : (board[i] == -1 ? "O " : to_string(i + 1) + " "));
            if (i % 3 == 2)
                cout << endl;
        }
    }
};

int main() {
    Main game;
    game.playGame();
    return 0;
}