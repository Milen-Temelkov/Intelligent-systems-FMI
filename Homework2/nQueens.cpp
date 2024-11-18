#include<iostream>
#include<random>
#include<vector>
#include<iomanip>
#include<chrono>

using namespace std;

struct Conflicts {
    vector<int> queensOnRow;
    vector<int> queensOnMainDiagonal;
    vector<int> queensOnSecondaryDiagonal;

    Conflicts(int numberOfQueens, vector<int> queens) {
        queensOnRow = vector<int>(numberOfQueens, 0);
        queensOnMainDiagonal = vector<int>(2 * numberOfQueens - 1, 0);
        queensOnSecondaryDiagonal = vector<int>(2 * numberOfQueens - 1, 0);

        for (int i = 0; i < queens.size(); i++) {
            queensOnRow[queens[i]]++;

            int mainDiagonalIndex = i - queens[i] + queens.size() - 1;
            int secondaryDiagonalIndex = i + queens[i];

            queensOnMainDiagonal[mainDiagonalIndex]++;
            queensOnSecondaryDiagonal[secondaryDiagonalIndex]++;
        }
    }

    void moveQueen(vector<int> queens, int qIndex, int newRowIndex) {
        queensOnRow[queens[qIndex]]--;
        queensOnRow[newRowIndex]++;

        int mainDiagonalIndex = qIndex - queens[qIndex] + queens.size() - 1;
        int secondaryDiagonalIndex = qIndex + queens[qIndex];

        queensOnMainDiagonal[mainDiagonalIndex]--;
        queensOnSecondaryDiagonal[secondaryDiagonalIndex]--;

        mainDiagonalIndex = qIndex - newRowIndex + queens.size() - 1;
        secondaryDiagonalIndex = qIndex + newRowIndex;

        queensOnMainDiagonal[mainDiagonalIndex]++;
        queensOnSecondaryDiagonal[secondaryDiagonalIndex]++;
    }

    bool hasConflicts() {
        for (int i = 0; i < queensOnRow.size(); i++) {
            if (queensOnRow[i] != 1) {
                return true;
            }
        }

        for (int i = 0; i < queensOnMainDiagonal.size(); i++) {
            if (queensOnMainDiagonal[i] > 1 || queensOnSecondaryDiagonal[i] > 1) {
                return true;
            }
        }

        return false;
    }
};

vector<int> init(int numberOfQueens) {
    
    vector<int> queens(numberOfQueens, 0);


    int queenRow = rand() % numberOfQueens; // fix me

    for(int col = 0; col < numberOfQueens; col++) {
        queens[col] = queenRow;

        queenRow += 2;
        if (queenRow >= numberOfQueens) {
            queenRow = 0;
        }
        
    }

    return queens;
}



int getColWithQueenWithMaxConf(vector<int>& queens, const Conflicts& c) {
    
    int numberOfQueens = queens.size();

    vector<int> conflictsPerQueen(numberOfQueens, 0);

    int currMax = 0;

    for (int i = 0; i < numberOfQueens; i++) {
        int mainDiagonalIndex = i - queens[i] + numberOfQueens - 1;
        int secondaryDiagonalIndex = i + queens[i];

        int conflicts = 0;
        conflicts += c.queensOnRow[queens[i]] - 1; // how much qns are on the row of the ith queen
        conflicts += c.queensOnMainDiagonal[mainDiagonalIndex] - 1;
        conflicts += c.queensOnSecondaryDiagonal[secondaryDiagonalIndex] - 1;

        conflictsPerQueen[i] = conflicts;
        currMax = max(currMax, conflicts);

    }

    if (!currMax) {
        return -1;
    }

    // cout << "maximum conflicts are: " << currMax << endl;
    
    vector<int> indexesOfQueensWithMaxConflicts;

    for (int i = 0; i < numberOfQueens; i++) {
        if (conflictsPerQueen[i] == currMax) {
            indexesOfQueensWithMaxConflicts.push_back(i);
        }
    }

    int index = rand() % indexesOfQueensWithMaxConflicts.size(); // random part

    return indexesOfQueensWithMaxConflicts[index];
}



int getRowWithMinConflict(vector<int>& queens, int col, const Conflicts& c) {
    int numberOfQueens = queens.size();

    vector<int> conflictsOnRow(numberOfQueens, 0);

    int currMin = numberOfQueens + 1;

    for(int row = 0; row < numberOfQueens; row++) {
        int mainDiagonalIndex = col - row + numberOfQueens - 1;
        int secondaryDiagonalIndex = col + row;

        int conflicts = 0;
        conflicts += c.queensOnRow[row];
        conflicts += c.queensOnMainDiagonal[mainDiagonalIndex];
        conflicts += c.queensOnSecondaryDiagonal[secondaryDiagonalIndex]; 
        conflictsOnRow[row] = conflicts;
        currMin = min(currMin, conflicts);
    }

    // cout << "minimum conflicts are: " << currMin << endl;

    vector<int> indexesOfRowsWithMinConflicts;

    for (int i = 0; i < numberOfQueens; i++) {
        if (conflictsOnRow[i] == currMin) {
            indexesOfRowsWithMinConflicts.push_back(i);
        }
    }

    int index = rand() % indexesOfRowsWithMinConflicts.size(); // random part

    return indexesOfRowsWithMinConflicts[index];
}


void print(const vector<int>& board) {
    for(int i = 0; i < board.size(); i++)     {
        for (int j = 0; j < board.size(); j++) {
            if(board[j] == i) {
                cout << '*' << ' ';
            }

            else {
                cout << '_' << ' ';
            }
        }
        cout << endl;
    }
}


void print(const Conflicts& c) {
    for(int r : c.queensOnRow) {
        cout << r << ' ';
    }

    cout << endl;

    for(int r : c.queensOnMainDiagonal) {
        cout << r << ' ';
    }

    cout << endl;

    for(int r : c.queensOnSecondaryDiagonal) {
        cout << r << ' ';
    }

    cout << endl;
}

void solve(int numberOfQueens) {

    if (numberOfQueens == 2 || numberOfQueens == 3) {
        cout << -1 << endl;
        return;
    }

    vector<int> qns = init(numberOfQueens);
    
    Conflicts c = Conflicts(qns.size(), qns);

    int i = 0;
    
    while (i++ < qns.size()) {

        int col = getColWithQueenWithMaxConf(qns, c);

        if (col < 0) {
            if (numberOfQueens <= 100) {
                print(qns);
            }

            return;
        }
        
        int row = getRowWithMinConflict(qns, col, c);

        c.moveQueen(qns, col, row);

        qns[col] = row;
    }


    if (c.hasConflicts()) {
        solve(numberOfQueens);
    }
}


int main() {

    int numberOfQueens;
    cin >> numberOfQueens;

    // vector<int> qns = init(numberOfQueens);
    // print(qns);

    // Започваме да измерваме времето
    auto start = std::chrono::high_resolution_clock::now();

    solve(numberOfQueens);
    
    // Край на измерването на времето
    auto end = std::chrono::high_resolution_clock::now();

    // // Изчисляване на времето за изпълнение в секунди
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << std::fixed << std::setprecision(2) << elapsed.count() << " seconds\n";

    return 0;
}