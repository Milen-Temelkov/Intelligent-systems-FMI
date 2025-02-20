#include<iostream>
#include<chrono>
#include<iomanip>

using namespace std;

void fillPond(char* pond, int arrSize, int frogsCount) {
	
	for(int i = 0 ; i < frogsCount; i++) {
	    pond[i] = '>';
	}
	pond[frogsCount] = '_';
	
	for(int i = frogsCount + 1; i < arrSize; i++) {
	    pond[i] = '<';
	}
	
    return;   
}



void print(char* arr) {
    cout << arr << endl;
}



void move(char* arr, int frog, bool isLeft) {
    int nextFrog = isLeft ? frog + 1 : frog - 1;
    
    swap(arr[frog], arr[nextFrog]);
    
    print(arr); 
}



void jump(char* arr, int frog, bool isLeft) {
    int nextFrog = isLeft ? frog + 2 : frog - 2;
    
    swap(arr[frog], arr[nextFrog]);

    print(arr);  
}



bool canMove(char* arr, int arrSize, int frog, bool isLeft) {
    int nextFrog = isLeft ? frog + 1 : frog - 1;

    if(nextFrog >= 0 && nextFrog < arrSize) {
        return arr[nextFrog] == '_';
    }
    return false;
}



int findNextInLine(char* arr, int arrSize, int current, bool isLeft) {
    char lookFor = isLeft ? '>' : '<';

    while(current >= 0 && current < arrSize) {
        isLeft ? current-- : current++;

        if(arr[current] == lookFor) {
            return current;
        }
    }

    return -1; //move da stigne do tuk no rezultata she se ignorira
}

int findNewFurthest(char* arr, int arrSize, int current, bool isLeft) {
    char lookFor = isLeft ? '>' : '<';
    
    if(isLeft) {
        while(current < arrSize - 1) {
        
            current++;

            if(arr[current] == lookFor) {
                break;
            }
        }
        return current;
    }
    else {
        while(current > 0) {
        
            current--;

            if(arr[current] == lookFor) {
                break;
            }
        }
        return current;
    }
}

void doJumpMove(char* arr, int arrSize, int frogsCount, int furthestFrog, bool isLeft, bool& allJumped) {
    
    while(frogsCount > 0) {
        
        if(canMove(arr, arrSize, furthestFrog, isLeft)) {
            move(arr, furthestFrog, isLeft);
            return;
        }

        jump(arr, furthestFrog, isLeft);
        furthestFrog = findNextInLine(arr, arrSize, furthestFrog, isLeft);
        frogsCount--;
    }
    
    allJumped = true;
}

void doMoveJump(char* arr, int arrSize, int frogsCount, int furthestFrog, bool isLeft) {

    while(!canMove(arr, arrSize, furthestFrog, isLeft)) {
        furthestFrog = findNextInLine(arr, arrSize, furthestFrog, isLeft);
        frogsCount--;
    }

    move(arr, furthestFrog, isLeft);
    furthestFrog = findNextInLine(arr, arrSize, furthestFrog, isLeft);
    frogsCount--;

    while (frogsCount > 0) {
        jump(arr, furthestFrog, isLeft);
        furthestFrog = findNextInLine(arr, arrSize, furthestFrog, isLeft);
        frogsCount--;
    }
}

void solve(char* arr, int arrSize, int n) {
    print(arr);

    bool allJumped = false;
    bool isLeft = true;

    int furthestLeft = n - 1;
    int furthestRight = n + 1;

    while(!allJumped) {
        
        int furthest = isLeft ? furthestLeft : furthestRight;
        

        doJumpMove(arr, arrSize, n, furthest, isLeft, allJumped);

        if (isLeft) {
            furthestLeft = findNewFurthest(arr, arrSize, furthestLeft, isLeft);
        }
        else {
            furthestRight = findNewFurthest(arr, arrSize, furthestRight, isLeft);
        }

        isLeft = !isLeft; // aka flip value
    }

    while(arr[n] != '_') {
        
        int furthest = isLeft ? furthestLeft : furthestRight;
        
        doMoveJump(arr, arrSize, n, furthest, isLeft);

        if (isLeft) {
            furthestLeft = findNewFurthest(arr, arrSize, furthestLeft, isLeft);
        }
        else {
            furthestRight = findNewFurthest(arr, arrSize, furthestRight, isLeft);
        }

        isLeft = !isLeft; // aka flip value
    }
    
}

int main() {
    int n;
    cin >> n;
	const int arrSize = (2 * n) + 1;

	char* pond = new char[arrSize];
	fillPond(pond, arrSize, n);
    
    // time_t startTime;
    // time(&startTime);

    // Започваме да измерваме времето
    auto start = std::chrono::high_resolution_clock::now();

    solve(pond, arrSize, n);
    

    // Край на измерването на времето
    auto end = std::chrono::high_resolution_clock::now();

    // Изчисляване на времето за изпълнение в секунди
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << std::fixed << std::setprecision(2) << elapsed.count() << " seconds\n";
	return 0;
	
}
 