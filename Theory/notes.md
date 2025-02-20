## **HW01: Search Algorithms**  

### **Key Concepts**
- **States, Actions, Goal Test, Path Cost**  
- **d** → Depth of the least-cost solution  
- **C** → Path cost of the least-cost solution  

### **Search Algorithms**
- **Uniform Cost Search (UCS)**  
  - Expands the least-cost unexpanded node (like Dijkstra’s algorithm)  
  - **Optimal and Complete**  

- **Depth-First Search (DFS)**  
  - Uses linear space  
  - **Not Complete**  

- **Breadth-First Search (BFS)**  
  - Uses a queue for the fringe  

- **Depth-Limited Search (DLS)**  
  - DFS with a depth limit (e.g., l=2)  
  - Stops and backtracks when the limit is reached  

- **Greedy Search**  
  - Uses **h(n)**, a heuristic that estimates closeness to the goal  
  - Can get stuck in local minima (**Not Complete**)  
  - Time and space complexity: **O(b^m)** (branching factor ^ max depth)  

- **A\* Search**  
  - Uses **f(n) = g(n) + h(n)**  
  - **Admissible heuristic**: h(n) ≤ true cost  
  - Based on **relaxed problems** (e.g., tile can move anywhere)  
  - **Complete** (except for infinite state spaces)  
  - **Optimal** with an admissible heuristic  
  - **High memory requirement** (worst case)  
  - Memory-bounded optimization available  

- **Iterative Deepening Search (IDS)**  
  - **Time Complexity**: O(b^d)  
  - **Space Complexity**: O(bd)  
  - **Not Optimal**  

### **Heuristics**
- **Hamming Distance** → Number of misplaced tiles  
- **Manhattan Distance** → Sum of tile distances to their correct positions  
- **Consistent Heuristic** → Never overestimates the actual step cost  
  - **h(start) > 0**  
  - **Consistency ⇒ Admissibility**  
- **Better heuristic** → Dominates others while minimizing drawbacks  

### **Other Methods**
- **Iterative Deepening A\* (IDA\*)** → **Optimal with linear space**  
- **Simulated Annealing** → Allows bad moves to escape local minima  
- **Heuristics** → Reduce the number of explored states  

---

## **HW03: Knapsack Problem**  

### **Local Search Algorithms**
- **Does not explore the entire state space**  
- **Simulated Annealing** → Allows bad solutions to escape local minima  
- **Beam Search** → Keeps the best **l=2** candidates, but **not complete or optimal**  
- **Hill Climbing** → Similar to beam search with **l=1**  

### **Genetic Algorithms (GA)**
- **Mimics evolution**:  
  - **Selection → Crossover → Mutation**  
- **Fitness Function**: Evaluates how good an individual is  
- **Stochastic Local Beam Search**: Includes randomness in the search  
- **Metaheuristic Approach**: Uses **fitness + selection** (inspired by natural selection)  

### **Selection Methods**
- **Roulette Wheel Selection (Fitness-Proportionate Selection)**:  
  - Calculate total fitness  
  - Assign probability to each individual  
  - Pick a random number and select the individual with the corresponding probability  

### **Crossover & Mutation**
- **Single-Point Crossover** → Selects a random split point and swaps genes  
- **Two-Point Crossover** → Uses two split points  
- **Uniform Crossover** → Randomly swaps genes  
- **Bit-Flip Mutation** → Each gene has a small probability (MUTATION_RATE) of flipping  
- **Insertion Mutation** → Adds a new gene  

### **Key Considerations**
- **Elitism** → Preserves the best individuals  
- **Mutation** → Helps escape local optima  

---

## **HW00: k-Nearest Neighbors (kNN)**  

### **Machine Learning Types**
- **Supervised Learning** → Classification & Regression  
- **Unsupervised Learning** → Clustering  
- **Global Learning** → Uses all instances (e.g., linear regression, Naïve Bayes)  
- **Local Learning** → Uses only some instances (e.g., kNN)  
- **Instance-Based Learning** → Uses the entire dataset (e.g., kNN)  
- **Model-Based Learning** → Creates a model from training data  
- **Lazy Learning** → Less training time, more time predicting  
- **Eager Learning** → Single hypothesis trained before predictions  

### **Key Concepts**
- **Linear Regression** → Best-fitting line for data points  
- **Gradient Descent** → Optimizes by taking small steps against the gradient  
- **Hyperparameters** → Learning rate, optimization algorithm (e.g., k in kNN, distance metric)  
- **Parameters** → Learned from data (e.g., weight & bias, **not used in kNN**)  
- **Euclidean Distance** → Common metric for kNN  
- **10-Fold Cross Validation** → Splits data into 10 groups, training on 9, testing on 1, then averaging results  
- **Data Split Ratios** → 70-20-10 or 80-20 (train-test split)  

### **Overfitting & Underfitting**
- **Overfitting** → k too small (e.g., k=1)  
- **Underfitting** → k too large (e.g., the entire dataset)  

### **Optimization**
- **KD-Tree** → Speeds up kNN by partitioning data using hyperrectangles  

---

## **HW05: Naïve Bayes**  

### **Bayes’ Theorem**
- **P(A | B) = P(A & B) / P(B)**  
- **P(A | B) = (P(B | A) * P(A)) / P(B)**  

### **Naïve Bayes**
- **P(Hypothesis | Data) = (P(Hypothesis) * P(Data | Hypothesis)) / P(Data)**  
- **Posterior = (Prior * Likelihood) / Evidence**  
- **Naïve assumption** → Features are independent given the class  

### **Key Issues**
- **Zero-Frequency Problem** → Use **Laplace Smoothing** (α / α * A, where α = 1)  
- **Logarithmic Smoothing** → Prevents underflow when multiplying many probabilities  
- **Overfitting** → Occurs when rare features have high probability  
- **Handling Missing Data** → Replace "?" with the mode of the column or treat as "unknown"  

---

## **HW06: Decision Trees**  

### **Entropy & Information Gain**
- **Entropy (H)** → Measures uncertainty in data  
- **Formula**: H(S) = -∑(p * log p)  
- **Information Gain**: **Best attribute = E(S) - Σ(|Sa| / |S| * E(Sa))**  

### **Bias vs. Variance**
- **Variance** → Spread of predictions  
- **Bias** → Deviation from true values  
- **Overfitting** → High variance  
- **Underfitting** → High bias  

### **Pruning**
- **Pre-Pruning** → Limits depth, minimum data, or minimum gain  
- **Post-Pruning** → Removes branches after training if they don’t improve performance  

### **Ensemble Methods**
- **Bagging** → Parallel training + majority voting  
- **Boosting** → Sequential training + higher weight on misclassified examples  

---

## **HW07: k-Means Clustering**  

### **Key Concepts**
- **Local Search Algorithm**  
- **May not always work well due to random initialization**  
- **Random Restarts** → Improves reliability by selecting the best outcome  
- **Always converges** but can stop early after N iterations  

### **Determining k**
- **Elbow Method** → Find the point where adding more clusters stops reducing WCSS significantly  
- **Silhouette Method** → Measures how well-separated clusters are  

### **Variants**
- **k-Modes** → Handles categorical data  
- **k-Means++** → Better initialization by selecting initial centroids far apart  
- **Soft k-Means** → Assigns probabilities to clusters instead of hard assignment  
- **Hierarchical k-Means** → Splits into binary clusters iteratively  

### **Distance Metrics**
- **Single Linkage** → Smallest distance between points  
- **Complete Linkage** → Largest distance between points  
- **Centroid Linkage** → Uses the mean of cluster points  
