#include <iostream>
using namespace std;

//struct for TicTacToe board
struct TicTacToe{
    char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
};

//print out properly formatted board
void printBoard(TicTacToe tic){
    cout<< "   |   |" << endl;
    cout<< " " << tic.board[0][0] << " | " << tic.board[0][1] << " | " << tic.board[0][2] << endl;
    cout<< "---+---+---" << endl;
    cout<< " " << tic.board[1][0] << " | " << tic.board[1][1] << " | " << tic.board[1][2] << endl;
    cout<< "---+---+---" << endl;
    cout<< " " << tic.board[2][0] << " | " << tic.board[2][1] << " | " << tic.board[2][2] << endl;
    cout<< "   |   |" << endl;
}

int main(){
    //variables used
    int row, col; //user input variables
    bool adjacentEdge = false;

    //start and display game
    TicTacToe game;
    cout<< "Game Starting!" << endl;
    printBoard(game);

    //play first computer move (always same)
    cout<<"Computer moves first:" << endl;
    game.board[1][1] = 'X';
    printBoard(game);

    //initial user input
    cout<< "Enter move as \"row col\" (e.g. 0 1 for top middle spot):" << endl;
    cin>>row>>col;
    game.board[row][col] = 'O';
    printBoard(game);

    //nested if statements for every continuation (using requirements that group similar statements)
    if((row+col)%2 == 0){//check if corner
        game.board[(row+2)%4][(col+2)%4] = 'X';//play opposite corner        
        cout<<"Computer moves:" << endl;
        printBoard(game);
        
        cout<< "Enter move as \"row col\" (e.g. 0 1 for top middle spot):" << endl; //input
        cin>>row>>col;
        game.board[row][col] = 'O';
        printBoard(game);

        if((row+col)%2 == 0){//check if corner
            if(game.board[(row+2)%4][col] == 'O')//find blocking move
                game.board[1][col] = 'X';
            else
                game.board[row][1] = 'X';
            cout<<"Computer moves:" << endl;
            printBoard(game);

            cout<< "Enter move as \"row col\" (e.g. 0 1 for top middle spot):" << endl; //input
            cin>>row>>col;
            game.board[row][col] = 'O';
            printBoard(game);
            
            if(col==1 && game.board[(row+2)%4][col] == 'X'){//check if blocking column win (no need to check middle space)
                if(game.board[row][col+1] == 'X')
                    game.board[row][col-1] = 'X';
                else
                    game.board[row][col+1] = 'X';
            }
            else if(row==1 && game.board[row][(col+2)%4] == 'X'){//check if blocking row win (no need to check middle space)
                if(game.board[row+1][col] == 'X')
                    game.board[row-1][col] = 'X';
                else
                    game.board[row+1][col] = 'X';
            }
            else{//if unblocked, find and use winning move
                for(int i = 0; i<3 ; i+=2){
                    if(game.board[i][1] == 'X')
                        game.board[(i+2)%4][1] = 'X';
                    if(game.board[1][i] == 'X')
                        game.board[1][(i+2)%4] = 'X';
                }
                cout<< "COMPUTER WINS ):" << endl;//announce win and exit so don't do remaining operations
                printBoard(game);
                exit(0);
            }

            cout<<"Computer moves:" << endl;
            printBoard(game);

            cout<< "Enter move as \"row col\" (e.g. 0 1 for top middle spot):" << endl; //input
            cin>>row>>col;
            game.board[row][col] = 'O';
            printBoard(game);

            for(int i = 0; i<3; i++){//check for and fill last empty space
                for(int j = 0; j<3; j++){
                    if(game.board[i][j] == ' ')
                        game.board[i][j] = 'X';
                }
            }

            cout<< "TIE GAME /:" << endl;//announce tie and exit to not interfere with other continuances
            printBoard(game);
            exit(0);
        }

        for(int i=0; i<2; i++){//check if adjacent edge and make next move to block within loop if so
            if(game.board[i][col] == 'O' && game.board[i+1][col] == 'O'){
                game.board[(i+2)%3][col] = 'X';
                adjacentEdge = true;
            }
            if(game.board[row][i] == 'O' && game.board[row][i+1] == 'O'){
                game.board[row][(i+2)%3] = 'X';
                adjacentEdge = true;
            }
        }
        if(adjacentEdge){
            cout<<"Computer moves:" << endl;
            printBoard(game);

            cout<< "Enter move as \"row col\" (e.g. 0 1 for top middle spot):" << endl; //input
            cin>>row>>col;
            game.board[row][col] = 'O';
            printBoard(game);

            for(int i=0; i<3; i+=2){
                if(game.board[i][0] == 'X' && game.board[i][1] == ' ' && game.board[i][2] == 'X'){//check for horizontal win
                    game.board[i][1] = 'X';
                    cout<< "COMPUTER WINS ):" <<endl;
                    printBoard(game);
                    exit(0);
                }
                if(game.board[0][i] == 'X' && game.board[1][i] == ' ' && game.board[2][i] == 'X'){//check for vertical win
                    game.board[1][i] = 'X';
                    cout<< "COMPUTER WINS ):" <<endl;
                    printBoard(game);
                    exit(0);
                }
                for(int j=0; j<3; j+=2){
                    if(game.board[i][j] == 'X' && game.board[(i+2)%4][(j+2)%4] == ' '){//check if diagonal win possible
                        game.board[(i+2)%4][(j+2)%4] = 'X';
                        cout<< "COMPUTER WINS ):" <<endl;
                        printBoard(game);
                        exit(0);
                    }   
                }
            }
        }
        else{//opposite edge case
            for(int i=0; i<3; i+=2){
                for(int j=0; j<3; j+=2){
                    if(game.board[i][j] == ' ' && i != row && j != col)//find opposite corner and play there
                        game.board[i][j] = 'X';
                }
            }
            cout<<"Computer moves:" << endl;
            printBoard(game);

            cout<< "Enter move as \"row col\" (e.g. 0 1 for top middle spot):" << endl; //input
            cin>>row>>col;
            game.board[row][col] = 'O';
            printBoard(game);

            for(int i=0; i<3; i+=2){
                if(game.board[i][0] == 'X' && game.board[i][1] == ' ' && game.board[i][2] == 'X'){//check for horizontal win
                    game.board[i][1] = 'X';
                    cout<< "COMPUTER WINS ):" <<endl;
                    printBoard(game);
                    exit(0);
                }
                if(game.board[0][i] == 'X' && game.board[1][i] == ' ' && game.board[2][i] == 'X'){//check for vertical win
                    game.board[1][i] = 'X';
                    cout<< "COMPUTER WINS ):" <<endl;
                    printBoard(game);
                    exit(0);
                }
                for(int j=0; j<3; j+=2){
                    if(game.board[i][j] == 'X' && game.board[(i+2)%4][(j+2)%4] == ' '){//check if diagonal win possible
                        game.board[(i+2)%4][(j+2)%4] = 'X';
                        cout<< "COMPUTER WINS ):" <<endl;
                        printBoard(game);
                        exit(0);
                    }   
                }
            }
        }
    }
    else{//if player plays on edge
        if(row==1)
            game.board[0][(col+2)%4] = 'X';
        else
            game.board[(row+2)%4][0] = 'X';
        cout<<"Computer moves:" << endl;
        printBoard(game);

        cout<< "Enter move as \"row col\" (e.g. 0 1 for top middle spot):" << endl; //input
        cin>>row>>col;
        game.board[row][col] = 'O';
        printBoard(game);

        if(game.board[(row+2)%4][(col+2)%4] == 'X'){//if diagonal win blocked
            for(int i=0; i<2; i++){//find spot to block
                if(game.board[i][col] == 'O' && game.board[i+1][col] == 'O'){
                    game.board[(i+2)%3][col] = 'X';
                }
                if(game.board[row][i] == 'O' && game.board[row][i+1] == 'O'){
                     game.board[row][(i+2)%3] = 'X';
                }
            }
            cout<<"Computer moves:" << endl;
            printBoard(game);

            cout<< "Enter move as \"row col\" (e.g. 0 1 for top middle spot):" << endl; //input
            cin>>row>>col;
            game.board[row][col] = 'O';
            printBoard(game);

            for(int i=0; i<3; i+=2){
                if(game.board[i][0] == 'X' && game.board[i][1] == ' ' && game.board[i][2] == 'X'){//check for horizontal win
                    game.board[i][1] = 'X';
                    cout<< "COMPUTER WINS ):" <<endl;
                    printBoard(game);
                    exit(0);
                }
                if(game.board[0][i] == 'X' && game.board[1][i] == ' ' && game.board[2][i] == 'X'){//check for vertical win
                    game.board[1][i] = 'X';
                    cout<< "COMPUTER WINS ):" <<endl;
                    printBoard(game);
                    exit(0);
                }
                for(int j=0; j<3; j+=2){
                    if(game.board[i][j] == 'X' && game.board[(i+2)%4][(j+2)%4] == ' '){//check if diagonal win possible
                        game.board[(i+2)%4][(j+2)%4] = 'X';
                        cout<< "COMPUTER WINS ):" <<endl;
                        printBoard(game);
                        exit(0);
                    }   
                }
            }
        }
        else{//if diagonal win not blocked
            for(int i=0; i<3; i+=2){
                for(int j=0; j<3; j+=2){
                    if(game.board[i][j] == ' ' && game.board[(i+2)%4][(j+2)%4] == 'X')                        
                        game.board[i][j] = 'X';
                }
            }
            cout<< "COMPUTER WINS ):" <<endl;
            printBoard(game);
        }
    }

    return 0;
}