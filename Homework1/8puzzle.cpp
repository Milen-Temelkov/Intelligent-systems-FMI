#include<iostream>
#include<cmath>
#include<vector>
#include<iomanip>
#include<chrono>


using namespace std;


enum class Move {
    up,
    down,
    right,
    left
};

struct Coordinates {
    int x = 0;
    int y = 0;

    void print() const {
        cout << "x: " << x << " y: " << y << '\t';
    }
};

struct Number {
    Coordinates current;
    Coordinates goal;

    void print() const {
        cout << "Current: ";
        current.print();
        cout << "  Goal: ";
        goal.print();
    }
};



pair<vector<Number>, vector<int>> input() {
    int numbersCount, nullIndex;
    cin >> numbersCount >> nullIndex;
    
    vector<Number> data(numbersCount + 1);
    int dimensionSize = sqrt(numbersCount + 1);
    vector<int> matrix(numbersCount + 1, 0);

    for (int i = 0; i <= numbersCount; i++) {
        int number;
        cin >> number;
        data[number].current.x = i / dimensionSize;
        data[number].current.y = i % dimensionSize;

        matrix[i] = number;
    }

    nullIndex = ((nullIndex == -1) ? numbersCount : nullIndex);

    data[0].goal.x = nullIndex / dimensionSize;
    data[0].goal.y = nullIndex % dimensionSize;

    for (int i = 1; i <= numbersCount; i++) {
        int goalIndex = nullIndex >= i ? i - 1 : i;
        data[i].goal.x = goalIndex / dimensionSize;
        data[i].goal.y = goalIndex % dimensionSize;
    }

    return pair(data, matrix);
}



void print(const vector<Number> data) {
    for (int i = 0; i < data.size(); i++) {
        cout << "Number: " << i << "\t Current coordinates: ";
        data[i].current.print();
        cout << "\t Goal coordinates: ";
        data[i].goal.print();
        cout << endl;
    }
}

void print(const vector<vector<int>> matrix) {
    for(vector<int> row : matrix) {
        for(int el : row) {
            cout << el << ' ';
        }
        cout << endl;
    }
}

int countInversionsOf(vector<Number> data) {
    int counter = 0;
    int dimensionSize = sqrt(data.size());
    for (int i = 1; i < data.size(); i++) {
        for (int j = i + 1; j < data.size(); j++) {
            if ((data[i].current.x * dimensionSize + data[i].current.y)  > (data[j].current.x * dimensionSize + data[j].current.y)) {
                counter++;
            }
        }
    }
    return counter;
}



bool isSolvable(vector<Number> data, bool emptyAtStart) {
    int inversions = countInversionsOf(data);
    int dimension = sqrt(data.size());
    if (dimension % 2) {
        return inversions % 2 == 0;
    }

    else {
        int blankRow = emptyAtStart ? data[0].current.x + 1 : dimension - data[0].current.x;
        
        return (inversions + blankRow) % 2 == 1;
    }
}



class Node {
    int distance = 0;
    int dimension;
    vector<int> matrix;
    vector<Number> data;

    void calculateManhattenDistance() {
        int dimensionSize = sqrt(data.size());
        for (int i = 1; i < data.size(); i++) {
            distance += abs((data[i].current.x) - (data[i].goal.x)) + abs((data[i].current.y) - (data[i].goal.y));
        }
    }

    void recalculateManhattenDistance(Move move) {

        int zeroX = data[0].current.x;
        int zeroY = data[0].current.y;
        int neighbourX = 0;
        int neighbourY = 0;

        switch (move) {
            case Move::up: 
                neighbourX = zeroX + 1;
                neighbourY = zeroY;
                break;

            case Move::down:
                neighbourX = zeroX - 1;
                neighbourY = zeroY;
                break;

            case Move::left:
                neighbourX = zeroX;
                neighbourY = zeroY + 1;
                break;

            case Move::right:
                neighbourX = zeroX;
                neighbourY = zeroY - 1;
                break;
        }

        
        int neighbourValue = matrix[neighbourX * dimension + neighbourY];
        
        int oldDistance = abs((data[neighbourValue].current.x) - (data[neighbourValue].goal.x)) + abs((data[neighbourValue].current.y) - (data[neighbourValue].goal.y));
        makeMove(neighbourValue);
        int newDistance = abs((data[neighbourValue].current.x) - (data[neighbourValue].goal.x)) + abs((data[neighbourValue].current.y) - (data[neighbourValue].goal.y));
        
        distance += newDistance - oldDistance;
        
    }

    void makeMove(int neighbourValue) {
        swap(matrix[data[0].current.x * dimension + data[0].current.y], matrix[data[neighbourValue].current.x * dimension + data[neighbourValue].current.y]);
        swap(data[0].current, data[neighbourValue].current);
        
    }

public:

