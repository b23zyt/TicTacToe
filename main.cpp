#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

using namespace std;

char board[3][3];
const char playerA = 'X';
const char playerB = 'O';
const char computer = '0';

bool COM = false;
bool PLA = false;
int number;
string nameA = " ";
string nameB = " ";



bool computerOrPlayer(){

    cout << "Choose the number of players (1/2): ";
    cin >> number;
    cin.clear();
    fflush(stdin);


    if (number == 1) {
        return COM = true;

    }
    else if (number == 2) {
        return PLA = true;
    }
    else
        throw invalid_argument("You need to enter 1 or 2 😡😡😡");
}

void resetBoard(){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++){
            board[i][j] = ' ';
        }
    }
};

void printBoard(){
    printf(" %c | %c | %c", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c", board[2][0], board[2][1], board[2][2]);
    cout << endl;
};

int checkFreeSpaces(){
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j] != ' ')
                freeSpaces--;
        }
    }
    return freeSpaces; //if return 0, the game will ends;  就是当输入9次后
};


void printWinner(char winner){
    if (winner == playerA)
        cout << nameA << " WIN!" << endl;
    else if (winner == playerB)
        cout << nameB << " WIN!" << endl;
    else if (winner == computer)
        cout << "YOU LOSS!" << endl;
    else
        cout << "It is a DRAW!" << endl;
};

void getOneName(){
    cout << "Please enter your name: ";
    cin >> nameA;
    srand(time(nullptr));
    int n = rand() % 9;
    n++;

    cout << "The game between " << nameA << " and Bot" << n << " starts... Good Luck!" << endl;
}

void getTwoName(){
    cout << "Name of Player A: ";
    cin >> nameA;

    cout << "Name of Player B: ";
    cin >> nameB;

    cout << "The game between "<< nameA << " and " << nameB << " begins ... Good Luck" << endl;
}

void playerAMove(){
    int x;
    int y;

    do {
        cout << nameA << " please enter row #(1-3): ";
        cin >> x;
        cin.clear();
        fflush(stdin);
        x--;

        cout << nameA << " please enter column #(1-3): ";
        cin >> y;
        cin.clear();
        fflush(stdin);
        y--;

        if (board[x][y] != ' ')
            cout << "Invalid move" << endl;
        else {
            board[x][y] = playerA;
            break;
        }
    } while(board[x][y] != ' ');
};

//when the game is between two person
void playBMove(){
    int x;
    int y;

    do {
        cout << nameB << " please enter row #(1-3): ";
        cin >> x;
        cin.clear();
        fflush(stdin);
        x--;
        cout << nameB << " please enter column #(1-3): ";
        cin >> y;
        cin.clear();
        fflush(stdin);
        y--;

        if (board[x][y] != ' ')
            cout << "Invalid move" << endl;
        else {
            board[x][y] = playerB;
            break;
        }
    } while(board[x][y] != ' ');
};


// when the game is between a person and a computer
void computerMove(){
    //create a seed based on the current time
    srand(time(nullptr));

    int x;
    int y;
    if (checkFreeSpaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' '); //we will keep generating random numbers util there's a empty space, then escape this do while loop
        board[x][y] = computer;
    }
    else
        printWinner(' '); //到这了
}


char checkWinner(){
    //check rows
    for (int i = 0; i < 3; i++){
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }

    //check columns
    for (int i = 0; i < 3; i++){
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return board[0][i];
    }

    //check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return board[0][2];

    return ' '; //means that currently there's no winner
};



int main() {
    char winner = ' ';
    char response;

    do {

        cout << "Welcome to Tic Tac Toe Game!" << endl;

        winner = ' ';
        response = ' ';

        try {
            computerOrPlayer();
        }

        catch (const logic_error &ex) {
            cout << ex.what() << endl;
        }

        if (PLA) {

            getTwoName();

            resetBoard();

            while (winner = ' ' && checkFreeSpaces() != 0) {
                printBoard();

                playerAMove();
                winner = checkWinner();
                if (winner != ' ' ||
                checkFreeSpaces() == 0) //when there's a winner or there's no winner(no space left)
                    break;

                printBoard(); //display the board after player one finish selecting the block

                playBMove();
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpaces() == 0)
                    break;
            }
            printBoard(); //to show the final result
            cout << endl;

            printWinner(winner); //print who is the winner

            cout << endl;
            cout << "Would you want to play again (Y/N): ";
            cin >> response;
        }



        else if (COM) {

            getOneName();

            resetBoard();

            while (winner = ' ' && checkFreeSpaces() != 0) {
                printBoard();

                playerAMove();
                winner = checkWinner();
                if (winner != ' ' ||
                checkFreeSpaces() == 0) //when there's a winner or there's no winner(no space left)
                    break;

                computerMove();
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpaces() == 0)
                    break;
            }

            printBoard(); //to show the final result
            cout << endl;

            printWinner(winner); //print who is the winner

            cout << endl;
        }

        else {
            cout << "Please restart the game by selecting Y" << endl;
            cout << endl;
        }


        cout << "Would you want to play again (Y/N): ";
        cin >> response;
        cout << endl;
        cout << "---------------------------------------------------" << endl;
        cout << endl;


    } while (toupper(response) == 'Y');

    cout << "Thanks for playing the game!";

    return 0;
}
