def create_board():
    return [[0, 0, 0], [0, 0, 0], [0, 0, 0]]


def print_board(board):
    for row in board:
        print(row)
    print("--------")


def check_winner(board):
    for row in board:
        if row[0] == row[1] == row[2] and row[0] != 0:
            return row[0]  # 1 or -1 wins

    for i in range(3):
        if board[0][i] == board[1][i] == board[2][i] and board[0][i] != 0:
            return board[0][i]

    for i in (2, 0):
        if board[0][2 - i] == board[1][1] == board[2][i] and board[1][1] != 0:
            return board[1][1]

    for row in board:
        if 0 in row:
            return None  # No winner yet

    return 0  # draw


def get_possible_moves(board):
    possible_moves = []
    for i in range(3):
        for j in range(3):
            if board[i][j] == 0:
                possible_moves.append((i, j))
    return possible_moves


def make_move(board, player, move):
    board[move[0]][move[1]] = player


def reset_move(board, move):
    board[move[0]][move[1]] = 0


def is_move_valid(board, move):
    if move[0] < 0 or move[0] > 2 or move[1] < 0 or move[1] > 2:
        return False
    return board[move[0]][move[1]] == 0


def get_user_move(board):
    while True:
        move = input("Enter move (e.g. '1 1' to put in the center): ")
        move = tuple(map(int, move.split()))

        try:
            if is_move_valid(board, move):
                return move
        except:
            print("Error, Invalid move. Retry")


def choose_if_first():
    while True:
        first = input("Do you want to go first? (y/n): ")
        if first in ("y", "n"):
            return first == "y"
        else:
            print("Error, Retry")


def play_local_game():
    board = create_board()
    player = 1
    print_board(board)

    while True:
        move = get_user_move(board)
        make_move(board, player, move)
        print_board(board)

        winner = check_winner(board)
        if winner is not None:
            if winner == 0:
                print("Draw")
            else:
                print(f"Player {winner} wins!")
            break

        player = -player


def minimax(board, player, depth, alpha=-float("inf"), beta=float("inf")):
    winner = check_winner(board)
    if winner is not None:  # end state
        if winner == 1:
            return 10 - depth
        elif winner == -1:
            return depth - 10
        else:
            return 0

    if player == -1:
        min_score = float("inf")
        for move in get_possible_moves(board):
            make_move(board, player, move)
            score = minimax(board, -player, depth + 1, alpha, beta)
            reset_move(board, move)
            min_score = min(min_score, score)
            beta = min(beta, min_score)
            if beta <= alpha:
                break
        return min_score

    else:
        max_score = -float("inf")
        for move in get_possible_moves(board):
            make_move(board, player, move)
            score = minimax(board, -player, depth + 1, alpha, beta)
            reset_move(board, move)
            max_score = max(max_score, score)
            alpha = max(alpha, max_score)
            if beta <= alpha:
                break
        return max_score


def find_best_move(board, player):
    best_score = float("inf")
    best_move = None

    for move in get_possible_moves(board):
        make_move(board, player, move)
        score = minimax(board, -player, 0)
        reset_move(board, move)

        if score < best_score:
            best_score = score
            best_move = move

    return best_move


def play_game_vs_ai():
    board = create_board()
    is_player_first = choose_if_first()
    turn = 1 if is_player_first else -1  # -1 is bot always

    print_board(board)
    while True:
        if turn == 1:
            move = get_user_move(board)
        else:
            move = find_best_move(board, -1)

        make_move(board, turn, move)

        winner = check_winner(board)
        if winner is not None:
            if winner == 0:
                print("Draw :/")
            elif winner == 1:
                print(f"Player wins, Student loses!")
            else:
                print("AI wins unfortunately for humanity!")
            break

        turn = -turn
        print_board(board)

    print_board(board)


def main():
    play_game_vs_ai()


if __name__ == "__main__":
    main()
