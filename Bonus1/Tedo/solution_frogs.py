from time import perf_counter


def timing_decorator(func):
    def wrapper(*args, **kwargs):
        start_time = perf_counter()
        result = func(*args, **kwargs)
        end_time = perf_counter()
        print(f"Execution time: {end_time - start_time:.6f} seconds")
        return result

    return wrapper


class JumpingFrogsPuzzle:
    def __init__(self, N):
        self.N = N
        self.board = self.generate_starting_board()
        self.board_history = [self.board.copy()]
        self.color = 1  # 1 for blue's turn, -1 for red's turn
        self.next_blue_idx = self.rightmost_blue = N - 1
        self.next_red_idx = self.leftmost_red = N + 1
        self.count_blue_placed_ok = self.count_red_placed_ok = 0

        self.symbol_map = {1: ">", 0: "_", -1: "<"}

    def generate_starting_board(self):
        return self.N * [1] + [0] + self.N * [-1]

    def stringify_board(self, board):
        return "".join(self.symbol_map[num] for num in board)

    def display_board_history(self):
        for board in self.board_history:
            print(self.stringify_board(board))

    def optimal_move_count(self):
        return self.N * (self.N + 2)

    def check_win(self):
        return all(i == -1 for i in self.board[: self.N]) and all(i == 1 for i in self.board[-self.N :])

    def search_to_the_left(self, curr_idx, color):
        result_idx = curr_idx - 1
        while result_idx >= 0 and self.board[result_idx] != color:
            result_idx -= 1
        return result_idx

    def search_to_the_right(self, curr_idx, color):
        result_idx = curr_idx + 1
        while result_idx < len(self.board) and self.board[result_idx] != color:
            result_idx += 1
        return result_idx

    def move_blue(self, curr_idx):
        if self.board[curr_idx + 1] == 0:
            new_position = curr_idx + 1
            if new_position == 2 * self.N - self.count_blue_placed_ok:
                self.next_blue_idx = self.search_to_the_left(curr_idx, 1)
            else:
                self.color = -1
                self.next_blue_idx = None
        else:
            new_position = curr_idx + 2
            self.next_blue_idx = self.search_to_the_left(curr_idx, 1)
            if self.next_blue_idx < 0:
                self.color = -1
                self.next_blue_idx = None

        self.board[curr_idx] = 0
        self.board[new_position] = 1
        self.rightmost_blue = max(new_position, self.rightmost_blue)

        if new_position == 2 * self.N - self.count_blue_placed_ok:
            self.count_blue_placed_ok += 1
            self.rightmost_blue = self.search_to_the_left(curr_idx, 1)

    def move_red(self, curr_idx):
        if self.board[curr_idx - 1] == 0:
            new_position = curr_idx - 1
            if new_position == 0 + self.count_red_placed_ok:
                self.next_red_idx = self.search_to_the_right(curr_idx, -1)
            else:
                self.color = 1
                self.next_red_idx = None
        else:
            new_position = curr_idx - 2
            self.next_red_idx = self.search_to_the_right(curr_idx, -1)
            if self.next_red_idx >= len(self.board):
                self.color = 1
                self.next_red_idx = None

        self.board[curr_idx] = 0
        self.board[new_position] = -1
        self.leftmost_red = min(new_position, self.leftmost_red)

        if new_position == 0 + self.count_red_placed_ok:
            self.count_red_placed_ok += 1
            self.leftmost_red = self.search_to_the_right(curr_idx, -1)

    # Uncomment the following line to see the execution time of the solve method
    @timing_decorator
    def solve(self):
        for _ in range(self.optimal_move_count()):
            if self.color == 1:
                self.move_blue(self.next_blue_idx)
                self.next_blue_idx = self.next_blue_idx if self.next_blue_idx is not None else self.rightmost_blue
            else:
                self.move_red(self.next_red_idx)
                self.next_red_idx = self.next_red_idx if self.next_red_idx is not None else self.leftmost_red

            self.board_history.append(self.board.copy())

    def play(self):
        self.solve()

        if self.check_win():
            # self.display_board_history()
            pass


def main():
    N = 100
    game = JumpingFrogsPuzzle(N)
    game.play()


if __name__ == "__main__":
    main()
