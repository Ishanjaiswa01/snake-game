#include <conio.h>
#include <iostream>
#include <windows.h>
#include <cstdlib>   // for rand()
using namespace std;

// Global variables
const int width = 80;   // Width of the game boundary
const int height = 20;  // Height of the game boundary
int x, y;               // Snake's head coordinates
int fruitCordX, fruitCordY; // Food coordinates
int playerScore;        // Player's score
int snakeTailX[100], snakeTailY[100]; // Coordinates of the snake's tail
int snakeTailLen;       // Length of the snake's tail

enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection sDir;   // Current direction of the snake
bool isGameOver;        // Game over status

// Function to initialize game variables
void GameInit() {
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
    snakeTailLen = 0;
}

// Function for creating the game board & rendering
void GameRender(string playerName) {
    system("cls"); // Clear the console

    // Top wall
    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            // Side walls
            if (j == 0 || j == width)
                cout << "|";

            // Snake's head
            else if (i == y && j == x)
                cout << "O";

            // Snake's food
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";

            // Snake's tail
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        cout << "o";
                        prTail = true;
                        break;
                    }
                }
                if (!prTail) cout << " ";
            }
        }
        cout << endl;
    }

    // Bottom wall
    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    // Display the player's score
    cout << playerName << "'s Score: " << playerScore << endl;
}

// Function to update the game state
void UpdateGame() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;

    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    // Check for collision with walls
    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    // Check for collision with tail
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            isGameOver = true;
    }

    // Check for collision with food
    if (x == fruitCordX && y == fruitCordY) {
        playerScore += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLen++;
    }
}

// Function to set the game difficulty level
int SetDifficulty() {
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\n"
         << "NOTE: If not chosen or pressed any other key, "
         << "difficulty will be automatically set to Medium\nChoose difficulty level: ";
    cin >> choice;

    switch (choice) {
        case 1: dfc = 150; break;
        case 2: dfc = 100; break;
        case 3: dfc = 50;  break;
        default: dfc = 100;
    }
    return dfc;
}

// Function to handle user input
void UserInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': sDir = LEFT; break;
            case 'd': sDir = RIGHT; break;
            case 'w': sDir = UP; break;
            case 's': sDir = DOWN; break;
            case 'x': isGameOver = true; break;
        }
    }
}

// Main function
int main() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    int dfc = SetDifficulty();
    GameInit();

    while (!isGameOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        Sleep(dfc);
    }

    cout << "Game Over! Final Score: " << playerScore << endl;
    return 0;
}
