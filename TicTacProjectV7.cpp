#include <iostream>
#include <time.h>
#include <vector>


/*

level 5

P-7.11 Write a program that can play Tic-Tac-Toe effectively.
 (See Section 3.1.3.)
To do this, you will need to create a game tree T, which is a tree where
each node corresponds to a game configuration, which, in this case, is
a representation of the tic-tac-toe board. The root node corresponds to
the initial configuration. For each internal node v in T, the children
of v
correspond to the game states we can reach from v’s game state in a single
legal move for the appropriate player, A (the first player) or B
(the second
player). Nodes at even depths correspond to moves for A and nodes at
odd depths correspond to moves for B. External nodes are either final
game states or are at a depth beyond which we don’t want to explore. We
score each external node with a value that indicates how good this state
is for player A. In large games, like chess, we have to use a heuristic
scoring function, but for small games, like tic-tac-toe, we can construct
the entire game tree and score external nodes as +1, 0, −1, indicating
whether player A has a win, draw, or lose in that configuration. A good
algorithm for choosing moves is minimax. In this algorithm, we assign a
score to each internal node v in T, such that if v represents A’s turn,we
compute v’s score as the maximum of the scores of v’s children (which
corresponds to A’s optimal play from v). If an internal node v represents
B’s turn, then we compute v’s score as the minimum of the scores of v’s
children (which corresponds to B’s optimal play from v).


minmax puesdo code

function minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value


*/

using namespace std; // make std:: accessible




class Tictactoe
{


private:

    int X; //= 1;  // possible marks
    int O; //= -1;
    int EMPTY; //= 0;



    int board[3][3]; // playing board

    int currentPlayer; // current player (X or O)

    int score;



public:





    Tictactoe()
        :
        X(1),
        O(-1),
        EMPTY(0),
        board(),
        currentPlayer(1),
        score(0)
        //internalPlays()


    {

    }




    Tictactoe(const Tictactoe & other) = default;

    Tictactoe & operator=(const Tictactoe & c)
    {
        if (this != &c) // not a self-assignment
        {
            X = c.X;
            O = c.O;
            EMPTY = c.EMPTY;
            //board = c.board;
            for (int x=0 ; x < 3; x++)
            {
                for (int y=0 ; y < 3; y++)
                {
                    board[x][y] = c.board[x][y];
                }
            }
            currentPlayer = c.currentPlayer;
            score = c.score;


        }

        return *this;

    }

    void clearBoard()   // clear the board
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = EMPTY; // every cell is empty
        currentPlayer = X; // player X starts
    }
    void putMark(size_t i, size_t j)   // mark row i column j
    {

        board[i][j] = currentPlayer; // mark with current player


        currentPlayer = -currentPlayer; // switch players
    }
    bool isWin(int mark)   // is mark the winner?
    {
        int win = 3*mark; // +3 for X and -3 for O
        return ((board[0][0] + board[0][1] + board[0][2] == win) // row 0
        || (board[1][0] + board[1][1] + board[1][2] == win) // row 1
        || (board[2][0] + board[2][1] + board[2][2] == win) // row 2
        || (board[0][0] + board[1][0] + board[2][0] == win) // column 0
        || (board[0][1] + board[1][1] + board[2][1] == win) // column 1
        || (board[0][2] + board[1][2] + board[2][2] == win) // column 2
        || (board[0][0] + board[1][1] + board[2][2] == win) // diagonal
        || (board[2][0] + board[1][1] + board[0][2] == win)); // diagonal
    }


    int getWinner()   // who wins? (EMPTY means tie)
    {
        if (isWin(X)) return X;
        else if (isWin(O)) return O;
        else return EMPTY;
    }

    int getCurrentPlayer()
    {
        return currentPlayer;
    }

    int getX()
    {
        return X;
    }

    int getO()
    {
        return O;
    }

    int getEMPTY()
    {
        return EMPTY;

    }

    int getScore()
    {
        return score;
    }

    int getBoard(size_t i, size_t j)
    {
        return board[i][j];
    }

    /*

    int returnAVaildBoardPos(int i, int j)
    {
        return board[i][j];
    }

    */


    bool isBoardFilled(int fullness)
    {
        int count = 0;

        bool filled = true;

        for(size_t i = 0; i < 3; i++)
        {
            for(size_t j = 0; j < 3; j++)
            {
                count += abs(board[i][j]);

            }
        }

        if(count != fullness)
        {
            filled = false;
        }

        return filled;
    }


    void setScore(int in)
    {
        score = in;
    }


    void printBoard()   // print the board
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                /*
                switch (board[i][j])
                {
                case X:
                    cout << "X";
                    break;
                case O:
                    cout << "O";
                    break;
                case EMPTY:
                    cout << " ";
                    break;
                }
                */

                if(board[i][j] == X)
                {
                    cout << "X";
                }
                else if(board[i][j] == O)
                {
                    cout << "O";
                }
                else if(board[i][j] == EMPTY)
                {
                    cout << "E";
                }


                if (j < 2) cout << "|"; // column boundary
            }
            if (i < 2) cout << "\n-+-+-\n"; // row boundary
        }
    }



    int calcScore()
    {
        int winner = getWinner();

        if(winner == X)
        {
            return 10;
        }
        else if(winner == O)
        {
            return -10;
        }
        else
        {
            return 0;
        }

    }

};





