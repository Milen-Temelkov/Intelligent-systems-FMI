#include<iostream>
#include<vector>

using namespace std;

struct Turn {
    int row = 0;
    int col = 0;

    void print() const {
        cout << "row: " << row << " col: " << col << endl;
    }
};

struct Win {
    bool isWin;
    char winner;
};

void makeMove(int x, int y, vector<vector<char>>& board, char moveType) {
    board[x][y] = moveType;
}

bool hasWinner(const vector<vector<char>>& board) {
    int onRow = 0, onCol = 0, onMain = 0, onSec = 0;

    for(int i = 0; i < 3; i++) {
        
        switch (board[i][i]) {
        case 'x':
            onMain += 1;
            break;
        case 'o':
            onMain -= 1;
            break;
        default:
            break;
        }

        switch (board[i][2 - i]) {
        case 'x':
            onSec += 1;
            break;
        case 'o':
            onSec -= 1;
            break;
        default:
            break;
        }

        for (int j = 0; j < 3; j++) {
            switch (board[i][j]) {
            case 'x':
                onRow += 1;
                break;
            case 'o':
                onRow -= 1;
                break;
            default:
                break;
            }

            switch (board[j][i]) {
            case 'x':
                onCol += 1;
                break;
            case 'o':
                onCol -= 1;
                break;
            default:
                break;
            }
        }
    
        if (abs(onRow) == 3 || abs(onCol) == 3) {
            return true;
        }

        onRow = 0;
        onCol = 0;
    }

    if (abs(onMain) == 3 || abs(onSec) == 3) {
        return true;
    }

    return false;
    
}

bool isTie(const vector<vector<char>>& board) {
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                return false;
            }
        }
    }
    return true;
}

void print(const vector<vector<char>>& board) {
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

vector<Turn> getPossibleTurns(const vector<vector<char>>& board) {
    vector<Turn> possibleTurns;

    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                possibleTurns.push_back({i, j});
            }
        }
    }

    return possibleTurns;
}

int minimizer(vector<vector<char>>& board, int alphaValue, int betaValue, vector<Turn> possibleTurns, int depth);
int maximizer(vector<vector<char>>& board, int alphaValue, int betaValue, vector<Turn> possibleTurns, int depth);

Turn makeDecision(vector<vector<char>>& board) { //make decision is a maximizer of 'o' moves
    vector<Turn> possibleTurns = getPossibleTurns(board);

    int maxVal = INT_MIN;

    int alphaValue = INT_MIN;
    int betaValue = INT_MAX;    

    Turn bestTurn;

    while(!possibleTurns.empty()) {
        Turn currTurn = possibleTurns.back();

        // cout << "current turn is: ";
        // currTurn.print();

        possibleTurns.pop_back();

        makeMove(currTurn.row, currTurn.col, board, 'o'); // making the move


        int currRes = minimizer(board, alphaValue, betaValue, possibleTurns, 2);

        // cout << "current result is: " << currRes << endl;
        // cout << "max result is: " << maxVal << endl;

        if (maxVal < currRes) {
            // cout << "swaping best turn" <<  endl;
            
            maxVal = currRes;
            bestTurn = currTurn;
        }

        makeMove(currTurn.row, currTurn.col, board, '_'); // unmaking the move

        //update alpha
        alphaValue = max(alphaValue, maxVal);

        //prune
        if (maxVal > betaValue) {
            continue;
        }
    }

    return bestTurn;
}

int maximizer(vector<vector<char>>& board, int alphaValue, int betaValue, vector<Turn> possibleTurns, int depth) {

    int maxVal = INT_MIN;

    if (hasWinner(board)) {
        return depth - 10;
        
    }

    if (possibleTurns.empty()) {
        return 0;
    }

    while(!possibleTurns.empty()) {
        Turn curr = possibleTurns.back();
        possibleTurns.pop_back();

        makeMove(curr.row, curr.col, board, 'o'); // making the move
        
        maxVal = max(maxVal, minimizer(board, alphaValue, betaValue, possibleTurns, depth + 1));

        makeMove(curr.row, curr.col, board, '_'); // unmaking the move
        
        //update alpha
        alphaValue = max(alphaValue, maxVal);

        //prune
        if (maxVal > betaValue) {
            return betaValue;
        }
    }

    return maxVal;
}

int minimizer(vector<vector<char>>& board, int alphaValue, int betaValue, vector<Turn> possibleTurns, int depth) {
    int minVal = INT_MAX;

    if (hasWinner(board)) {
        return 10 - depth;
    }

    if (possibleTurns.empty()) {
        return 0;
    }

    while(!possibleTurns.empty()) {
        Turn curr = possibleTurns.back();
        possibleTurns.pop_back();

        makeMove(curr.row, curr.col, board, 'x'); // making the move

        minVal = min(minVal, maximizer(board, alphaValue, betaValue, possibleTurns, depth + 1));

        makeMove(curr.row, curr.col, board, '_'); // unmaking the move
        
        //update beta
        betaValue = min(betaValue, minVal);

        //prune
        if (minVal < alphaValue) {
            return alphaValue;
        }


    }

    return minVal;
}

void playGame() {
    vector<vector<char>> board(3, std::vector<char>(3, '_'));

    int row, col;
    for (int turns = 0; turns < 9; turns++) {

        if (turns % 2 == 0) {
            cout << "input row and col: " << endl;
            cin >> row >> col;

            cout << "X plays:        " << endl;
            makeMove(row - 1, col - 1, board, 'x');
            print(board);

            if (hasWinner(board)) {
                cout << "You win!" << endl;
                return;
            }
        } else {
            Turn bestTurnForComputer = makeDecision(board);

            cout << "O plays:        " << endl;
            makeMove(bestTurnForComputer.row, bestTurnForComputer.col, board, 'o');
            print(board);

            if (hasWinner(board)) {
                cout << "Computer wins!" << endl;
                return;
            }
        }
    }

    cout << "Its a tie :(" << endl;
    return;
}

int main() {

    playGame();

    return 0;
}