#include <raylib.h>
#include <iostream>
using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
int cellSize = 200;
int winner = 0;
char turn = 'X';

void drawBoard();
void handleMouseClick(int mousex, int mousey);

int main()
{
    InitWindow(600, 600, "Tic Tac Toe");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawBoard();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int mousex = GetMouseX();
            int mousey = GetMouseY();
            handleMouseClick(mousex, mousey);
        }
        if (winner != 0)
        {
            DrawText(winner == 3 ? "Game Draw!" : (winner == 1 ? "Player X Wins!" : "Player O Wins!"),
                     150, 550, 30, DARKBLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void drawBoard()
{
    for (int i = 1; i < 3; i++)
    {
        DrawLine(i * cellSize, 0, i * cellSize, 600, BLACK);
        DrawLine(0, i * cellSize, 600, i * cellSize, BLACK);
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int x = col * cellSize + cellSize / 2;
            int y = row * cellSize + cellSize / 2;

            if (board[row][col] == 'X')
            {
                DrawText("X", x - 20, y - 30, 50, RED);
            }
            else if (board[row][col] == 'O')
            {
                DrawText("O", x - 20, y - 30, 50, BLUE);
            }
        }
    }
}

void handleMouseClick(int mousex, int mousey)
{
    if (winner != 0)
        return; 

    int row = mousex / cellSize;
    int col = mousey / cellSize;

    if (board[row][col] != 'X' && board[row][col] != 'O')
    {
        board[row][col] = turn;

        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
                winner = (board[i][0] == 'X') ? 1 : 2;
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
                winner = (board[0][i] == 'X') ? 1 : 2;
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
            winner = (board[0][0] == 'X') ? 1 : 2;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
            winner = (board[0][2] == 'X') ? 1 : 2;

        bool draw = true;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != 'X' && board[i][j] != 'O')
                    draw = false;
        if (draw && winner == 0)
            winner = 3;
        turn = (turn == 'X') ? 'O' : 'X';
    }
}