/////////////////////////////////////////////////////////////simple minmax

int myMinMaxSimple(Tictactoe obj, //used for predicting move
                   int player,
                   int counter,
                   long &winsX,
                   long &winsO,
                   long &ties)
{

   // Tictactoe oldObj = obj;


    if(obj.isBoardFilled(9) || obj.isWin(player) || obj.isWin(-player))
    {



            if(obj.isWin(1))
            {
                ++winsX;

               // return 10;
                return 10 - counter; //extra points?

            }

            if(obj.isWin(-1))
            {
                ++winsO;

               // return -10;
                return -10 + counter; //extra points?

            }

            if(obj.getWinner() == 0)
            {
                ++ties;

                return 0;

            }
    }




    if (player == obj.getX())
    {
        int best = -1000;

        for(size_t i = 0; i < 3; i++)
        {
            for(size_t j = 0; j < 3; j++)
            {
                if(obj.getBoard(i,j) == 0)
                {
                    Tictactoe copyTemp = obj;

                    copyTemp.putMark(i,j);

                    best = max(best,
                               myMinMaxSimple(copyTemp,
                                              -player,
                                              counter+1,
                                              winsX,
                                              winsO,
                                              ties));


                }

            }
        }

        //std::cout << "\n" << best;

        return best;

    }
    else if (player == obj.getO())
    {
        int best = 1000;

        for(size_t i = 0; i < 3; i++)
        {
            for(size_t j = 0; j < 3; j++)
            {
                if(obj.getBoard(i,j) == 0)
                {
                    Tictactoe copyTemp = obj;

                    copyTemp.putMark(i,j);

                    best = min(best,
                               myMinMaxSimple(copyTemp,
                                              -player,
                                              counter+1,
                                              winsX,
                                              winsO,
                                              ties));

                }

            }
        }

        //std::cout << "\n" << best;

        return best;
    }


//return obj;

    return -69; //means something went wrong
}


Tictactoe findbestMove(Tictactoe mainGameTest)
{
   // Tictactoe bestmove = mainGameTest;
   // Tictactoe bestmove;

    Tictactoe copyTemp;

    int bestVal = -10000;

    long winsX = 0;
    long winsO = 0;
    long ties = 0;

    size_t besti = -1;
    size_t bestj = -1;

    for(size_t i = 0; i < 3; i++)
    {
        for(size_t j = 0; j < 3; j++)
        {
            if(mainGameTest.getBoard(i,j) == 0)
            {


                copyTemp = mainGameTest;
                copyTemp.putMark(i,j);


                int player = -copyTemp.getCurrentPlayer();

                int moveVal = myMinMaxSimple(copyTemp,
                                             player,
                                             0,
                                             winsX,
                                             winsO,
                                             ties);

                //std::cout << moveVal;//

               // copyTemp = mainGameTest;




                if(moveVal > bestVal)
                {
                   // copyTemp = mainGameTest;

                    bestVal = moveVal;
                    //copyTemp.putMark(i,j);
                    besti = i;
                    bestj = j;

                    //break;

                }





            }

        }
    }

    Tictactoe copyTemp2 = mainGameTest;

    copyTemp2.putMark(besti,bestj);

    return copyTemp2;
}


int main()   // main program
{


    Tictactoe k;

    bool run = true;



    while(run)
    {

        if(k.isWin(-1) || k.isWin(1) || k.isBoardFilled(9))
        {
            run = false;
        }

        std::cout << "\n";


        k = findbestMove(k);


        if(k.isWin(-1) || k.isWin(1) || k.isBoardFilled(9))
        {
            run = false;
        }
        std::cout << "\nX made its move, your turn\n";
        k.printBoard();


        if(!k.isWin(-1) && !k.isWin(1) && !k.isBoardFilled(9))
        {
            int i, j;
            std::cin >> i;
            std::cin >> j;
            k.putMark(i,j);

        }

        if(k.isWin(-1) || k.isWin(1) || k.isBoardFilled(9))
        {
            run = false;
        }

        std::cout << "\n";
        std::cout << "\nO move recorded\n";
        k.printBoard();

        std::cout << "\n";

        if(k.isWin(-1) || k.isWin(1) || k.isBoardFilled(9))
        {
            run = false;
        }


    }

    std:: cout << "\n==============Final Board!\n\n";
    k.printBoard();

    if(k.getWinner() == 1)
    {
        std::cout << "\n\nX won! \n";
    }
    else if (k.getWinner() == -1)
    {
        std::cout << "\n\nO won! \n";
    }
    else
    {
        std::cout << "\n\nTie/Draw ! \n";
    }

    return 0;
}

