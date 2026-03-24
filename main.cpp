#include<iostream>
#include<cstdlib>
#include<ctime>


const int ROWS = 4;
const int COLS = 4;

void printBoard(char board[][COLS])
{
    std::cout<<"\t  0     1     2     3\n";
    std::cout<<"       +-----+-----+-----+-----+\n";
    for(int i = 0; i<ROWS ; i++)
    {
        std::cout<<"    "<<i<<"  ";
        std::cout<<"|";
        for(int j = 0; j<COLS; j++)
        {
            std::cout<<"  "<<board[i][j]<<"  |";
        }
        std::cout<<'\n';
        std::cout<<"       +-----+-----+-----+-----+\n";
    }
    
}
void printBoard(int board[][COLS])
{
    std::cout<<"\t  0     1     2     3\n";
    std::cout<<"       +-----+-----+-----+-----+\n";
    for(int i = 0; i<ROWS ; i++)
    {
        std::cout<<"    "<<i<<"  ";
        std::cout<<"|";
        for(int j = 0; j<COLS; j++)
        {
            std::cout<<"  "<<board[i][j]<<"  |";
        }
        std::cout<<'\n';
        std::cout<<"       +-----+-----+-----+-----+\n";
    }
    
}
bool gameLogic(char visibleBoard[][COLS],int hiddenBoard[][COLS],int rows,int cols,int* score)
{

    if(hiddenBoard[rows][cols] == 1)
    {
        visibleBoard[rows][cols] = '?';
        printBoard(visibleBoard);
        std::cout<<"\nBOOM! Game Over! YOU LOST! \n";
        std::cout<<"Final Score: "<<*score<<'\n';
        printBoard(hiddenBoard);
        return false;
    }
    else if(hiddenBoard[rows][cols] == 2)
    {
        std::cout << "You already pick that spot! Try different one.\n";
        return true;
    }
    else
    {
        (*score)++;
        visibleBoard[rows][cols] = '0';
        hiddenBoard[rows][cols] = 2;
        printBoard(visibleBoard);
        return true;
    }
}

void randomBombs(int board[][COLS],int bombs)
{
    int rows,cols;
    for(int i = 0; i<bombs; i++)
    {
        rows = rand() % ROWS;
        cols = rand() % COLS;

        if(board[rows][cols] == 0)
        {
        board[rows][cols] = 1;
        }
        else i--;
    }
}

int main()
{
    srand(time(0));
    char board[ROWS][COLS] = {{'#','#','#','#'},
                              {'#','#','#','#'},
                              {'#','#','#','#'},
                              {'#','#','#','#'}};

    int bombBoard[ROWS][COLS] =   {0};
                       
    

    std::string difficulty;
    std::string choice;
    int bombs = 0;
    int rows,cols = 0;
    int score = 0;

    do
    {
    std::cout<<"MineSweeper\nDifficulty: (easy, medium, hard): ";
    std::cin>>difficulty;

    if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard")
        std::cout << "Invalid choice! Try again.\n";
    
    } while(difficulty != "easy" && difficulty != "medium" && difficulty != "hard");

    if(difficulty == "easy")
        bombs = 2;
    else if(difficulty == "medium")
        bombs = 4;
    else if(difficulty == "hard")
        bombs = 6;

    randomBombs(bombBoard,bombs);

    printBoard(board);
    do
    {
        std::cout<<"Exit:\n";
        std::cout<<"Enter number: ";
        std::cin>>choice;

        if(choice == "exit") break;;

        rows = choice[0] - '0';
        cols = choice[1] - '0';

        if(rows >= 0 && rows < ROWS && cols < COLS)
        {
            if(!gameLogic(board,bombBoard,rows,cols,&score))
            {
                return 0;
            }
        }
        else std::cout<<"INVALID POSITION! :<\n";

        if(score == (ROWS * COLS) - bombs)
        {
            std::cout<<"CONGRATULATIONS! YOU WON!\n";
            std::cout<<"Final Score: "<<score<<'\n';
        }

    } while(choice!="exit");

    return 0;
}