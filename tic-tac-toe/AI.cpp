#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int board_size = 3;  // Tic-Tac-Toe board is 3x3
vector<vector<char>> board(board_size, vector<char>(board_size, ' '));

bool isBoardFull() {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

bool hasPlayerWon(char player) {
    // Check rows and columns
    for (int i = 0; i < board_size; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

bool isValidMove(int position) {
    int row = (position - 1) / board_size;
    int col = (position - 1) % board_size;
    if (position < 1 || position > board_size * board_size || board[row][col] != ' ') {
        return false;
    }
    return true;
}

void makeHumanMove() {
    int position;
    cout << "Enter your move (1-9): ";
    while (!(cin >> position) || !isValidMove(position)) {
        cin.clear();
        cout << "Invalid move. Enter a valid move (1-9): ";
    }
    int row = (position - 1) / board_size;
    int col = (position - 1) % board_size;
    board[row][col] = 'X';
}

vector<int> minimax(int depth, char player) {
    char opponent = (player == 'O') ? 'X' : 'O';

    if (hasPlayerWon('O')) {
        return {10 - depth, -1};  // AI wins
    } else if (hasPlayerWon('X')) {
        return {-10 + depth, -1};  // Human wins
    } else if (isBoardFull()) {
        return {0, -1};  // Draw
    }

    int bestScore = (player == 'O') ? numeric_limits<int>::min() : numeric_limits<int>::max();
    int bestMove = -1;

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                int currentScore = minimax(depth + 1, opponent)[0];
                board[i][j] = ' ';

                if (player == 'O') {
                    if (currentScore > bestScore) {
                        bestScore = currentScore;
                        bestMove = i * board_size + j;
                    }
                } else {
                    if (currentScore < bestScore) {
                        bestScore = currentScore;
                        bestMove = i * board_size + j;
                    }
                }
            }
        }
    }
    return {bestScore, bestMove};
}

void makeComputerMove() {
    vector<int> result = minimax(0, 'O');
    int bestMove = result[1];
    int row = bestMove / board_size;
    int col = bestMove % board_size;
    board[row][col] = 'O';
    cout << "Computer chose position: " << (row * board_size + col + 1) << endl;
}

void printBoard() {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            cout << board[i][j];
            if (j < board_size - 1) cout << " | ";
        }
        cout << endl;
        if (i < board_size - 1) {
            cout << "--|---|--" << endl;
        }
    }
}

void TicTacToe() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "You are X, Computer is O." << endl;

    while (true) {
        printBoard();
        makeHumanMove();

        if (hasPlayerWon('X')) {
            printBoard();
            cout << "Congratulations! You won!" << endl;
            break;
        } else if (isBoardFull()) {
            printBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        makeComputerMove();
        if (hasPlayerWon('O')) {
            printBoard();
            cout << "Computer wins!" << endl;
            break;
        } else if (isBoardFull()) {
            printBoard();
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

int main() {
    TicTacToe();
    return 0;
}
