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

int minimizer(vector<vector<char>>& board, int alphaValue, int betaValue, int depth);
int maximizer(vector<vector<char>>& board, int alphaValue, int betaValue, int depth);

Turn makeDecision(vector<vector<char>>& board, bool compStartsFirst) {
    vector<Turn> possibleTurns = getPossibleTurns(board);

    int maxVal = INT_MIN;

    int alphaValue = INT_MIN;
    int betaValue = INT_MAX;    

    Turn bestTurn;

    int depth = compStartsFirst ? 1 : 2;
    
    for (Turn curr : possibleTurns) {
        makeMove(curr.row, curr.col, board, 'o');

        int currRes = minimizer(board, alphaValue, betaValue, depth);

        makeMove(curr.row, curr.col, board, '_');

        //fancy max()
        if (maxVal < currRes) {
            maxVal = currRes;
            bestTurn = curr;
        }

        alphaValue = max(alphaValue, maxVal);

    }

    return bestTurn;
}

int maximizer(vector<vector<char>>& board, int alphaValue, int betaValue, int depth) {
    
    int maxVal = INT_MIN;
    vector<Turn> possibleTurns = getPossibleTurns(board);

    if (hasWinner(board)) {
        return depth - 10;
    }

    if (possibleTurns.empty()) {
        return 0;
    }

    for (Turn curr : possibleTurns) {
        makeMove(curr.row, curr.col, board, 'o');
        
        maxVal = max(maxVal, minimizer(board, alphaValue, betaValue, depth + 1));

        makeMove(curr.row, curr.col, board, '_');
        
        alphaValue = max(alphaValue, maxVal);

        if (maxVal >= betaValue) {
            return betaValue;
        }
    }

    return maxVal;
}

int minimizer(vector<vector<char>>& board, int alphaValue, int betaValue, int depth) {
    
    int minVal = INT_MAX;
    vector<Turn> possibleTurns = getPossibleTurns(board);
   
    if (hasWinner(board)) {
        return 10 - depth;
    }

    if (possibleTurns.empty()) {
        return 0;
    }

    for (Turn curr : possibleTurns) {
        makeMove(curr.row, curr.col, board, 'x');

        minVal = min(minVal, maximizer(board, alphaValue, betaValue, depth + 1));

        makeMove(curr.row, curr.col, board, '_');

        betaValue = min(betaValue, minVal);

        if (minVal <= alphaValue) {
            return alphaValue;
        }
    }

    return minVal;
}

void playGame(bool playerIsFirst) {
    vector<vector<char>> board(3, std::vector<char>(3, '_'));

    int row, col;
    for (int turns = 0; turns < 9; turns++) {

        if (turns % 2 == !playerIsFirst) {
            cout << "input row and col: " << endl;
            cin >> row >> col;

            cout << "X plays:        " << endl;
            makeMove(row - 1, col - 1, board, 'x');
            print(board);

            if (hasWinner(board)) {
                cout << "You win! :)" << endl;
                return;
            }

        } else {
            Turn bestTurnForComputer = makeDecision(board, !playerIsFirst);

            cout << "O plays:        " << endl;

            makeMove(bestTurnForComputer.row, bestTurnForComputer.col, board, 'o');
            print(board);

            if (hasWinner(board)) {
                cout << "Computer wins! :(" << endl;
                return;
            }
        }
    }

    cout << "Its a tie! :|" << endl;
    return;
}

int main() {

    bool playerIsFirst;

    cout << "Do you want to start first?" << endl;
    cin >> playerIsFirst;

    playGame(playerIsFirst);

    return 0;
}