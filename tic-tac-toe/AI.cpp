#include <bits/stdc++.h>
#include <vector>
using namespace std;

int size = 3;
bool isHumanTurn = true;
bool hasGameStarted = false;
const char Human = 'X';
const char Computer = 'O';

vector<vector<char>> board(size, vector<char>(size, ' '));

bool isBoardFull()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (isdigit(board[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}

bool hasPlayerWon(char player)
{
    // row check
    for (int i = 0; i < size; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true;
        }
    }

    // col check
    for (int j = 0; j < size; j++)
    {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
        {
            return true;
        }
    }

    // digonals check
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true;
    }
}
bool isGameOver()
{
    if (isBoardFull() || hasPlayerWon(Human) || hasPlayerWon(Computer))
    {
        return true;
    }
    return false;
}

bool isValidMove(int position)
{
    int row = (position - 1) / size;
    int col = (position - 1) % size;

    if (position < 1 || position > size * size)
    {
        cout << "Invalid move" << endl;
        return false;
    }
    if (!isdigit(board[row][col]))
    {
        cout << "Already occupied" << endl;
        return false;
    }
    return true;
}

void makeHumanMove()
{
    int position;
    do
    {
        cout << "Enter the position : ";
        cin >> position;
    } while (!isValidMove(position));

    int row = (position - 1) / size;
    int col = (position - 1) % size;

    board[row][col] = Human;
}

int evaluteBoard()
{
    if (hasPlayerWon(Computer))
    {
        return 1;
    }
    else if (hasPlayerWon(Human))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

vector<int> minimax(int depth, char player)
{
    // row, col, score
    vector<int> bestMove = {-1, -1, 0};
    int bestScore;

    if (player == Computer)
    {
        bestScore = -10;
    }
    else
    {
        bestScore = 10;
    }

    if (isGameOver())
    {
        int score = evaluteBoard();
        return {-1, -1, score};
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (isdigit(board[i][j]))
            {
                board[i][j] = player;
                vector<int> currentMove = minimax(depth + 1, (player == Computer) ? Human : Computer);
                int currentScore = currentMove[2];

                board[i][j] = ('0' + i * size + j + 1);
                // cout << board[i][j] << endl;

                if (player == Computer)
                {
                    if (currentScore > bestScore)
                    {
                        bestScore = currentScore;
                        bestMove[0] = i;
                        bestMove[1] = j;
                    }
                }
                else
                {
                    if (currentScore < bestScore)
                    {
                        bestScore = currentScore;
                        bestMove[0] = i;
                        bestMove[1] = j;
                    }
                }
            }
        }
    }
    bestMove[2] = bestScore;
    return bestMove;
}

void makeComputerMove()
{
    vector<int> bestMove = minimax(0, Computer);
    int position = bestMove[0] * size + bestMove[1] + 1;

    board[bestMove[0]][bestMove[1]] = Computer;
    cout << "Computer chose position : " << position << endl;
}

void printBoard()
{
    cout << "-------------" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "| ";
        for (int j = 0; j < size; j++)
        {
            if (isHumanTurn && board[i][j] != Human && board[i][j] != Computer)
            {
                cout << (hasGameStarted ? ' ' : board[i][j]) << " | ";
            }
            else
            {
                cout << board[i][j] << " | ";
            }
        }
        cout << endl
             << "-------------" << endl;
    }
}

void printResult()
{
    if (hasPlayerWon(Human))
    {
        cout << "Congratulations! You won!" << endl;
    }
    else if (hasPlayerWon(Computer))
    {
        cout << "Computer wins!" << endl;
    }
    else
    {
        cout << "It's a draw!" << endl;
    }
}

void TicTacToe()
{

    char val = '1';
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = val++;
        }
    }

    while (!isGameOver())
    {
        printBoard();

        if (isHumanTurn)
        {
            makeHumanMove();
        }
        else
        {
            makeComputerMove();
        }
        isHumanTurn = !isHumanTurn;
        hasGameStarted = true;
    }

    printBoard();
    printResult();
}

int main()
{
    TicTacToe();
    return 0;
}
