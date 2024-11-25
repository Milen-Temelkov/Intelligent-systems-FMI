#include<iostream>
#include<vector>
#include<random>
#include<algorithm>

using namespace std;

struct Item {
    int weight = 0;
    int value = 0;

    void print() const {
        cout << "weight: " << weight << " value: " << value << endl;
    }
};

struct Chromosome {
    vector<bool> itemsIncluded;
    int fitness = 0;
    int weight = 0;

    Chromosome() = default;

    Chromosome(int maxWeight, const vector<Item>& items, const vector<bool> itemsToInclude) : itemsIncluded(itemsToInclude) {

        for (int i = 0; i < items.size(); i++) {
            if (itemsIncluded[i]) {
                fitness += items[i].value;
                weight += items[i].weight;
            }

            if (weight > maxWeight) {
                fitness = 0;
                break;
            }
        }
    }

    bool invert(int maxWeight, const vector<Item>& items, int item) {
        itemsIncluded[item] = !itemsIncluded[item];

        if (itemsIncluded[item]) {
            fitness += items[item].value;
            weight += items[item].weight;

            fitness = weight > maxWeight ? 0 : fitness;
        } else {
            fitness -= items[item].value;
            weight -= items[item].weight;
        }

        return fitness;
    }
};

vector<Item> input() {
    int maxWeight, itemsCount, itemWeight, itemValue;
    cin >> maxWeight >> itemsCount;
    vector<Item> items(itemsCount);
    for (int i = 0; i < itemsCount; i++) {
        cin >> itemWeight >> itemValue;
        items[i] = Item( {itemWeight, itemValue } );
    }

    return items;
}

void print(const vector<Item>& items) {
    for (Item item : items) {
        item.print();
    }
}

bool compareChromosomesFitness(const Chromosome& lhs, const Chromosome& rhs) {
    return lhs.fitness > rhs.fitness; 
}

Chromosome generateRandomChromosome(int maxWeight, const vector<Item>& items) {
    vector<bool> itemsIncluded(items.size(), 0);
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dist(0, items.size() - 1);
    int currWeight = 0;

    while (true) {
        int index = dist(gen);
        if (itemsIncluded[index] != 1 && items[index].weight + currWeight > maxWeight) {
            break;
        }

        if (itemsIncluded[index] != 1) {
            itemsIncluded[index] = 1;
            currWeight += items[index].weight;
        }
    }

    return Chromosome(maxWeight, items, itemsIncluded);
}


vector<Chromosome> buildRandomPopulation(int maxWeight, const vector<Item>& items ,int populationSize) {
    vector<Chromosome> population(populationSize);
    for (int i = 0; i < populationSize; i++) {
        population[i] = generateRandomChromosome(maxWeight, items);
    }

    sort(population.begin(), population.end(), compareChromosomesFitness);

    return population;
}


Chromosome crossbreed(int maxWeight, const vector<Item>& items, const Chromosome& parent1, const Chromosome& parent2) { //mnogo politkorektna funkciq

    vector<bool> childItems(items.size(), 0);
    int currWeight = 0;

    for (int i = 0; i < items.size(); i++) {

        childItems[i] = (rand() % 2) ? parent1.itemsIncluded[i] : parent2.itemsIncluded[i];

        currWeight += childItems[i] ? items[i].weight : 0;
        
        if (currWeight > maxWeight) {
            currWeight -= items[i].weight;
            childItems[i] = 0;
            break;
        }

    }
    return Chromosome(maxWeight, items, childItems);
}

vector<Chromosome> makeCrossoverOfPopulation(int maxWeight, const vector<Item>& items, const vector<Chromosome>& population) {
    vector<Chromosome> newPopulation(population.size());
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, population.size() - 1);
    
    for (int i = 0; i < population.size(); i++) {
        const Chromosome& parent1 = population[dist(gen)];
        const Chromosome& parent2 = population[dist(gen)];
    
        newPopulation[i] = crossbreed(maxWeight, items, parent1, parent2);
    }

    sort(newPopulation.begin(), newPopulation.end(), compareChromosomesFitness);

    return newPopulation;
}

vector<Chromosome> selectivePurge(const vector<Chromosome>& randomPopulation, const vector<Chromosome>& parentPopulation, const vector<Chromosome>& breededPopulation) {
    vector<Chromosome> resultPopulation(parentPopulation.size());
    
    int parentIndex = 0, breededIndex = 0;

    for (int i = 0; i < parentPopulation.size(); i++) {
        resultPopulation[i] = parentPopulation[parentIndex].fitness > breededPopulation[breededIndex].fitness ? parentPopulation[parentIndex++] : breededPopulation[breededIndex++];
    }

    sort(resultPopulation.begin(), resultPopulation.end(), compareChromosomesFitness);

    return resultPopulation;
}

void mutate(int maxWeight, const vector<Item>& items, vector<Chromosome>& population, int fromWhere) {
    for (int i = fromWhere; i < population.size(); i++) {
        for (int j = 0; j < population[i].itemsIncluded.size(); j++) {
            if (!(rand() % 100)) {
                if (!population[i].invert(maxWeight, items, j)) {
                    population[i].invert(maxWeight, items, j);
                }
            }
        }
    }
}

void solveKnapsack(int maxWeight, const vector<Item>& items, int generations, int populationSize) {
    vector<Chromosome> population = buildRandomPopulation(maxWeight, items, populationSize);

    for (int generation = 0; generation < generations; generation++) {
        
        if (!(generation % 8)) {
            cout << "Generation " << generation + 1 << ": Best fitness = " << population[0].fitness << endl;
        }

        vector<Chromosome> breededPopulation = makeCrossoverOfPopulation(maxWeight, items, population);
        vector<Chromosome> randomPopulation = buildRandomPopulation(maxWeight, items, populationSize);

        population = selectivePurge(randomPopulation, population, breededPopulation);

        mutate(maxWeight, items, population, (population.size() / 10));
    }
}

int main() {

    int maxWeight, itemsCount, itemWeight, itemValue;
    cin >> maxWeight >> itemsCount;
    vector<Item> items(itemsCount);
    for (int i = 0; i < itemsCount; i++) {
        cin >> itemWeight >> itemValue;
        items[i] = Item( {itemWeight, itemValue } );
    }

    int generations = itemsCount * 2;
    int individuals = itemsCount;
    solveKnapsack(maxWeight, items, generations, individuals);

    return 0;
}