    Node(const Node& oth, Move move) {
        this->distance = oth.distance;
        this->dimension = oth.dimension;
        this->matrix = oth.matrix;
        this->data = oth.data;
        recalculateManhattenDistance(move);
    }

    Node(vector<Number> data, vector<int> matrix) {
        this->dimension = sqrt(data.size());
        this->data = data;
        this->matrix = matrix;
        calculateManhattenDistance();
    }

    int getDistance() const {
        return distance;
    }

    vector<int> getMatrix() const {
        return matrix;
    }

    vector<Number> getData() const {
        return data;
    }
    
    int getDimension() const {
        return dimension;
    }

    Coordinates zeroCoordinates() const {
        return Coordinates{data[0].current.x, data[0].current.y};
    }
};



pair<bool, int> search(const Node& node, int threshold, int currentCost, vector<Move>& moves) {

    if(node.getDistance() == 0) {
        cout << currentCost << endl;
        for (int i = 0; i < moves.size(); i++) {
            switch (moves[i]) {
                case Move::up:
                    cout << "up" << endl;
                    break;

                case Move::down:
                    cout << "down" << endl;
                    break;

                case Move::left:
                    cout << "left" << endl;
                    break;

                case Move::right:
                    cout << "right" << endl;
                    break;
            }
        }

        return pair(true, 0);
    }


    if (currentCost + node.getDistance() > threshold) {
        return pair(false, currentCost + node.getDistance());
    }

    Coordinates zeroCoordinates = node.zeroCoordinates();
    
    int dimension = node.getDimension() - 1;
    int nextMinThreshold = INT_MAX;


    if ((zeroCoordinates.y >= 0 && zeroCoordinates.y < dimension) && 
        ((!moves.empty() && moves.back() != Move::right) || moves.empty())) {

        moves.push_back(Move::left);

        pair<bool, int> leftRes = search(Node(node, Move::left), threshold, currentCost + 1, moves);

        moves.pop_back();

        if(leftRes.first == true) {
            return leftRes;
        }

        if(leftRes.second < nextMinThreshold) {
            nextMinThreshold = leftRes.second;
        }
    }


    if ((zeroCoordinates.y > 0 && zeroCoordinates.y <= dimension) &&
        ((!moves.empty() && moves.back() != Move::left) || moves.empty())) {

        moves.push_back(Move::right);

        pair<bool, int> rightRes = search(Node(node, Move::right), threshold, currentCost + 1, moves);

        moves.pop_back();

        if(rightRes.first == true) {
            return rightRes;
        }

        if(rightRes.second < nextMinThreshold) {
            nextMinThreshold = rightRes.second;
        }
    }


    if ((zeroCoordinates.x > 0 && zeroCoordinates.x <= dimension) &&
        ((!moves.empty() && moves.back() != Move::up) || moves.empty())) {

        moves.push_back(Move::down);

        pair<bool, int> downRes = search(Node(node, Move::down), threshold, currentCost + 1, moves);

        moves.pop_back();

        if(downRes.first == true) {
            return downRes;
        }

        if(downRes.second < nextMinThreshold) {
            nextMinThreshold = downRes.second;
        }
    }


    if ((zeroCoordinates.x >= 0 && zeroCoordinates.x < dimension) &&
        ((!moves.empty() && moves.back() != Move::down) || moves.empty())) {

        moves.push_back(Move::up);

        pair<bool, int> upRes = search(Node(node, Move::up), threshold, currentCost + 1, moves);

        moves.pop_back();

        if(upRes.first == true) {
            return upRes;
        }

        if(upRes.second < nextMinThreshold) {
            nextMinThreshold = upRes.second;
        }
    }

    
    return pair(false, nextMinThreshold);

}


void IDAStar(const Node& start) {
    int threshold = start.getDistance();
    vector<Move> moves(0);

    while(true) {
        pair<bool, int> iterationResult = search(start, threshold, 0, moves);
        if(iterationResult.first == true) {
            return;
        }
        threshold = iterationResult.second;
    }
}

void solve(vector<Number> data, vector<int> matrix) {
    bool zeroAtStart = (data[0].goal.x == 0 && data[0].goal.y == 0);
    
    if(!isSolvable(data, zeroAtStart)) {
        cout << -1 << endl;
        return;
    }
    Node start = Node(data, matrix);
    IDAStar(start);
}


int main() {
    pair<vector<Number>, vector<int>> data = input();


    // Започваме да измерваме времето
    auto start = std::chrono::high_resolution_clock::now();

    solve(data.first, data.second);
    

    // Край на измерването на времето
    auto end = std::chrono::high_resolution_clock::now();

    // // Изчисляване на времето за изпълнение в секунди
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << std::fixed << std::setprecision(2) << elapsed.count() << " seconds\n";

    return 0;
}