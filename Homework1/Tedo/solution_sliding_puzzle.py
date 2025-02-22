import time
from heapq import heappush, heappop
from itertools import count


board_manhattan_cache = {}


def manhattan_distance(state, goal, rows):
    global board_manhattan_cache
    state_key = tuple(tuple(row) for row in state)
    if state_key in board_manhattan_cache:
        return board_manhattan_cache[state_key]

    distance = 0
    for i in range(rows):
        for j in range(rows):
            value = state[i][j]
            if value != 0:
                goal_x, goal_y = divmod(value - 1, rows)
                distance += abs(goal_x - i) + abs(goal_y - j)

    board_manhattan_cache[state_key] = distance
    return distance


def find_blank(state):
    for i, row in enumerate(state):
        for j, value in enumerate(row):
            if value == 0:
                return i, j


def is_solvable(state, rows):
    inversions = 0
    flat_state = [num for row in state for num in row if num != 0]
    for i in range(len(flat_state)):
        for j in range(i + 1, len(flat_state)):
            if flat_state[i] > flat_state[j]:
                inversions += 1
    if rows % 2 == 1:
        return inversions % 2 == 0
    blank_row = find_blank(state)[0]
    return (inversions + rows - blank_row) % 2 == 1


def generate_moves(state, blank_pos, rows):
    i, j = blank_pos
    moves = []
    directions = [(0, 1, "left"), (0, -1, "right"), (1, 0, "up"), (-1, 0, "down")]
    for di, dj, move in directions:
        ni, nj = i + di, j + dj
        if 0 <= ni < rows and 0 <= nj < rows:
            new_state = [row[:] for row in state]
            new_state[i][j], new_state[ni][nj] = new_state[ni][nj], new_state[i][j]
            moves.append((new_state, (ni, nj), move))
    return moves


def ida_star(initial_state, goal_state, rows):
    threshold = manhattan_distance(initial_state, goal_state, rows)
    blank_pos = find_blank(initial_state)
    path = []

    def search(state, blank_pos, g, threshold, parent_state):
        f = g + manhattan_distance(state, goal_state, rows)
        if f > threshold:
            return f
        if state == goal_state:
            return True
        min_threshold = float("inf")
        for new_state, new_blank_pos, move in generate_moves(state, blank_pos, rows):
            state_key = tuple(tuple(row) for row in new_state)
            if new_state == parent_state:
                continue
            path.append(move)
            result = search(new_state, new_blank_pos, g + 1, threshold, state)
            if result is True:
                return True
            if result < min_threshold:
                min_threshold = result
            path.pop()
        return min_threshold

    while True:
        result = search(initial_state, blank_pos, 0, threshold, None)
        if result is True:
            return len(path), path
        if result == float("inf"):
            return -1, []
        threshold = result


def generate_final_state(num_tiles, rows, blank_index):
    if blank_index == -1:
        blank_index = num_tiles

    goal_flat = list(range(1, rows * rows)) + [0]
    goal_flat.insert(blank_index, goal_flat.pop())
    goal_state = [goal_flat[i * rows : (i + 1) * rows] for i in range(rows)]

    return goal_state


def main():
    num_tiles = int(input())
    rows = int((num_tiles + 1) ** 0.5)
    blank_index = int(input())
    initial_state = [list(map(int, input().split())) for _ in range(rows)]
    goal_state = generate_final_state(num_tiles, rows, blank_index)

    start_time = time.time()

    if not is_solvable(initial_state, rows):
        print(-1)
        return

    length, steps = ida_star(initial_state, goal_state, rows)
    elapsed_time = time.time() - start_time

    print(length)
    for step in steps:
        print(step)


if __name__ == "__main__":
    main()
