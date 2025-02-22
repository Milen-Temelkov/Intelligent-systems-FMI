# Intelligent Systems

## Summary

The repository contains a collection of algorithm and machine learning projects developed for the Intelligent Systems course. The projects range from search algorithms and puzzle solvers to optimization techniques, classifiers, clustering methods, and neural networks - organized by contributor.

## Homeworks Navigation

| Homework/Bonus | Milen                         | Tedo                         | Tom                         |
| -------------- | ----------------------------- | ---------------------------- | --------------------------- |
| **Bonus1**     | [solution](./Bonus1/Milen)    | [solution](./Bonus1/Tedo)    | [solution](./Bonus1/Tom)    |
| **Homework1**  | [solution](./Homework1/Milen) | [solution](./Homework1/Tedo) | [solution](./Homework1/Tom) |
| **Homework2**  | [solution](./Homework2/Milen) | [solution](./Homework2/Tedo) | [solution](./Homework2/Tom) |
| **Homework3**  | [solution](./Homework3/Milen) | [solution](./Homework3/Tedo) | [solution](./Homework3/Tom) |
| **Homework4**  | [solution](./Homework4/Milen) | [solution](./Homework4/Tedo) | [solution](./Homework4/Tom) |
| **Bonus2**     | -                             | [solution](./Bonus2/Tedo)    | [solution](./Bonus2/Tom)    |
| **Homework5**  | [solution](./Homework5/Milen) | [solution](./Homework5/Tedo) | [solution](./Homework5/Tom) |
| **Homework6**  | -                             | [solution](./Homework6/Tedo) | [solution](./Homework6/Tom) |
| **Homework7**  | [solution](./Homework7/Milen) | [solution](./Homework7/Tedo) | [solution](./Homework7/Tom) |
| **Homework8**  | [solution](./Homework8/Milen) | -                            | [solution](./Homework8/Tom) |

## Homeworks descriptions

### Bonus 1 – Uninformed Search (Frog Puzzle)
- **Algorithm**: Uses Depth-First Search (DFS) to explore game configurations where frogs swap positions according to defined move rules.  
- **Goal**: Display the entire solution path by outputting every intermediate configuration from the starting state to the goal state.


### Homework 1 – 8 Puzzle (IDA* with Manhattan)
- **Algorithm**: Uses IDA* (Iterative Deepening A*) with the Manhattan distance heuristic to solve the sliding tile puzzle optimally.  
- **Goal**: Find and output the optimal move sequence from the initial state to the goal configuration, or return –1 if unsolvable.


### Homework 2 – N-Queens Problem (MinConflicts)
- **Algorithm**: Uses the MinConflicts algorithm to place N queens on an NxN board so that no two queens threaten each other.  
- **Goal**: Display the board configuration, return –1 if unsolvable, and for large N, output only the time taken to solve.


### Homework 3 – Knapsack Problem (Genetic Algorithm)
- **Algorithm**: Implements a Genetic Algorithm to select items that maximize total value without exceeding a given weight capacity.  
- **Goal**: Output the best configuration’s value at various stages (initial, intermediate, and final generations) to illustrate the optimization process.


### Homework 4 – Tic-Tac-Toe (Min-Max with Alpha-Beta Pruning)
- **Algorithm**: Uses the Min-Max algorithm with alpha-beta pruning to determine optimal moves in a Tic-Tac-Toe game against an opponent.  
- **Goal**: Simulate a game by displaying the board state after each move—allowing the user to choose who starts—until a winner is declared.


### Bonus 2 – Naive Bayes Classifier (Congressional Voting Records)
- **Algorithm**: Implements a Naive Bayes classifier from scratch to classify congressional voting records into Democrats or Republicans, handling missing values either as a third category or via imputation, with Laplace smoothing and logarithmic probabilities to avoid zero probabilities.  
- **Goal**: Evaluate the classifier on an 80:20 stratified train-test split using 10-fold cross-validation, reporting training accuracy, average cross-validation accuracy (with standard deviation), and test set accuracy.


### Homework 5 – k-Nearest Neighbors (kNN) on Iris
- **Algorithm**: Implements the k-Nearest Neighbors algorithm from scratch—optionally using a kd-tree for efficiency—and applies data normalization (if necessary) on the Iris dataset.  
- **Goal**: Evaluate model performance by reporting the training set accuracy, the average and standard deviation from 10-fold cross-validation, and the test set accuracy for a user-specified k value.


### Homework 6 – Decision Tree (ID3 with Pruning) on Breast Cancer
- **Algorithm**: Implements the ID3 decision tree algorithm on the breast-cancer dataset, handling missing values and applying configurable pre-pruning (max depth, minimum samples, minimum information gain) and post-pruning (error estimation, chi-square test, or minimal cost-complexity) strategies.  
- **Goal**: Evaluate the model using an 80:20 stratified train-test split and 10-fold cross-validation, and report training accuracy, average cross-validation accuracy (with standard deviation), and test set accuracy.


### Homework 7 – kMeans Clustering 
- **Algorithm**: Implements kMeans clustering with both random restart and kMeans++ initialization, assessing cluster quality using the Within-Cluster Sum of Squares (WCSS) and an additional chosen metric (e.g., between-cluster distance).  
- **Goal**: Automatically cluster data from files such as "normal.txt" and "unbalance.txt" and output a color-coded plot of the clusters, comparing the performance of the different initialization strategies.


### Homework 8 – Neural Network for Boolean Functions
- **Algorithm**: Implements a neural network with configurable hidden layers and neurons, trained via error backpropagation using a selectable activation function (sigmoid or tanh) to solve boolean functions like AND, OR, and XOR.  
- **Goal**: For a given boolean function (or ALL), output the computed results for all input combinations, enabling experimentation with different network parameters and comparisons of performance.
