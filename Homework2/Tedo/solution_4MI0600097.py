import random
import time


class NQueensSolver:
    def __init__(self, n):
        self.n = n
        self.max_non_improving_steps = 300
        self.reset()

    def reset(self):
        self.queens = [random.randint(0, self.n - 1) for _ in range(self.n)]
        self.col_conflicts = [0] * self.n
        self.diag1_conflicts = [0] * (2 * self.n - 1)
        self.diag2_conflicts = [0] * (2 * self.n - 1)
        self.total_conflicts = 0
        self._initialize_conflicts()

    def _initialize_conflicts(self):
        for col in range(self.n):
            row = self.queens[col]
            self.col_conflicts[row] += 1
            self.diag1_conflicts[row + col] += 1
            self.diag2_conflicts[row - col + self.n - 1] += 1
            self.total_conflicts += self._count_conflicts(row, col)

    def _count_conflicts(self, row, col):
        return (
            self.col_conflicts[row]
            - 1
            + self.diag1_conflicts[row + col]
            - 1
            + self.diag2_conflicts[row - col + self.n - 1]
            - 1
        )

    def _move_conflicts(self, row, col):
        return self.col_conflicts[row] + self.diag1_conflicts[row + col] + self.diag2_conflicts[row - col + self.n - 1]

    def _move_queen(self, col, new_row):
        old_row = self.queens[col]
        self.col_conflicts[old_row] -= 1
        self.diag1_conflicts[old_row + col] -= 1
        self.diag2_conflicts[old_row - col + self.n - 1] -= 1
        self.total_conflicts -= self._count_conflicts(old_row, col)

        self.queens[col] = new_row
        self.total_conflicts += self._count_conflicts(new_row, col)
        self.col_conflicts[new_row] += 1
        self.diag1_conflicts[new_row + col] += 1
        self.diag2_conflicts[new_row - col + self.n - 1] += 1

    def solve(self, max_steps=10000000):
        non_improving_steps = 0
        for step in range(max_steps):
            if self.total_conflicts == 0:
                return True

            # Randomly select a conflicted column
            conflicted_cols = [col for col in range(self.n) if self._count_conflicts(self.queens[col], col) > 0]
            col = random.choice(conflicted_cols)

            current_row = self.queens[col]
            min_row = current_row

            # Occasionally choose a random row to escape loops/local minima
            if random.randint(0, 15) == 1:
                min_row = random.randint(0, self.n - 1)
            else:
                min_conflicts = self.total_conflicts
                row = random.randint(0, self.n - 1)
                for _ in range(self.n):
                    row = (row + 1) % self.n
                    conflicts = self._move_conflicts(row, col)
                    if conflicts < min_conflicts:
                        min_conflicts = conflicts
                        min_row = row

            if min_row == current_row:
                non_improving_steps += 1
            else:
                non_improving_steps = 0

            if non_improving_steps >= self.max_non_improving_steps:
                self.reset()
                non_improving_steps = 0

            self._move_queen(col, min_row)

        return False

    def print_board(self):
        for row in range(self.n):
            print(" ".join("*" if self.queens[col] == row else "_" for col in range(self.n)))


def main():
    N = int(input())
    solver = NQueensSolver(N)
    start_time = time.time()

    if N in (2, 3):
        print("-1")
        return

    if not solver.solve():
        print("-1")
        return

    if N <= 100:
        print(solver.queens)
        return

    exit_time = time.time() - start_time
    print(f"{exit_time:.2f}")


if __name__ == "__main__":
    main()
