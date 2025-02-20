import random
import os

FROM_FILE = True
INPUT_FILE = "inputs/long.txt"
POPULATION_SIZE = 1000
GENERATIONS = 500
MUTATION_RATE = 0.02
ELITISM = 20


def read_input():
    if FROM_FILE:
        full_path = os.path.join(os.path.dirname(__file__), INPUT_FILE)
        with open(full_path, "r") as file:
            lines = file.readlines()
            capacity, num_items = map(int, lines[0].split())
            items = [tuple(map(int, line.split())) for line in lines[1:]]
    else:
        capacity, num_items = map(int, input().split())
        items = [tuple(map(int, input().split())) for _ in range(num_items)]
    return capacity, items


def generate_population(size, items, capacity):
    population = []
    num_items = len(items)
    while len(population) < size:
        chromosome = [1] + [0 for _ in range(num_items - 1)]
        if is_valid_solution(chromosome, items, capacity):
            population.append(chromosome)
    return population


def is_valid_solution(chromosome, items, capacity):
    total_weight = sum(gene * weight for gene, (weight, _) in zip(chromosome, items))
    return total_weight <= capacity


def evaluate_fitness(chromosome, items, capacity):
    total_weight, total_value = 0, 0
    for gene, (weight, value) in zip(chromosome, items):
        if gene:
            total_weight += weight
            total_value += value
        if total_weight > capacity:
            return 0
    return total_value


def select(population, fitness_scores):
    total_fitness = sum(fitness_scores)
    if total_fitness == 0:
        return random.choice(population)
    pick = random.uniform(0, total_fitness)
    current = 0
    for individual, score in zip(population, fitness_scores):
        current += score
        if current >= pick:
            return individual


def crossover(parent1, parent2):
    point = random.randint(1, len(parent1) - 1)
    return (parent1[:point] + parent2[point:], parent2[:point] + parent1[point:])


def mutate(chromosome):
    return [1 - gene if random.random() < MUTATION_RATE else gene for gene in chromosome]


def genetic_algorithm(capacity, items):
    num_items = len(items)
    population = generate_population(POPULATION_SIZE, items, capacity)
    best_solution, best_fitness = None, 0

    for generation in range(GENERATIONS):
        fitness_scores = [evaluate_fitness(ind, items, capacity) for ind in population]

        max_fitness = max(fitness_scores)
        if max_fitness > best_fitness:
            best_fitness = max_fitness
            best_solution = population[fitness_scores.index(max_fitness)]

        if generation == 0 or generation == GENERATIONS - 1 or generation % (GENERATIONS // 10) == 0:
            print(f"Generation {generation + 1}: Best Value = {best_fitness}")

        next_generation = sorted(zip(population, fitness_scores), key=lambda x: x[1], reverse=True)[:ELITISM]
        next_population = [ind for ind, _ in next_generation]

        while len(next_population) < POPULATION_SIZE:
            parent1 = select(population, fitness_scores)
            parent2 = select(population, fitness_scores)
            child1, child2 = crossover(parent1, parent2)
            if is_valid_solution(child1, items, capacity):
                next_population.append(mutate(child1))
            if len(next_population) < POPULATION_SIZE and is_valid_solution(child2, items, capacity):
                next_population.append(mutate(child2))

        population = next_population

    return best_solution, best_fitness


if __name__ == "__main__":
    M, items = read_input()
    best_solution, best_fitness = genetic_algorithm(M, items)
    print("\nOptimal Solution:")
    print(f"Items Selected: {best_solution}")
    print(f"Maximum Value: {best_fitness}")  # Best is 1130 for the small one, 5119 for the long one
